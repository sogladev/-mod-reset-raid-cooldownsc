/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "reset_raid_cooldowns.h"

class reset_raid_cooldowns_worldscript : public WorldScript
{
public:
    reset_raid_cooldowns_worldscript() : WorldScript("reset_raid_cooldowns_worldscript") { }

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

class reset_raid_cooldowns_globalscript : public GlobalScript
{
public:
    reset_raid_cooldowns_globalscript() : GlobalScript("reset_raid_cooldowns_globalscript") { }

    void OnAfterUpdateEncounterState(Map* map, EncounterCreditType /*type*/, uint32 /*creditEntry*/, Unit* source, Difficulty /*difficulty_fixed*/, DungeonEncounterList const* /*encounters*/, uint32 /*dungeonCompleted*/, bool /*updated*/) override
    {
        if (!sResetRaidCooldowns->isEnabled || !source)
            return;

        uint32 mapId = map->GetId();
        if (!sResetRaidCooldowns->IsMapEnabled(mapId))
            return;

        LOG_INFO("module", "mod-reset-raid-cooldowns::OnAfterUpdateEncounterState: Map enabled. Checking for source: {}", source->GetEntry());

        // NYI: check for source entries

        if (map->IsHeroic() && map->IsNonRaidDungeon())
        {
            // NYI: enable config bool for heroic
        }
        else if (map->IsRaid())
        {
            sResetRaidCooldowns->DoResetRaidCooldowns(map);
        }
    }

    void OnBeforeSetBossState(uint32 bossId, EncounterState newState, EncounterState oldState, Map* instance) override
    {
        if (!sResetRaidCooldowns->isEnabled || (oldState == newState) || !instance->GetInstanceId())
            return;

        uint32 mapId = instance->GetId();
        uint32 instanceId = instance->GetInstanceId();
        if (!sResetRaidCooldowns->IsMapBossEnabled(mapId, bossId))
            return;

        LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: {} ({}-{}) id: {} old: {} new: {}", instance->GetMapName(), mapId, std::to_string(instanceId), bossId, oldState, newState);

        if (newState == IN_PROGRESS)
        {
            sResetRaidCooldowns->SetCombatStarted(instanceId, bossId);
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: store pair {} ({}-{}) pair: {}-{}", instance->GetMapName(), mapId, std::to_string(instanceId), std::to_string(instanceId), bossId);
            return;
        }

        // newState == DONE is handled with encounter done
        bool isAllowedStateChange = ((oldState == IN_PROGRESS) && (newState == FAIL || newState == NOT_STARTED));
        if (!isAllowedStateChange)
            return;

        if (!sResetRaidCooldowns->HasEnoughTimePassed(instanceId, bossId))
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: Not enough time has passed!");
        else
            sResetRaidCooldowns->DoResetRaidCooldowns(instance);
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

        uint32 entry = unit->GetEntry();
        // NYI: check if creature entry is enabled

        if (uint32 instanceId = unit->GetMap()->GetInstanceId())
            sResetRaidCooldowns->SetCombatStarted(unit->GetGUID());
    }

    void OnUnitEnterEvadeMode(Unit* unit, uint8 evadeReason) override
    {
        if (!sResetRaidCooldowns->isEnabled)
            return;

        uint32 entry = unit->GetEntry();
        // NYI: check if creature entry is enabled

        ObjectGuid guid = unit->GetGUID();
        sResetRaidCooldowns->SetCombatStarted(guid);
        if (!sResetRaidCooldowns->HasEnoughTimePassed(guid))
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: Not enough time has passed!");
        else
            sResetRaidCooldowns->DoResetRaidCooldowns(unit->GetMap());
    }
};

void AddSC_reset_raid_cooldowns()
{
    new reset_raid_cooldowns_globalscript();
    new reset_raid_cooldowns_worldscript();
    new reset_raid_cooldowns_unitscript();
}
