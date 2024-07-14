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
        sResetRaidCooldowns->doResetArenaSpells = sConfigMgr->GetOption<bool>("ModResetRaidCooldowns.DoResetArenaSpells", false);
        sResetRaidCooldowns->doResetPetCooldowns = sConfigMgr->GetOption<bool>("ModResetRaidCooldowns.DoResetPetCooldowns", false);
        sResetRaidCooldowns->combatTimeRequiredInSeconds = sConfigMgr->GetOption<uint32>("ModResetRaidCooldowns.CombatTimeRequiredInSeconds", 30);
        sResetRaidCooldowns->LoadSpellsSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.Spells", ""));
        sResetRaidCooldowns->LoadCategoriesSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.Categories", ""));
        sResetRaidCooldowns->LoadMapIdEnableSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.MapIdEnableSettings", ""));
        sResetRaidCooldowns->LoadMapIdBossIdDisableSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.MapIdBossIdDisableSettings", ""));
    }
};

class global_reset_raid_cooldowns : public GlobalScript
{
public:
    global_reset_raid_cooldowns() : GlobalScript("global_reset_raid_cooldowns") { }

    void OnBeforeSetBossState(uint32 bossId, EncounterState newState, EncounterState oldState, Map* instance) override
    {
        if (!sResetRaidCooldowns->isEnabled || (oldState == newState) || !instance->GetInstanceId())
        {
            return;
        }
        uint32 mapId = instance->GetId();
        uint32 instanceId = instance->GetInstanceId();
        if (!sResetRaidCooldowns->IsMapBossEnabled(mapId, bossId))
        {
            return;
        }
        LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: {} ({}-{}) id: {} old: {} new: {}", instance->GetMapName(), mapId, std::to_string(instanceId), bossId, oldState, newState);
        if (newState == IN_PROGRESS)
        {
            sResetRaidCooldowns->SetCombatStarted(mapId, bossId);
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: store pair {} ({}-{}) pair: {}-{}", instance->GetMapName(), mapId, std::to_string(instanceId), std::to_string(instanceId), bossId);
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
            if (GetMSTimeDiffToNow(combatStartedTime) >= (sResetRaidCooldowns->combatTimeRequiredInSeconds * IN_MILLISECONDS))
            {
                hasRequiredTimePassed = true;
            }
        }
        if (!hasRequiredTimePassed)
        {
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: Not enough time has passed!");
            return;
        }
        instance->DoForAllPlayers([&](Player* player)
        {
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::DoForAllPlayers: {}", player->GetName());
            if (sResetRaidCooldowns->doResetArenaSpells)
            {
                // Remove cooldowns on spells that have less than 10 minutes of cooldown from the Player
                player->RemoveArenaSpellCooldowns(false); // no reset pet cooldowns
            }
            for (auto const& spellId : sResetRaidCooldowns->spells)
            {
                player->RemoveSpellCooldown(spellId, true);
            }
            for (auto const& categoryId : sResetRaidCooldowns->categories)
            {
                player->RemoveSpellCooldown(categoryId, true);
            }
            // Remove Exhaustion and Sated from player
            player->RemoveAura(SPELL_EXHAUSTION);
            player->RemoveAura(SPELL_SATED);
            if (sResetRaidCooldowns->doResetPetCooldowns)
            {
                if (Pet* pet = player->GetPet())
                {
                    LOG_DEBUG("module", "mod-reset-raid-cooldowns::DoForAllPlayers::Pet: {}", pet->GetName());
                    // Remove pet cooldowns
                    for (CreatureSpellCooldowns::const_iterator itr2 = pet->m_CreatureSpellCooldowns.begin(); itr2 != pet->m_CreatureSpellCooldowns.end(); ++itr2)
                        player->SendClearCooldown(itr2->first, pet);
                    pet->m_CreatureSpellCooldowns.clear();
                    // Remove Exhaustion and Sated from pet
                    player->RemoveAura(SPELL_EXHAUSTION);
                    player->RemoveAura(SPELL_SATED);
                }
            }
        });
    }
};

void AddSC_reset_raid_cooldowns()
{
    new global_reset_raid_cooldowns();
    new world_reset_raid_cooldowns();
}
