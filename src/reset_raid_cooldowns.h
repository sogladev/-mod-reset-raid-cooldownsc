#ifndef DEF_RESETRAIDCOOLDOWNS_H
#define DEF_RESETRAIDCOOLDOWNS_H

#include "ScriptMgr.h"

enum ResetRaidCooldownsSpells
{
    SPELL_EXHAUSTION = 57723,
    SPELL_SATED = 57724
};

struct InstanceIdBossIdKey
{
    uint32 id1;
    uint32 id2;
    InstanceIdBossIdKey(uint32 id1, uint32 id2) : id1(id1), id2(id2) {}
    bool operator<(const InstanceIdBossIdKey& other) const
    {
        return std::tie(id1, id2) < std::tie(other.id1, other.id2);
    }
};

class ResetRaidCooldowns
{
public:
    static ResetRaidCooldowns* instance();

    bool doResetArenaSpells;
    bool doResetPetCooldowns;
    bool isEnabled;
    bool isEnabledForHeroics;
    std::vector<uint32> categories;
    std::vector<uint32> spells;
    uint32 combatTimeRequiredInSeconds;

    void LoadSpellsSettings(std::string const& spellsSettingsString);
    void LoadCategoriesSettings(std::string const& categoriesSettingsString);

    bool IsMapEnabled(uint32 mapId) const;
    bool IsMapBossEnabled(uint32 mapId, uint32 bossId) const;

    // combat timer for instanceId-bossId pair
    std::map<InstanceIdBossIdKey, uint32> instanceIdBossIdCombatStartedTimeMap;
    void SetCombatStarted(uint32 instanceId, uint32 bossId);
    bool HasEnoughTimePassed(uint32 instanceId, uint32 bossId) const;
    uint32 GetCombatStartedTime(uint32 instanceId, uint32 bossId) const;

    // combat timer for guid
    // NOTE: this can be stored in creature->CustomData instead
    std::map<ObjectGuid, uint32> creatureGUIDCombatStartedTimeMap;
    void SetCombatStarted(ObjectGuid guid);
    bool HasEnoughTimePassed(ObjectGuid guid) const;
    uint32 GetCombatStartedTime(ObjectGuid guid) const;

    void DoResetRaidCooldowns(Map* map);
};

#define sResetRaidCooldowns ResetRaidCooldowns::instance()

#endif
