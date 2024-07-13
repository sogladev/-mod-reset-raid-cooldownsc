/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */
#include "Pet.h"
#include "Player.h"
#include "ScriptMgr.h"

class global_reset_raid_cooldowns : public GlobalScript
{
public:
    global_reset_raid_cooldowns() : GlobalScript("global_reset_raid_cooldowns") { }

    void OnBeforeSetBossState(uint32 id, EncounterState newState, EncounterState oldState, Map* instance) override
    {
        if (oldState == newState)
        {
            return;
        }
        LOG_INFO("module", "mod-reset-raid-cooldowns::OnBeforeSetBossState: {} ({}{}) id: {} old: {} new: {}",
            instance->GetMapName(),
            instance->GetId(),
            instance->GetInstanceId() ? "-" + std::to_string(instance->GetInstanceId()) : "",
            id, oldState, newState
        );
        bool isAllowedStateChange = oldState == IN_PROGRESS && (newState == DONE || newState == FAIL || newState == NOT_STARTED);
        if (!isAllowedStateChange)
        {
            return;
        }
        instance->DoForAllPlayers([&](Player* player)
        {
            LOG_INFO("module", "mod-reset-raid-cooldowns::DoForAllPlayers: {}", player->GetName());
            // Remove cooldowns on spells that have less than 10 minutes of cooldown from the Player
            player->RemoveArenaSpellCooldowns(true); // includes pets
            // Remove cooldowns
            player->RemoveCategoryCooldown(26); // rebirth
            player->RemoveSpellCooldown(42650, true); // army of the dead
            player->RemoveSpellCooldown(2062, true); // earth elemental totem
            player->RemoveSpellCooldown(2894, true); // fire elemental totem
            player->RemoveSpellCooldown(1122, true); // inferno
            // player->RemoveSpellCooldown(48788, true); // lay on hands
            // Remove Exhaustion and Sated from player
            player->RemoveAura(57723); // Exhaustion
            player->RemoveAura(57724); // Sated
            // Remove Exhaustion and Sated from pet
           if (Pet* pet = player->GetPet())
           {
                LOG_INFO("module", "mod-reset-raid-cooldowns::DoForAllPlayers::Pet: {}", pet->GetName());
                pet->RemoveAura(57723); // Exhaustion
                pet->RemoveAura(57724); // Sated
           }
        });
    }
};

void AddSC_reset_raid_cooldowns_spell_script()
{
    new global_reset_raid_cooldowns();
}
