/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "reset_raid_cooldowns.h"

ResetRaidCooldowns* ResetRaidCooldowns::instance()
{
    static ResetRaidCooldowns instance;
    return &instance;
}

// combat timer instanceId-bossId
void ResetRaidCooldowns::SetCombatStarted(uint32 instanceId, uint32 bossId)
{
    InstanceIdBossIdKey key(instanceId, bossId);
    instanceIdBossIdCombatStartedTimeMap[key] = getMSTime();
}

uint32 ResetRaidCooldowns::GetCombatStartedTime(uint32 instanceId, uint32 bossId) const
{
    InstanceIdBossIdKey key(instanceId, bossId);
    auto it = instanceIdBossIdCombatStartedTimeMap.find(key);
    if (it != instanceIdBossIdCombatStartedTimeMap.end())
    {
        return it->second;
    }
    return 0;
}

bool ResetRaidCooldowns::HasEnoughTimePassed(uint32 instanceId, uint32 bossId) const
{
    bool hasRequiredTimePassed = false;
    LOG_DEBUG("module", "mod-reset-raid-cooldowns::HasEnoughTimePassed: Time check");
    if (uint32 combatStartedTime = sResetRaidCooldowns->GetCombatStartedTime(instanceId, bossId))
    {
        LOG_DEBUG("module", "mod-reset-raid-cooldowns::HasEnoughTimePassed: Combat Time Diff required {}", sResetRaidCooldowns->combatTimeRequiredInSeconds * IN_MILLISECONDS);
        LOG_DEBUG("module", "mod-reset-raid-cooldowns::HasEnoughTimePassed: Combat Diff {}", GetMSTimeDiffToNow(combatStartedTime));
        hasRequiredTimePassed = (GetMSTimeDiffToNow(combatStartedTime) >= (sResetRaidCooldowns->combatTimeRequiredInSeconds * IN_MILLISECONDS));
    }
    return hasRequiredTimePassed;
}

// combat timer guid
void ResetRaidCooldowns::SetCombatStarted(ObjectGuid guid)
{
    creatureGUIDCombatStartedTimeMap[guid] = getMSTime();
}

uint32 ResetRaidCooldowns::GetCombatStartedTime(ObjectGuid guid) const
{
    auto it = creatureGUIDCombatStartedTimeMap.find(guid);
    if (it != creatureGUIDCombatStartedTimeMap.end())
        return it->second;
    return 0;
}

bool ResetRaidCooldowns::HasEnoughTimePassed(ObjectGuid guid) const
{
    bool hasRequiredTimePassed = false;
    LOG_DEBUG("module", "mod-reset-raid-cooldowns::HasEnoughTimePassed: Time check");
    if (uint32 combatStartedTime = sResetRaidCooldowns->GetCombatStartedTime(guid))
    {
        LOG_DEBUG("module", "mod-reset-raid-cooldowns::HasEnoughTimePassed: GUID Combat Time Diff required {}", sResetRaidCooldowns->combatTimeRequiredInSeconds * IN_MILLISECONDS);
        LOG_DEBUG("module", "mod-reset-raid-cooldowns::HasEnoughTimePassed: GUID: Combat Diff {}", GetMSTimeDiffToNow(combatStartedTime));
        hasRequiredTimePassed = (GetMSTimeDiffToNow(combatStartedTime) >= (sResetRaidCooldowns->combatTimeRequiredInSeconds * IN_MILLISECONDS));
    }
    return hasRequiredTimePassed;
}

void ResetRaidCooldowns::LoadSpellsSettings(std::string const& spellsSettingsString)
{
    std::string delimitedValue;
    std::stringstream spellsSettingsStream;

    spellsSettingsStream.str(spellsSettingsString);
    while (std::getline(spellsSettingsStream, delimitedValue, ','))
    {
        uint32 spellId = atoi(delimitedValue.c_str());
        LOG_INFO("module", "mod-reset-raid-cooldowns::LoadSpellsSettings:SpellId {}", spellId);
        sResetRaidCooldowns->spells.push_back(spellId);
    }
}

void ResetRaidCooldowns::LoadCategoriesSettings(std::string const& categoriesSettingsString)
{
    std::string delimitedValue;
    std::stringstream categoriesSettingsStream;

    categoriesSettingsStream.str(categoriesSettingsString);
    while (std::getline(categoriesSettingsStream, delimitedValue, ','))
    {
        uint32 categoryId = atoi(delimitedValue.c_str());
        LOG_INFO("module", "mod-reset-raid-cooldowns::LoadCategoriesSettings:CategoryId {}", categoryId);
        sResetRaidCooldowns->categories.push_back(categoryId);
    }
}

void ResetRaidCooldowns::LoadMapIdEnableSettings(std::string const& mapIdEnableSettingsString)
{
    std::string delimitedValue;
    std::stringstream mapIdEnableSettingsStream;

    mapIdEnableSettingsStream.str(mapIdEnableSettingsString);
    while (std::getline(mapIdEnableSettingsStream, delimitedValue, ','))
    {
        uint32 mapId = atoi(delimitedValue.c_str());
        LOG_INFO("module", "mod-reset-raid-cooldowns::LoadMapIdEnableSettings:MapId {}", mapId);
        sResetRaidCooldowns->mapIdEnableSettings[mapId] = true;
    }
}

void ResetRaidCooldowns::LoadMapIdBossIdDisableSettings(std::string const& mapIdBossIdDisableSettingsString)
{
    std::string delimitedValue;
    std::stringstream MapIdBossIdDisableSettingsStream;

    MapIdBossIdDisableSettingsStream.str(mapIdBossIdDisableSettingsString);
    while (std::getline(MapIdBossIdDisableSettingsStream, delimitedValue, ','))
    {
        std::string pairOne, pairTwo;
        std::stringstream progressionPairStream(delimitedValue);
        progressionPairStream>>pairOne>>pairTwo;
        uint32 mapId = atoi(pairOne.c_str());
        uint8 bossId = atoi(pairTwo.c_str());
        MapIdBossIdKey key(mapId, bossId);
        LOG_INFO("module", "mod-reset-raid-cooldowns::LoadMapIdBossIdDisableSettings:MapId-BossId {}-{}", mapId, bossId);
        sResetRaidCooldowns->mapIdBossIdDisableSettings[key] = true;
    }
}

bool ResetRaidCooldowns::IsMapEnabled(uint32 mapId) const
{
    if (!sResetRaidCooldowns->mapIdEnableSettings[mapId])
    {
        return false;
    }
    return true;
}

bool ResetRaidCooldowns::IsMapBossEnabled(uint32 mapId, uint32 bossId) const
{
    if (!sResetRaidCooldowns->mapIdEnableSettings[mapId])
    {
        return false;
    }
    MapIdBossIdKey key(mapId, bossId);
    bool isDisabled = sResetRaidCooldowns->mapIdBossIdDisableSettings[key];
    return !isDisabled;
}

void ResetRaidCooldowns::DoResetRaidCooldowns(Map* map)
{
    map->DoForAllPlayers([&](Player* player)
    {
        LOG_DEBUG("module", "mod-reset-raid-cooldowns::DoForAllPlayers: {}", player->GetName());
        if (sResetRaidCooldowns->doResetArenaSpells)
        {
            // Remove cooldowns on spells that have less than 10 minutes of cooldown from the Player
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: arena cooldowns");
            player->RemoveArenaSpellCooldowns(false); // no reset pet cooldowns
        }
        for (auto const& spellId : sResetRaidCooldowns->spells)
        {
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: spell {}", spellId);
            player->RemoveSpellCooldown(spellId, true);
        }
        for (auto const& categoryId : sResetRaidCooldowns->categories)
        {
            LOG_DEBUG("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: category {}", categoryId);
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
                for (auto const& spell : pet->m_CreatureSpellCooldowns)
                    player->SendClearCooldown(spell.first, pet);
                pet->m_CreatureSpellCooldowns.clear();
                // Remove Exhaustion and Sated from pet
                player->RemoveAura(SPELL_EXHAUSTION);
                player->RemoveAura(SPELL_SATED);
            }
        }
    });
}
