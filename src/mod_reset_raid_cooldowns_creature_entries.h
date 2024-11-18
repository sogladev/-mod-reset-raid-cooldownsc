#ifndef DEF_RESETRAIDCOOLDOWNS_CREATURE_ENTRIES_H
#define DEF_RESETRAIDCOOLDOWNS_CREATURE_ENTRIES_H

#include "Define.h"
#include <unordered_set>

namespace ModResetRaidCooldowns
{
    constexpr uint32 ENABLED_ENTRIES[] =
    {
        1,
        2,
        3,
        33293,
    };

    inline const std::unordered_set<uint32> EnabledEntriesSet(
        ENABLED_ENTRIES, ENABLED_ENTRIES + sizeof(ENABLED_ENTRIES) / sizeof(ENABLED_ENTRIES[0])
    );

    inline bool IsEnabledForCreatureEntry(uint32 entry)
    {
        if (EnabledEntriesSet.find(entry) == EnabledEntriesSet.end()) {
            // Entry not found, return
            return false;
        }
        return true;
    }
}

#endif // DEF_RESETRAIDCOOLDOWNS_CREATURE_ENTRIES_H
