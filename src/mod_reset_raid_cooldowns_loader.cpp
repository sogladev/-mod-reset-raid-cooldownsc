/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "Config.h"

// From SC
void AddSC_reset_raid_cooldowns_spell_script();

// Add all
// cf. the naming convention https://github.com/azerothcore/azerothcore-wotlk/blob/master/doc/changelog/master.md#how-to-upgrade-4
// additionally replace all '-' in the module folder name with '_' here
void Addmod_reset_raid_cooldownsScripts()
{
    if (!sConfigMgr->GetOption<bool>("ResetRaidCooldowns.Enable", true))
        return;
    AddSC_reset_raid_cooldowns_spell_script();
}

