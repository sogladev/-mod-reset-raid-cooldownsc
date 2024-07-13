/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "Pet.h"
#include "Player.h"
#include "Config.h"
#include "ScriptMgr.h"


struct InstanceIdBossIdKey
{
    uint32 InstanceId;
    uint32 id;
    InstanceIdBossIdKey(uint32 instanceId, uint32 id) : InstanceId(instanceId), id(id) {}
    // Overload the less-than operator for use in std::map
    bool operator<(const InstanceIdBossIdKey& other) const
    {
        return std::tie(InstanceId, id) < std::tie(other.InstanceId, other.id);
    }
};

std::map<InstanceIdBossIdKey, uint32> instanceIdBossIdCombatStartedTimeMap;

void SetCombatStartedTime(uint32 instanceId, uint32 id, uint32 currTime)
{
    InstanceIdBossIdKey key(instanceId, id);
    instanceIdBossIdCombatStartedTimeMap[key] = currTime;
}

uint32 GetCombatStartedTime(uint32 instanceId, uint32 id)
{
    InstanceIdBossIdKey key(instanceId, id);
    auto it = instanceIdBossIdCombatStartedTimeMap.find(key);
    if (it != instanceIdBossIdCombatStartedTimeMap.end())
    {
        return it->second;
    }
    return 0;
}

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
            // unique key: InstanceId, id
            uint32 currTime = getMSTime()
            SetCombatStartedTime(instance->GetId(), id, currTime);
            LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: store pair {} ({}-{}) pair: {}-{} value: {}",
                instance->GetMapName(),
                instance->GetId(),
                std::to_string(instance->GetInstanceId()),
                std::to_string(instance->GetInstanceId()),
                id,
                currTime
            );
            return;
        }
        bool isAllowedStateChange = oldState == IN_PROGRESS && (newState == DONE || newState == FAIL || newState == NOT_STARTED);
        if (!isAllowedStateChange)
        {
            return;
        }
        bool hasRequiredTimePassed = false;
        if (uint32 combatStartedTime = GetCombatStartedTime(instance->GetId(), id))
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
};

void AddSC_reset_raid_cooldowns_spell_script()
{
    new global_reset_raid_cooldowns();
}
