#ifndef DEF_RESETRAIDCOOLDOWNS_H
#define DEF_RESETRAIDCOOLDOWNS_H

#include "Pet.h"
#include "Player.h"
#include "Config.h"
#include "ScriptMgr.h"

struct Id1Id2Key
{
    uint32 id1;
    uint32 id2;
    Id1Id2Key(uint32 id1, uint32 id2) : id1(id1), id2(id2) {}
    bool operator<(const Id1Id2Key& other) const
    {
        return std::tie(id1, id2) < std::tie(other.id1, other.id2);
    }
};

typedef Id1Id2Key InstanceIdBossIdKey;
typedef Id1Id2Key MapIdBossIdKey;

class ResetRaidCooldowns
{
public:
    static ResetRaidCooldowns* instance();

    bool IsEnabled{false};
    uint32 CombatTimeRequiredInSeconds;

    void LoadMapIdEnableSettings(std::string const& mapIdEnableSettingsString);
    void LoadMapIdBossIdDisableSettings(std::string const& mapIdBossIdDisableSettingsString);

    bool IsMapBossEnabled(uint32 mapId, uint32 bossId);
    void SetCombatStarted(uint32 instanceId, uint32 bossId);
    uint32 GetCombatStartedTime(uint32 instanceId, uint32 bossId) const;

    typedef std::map<uint32, bool> MapIdEnableSettings;
    MapIdEnableSettings mapIdEnableSettings;
    typedef std::map<MapIdBossIdKey, bool> MapIdBossIdDisableSettings;
    MapIdBossIdDisableSettings mapIdBossIdDisableSettings;
    typedef std::map<InstanceIdBossIdKey, uint32> InstanceIdBossIdCombatStartedTimeMap;
    InstanceIdBossIdCombatStartedTimeMap instanceIdBossIdCombatStartedTimeMap;
};

#define sResetRaidCooldowns ResetRaidCooldowns::instance()

#endif
