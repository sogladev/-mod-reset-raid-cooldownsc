-- Apply reset of player cooldowns and removal of exhaustion/sated debuffs
-- to players and their pets under the following conditions:
-- if creature has been in combat for amountOfSecondsUntilReset
-- if creature is on cooldown: prevent triggering too frequently

-- Config
local AMOUNT_OF_COMBAT_REQUIRED_IN_SECONDS = 1 -- default: 30
local AMOUNT_OF_COOLDOWN_IN_SECONDS = 30 -- default: 30
local AMOUNT_OF_TIME_BETWEEN_CLEAN_COMBAT_ENTRY_TABLE_IN_MINUTES = 15 -- default: 15
local DO_PLAYER_IN_RANGE_CHECK = true -- default: true
local DO_REMOVE_SATED_FROM_PETS = true -- default: true
local MAX_PLAYER_DISTANCE = 150 -- exact distance, default: 150
local PET_SEARCH_RADIUS = 45 -- default: 45
-- Configuration table for cooldown resets
local COOLDOWN_CONFIG = {
    [26] = true, -- category rebirth
    [42650] = true, -- army of the dead
    [2062] = true, -- earth elemental totem
    [2894] = true, -- fire elemental totem
    [1122] = true, -- inferno
    [48788] = false, -- lay on hands, default: false
}
-- Spells
local SPELL_EXHAUSTION = 57723
local SPELL_SATED = 57724
-- Constants
local CREATURE_EVENT_ON_ENTER_COMBAT = 1
local CREATURE_EVENT_ON_RESET = 23
local INSTANCE_EVENT_ON_UPDATE = 3
local IN_MILLISECONDS = 1000
local IN_MINUTES_IN_MILLISECONDS = 60000
-- Special requirements
local IronCouncilEntries = {[32927] = true, [32857] = true, [32867] = true} -- Runemaster Molgein: 32927, Stormcaller Brundir: 32857, Steelbreaker: 32867
-- Tables
local creatureOnCombatEntryTimestamp = {} -- stores guid, timestamp pairs
local instanceResetTimestamp = {} -- stores instanceId, timestamp pairs

-- print line surrounded by dashes (-)
local function PrintUnderlineWithDashes(line)
    PrintDebug(string.rep("-", string.len(line)))
    PrintDebug(line)
    PrintDebug(string.rep("-", string.len(line)))
end
local PrintD = PrintUnderlineWithDashes


-- Reset player cooldowns and pet
local function ResetPlayerCooldowns(player)
    -- """Remove cooldowns on spells that have less than 10 minutes of cooldown from the Player
    -- similarly to when you enter an arena."""
    player:RemoveArenaSpellCooldowns() -- includes pets
    -- Remove cooldowns that are not reset by the above based on configuration
    for spell, shouldReset in pairs(COOLDOWN_CONFIG) do
        if shouldReset then
            -- Check if the spell is a category or a specific spell ID
            if spell == 26 then -- gategory rebirth
                player:ResetTypeCooldowns(spell, true) -- send update for category
            else
                player:ResetSpellCooldown(spell, true) -- send update for specific spell
            end
        end
    end
end


-- Remove exhaustion and sated debuff from player and pet
local function RemoveExhaustionSatedDebuffFromPlayerAndPet(player)
    player:RemoveAura(SPELL_EXHAUSTION)
    player:RemoveAura(SPELL_SATED)
    local petGUID = player:GetPetGUID()
    if DO_REMOVE_SATED_FROM_PETS and petGUID then
        -- """There's no direct way to get the pet as a creature object
        -- you have to get the pet guid then check for nearby creatures
        -- and compare the guids"""
        local typeId = GetGUIDType(petGUID)
        local worldObjectList = player:GetNearObjects(PET_SEARCH_RADIUS, typeId, entry, 2) -- radius, friendly
        local pet = nil
        for _, worldObject in pairs(worldObjectList) do
            if worldObject:GetGUID() == petGUID then
            pet = worldObject
            break
            end
        end
        if pet then
            pet:RemoveAura(SPELL_EXHAUSTION)
            pet:RemoveAura(SPELL_SATED)
        end
    end
end


local function OnCreatureEventOnEnterCombat(event, creature, target)
    PrintD("OnCreatureEventOnEnterCombat")
    PrintDebug(event)
    PrintDebug(creature)
    PrintDebug(target)
    --
    local guid = creature:GetGUID() -- unique
    PrintDebug("guid")
    PrintDebug(guid)
    local currTime = GetCurrTime()
    PrintDebug("currTime")
    PrintDebug(currTime)
    creatureOnCombatEntryTimestamp[tostring(guid)] = currTime
end


local function HasCreatureBeenInCombatLongEnough(creature)
    local guid = creature:GetGUID() -- unique
    local oldTime = creatureOnCombatEntryTimestamp[tostring(guid)]
    PrintDebug("oldTime")
    PrintDebug(oldTime)
    if not oldTime then
        PrintDebug("No oldTime was found for this guid")
        return false
    end
    local timeDiff = GetTimeDiff(oldTime) -- in milliseconds
    PrintDebug("timeDiff")
    PrintDebug(timeDiff)
    PrintDebug("Checking timeDiff for reset logic")
    if timeDiff < (AMOUNT_OF_COMBAT_REQUIRED_IN_SECONDS * IN_MILLISECONDS) then
        PrintDebug("timeDiff < AMOUNT_OF_COMBAT_REQUIRED")
        return false
    else
        PrintDebug("timeDiff >= AMOUNT_OF_COMBAT_REQUIRED")
        return true
    end
end


local function HasCreatureCooldown(creature)
    local instanceId = creature:GetInstanceId()
    local oldTime = instanceResetTimestamp[tostring(instanceId)]
    if oldTime and GetTimeDiff(oldTime) < (AMOUNT_OF_COOLDOWN_IN_SECONDS * IN_MILLISECONDS) then
        PrintDebug("creature has cooldown!")
        return true
    end
    return false
end


local function CheckSpecialRequirements(creature)
    -- Iron Council, prevent reset in combat
    local entry = creature:GetEntry()
    if IronCouncilEntries[entry] then
        PrintDebug("doing check for iron council")
        -- check if other bosses are dead
        for entryId, _ in pairs(IronCouncilEntries)  do
            if entry ~= entryId then
                local nearestCreature = creature:GetNearestCreature(150, entryId, 0, 1) -- range, entry, hostile both, alive
                if nearestCreature ~= nil then
                    -- another boss is still alive
                    PrintDebug("check failed: another boss is still alive")
                    return false
                end
            end
        end
    end
    PrintDebug("special requirements success!")
    return true
 end


local function OnCreatureEventOnReset(event, creature)
    PrintD("OnCreateEventOnReset")
    PrintDebug(event)
    PrintDebug(creature)
    -- Has creature been in combat long enough?
    if not HasCreatureBeenInCombatLongEnough(creature) then
        PrintDebug("No reset: creature has not been in combat long enough!")
        return
    end
    -- Is cooldown?
    if HasCreatureCooldown(creature) then
        PrintDebug("No reset: creature has reset cooldown!")
        return
    end
    -- Special cases
    if not CheckSpecialRequirements(creature) then
        PrintDebug("No reset: failed special requirements for specific creature!")
        return
    end
    -- Do reset
    local mapObject = creature:GetMap()
    local mapPlayers = mapObject:GetPlayers()
    for _, player in ipairs(mapPlayers) do
        -- Is player in range?
        if (DO_PLAYER_IN_RANGE_CHECK and player:GetExactDistance2d(creature) > MAX_PLAYER_DISTANCE) then
            PrintDebug("No reset for player: player is out of range!")
        else
            ResetPlayerCooldowns(player)
            RemoveExhaustionSatedDebuffFromPlayerAndPet(player)
        end
    end
    --
    local guid = creature:GetGUID() -- unique
    local currTime = GetCurrTime()
    instanceResetTimestamp[tostring(instanceId)] = currTime
    creatureOnCombatEntryTimestamp[tostring(guid)] = nil
end


-- clean old entries from table
local function OnCleanCreatureOnCombatEntryTimestamp()
    -- remove any keys with values greater than 15 minutes (900000) from the table
    for key, value in pairs(creatureOnCombatEntryTimestamp) do
        if value >= (AMOUNT_OF_TIME_BETWEEN_CLEAN_COMBAT_ENTRY_TABLE_IN_MINUTES * IN_MINUTES_IN_MILLISECONDS) then
            creatureOnCombatEntryTimestamp[key] = nil -- remove key
        end
    end
end


-- Table cleanup
CreateLuaEvent(OnCleanCreatureOnCombatEntryTimestamp, 15*IN_MINUTES_IN_MILLISECONDS, 0) -- repeats infinitely

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
