-- Config
local amountOfSecondsUntilReset = 10
local amountOfMinutesUntilNoReset = 10 -- safety
--
local CREATURE_EVENT_ON_ENTER_COMBAT = 1
local CREATURE_EVENT_ON_RESET = 23
local INSTANCE_EVENT_ON_UPDATE = 3
local IN_MILLISECONDS = 1000
local IN_MINUTES_IN_MILLISECONDS = 60000
--
local creatureOnCombatEntryTimestamp = {}

-- print line surrounded by dashes (-)
local function PrintUnderlineWithDashes(line)
    print(string.rep("-", string.len(line)))
    print(line)
    print(string.rep("-", string.len(line)))
end
local PrintD = PrintUnderlineWithDashes

-- clean old entries from table
local function OnCleanCreatureOnCombatEntryTimestamp()
    -- remove any keys with values greater than 15 minutes (900000) from the table
    for key, value in pairs(creatureOnCombatEntryTimestamp) do
        if value >= 15*IN_MINUTES_IN_MILLISECONDS then
            delete(creatureOnCombatEntryTimestamp, key)
        end
    end
end

local function OnCreatureEventOnEnterCombat(event, creature, target)
    PrintD("OnCreatureEventOnEnterCombat")
    print(event)
    print(creature)
    print(target)
    --
    guid = creature:GetGUID() -- unique
    print("guid")
    print(guid)
    currTime = GetCurrTime()
    print(currTime)
    print("Store")
    creatureOnCombatEntryTimestamp[tostring(guid)] = currTime
end

local function OnCreatureEventOnReset(event, creature)
    PrintD("OnCreateEventOnReset")
    print(event)
    print(creature)
    --
    guid = creature:GetGUID() -- unique
    print("guid")
    print(guid)
    --
    scriptName = creature:GetScriptName()
    print("scriptName")
    print(scriptName)
    --
    oldTime = creatureOnCombatEntryTimestamp[tostring(guid)]
    print("oldTime")
    print(oldTime)
    if not oldTime then
        print("No oldTime was found for this guid")
    else
        timeDiff = GetTimeDiff(oldTime) -- in milliseconds
        print(timeDiff)
        print("Checking timeDiff for reset logic")
        if timeDiff < (amountOfSecondsUntilReset * IN_MILLISECONDS) then
            print("timeDiff <")
        elseif timeDiff > (amountOfMinutesUntilNoReset * IN_MINUTES_IN_MILLISECONDS) then
            print("timeDiff too large")
        else
            print("timeDiff >=")
            -- do reset logic here
            -- Creature has been in combat for amountOfSecondsUntilReset
            -- Apply reset to players and their pets
            -- under the following conditions:
            -- if combat in range: maybe not needed
            -- if zone is no longer in combat: prevent iron council to mid-combat reset, side effects?
            -- challenges: Iron Council - multiple bosses, Thorim - long outro, Gunship battle - ?, BPC - multiple bosses that die together
            -- add cooldown GUID per player guid? only reset once every x seconds
            -- Proper: OnAfterUpdateEncounterState with cpp
    end
end

-- Noth: 15954
RegisterCreatureEvent(15954, CREATURE_EVENT_ON_ENTER_COMBAT, OnCreatureEventOnEnterCombat)
RegisterCreatureEvent(15954, CREATURE_EVENT_ON_RESET, OnCreatureEventOnReset)
-- Steelbreaker: 32867
RegisterCreatureEvent(32867, CREATURE_EVENT_ON_ENTER_COMBAT, OnCreatureEventOnEnterCombat)
RegisterCreatureEvent(32867, CREATURE_EVENT_ON_RESET, OnCreatureEventOnReset)
-- Runemaster Molgein: 32927
RegisterCreatureEvent(32927, CREATURE_EVENT_ON_ENTER_COMBAT, OnCreatureEventOnEnterCombat)
RegisterCreatureEvent(32927, CREATURE_EVENT_ON_RESET, OnCreatureEventOnReset)
-- Stormcaller Brundir: 32857
RegisterCreatureEvent(32857, CREATURE_EVENT_ON_ENTER_COMBAT, OnCreatureEventOnEnterCombat)
RegisterCreatureEvent(32857, CREATURE_EVENT_ON_RESET, OnCreatureEventOnReset)

-- Table cleanup
CreateLuaEvent(OnCleanCreatureOnCombatEntryTimestamp, 15*IN_MINUTES_IN_MILLISECONDS, 0) -- repeats infinitely
