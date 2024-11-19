/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "Pet.h"
#include "Player.h"
#include "reset_raid_cooldowns.h"

ResetRaidCooldowns* ResetRaidCooldowns::instance()
{
    static ResetRaidCooldowns instance;
    return &instance;
}

// combat timer instanceId-bossId
void ResetRaidCooldowns::SetCombatStarted(uint32 instanceId, uint32 bossId)
{
    const auto key = InstanceIdBossIdKey{instanceId, bossId};
    instanceIdBossIdCombatStartedTimeMap[key] = getMSTime();
}

uint32 ResetRaidCooldowns::GetCombatStartedTime(uint32 instanceId, uint32 bossId) const
{
    const auto key = InstanceIdBossIdKey{instanceId, bossId};
    const auto it = instanceIdBossIdCombatStartedTimeMap.find(key);
    return (it != instanceIdBossIdCombatStartedTimeMap.end()) ? it->second : 0;
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
