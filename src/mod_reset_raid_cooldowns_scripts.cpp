/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "reset_raid_cooldowns.h"

class world_reset_raid_cooldowns : public WorldScript
{
public:
    world_reset_raid_cooldowns() : WorldScript("world_reset_raid_cooldowns") { }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        sResetRaidCooldowns->isEnabled = sConfigMgr->GetOption<bool>("ModResetRaidCooldowns.Enable", false);
        sResetRaidCooldowns->combatTimeRequiredInSeconds = sConfigMgr->GetOption<uint32>("ModResetRaidCooldowns.CombatTimeRequiredInSeconds", 30);
        sResetRaidCooldowns->LoadMapIdEnableSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.MapIdEnableSettings", ""));
        sResetRaidCooldowns->LoadMapIdBossIdDisableSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.MapIdBossIdDisableSettings", ""));
    }

    // void OnStartup() override
    // {
    // }
};

class global_reset_raid_cooldowns : public GlobalScript
{
public:
    global_reset_raid_cooldowns() : GlobalScript("global_reset_raid_cooldowns") { }

    void OnBeforeSetBossState(uint32 bossId, EncounterState newState, EncounterState oldState, Map* instance) override
    {
        if (!sResetRaidCooldowns->IsEnabled || (oldState == newState) || !instance->GetInstanceId())
        {
            return;
        }
        uint32 mapId = instance->GetId();
        uint32 instanceId = instance->GetInstanceId();
        if (!sResetRaidCooldowns->IsMapBossEnabled(mapId, bossId))
        {
            return;
        }
        LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: {} ({}-{}) id: {} old: {} new: {}", instance->GetMapName(), mapId, std::to_string(instanceId), bossId, oldState, newState);
        if (newState == IN_PROGRESS)
        {
            sResetRaidCooldowns->SetCombatStarted(mapId, bossId);
            LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: store pair {} ({}-{}) pair: {}-{}", instance->GetMapName(), mapId, std::to_string(instanceId), std::to_string(instanceId), bossId);
            return;
        }
        bool isAllowedStateChange = ((oldState == IN_PROGRESS) && (newState == DONE || newState == FAIL || newState == NOT_STARTED));
        if (!isAllowedStateChange)
        {
            return;
        }
        bool hasRequiredTimePassed = false;
        if (uint32 combatStartedTime = sResetRaidCooldowns->GetCombatStartedTime(instanceId, bossId))
        {
            if (GetMSTimeDiffToNow(combatStartedTime) >= (sResetRaidCooldowns->CombatTimeRequiredInSeconds * IN_MILLISECONDS))
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

void AddSC_reset_raid_cooldowns()
{
    new global_reset_raid_cooldowns();
    new world_reset_raid_cooldowns();
}
