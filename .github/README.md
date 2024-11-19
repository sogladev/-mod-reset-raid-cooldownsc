# AzerothCore Module Reset Raid Cooldowns

- Latest build status with azerothcore:

[![Build Status](
https://github.com/sogladev/mod-reset-raid-cooldowns/actions/workflows/core-build.yml/badge.svg?branch=main&event=push)](https://github.com/sogladev/mod-reset-raid-cooldowns)

This is a module for [AzerothCore](http://www.azerothcore.org) that removes Sated and Exhaustion debuffs, and resets player cooldowns after raid encounters to emulate how it was done in Wrath Classic

https://github.com/user-attachments/assets/b401789c-4ca7-4ce1-8fa0-589444c489d4

## FAQ

### What cooldowns are reset?
All cooldowns that are reset similar to Wrath Classic. This is emulated by resetting player cooldowns that are cleared when entering arena plus the following spells are also reset:
  * army of the dead
  * earth elemental totem
  * fire elemental totem
  * inferno

The above list can be modified by editing the config

Player pet cooldowns are not reset by default, but can be enabled in the config

### When are cooldowns reset?
Cooldowns are reset by the following events:
#### Completing a raid encounter
By default, completing any raid encounter will resets cooldowns, with the exception of the dragon mini-bosses in Obsidian Sanctum

Resetting cooldowns for completing encounters in heroic dungeons can be enabled in the config

#### Resetting a boss after a specified amount of time

After a boss is engaged for at least 30 seconds (configurable) and resets, all cooldowns are reset. This is implemented in 2 ways:
a. BossState changes: For any boss scripted with `BossAI` or that uses `SetBossState`
b. `OnUnitEnterCombat` and `OnUnitEnterEvadeMode`: This is a hack to make bosses that not use `SetBossState`. These entries are specified in `reset_raid_cooldowns_entries.h`


## Installation
https://www.azerothcore.org/wiki/installing-a-module

no database changes are required

requires config file

requires recompilation

### How to configure

All configuration can be done through the config file `.conf`

### How to disable

disable in config

### How to remove

To remove, delete the folder as no database changes are made.


## How to create your own module

1. Use the script `create_module.sh` located in [`modules/`](https://github.com/azerothcore/azerothcore-wotlk/tree/master/modules) to start quickly with all the files you need and your git repo configured correctly (heavily recommended).
1. You can then use these scripts to start your project: https://github.com/azerothcore/azerothcore-boilerplates
1. Do not hesitate to compare with some of our newer/bigger/famous modules.
1. Edit the `README.md` and other files (`include.sh` etc...) to fit your module. Note: the README is automatically created from `README_example.md` when you use the script `create_module.sh`.
1. Publish your module to our [catalogue](https://github.com/azerothcore/modules-catalogue).
