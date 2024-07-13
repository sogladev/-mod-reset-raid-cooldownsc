# AzerothCore Module Reset Raid Cooldowns

- Latest build status with azerothcore:

[![Build Status](
https://github.com/sogladev/mod-reset-raid-cooldowns/actions/workflows/core-build.yml/badge.svg?branch=master&event=push)](https://github.com/sogladev/mod-reset-raid-cooldowns)

This is a module for [AzerothCore](http://www.azerothcore.org) that resets Sated/Exhaustion and resets raid cooldowns to emulate how it was done in Wrath Classic:

Current (WIP) implementation is done in Eluna and is using creature reset and enter combat hooks

TODO: write cpp script with `OnAfterUpdateEncounterState` hook instead

## How to install
https://www.azerothcore.org/wiki/installing-a-module

requires: https://github.com/azerothcore/mod-eluna

place in `lua_scripts/` directory

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
