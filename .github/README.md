# AzerothCore Module Reset Raid Cooldowns

~~- Latest build status with azerothcore:~~

[![Build Status](
https://github.com/sogladev/mod-reset-raid-cooldowns/actions/workflows/core-build.yml/badge.svg?branch=master&event=push)](https://github.com/sogladev/mod-reset-raid-cooldowns)

This is a module for [AzerothCore](http://www.azerothcore.org) that removes Sated and Exhaustion debuffs, and resets player cooldowns after raid encounters to emulate how it was done in Wrath Classic

Current implementation is done in Eluna and is using creature reset and enter combat hooks

(WIP): write cpp script `OnBeforeSetBossState` hook instead
- Reset cooldowns and remove exhaustion/sated after 30 seconds boss encounter
- TODO: Add customization which spells with config
- TODO: Configure enable/disable encounters per map like Sartharion's dragons

## What spells are reset?
cooldowns on spells that have less than 10 minutes of cooldown from the Player, similarly to when you enter an arena AND custom defined spells (id) in the configuration

## For which creatures is there a reset?
Every creature (entry) that is enabled in the configuration


## How to install
https://www.azerothcore.org/wiki/installing-a-module

requires: https://github.com/azerothcore/mod-eluna

place in `lua_scripts/` directory

## Configuration
can be done by modifying .lua file

Enable or add spells by appending to `COOLDOWN_CONFIG` table
```
COOLDOWN_CONFIG = {
    [48788] = false, -- lay on hands, default: false
    ...
}
```

Enable or disable resets for creatures (entry) by modifying `CREATURE_CONFIG`.
```
CREATURE_CONFIG = {
    [28860] = true, -- Sartharion <-- ENABLED
    -- [30449] = true, -- Vesperon <-- DISABLED
    [30449] = false, -- Vesperon <-- DISABLED
    ...
}
```


<!---
Requires source recompilation

Apply database changes: `data/sql/db-world/base/demonic_pact_classic.sql`
```
-- reduce Internal Cooldown from 20 seconds (20000) to 5 seconds (5000), some sources say 1 second (1000)
SET @ICD:=5000;
UPDATE `spell_proc_event` SET `Cooldown`=@ICD WHERE `entry` IN (53646, 54909);
DELETE FROM `spell_script_names` WHERE `spell_id` = 48090;
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (48090, 'spell_warl_demonic_pact_classic');
```
-->

## How to remove

remove from `lua_scripts/` directory

<!---
1. Undo database changes: `optional/undo_demonic_pact_classic.sql`
```
-- restore Internal Cooldown to 20 seconds (20000)
SET @ICD:=20000;
UPDATE `spell_proc_event` SET `Cooldown`=@ICD WHERE `entry` IN (53646, 54909);
DELETE FROM `spell_script_names` WHERE `spell_id` = 48090;
```

2. Remove `mod-demonic-pact-classic` folder
-->

## How to create your own module

1. Use the script `create_module.sh` located in [`modules/`](https://github.com/azerothcore/azerothcore-wotlk/tree/master/modules) to start quickly with all the files you need and your git repo configured correctly (heavily recommended).
1. You can then use these scripts to start your project: https://github.com/azerothcore/azerothcore-boilerplates
1. Do not hesitate to compare with some of our newer/bigger/famous modules.
1. Edit the `README.md` and other files (`include.sh` etc...) to fit your module. Note: the README is automatically created from `README_example.md` when you use the script `create_module.sh`.
1. Publish your module to our [catalogue](https://github.com/azerothcore/modules-catalogue).
