# AzerothCore Module Reset Raid Cooldowns

- Latest build status with azerothcore:

[![Build Status](
https://github.com/sogladev/mod-reset-raid-cooldowns/actions/workflows/core-build.yml/badge.svg?branch=master&event=push)](https://github.com/sogladev/mod-reset-raid-cooldowns)

This is a module for [AzerothCore](http://www.azerothcore.org) that removes Sated and Exhaustion debuffs, and resets player cooldowns after raid encounters to emulate how it was done in Wrath Classic

This projects hosts 2 implementations which use different methods and could, but is not recommended, be used together

1. Eluna (lua): uses creature enter combat and reset hooks
2. cpp: uses `OnBeforeSetBossState` hooks+



https://github.com/user-attachments/assets/b401789c-4ca7-4ce1-8fa0-589444c489d4



## cpp

cpp: uses `OnBeforeSetBossState` hooks

This script only runs for instances.

All configuration can be done through the config file `.conf`

When a boss state is changed from IN_PROGRESS to  DONE, FAIL or NOT_STARTED cooldowns and exhausted/sated debuffs will be cleared for all players and their pets that are present in the map.

Conditions such as how long a boss should be in combat for, for which instances, for which bosses, which spells/categories, whether pets also reset, if all short cooldowns are reset similarly to when you enter arena, can be configured by modifying the config file

### How to install
https://www.azerothcore.org/wiki/installing-a-module

no database changes are required

requires config file


### How to remove

disable in config

or delete cpp and conf

no database changes are made

## lua

Eluna (lua): uses creature enter combat and reset hooks.

The cpp script is prefered for resets in raids like wrath classic but lua allows the script to also work in the open world and on any creature.

Similary to cpp, you can edit which spells are reset. You can choose for which creatures, by entry, spells are reset

configuration can be done by modifying .lua file

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

### How to install
https://www.azerothcore.org/wiki/installing-a-module

requires: https://github.com/azerothcore/mod-eluna

place in `lua_scripts/` directory

### How to remove

remove from `lua_scripts/` directory

no database changes are made

## How to create your own module

1. Use the script `create_module.sh` located in [`modules/`](https://github.com/azerothcore/azerothcore-wotlk/tree/master/modules) to start quickly with all the files you need and your git repo configured correctly (heavily recommended).
1. You can then use these scripts to start your project: https://github.com/azerothcore/azerothcore-boilerplates
1. Do not hesitate to compare with some of our newer/bigger/famous modules.
1. Edit the `README.md` and other files (`include.sh` etc...) to fit your module. Note: the README is automatically created from `README_example.md` when you use the script `create_module.sh`.
1. Publish your module to our [catalogue](https://github.com/azerothcore/modules-catalogue).
