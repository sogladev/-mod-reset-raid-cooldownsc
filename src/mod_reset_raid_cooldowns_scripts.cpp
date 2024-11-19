/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "Config.h"
#include "CreatureAI.h"
#include "reset_raid_cooldowns.h"
#include "reset_raid_cooldowns_entries.h"

class reset_raid_cooldowns_worldscript : public WorldScript
{
public:
    reset_raid_cooldowns_worldscript() : WorldScript("reset_raid_cooldowns_worldscript") { }

    void OnAfterConfigLoad(bool /*reload*/) override
    {
        sResetRaidCooldowns->isEnabled = sConfigMgr->GetOption<bool>("ModResetRaidCooldowns.Enable", true);
        sResetRaidCooldowns->isEnabledForHeroics = sConfigMgr->GetOption<bool>("ModResetRaidCooldowns.EnableForHeroics", false);
        sResetRaidCooldowns->doResetArenaSpells = sConfigMgr->GetOption<bool>("ModResetRaidCooldowns.DoResetArenaSpells", true);
        sResetRaidCooldowns->doResetPetCooldowns = sConfigMgr->GetOption<bool>("ModResetRaidCooldowns.DoResetPetCooldowns", false);
        sResetRaidCooldowns->combatTimeRequiredInSeconds = sConfigMgr->GetOption<uint32>("ModResetRaidCooldowns.CombatTimeRequiredInSeconds", 30);
        sResetRaidCooldowns->LoadSpellsSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.Spells", "42650, 2062, 2894, 1122"));
        sResetRaidCooldowns->LoadCategoriesSettings(sConfigMgr->GetOption<std::string>("ModResetRaidCooldowns.Categories", "26"));
    }
};

class reset_raid_cooldowns_globalscript : public GlobalScript
{
public:
    reset_raid_cooldowns_globalscript() : GlobalScript("reset_raid_cooldowns_globalscript") { }

    void OnAfterUpdateEncounterState(Map* map, EncounterCreditType /*type*/, uint32 creditEntry, Unit* /*source*/, Difficulty /*difficulty_fixed*/, DungeonEncounterList const* /*encounters*/, uint32 /*dungeonCompleted*/, bool /*updated*/) override
    {
        if (!sResetRaidCooldowns->isEnabled)
            return;

        uint32 mapId = map->GetId();

        if (ModResetRaidCooldowns::IsDeniedForCreditEntry(creditEntry))
            return;

        if (map->IsHeroic() && map->IsNonRaidDungeon())
        {
            if (!sResetRaidCooldowns->isEnabledForHeroics)
                return;
            sResetRaidCooldowns->DoResetRaidCooldowns(map);
            LOG_INFO("module", "mod-reset-raid-cooldowns::OnAfterUpdateEncounterState: Heroic Dungeon Reset {} ({}): creditEntry {}", map->GetMapName(), mapId, creditEntry);
        }
        else if (map->IsRaid())
        {
            LOG_INFO("module", "mod-reset-raid-cooldowns::OnAfterUpdateEncounterState: Raid Reset {} ({}): creditEntry {}", map->GetMapName(), mapId, creditEntry);
            sResetRaidCooldowns->DoResetRaidCooldowns(map);
        }
    }

    void OnBeforeSetBossState(uint32 bossId, EncounterState newState, EncounterState oldState, Map* instanceMap) override
    {
        if (!sResetRaidCooldowns->isEnabled || (oldState == newState) || !instanceMap->GetInstanceId())
            return;

        uint32 mapId = instanceMap->GetId();
        uint32 instanceId = instanceMap->GetInstanceId();

        LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: {} ({}-{}) id: {} old: {} new: {}", instanceMap->GetMapName(), mapId, std::to_string(instanceId), bossId, oldState, newState);

        if (newState == IN_PROGRESS)
        {
            sResetRaidCooldowns->SetCombatStarted(instanceId, bossId);
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: store pair {} ({}-{}) pair: {}-{}", instanceMap->GetMapName(), mapId, std::to_string(instanceId), std::to_string(instanceId), bossId);
            return;
        }

        // newState == DONE is handled with OnAfterUpdateEncounterState
        bool isAllowedStateChange = ((oldState == IN_PROGRESS) && (newState == FAIL || newState == NOT_STARTED));
        if (!isAllowedStateChange)
            return;

        if (!sResetRaidCooldowns->HasEnoughTimePassed(instanceId, bossId))
        {
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: Not enough time has passed!");
            return;
        }

        sResetRaidCooldowns->DoResetRaidCooldowns(instanceMap);
        LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: Raid Reset {} ({}-{}) pair: {}-{}", instanceMap->GetMapName(), mapId, std::to_string(instanceId), std::to_string(instanceId), bossId);
    }
};

class reset_raid_cooldowns_unitscript : public UnitScript
{
public:
    reset_raid_cooldowns_unitscript() : UnitScript("reset_raid_cooldowns_unitscript") { }

    void OnUnitEnterCombat(Unit* unit, Unit* /*victim*/) override
    {
        if (!sResetRaidCooldowns->isEnabled)
            return;

        if (!ModResetRaidCooldowns::IsEnabledForCreatureEntry(unit->GetEntry()))
            return;

        sResetRaidCooldowns->SetCombatStarted(unit->GetGUID());
    }

    void OnUnitEnterEvadeMode(Unit* unit, uint8 evadeReason) override
    {
        if (!sResetRaidCooldowns->isEnabled)
            return;

        // Avoid resetting on evade for some evadeReasons to prevent abuse
        // EVADE_REASON_SEQUENCE_BREAK,    // this is a boss and the pre-requisite encounters for engaging it are not defeated yet
        // EVADE_REASON_NO_PATH,           // the creature was unable to reach its target for over 5 seconds
        if (evadeReason == CreatureAI::EVADE_REASON_BOUNDARY || evadeReason == CreatureAI::EVADE_REASON_NO_PATH)
            return;

        if (!ModResetRaidCooldowns::IsEnabledForCreatureEntry(unit->GetEntry()))
            return;

        if (!sResetRaidCooldowns->HasEnoughTimePassed(unit->GetGUID()))
        {
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnUnitEnterEvadeMode: Not enough time has passed!");
            return;
        }

        sResetRaidCooldowns->DoResetRaidCooldowns(unit->GetMap());
        LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnUnitEnterEvadeMode: Raid Reset");
    }
};

void AddSC_reset_raid_cooldowns()
{
    new reset_raid_cooldowns_globalscript();
    new reset_raid_cooldowns_worldscript();
    new reset_raid_cooldowns_unitscript();
}
