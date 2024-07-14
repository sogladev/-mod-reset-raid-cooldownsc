#ifndef DEF_RESETRAIDCOOLDOWNS_H
#define DEF_RESETRAIDCOOLDOWNS_H

#include "Pet.h"
#include "Player.h"
#include "Config.h"
#include "ScriptMgr.h"

enum ResetRaidCooldownsSpells
{
    SPELL_EXHAUSTION = 57723,
    SPELL_SATED = 57724
};

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

using MapIdBossIdKey = Id1Id2Key;
using InstanceIdBossIdKey = Id1Id2Key;

class ResetRaidCooldowns
{
public:
    static ResetRaidCooldowns* instance();

    bool doResetArenaSpells;
    bool doResetPetCooldowns;
    bool isEnabled{false};
    std::vector<uint32> categories;
    std::vector<uint32> spells;
    uint32 combatTimeRequiredInSeconds;

    typedef std::map<uint32, bool> MapIdEnableSettings;
    MapIdEnableSettings mapIdEnableSettings;
    typedef std::map<MapIdBossIdKey, bool> MapIdBossIdDisableSettings;
    MapIdBossIdDisableSettings mapIdBossIdDisableSettings;
    typedef std::map<InstanceIdBossIdKey, uint32> InstanceIdBossIdCombatStartedTimeMap;
    InstanceIdBossIdCombatStartedTimeMap instanceIdBossIdCombatStartedTimeMap;

    void LoadSpellsSettings(std::string const& spellsSettingsString);
    void LoadCategoriesSettings(std::string const& categoriesSettingsString);
    void LoadMapIdEnableSettings(std::string const& mapIdEnableSettingsString);
    void LoadMapIdBossIdDisableSettings(std::string const& mapIdBossIdDisableSettingsString);

    bool IsMapBossEnabled(uint32 mapId, uint32 bossId);
    void SetCombatStarted(uint32 instanceId, uint32 bossId);
    uint32 GetCombatStartedTime(uint32 instanceId, uint32 bossId) const;
};

#define sResetRaidCooldowns ResetRaidCooldowns::instance()

#endif
