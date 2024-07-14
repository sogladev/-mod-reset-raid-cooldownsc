/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "reset_raid_cooldowns.h"

ResetRaidCooldowns* ResetRaidCooldowns::instance()
{
    static ResetRaidCooldowns instance;
    return &instance;
}

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

void ResetRaidCooldowns::LoadMapIdEnableSettings(std::string const& mapIdEnableSettingsString)
{
    std::string delimitedValue;
    std::stringstream mapIdEnableSettingsStream;

    mapIdEnableSettingsStream.str(mapIdEnableSettingsString);
    while (std::getline(mapIdEnableSettingsStream, delimitedValue, ','))
    {
        uint32 mapId = atoi(delimitedValue.c_str());
        // LOG_INFO("module", "mod-reset-raid-cooldowns::LoadMapIdEnableSettings:MapId {}", mapId);
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
        // LOG_INFO("module", "mod-reset-raid-cooldowns::LoadMapIdBossIdDisableSettings:MapId-BossId {}-{}", mapId, bossId);
        sResetRaidCooldowns->mapIdBossIdDisableSettings[key] = true;
    }
}

bool ResetRaidCooldowns::IsMapBossEnabled(uint32 mapId, uint32 bossId)
{
    if (!sResetRaidCooldowns->mapIdEnableSettings[mapId])
    {
        return false;
    }
    MapIdBossIdKey key(mapId, bossId);
    bool isEnabled = !(sResetRaidCooldowns->mapIdBossIdDisableSettings[key]);
    return isEnabled;
}
