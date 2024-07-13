-- Apply reset of player cooldowns and removal of exhaustion/sated debuffs
-- to players and their pets under the following conditions:
-- if creature has been in combat for amountOfSecondsUntilReset
-- if creature is not on cooldown: prevent triggering too frequently

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


local CREATURE_CONFIG = {
------------------------------
--  WRATH
------------------------------
    [10184] = true, -- Onyxia
    [15928] = true, -- Thaddius
    [15931] = true, -- Grobbulus
    [15932] = true, -- Gluth
    [15936] = true, -- Heigan the Unclean
    [15952] = true, -- Maexxna
    [15953] = true, -- Grand Widow Faerlina
    [15954] = true, -- Noth the Plaguebringer
    [15956] = true, -- Anub'Rekhan
    [15989] = true, -- Sapphiron
    [15990] = true, -- Kel'Thuzad
    [16011] = true, -- Loatheb
    [16028] = true, -- Patchwerk
    [16060] = true, -- Gothik the Harvester
    [28859] = true, -- Malygos
    [28860] = true, -- Sartharion
    [29249] = true, -- Anub'Rekhan (1)
    [29268] = true, -- Grand Widow Faerlina (1)
    [29278] = true, -- Maexxna (1)
    [29324] = true, -- Patchwerk (1)
    [29373] = true, -- Grobbulus (1)
    [29417] = true, -- Gluth (1)
    [29448] = true, -- Thaddius (1)
    [29615] = true, -- Noth the Plaguebringer (1)
    [29701] = true, -- Heigan the Unclean (1)
    [29718] = true, -- Loatheb (1)
    [29955] = true, -- Gothik the Harvester (1)
    [29991] = true, -- Sapphiron (1)
    [30061] = true, -- Kel'Thuzad (1)
    -- [30449] = true, -- Vesperon
    -- [30451] = true, -- Shadron
    -- [30452] = true, -- Tenebron
    [31125] = true, -- Archavon the Stone Watcher
    [31311] = true, -- Sartharion (1)
    -- [31520] = true, -- Shadron (1)
    -- [31534] = true, -- Tenebron (1)
    -- [31535] = true, -- Vesperon (1)
    [31722] = true, -- Archavon the Stone Watcher (1)
    [31734] = true, -- Malygos
    [32845] = true, -- Hodir
    [32846] = true, -- Hodir (1)
    [32857] = true, -- Stormcaller Brundir
    [32865] = true, -- Thorim
    [32867] = true, -- Steelbreaker
    [32871] = true, -- Algalon the Observer
    [32906] = true, -- Freya
    [32927] = true, -- Runemaster Molgeim
    [32930] = true, -- Kologarn
    [33070] = true, -- Algalon the Observer (1)
    [33113] = true, -- Flame Leviathan
    [33118] = true, -- Ignis the Furnace Master
    [33147] = true, -- Thorim (1)
    [33186] = true, -- Razorscale
    [33190] = true, -- Ignis the Furnace Master (1)
    [33271] = true, -- General Vezax
    [33288] = true, -- Yogg-Saron
    [33293] = true, -- XT-002 Deconstructor
    [33360] = true, -- Freya (1)
    [33432] = true, -- Leviathan Mk II
    [33449] = true, -- General Vezax (1)
    [33515] = true, -- Auriaya
    -- [33651] = true, -- VX-001
    -- [33670] = true, -- Aerial Command Unit
    [33692] = true, -- Runemaster Molgeim (1)
    [33693] = true, -- Steelbreaker (1)
    [33694] = true, -- Stormcaller Brundir (1)
    [33724] = true, -- Razorscale (1)
    [33885] = true, -- XT-002 Deconstructor (1)
    [33909] = true, -- Kologarn (1)
    [33955] = true, -- Yogg-Saron (1)
    [33993] = true, -- Emalon the Storm Watcher
    [33994] = true, -- Emalon the Storm Watcher (1)
    [34003] = true, -- Flame Leviathan (1)
    [34106] = true, -- Leviathan Mk II (1)
    -- [34108] = true, -- VX-001 (1)
    -- [34109] = true, -- Aerial Command Unit (1)
    [34175] = true, -- Auriaya (1)
    -- [34441] = true, -- Vivienne Blackwhisper
    -- [34442] = true, -- Vivienne Blackwhisper (1)
    -- [34443] = true, -- Vivienne Blackwhisper (2)
    -- [34444] = true, -- Thrakgar
    -- [34445] = true, -- Liandra Suncaller
    -- [34447] = true, -- Caiphus the Stern
    -- [34448] = true, -- Ruj'kah
    -- [34449] = true, -- Ginselle Blightslinger
    -- [34450] = true, -- Harkzog
    -- [34451] = true, -- Birana Stormhoof
    -- [34453] = true, -- Narrhok Steelbreaker
    -- [34454] = true, -- Maz'dinah
    -- [34455] = true, -- Broln Stouthorn
    -- [34456] = true, -- Malithas Brightblade
    -- [34458] = true, -- Gorgrim Shadowcleave
    -- [34459] = true, -- Erin Misthoof
    -- [34460] = true, -- Kavina Grovesong
    -- [34461] = true, -- Tyrius Duskblade
    -- [34463] = true, -- Shaabad
    -- [34465] = true, -- Velanaa
    -- [34466] = true, -- Anthar Forgemender
    -- [34467] = true, -- Alyssia Moonstalker
    -- [34468] = true, -- Noozle Whizzlestick
    -- [34469] = true, -- Melador Valestrider
    -- [34470] = true, -- Saamul
    -- [34471] = true, -- Baelnor Lightbearer
    -- [34472] = true, -- Irieth Shadowstep
    -- [34474] = true, -- Serissa Grimdabbler
    -- [34475] = true, -- Shocuul
    -- [34496] = true, -- Eydis Darkbane
    [34497] = true, -- Fjola Lightbane
    [34564] = true, -- Anub'arak
    [34566] = true, -- Anub'arak (1)
    [34780] = true, -- Lord Jaraxxus
    -- [34796] = true, -- Gormok the Impaler
    [34797] = true, -- Icehowl
    -- [34799] = true, -- Dreadscale
    [35013] = true, -- Koralon the Flame Watcher
    -- [35144] = true, -- Acidmaw
    [35216] = true, -- Lord Jaraxxus (1)
    [35268] = true, -- Lord Jaraxxus (2)
    [35269] = true, -- Lord Jaraxxus (3)
    -- [35347] = true, -- Eydis Darkbane (1)
    -- [35348] = true, -- Eydis Darkbane (2)
    -- [35349] = true, -- Eydis Darkbane (3)
    [35350] = true, -- Fjola Lightbane (1)
    [35351] = true, -- Fjola Lightbane (2)
    [35352] = true, -- Fjola Lightbane (3)
    [35360] = true, -- Koralon the Flame Watcher (1)
    -- [35438] = true, -- Gormok the Impaler (1)
    -- [35439] = true, -- Gormok the Impaler (2)
    -- [35440] = true, -- Gormok the Impaler (3)
    [35447] = true, -- Icehowl (1)
    [35448] = true, -- Icehowl (2)
    [35449] = true, -- Icehowl (3)
    -- [35511] = true, -- Acidmaw (1)
    -- [35512] = true, -- Acidmaw (2)
    -- [35513] = true, -- Acidmaw (3)
    -- [35514] = true, -- Dreadscale (1)
    -- [35515] = true, -- Dreadscale (2)
    -- [35516] = true, -- Dreadscale (3)
    [35615] = true, -- Anub'arak (2)
    [35616] = true, -- Anub'arak (3)
    -- [35662] = true, -- Alyssia Moonstalker (1)
    -- [35663] = true, -- Alyssia Moonstalker (2)
    -- [35664] = true, -- Alyssia Moonstalker (3)
    -- [35665] = true, -- Anthar Forgemender (1)
    -- [35666] = true, -- Anthar Forgemender (2)
    -- [35667] = true, -- Anthar Forgemender (3)
    -- [35668] = true, -- Baelnor Lightbearer (1)
    -- [35669] = true, -- Baelnor Lightbearer (2)
    -- [35670] = true, -- Baelnor Lightbearer (3)
    -- [35671] = true, -- Birana Stormhoof (1)
    -- [35672] = true, -- Birana Stormhoof (2)
    -- [35673] = true, -- Birana Stormhoof (3)
    -- [35680] = true, -- Broln Stouthorn (1)
    -- [35681] = true, -- Broln Stouthorn (2)
    -- [35682] = true, -- Broln Stouthorn (3)
    -- [35683] = true, -- Caiphus the Stern (1)
    -- [35684] = true, -- Caiphus the Stern (2)
    -- [35685] = true, -- Caiphus the Stern (3)
    -- [35686] = true, -- Erin Misthoof (1)
    -- [35687] = true, -- Erin Misthoof (2)
    -- [35688] = true, -- Erin Misthoof (3)
    -- [35689] = true, -- Ginselle Blightslinger (1)
    -- [35690] = true, -- Ginselle Blightslinger (2)
    -- [35691] = true, -- Ginselle Blightslinger (3)
    -- [35692] = true, -- Gorgrim Shadowcleave (1)
    -- [35693] = true, -- Gorgrim Shadowcleave (2)
    -- [35694] = true, -- Gorgrim Shadowcleave (3)
    -- [35695] = true, -- Harkzog (1)
    -- [35696] = true, -- Harkzog (2)
    -- [35697] = true, -- Harkzog (3)
    -- [35699] = true, -- Irieth Shadowstep (1)
    -- [35700] = true, -- Irieth Shadowstep (2)
    -- [35701] = true, -- Irieth Shadowstep (3)
    -- [35702] = true, -- Kavina Grovesong (1)
    -- [35703] = true, -- Kavina Grovesong (2)
    -- [35704] = true, -- Kavina Grovesong (3)
    -- [35705] = true, -- Liandra Suncaller (1)
    -- [35706] = true, -- Liandra Suncaller (2)
    -- [35707] = true, -- Liandra Suncaller (3)
    -- [35708] = true, -- Malithas Brightblade (1)
    -- [35709] = true, -- Malithas Brightblade (2)
    -- [35710] = true, -- Malithas Brightblade (3)
    -- [35711] = true, -- Maz'dinah (1)
    -- [35712] = true, -- Maz'dinah (2)
    -- [35713] = true, -- Maz'dinah (3)
    -- [35714] = true, -- Melador Valestrider (1)
    -- [35715] = true, -- Melador Valestrider (2)
    -- [35716] = true, -- Melador Valestrider (3)
    -- [35718] = true, -- Narrhok Steelbreaker (1)
    -- [35719] = true, -- Narrhok Steelbreaker (2)
    -- [35720] = true, -- Narrhok Steelbreaker (3)
    -- [35721] = true, -- Noozle Whizzlestick (1)
    -- [35722] = true, -- Noozle Whizzlestick (2)
    -- [35723] = true, -- Noozle Whizzlestick (3)
    -- [35724] = true, -- Ruj'kah (1)
    -- [35725] = true, -- Ruj'kah (2)
    -- [35726] = true, -- Ruj'kah (3)
    -- [35728] = true, -- Saamul (1)
    -- [35729] = true, -- Saamul (2)
    -- [35730] = true, -- Saamul (3)
    -- [35731] = true, -- Serissa Grimdabbler (1)
    -- [35732] = true, -- Serissa Grimdabbler (2)
    -- [35733] = true, -- Serissa Grimdabbler (3)
    -- [35734] = true, -- Shaabad (1)
    -- [35735] = true, -- Shaabad (2)
    -- [35736] = true, -- Shaabad (3)
    -- [35737] = true, -- Shocuul (1)
    -- [35738] = true, -- Shocuul (2)
    -- [35739] = true, -- Shocuul (3)
    -- [35740] = true, -- Thrakgar (1)
    -- [35741] = true, -- Thrakgar (2)
    -- [35742] = true, -- Thrakgar (3)
    -- [35743] = true, -- Tyrius Duskblade (1)
    -- [35744] = true, -- Tyrius Duskblade (2)
    -- [35745] = true, -- Tyrius Duskblade (3)
    -- [35746] = true, -- Velanaa (1)
    -- [35747] = true, -- Velanaa (2)
    -- [35748] = true, -- Velanaa (3)
    -- [35749] = true, -- Vivienne Blackwhisper (3)
    [36538] = true, -- Onyxia (1)
    [36597] = true, -- The Lich King
    [36612] = true, -- Lord Marrowgar
    [36626] = true, -- Festergut
    [36627] = true, -- Rotface
    [36678] = true, -- Professor Putricide
    [36855] = true, -- Lady Deathwhisper
    -- [36899] = true, -- Big Ooze
    -- [36939] = true, -- High Overlord Saurfang
    -- [36948] = true, -- Muradin Bronzebeard
    [37504] = true, -- Festergut (1)
    [37505] = true, -- Festergut (2)
    [37506] = true, -- Festergut (3)
    -- [37562] = true, -- Gas Cloud
    [37813] = true, -- Deathbringer Saurfang
    [37955] = true, -- Blood-Queen Lana'thel
    [37957] = true, -- Lord Marrowgar (1)
    [37958] = true, -- Lord Marrowgar (2)
    [37959] = true, -- Lord Marrowgar (3)
    -- [37970] = true, -- Prince Valanar
    [37972] = true, -- Prince Keleseth
    -- [37973] = true, -- Prince Taldaram
    [38106] = true, -- Lady Deathwhisper (1)
    -- [38123] = true, -- Big Ooze (1)
    -- [38156] = true, -- High Overlord Saurfang (1)
    -- [38157] = true, -- Muradin Bronzebeard (1)
    [38216] = true, -- Mutated Professor Putricide
    [38296] = true, -- Lady Deathwhisper (2)
    [38297] = true, -- Lady Deathwhisper (3)
    [38390] = true, -- Rotface (1)
    [38399] = true, -- Prince Keleseth (1)
    -- [38400] = true, -- Prince Taldaram (1)
    -- [38401] = true, -- Prince Valanar (1)
    [38402] = true, -- Deathbringer Saurfang (1)
    [38431] = true, -- Professor Putricide (1)
    [38433] = true, -- Toravon the Ice Watcher
    [38434] = true, -- Blood-Queen Lana'thel (1)
    [38435] = true, -- Blood-Queen Lana'thel (2)
    [38436] = true, -- Blood-Queen Lana'thel (3)
    [38462] = true, -- Toravon the Ice Watcher (1)
    [38549] = true, -- Rotface (2)
    [38550] = true, -- Rotface (3)
    [38582] = true, -- Deathbringer Saurfang (2)
    [38583] = true, -- Deathbringer Saurfang (3)
    [38585] = true, -- Professor Putricide (2)
    [38586] = true, -- Professor Putricide (3)
    -- [38602] = true, -- Gas Cloud (1)
    -- [38637] = true, -- High Overlord Saurfang (2)
    -- [38638] = true, -- High Overlord Saurfang (3)
    -- [38639] = true, -- Muradin Bronzebeard (2)
    -- [38640] = true, -- Muradin Bronzebeard (3)
    -- [38760] = true, -- Gas Cloud (2)
    -- [38761] = true, -- Gas Cloud (3)
    [38769] = true, -- Prince Keleseth (2)
    [38770] = true, -- Prince Keleseth (3)
    -- [38771] = true, -- Prince Taldaram (2)
    -- [38772] = true, -- Prince Taldaram (3)
    -- [38784] = true, -- Prince Valanar (2)
    -- [38785] = true, -- Prince Valanar (3)
    -- [38883] = true, -- ScottG Test
    [39166] = true, -- The Lich King (1)
    [39167] = true, -- The Lich King (2)
    [39168] = true, -- The Lich King (3)
    -- [39231] = true, -- The Lich King (Temp)
    -- [39232] = true, -- The Lich King (Temp) (1)
    -- [39233] = true, -- The Lich King (Temp) (2)
    -- [39234] = true, -- The Lich King (Temp) (3)
    [39863] = true, -- Halion
    [39864] = true, -- Halion (1)
    [39944] = true, -- Halion (2)
    [39945] = true, -- Halion (3)
    [40142] = true, -- Halion
    [40143] = true, -- Halion (1)
    [40144] = true, -- Halion (2)
    [40145] = true, -- Halion (3)
------------------------------
--  TBC
------------------------------
    -- [1748] = true, -- Highlord Bolvar Fordragon
    [12397] = true, -- Lord Kazzak
    [15550] = true, -- Attumen the Huntsman
    [15608] = true, -- Medivh
    [15687] = true, -- Moroes
    [15690] = true, -- Prince Malchezaar
    [15691] = true, -- The Curator
    -- [16151] = true, -- Midnight
    [16152] = true, -- Attumen the Huntsman
    [16457] = true, -- Maiden of Virtue
    [16524] = true, -- Shade of Aran
    -- [16563] = true, -- Warchief Blackhand UNUSED
    -- [16581] = true, -- King Llane UNUSED
    -- [16775] = true, -- Spirit of Mograine
    -- [17161] = true, -- Blizzard (Shade of Aran)
    [17225] = true, -- Nightbane
    -- [17256] = true, -- Hellfire Channeler
    [17257] = true, -- Magtheridon
    [17521] = true, -- The Big Bad Wolf
    -- [17533] = true, -- Romulo
    [17534] = true, -- Julianne
    [17535] = true, -- Dorothee
    [17711] = true, -- Doomwalker
    [17767] = true, -- Rage Winterchill
    -- [17772] = true, -- Lady Jaina Proudmoore
    [17808] = true, -- Anetheron
    [17842] = true, -- Azgalor
    -- [17852] = true, -- Thrall
    [17888] = true, -- Kaz'rogal
    -- [17948] = true, -- Tyrande Whisperwind
    -- [17949] = true, -- Malfurion Stormrage
    [17968] = true, -- Archimonde
    -- [18040] = true, -- Lich
    -- [18041] = true, -- Doomguard Lord
    -- [18060] = true, -- Fel Reaver Netherstorm
    -- [18075] = true, -- Mannoroth
    -- [18076] = true, -- Grom Hellscream
    -- [18141] = true, -- Greatmother Geyah
    -- [18168] = true, -- The Crone
    -- [18412] = true, -- Cyclone (The Crone)
    -- [18624] = true, -- Unkillable Test Dummy 73 Warrior
    [18728] = true, -- Doom Lord Kazzak
    -- [18780] = true, -- The Curator Transform Visual
    [18805] = true, -- High Astromancer Solarian
    [18831] = true, -- High King Maulgar
    -- [18832] = true, -- Krosh Firehand
    -- [18834] = true, -- Olm the Summoner
    -- [18835] = true, -- Kiggler the Crazed
    -- [18836] = true, -- Blindeye the Seer
    -- [18847] = true, -- Wild Fel Stalker
    [19044] = true, -- Gruul the Dragonkiller
    [19514] = true, -- Al'ar
    [19516] = true, -- Void Reaver
    -- [19556] = true, -- Thrall
    -- [19597] = true, -- Thrall's Hero Music
    [19622] = true, -- Kael'thas Sunstrider
    -- [19647] = true, -- Thrall
    -- [20060] = true, -- Lord Sanguinar
    -- [20062] = true, -- Grand Astromancer Capernian
    -- [20063] = true, -- Master Engineer Telonicus
    -- [20064] = true, -- Thaladred the Darkener
    -- [20602] = true, -- Flame Patch (Al'ar)
    -- [21003] = true, -- QA Test Dummy 73 Raid Debuff (High Armor)
    [21174] = true, -- Magtheridon
    [21212] = true, -- Lady Vashj
    [21213] = true, -- Morogrim Tidewalker
    [21214] = true, -- Fathom-Lord Karathress
    [21215] = true, -- Leotheras the Blind
    [21216] = true, -- Hydross the Unstable
    [21217] = true, -- The Lurker Below
    [21845] = true, -- Leotheras the Blind
    -- [21875] = true, -- Shadow of Leotheras
    -- [22641] = true, -- Drek'Thar (1)
    -- [22644] = true, -- Vanndar Stormpike (1)
    [22841] = true, -- Shade of Akama
    [22856] = true, -- Reliquary of the Lost
    [22871] = true, -- Teron Gorefiend
    [22887] = true, -- High Warlord Naj'entus
    [22898] = true, -- Supremus
    [22917] = true, -- Illidan Stormrage
    [22947] = true, -- Mother Shahraz
    [22948] = true, -- Gurtogg Bloodboil
    -- [22949] = true, -- Gathios the Shatterer
    [22950] = true, -- High Nethermancer Zerevor
    -- [22951] = true, -- Lady Malande
    -- [22997] = true, -- Flame of Azzinoth
    [23054] = true, -- Kael'thas Sunstrider
    -- [23126] = true, -- [UNUSED] Boss Teron Gorefiend (Mounted)
    -- [23191] = true, -- Akama
    -- [23195] = true, -- Illidan Demon Form
    -- [23197] = true, -- Maiev Shadowsong
    -- [23418] = true, -- Essence of Suffering
    -- [23419] = true, -- Essence of Desire
    -- [23420] = true, -- Essence of Anger
    -- [23467] = true, -- Illidan Stormrage
    [23574] = true, -- Akil'zon
    [23576] = true, -- Nalorakk
    [23577] = true, -- Halazzi
    [23578] = true, -- Jan'alai
    -- [23812] = true, -- Lynx Spirit
    [23863] = true, -- Zul'jin
    -- [23877] = true, -- Amani Lynx Spirit
    -- [23878] = true, -- Amani Bear Spirit
    -- [23879] = true, -- Amani Dragonhawk Spirit
    -- [23880] = true, -- Amani Eagle Spirit
    -- [24144] = true, -- Halazzi
    [24232] = true, -- Highlord Tirion Fordring
    [24239] = true, -- Hex Lord Malacrass
    -- [24505] = true, -- Unkillable Test Dummy 73 Paladin
    [24850] = true, -- Kalecgos
    [24882] = true, -- Brutallus
    [24891] = true, -- Kalecgos
    [24892] = true, -- Sathrovarr the Corruptor
    [24895] = true, -- Madrigosa
    [25038] = true, -- Felmyst
    [25158] = true, -- Brutallus
    -- [25160] = true, -- Madrigosa
    -- [25165] = true, -- Lady Sacrolash
    [25166] = true, -- Grand Warlock Alythess
    [25315] = true, -- Kil'jaeden
    [25319] = true, -- Kalecgos
    [25741] = true, -- M'uru
    [25840] = true, -- Entropius
    -- [25960] = true, -- M'uru Sunwell
    -- [26246] = true, -- Prophet Velen
    -- [29075] = true, -- QA Test Dummy 73 Raid Debuff (Low Armor)
    -- [29179] = true, -- Leonid Barthalomew the Revered
}

for entry, shouldReset in pairs(CREATURE_CONFIG) do
    if shouldReset then
        RegisterCreatureEvent(entry, CREATURE_EVENT_ON_ENTER_COMBAT, OnCreatureEventOnEnterCombat)
        RegisterCreatureEvent(entry, CREATURE_EVENT_ON_RESET, OnCreatureEventOnReset)
    end
end
CREATURE_CONFIG = nil
