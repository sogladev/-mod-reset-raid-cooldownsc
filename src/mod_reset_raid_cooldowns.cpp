/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "Pet.h"
#include "Player.h"
#include "Config.h"
#include "ScriptMgr.h"

class InstanceCombatStartedTimeManager
{
public:
    void SetCombatStarted(uint32 instanceId, uint32 id)
    {
        _InstanceIdBossIdKey key(instanceId, id);
        _instanceIdBossIdCombatStartedTimeMap[key] = getMSTime();
    }

    uint32 GetCombatStartedTime(uint32 instanceId, uint32 id) const
    {
        _InstanceIdBossIdKey key(instanceId, id);
        auto it = _instanceIdBossIdCombatStartedTimeMap.find(key);
        if (it != _instanceIdBossIdCombatStartedTimeMap.end())
        {
            return it->second;
        }
        return 0;
    }

private:
    struct _InstanceIdBossIdKey
    {
        uint32 InstanceId;
        uint32 id;
        _InstanceIdBossIdKey(uint32 instanceId, uint32 id) : InstanceId(instanceId), id(id) {}
        bool operator<(const _InstanceIdBossIdKey& other) const
        {
            return std::tie(InstanceId, id) < std::tie(other.InstanceId, other.id);
        }
    };
    std::map<_InstanceIdBossIdKey, uint32> _instanceIdBossIdCombatStartedTimeMap;
};

class global_reset_raid_cooldowns : public GlobalScript
{
public:
    global_reset_raid_cooldowns() : GlobalScript("global_reset_raid_cooldowns") { }

    void OnBeforeSetBossState(uint32 id, EncounterState newState, EncounterState oldState, Map* instance) override
    {
        if (oldState == newState)
        {
            return;
        }
        if (!instance->GetInstanceId())
        {
            return;
        }
        LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: {} ({}-{}) id: {} old: {} new: {}",
            instance->GetMapName(),
            instance->GetId(),
            std::to_string(instance->GetInstanceId()),
            id, oldState, newState);
        if (newState == IN_PROGRESS)
        {
            _timeManager.SetCombatStarted(instance->GetId(), id); // unique key: InstanceId, id
            LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: store pair {} ({}-{}) pair: {}-{}",
                instance->GetMapName(),
                instance->GetId(),
                std::to_string(instance->GetInstanceId()),
                std::to_string(instance->GetInstanceId()),
                id
            );
            return;
        }
        bool isAllowedStateChange = oldState == IN_PROGRESS && (newState == DONE || newState == FAIL || newState == NOT_STARTED);
        if (!isAllowedStateChange)
        {
            return;
        }
        bool hasRequiredTimePassed = false;
        if (uint32 combatStartedTime = _timeManager.GetCombatStartedTime(instance->GetId(), id)) // unique key: InstanceId, id
        {
            if (GetMSTimeDiffToNow(combatStartedTime) >= (sConfigMgr->GetOption<uint32>("ResetRaidCooldowns.CombatTimeRequired", 30) * IN_MILLISECONDS))
            {
                hasRequiredTimePassed = true;
            }
        }
        if (!hasRequiredTimePassed)
        {
            LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: Not enough time has passed!");
            return;
        }
        instance->DoForAllPlayers([&](Player* player)
        {
            LOG_INFO("module", "mod-reset-raid-cooldowns::DoForAllPlayers: {}", player->GetName());
            // Remove cooldowns on spells that have less than 10 minutes of cooldown from the Player
            player->RemoveArenaSpellCooldowns(true); // includes pets
            // Remove cooldowns that were not included in the above
            player->RemoveCategoryCooldown(26); // rebirth
            player->RemoveSpellCooldown(42650, true); // army of the dead
            player->RemoveSpellCooldown(2062, true); // earth elemental totem
            player->RemoveSpellCooldown(2894, true); // fire elemental totem
            player->RemoveSpellCooldown(1122, true); // inferno
            // player->RemoveSpellCooldown(48788, true); // lay on hands
            // Remove Exhaustion and Sated from player
            player->RemoveAura(57723); // Exhaustion
            player->RemoveAura(57724); // Sated
            // Remove Exhaustion and Sated from pet
           if (Pet* pet = player->GetPet())
           {
                LOG_INFO("module", "mod-reset-raid-cooldowns::DoForAllPlayers::Pet: {}", pet->GetName());
                pet->RemoveAura(57723); // Exhaustion
                pet->RemoveAura(57724); // Sated
           }
        });
    }

private:
    InstanceCombatStartedTimeManager _timeManager;
};

void AddSC_reset_raid_cooldowns_spell_script()
{
    new global_reset_raid_cooldowns();
}
