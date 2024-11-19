#ifndef DEF_RESETRAIDCOOLDOWNS_CREATURE_ENTRIES_H
#define DEF_RESETRAIDCOOLDOWNS_CREATURE_ENTRIES_H

namespace ModResetRaidCooldowns
{
    /**
     * @brief ALLOW_ENTRIES
     *
     * List of all creatures that should have their cooldowns reset
     * This is a HACK for creatures that do not use BossAI OnBeforeSetBossState
     *
     * The following functions use this:
     * - void OnUnitEnterCombat() override
     * - void OnUnitEnterEvadeMode() override
     *
     * The following creatures should be commented out:
     * - creatures with BossAI scripts
     *
     **/
    constexpr uint32 ALLOW_ENTRIES[] =
    {
        // ------------------------------
        // --  WRATH
        // ------------------------------
        // 10184, // Onyxia
        // 15928, // Thaddius
        // 15931, // Grobbulus
        // 15932, // Gluth
        // 15936, // Heigan the Unclean
        // 15952, // Maexxna
        // 15953, // Grand Widow Faerlina
        // 15954, // Noth the Plaguebringer
        // 15956, // Anub'Rekhan
        // 15989, // Sapphiron
        // 15990, // Kel'Thuzad
        // 16011, // Loatheb
        // 16028, // Patchwerk
        // 16060, // Gothik the Harvester
        28859, // Malygos
        // 28860, // Sartharion
        // 29249, // Anub'Rekhan (1)
        // 29268, // Grand Widow Faerlina (1)
        // 29278, // Maexxna (1)
        // 29324, // Patchwerk (1)
        // 29373, // Grobbulus (1)
        // 29417, // Gluth (1)
        // 29448, // Thaddius (1)
        // 29615, // Noth the Plaguebringer (1)
        // 29701, // Heigan the Unclean (1)
        // 29718, // Loatheb (1)
        // 29955, // Gothik the Harvester (1)
        // 29991, // Sapphiron (1)
        // 30061, // Kel'Thuzad (1)
        // 30449, // Vesperon
        // 30451, // Shadron
        // 30452, // Tenebron
        31125, // Archavon the Stone Watcher
        // 31311, // Sartharion (1)
        // 31520, // Shadron (1)
        // 31534, // Tenebron (1)
        // 31535, // Vesperon (1)
        // 31722, // Archavon the Stone Watcher (1)
        31734, // Malygos
        32845, // Hodir
        32846, // Hodir (1)
        // 32857, // Stormcaller Brundir // Iron Council: avoid mid-fight reset
        32865, // Thorim
        // 32867, // Steelbreaker // Iron Council: avoid mid-fight reset
        32871, // Algalon the Observer
        32906, // Freya
        // 32927, // Runemaster Molgeim  // Iron Council: avoid mid-fight reset
        32930, // Kologarn
        33070, // Algalon the Observer (1)
        33113, // Flame Leviathan
        33118, // Ignis the Furnace Master
        33147, // Thorim (1)
        33186, // Razorscale
        33190, // Ignis the Furnace Master (1)
        33271, // General Vezax
        33288, // Yogg-Saron
        33293, // XT-002 Deconstructor
        33360, // Freya (1)
        33432, // Leviathan Mk II
        33449, // General Vezax (1)
        33515, // Auriaya
        // 33651, // VX-001
        // 33670, // Aerial Command Unit
        // 33692, // Runemaster Molgeim (1) // Iron Council: avoid mid-fight reset
        // 33693, // Steelbreaker (1) // Iron Council: avoid mid-fight reset
        // 33694, // Stormcaller Brundir (1) // Iron Council: avoid mid-fight reset
        33724, // Razorscale (1)
        33885, // XT-002 Deconstructor (1)
        33909, // Kologarn (1)
        33955, // Yogg-Saron (1)
        33993, // Emalon the Storm Watcher
        33994, // Emalon the Storm Watcher (1)
        34003, // Flame Leviathan (1)
        34106, // Leviathan Mk II (1)
        // 34108, // VX-001 (1)
        // 34109, // Aerial Command Unit (1)
        34175, // Auriaya (1)
        // 34441, // Vivienne Blackwhisper
        // 34442, // Vivienne Blackwhisper (1)
        // 34443, // Vivienne Blackwhisper (2)
        // 34444, // Thrakgar
        // 34445, // Liandra Suncaller
        // 34447, // Caiphus the Stern
        // 34448, // Ruj'kah
        // 34449, // Ginselle Blightslinger
        // 34450, // Harkzog
        // 34451, // Birana Stormhoof
        // 34453, // Narrhok Steelbreaker
        // 34454, // Maz'dinah
        // 34455, // Broln Stouthorn
        // 34456, // Malithas Brightblade
        // 34458, // Gorgrim Shadowcleave
        // 34459, // Erin Misthoof
        // 34460, // Kavina Grovesong
        // 34461, // Tyrius Duskblade
        // 34463, // Shaabad
        // 34465, // Velanaa
        // 34466, // Anthar Forgemender
        // 34467, // Alyssia Moonstalker
        // 34468, // Noozle Whizzlestick
        // 34469, // Melador Valestrider
        // 34470, // Saamul
        // 34471, // Baelnor Lightbearer
        // 34472, // Irieth Shadowstep
        // 34474, // Serissa Grimdabbler
        // 34475, // Shocuul
        // 34496, // Eydis Darkbane
        34497, // Fjola Lightbane
        34564, // Anub'arak
        34566, // Anub'arak (1)
        34780, // Lord Jaraxxus
        // 34796, // Gormok the Impaler
        34797, // Icehowl
        // 34799, // Dreadscale
        35013, // Koralon the Flame Watcher
        // 35144, // Acidmaw
        35216, // Lord Jaraxxus (1)
        35268, // Lord Jaraxxus (2)
        35269, // Lord Jaraxxus (3)
        // 35347, // Eydis Darkbane (1)
        // 35348, // Eydis Darkbane (2)
        // 35349, // Eydis Darkbane (3)
        35350, // Fjola Lightbane (1)
        35351, // Fjola Lightbane (2)
        35352, // Fjola Lightbane (3)
        35360, // Koralon the Flame Watcher (1)
        // 35438, // Gormok the Impaler (1)
        // 35439, // Gormok the Impaler (2)
        // 35440, // Gormok the Impaler (3)
        35447, // Icehowl (1)
        35448, // Icehowl (2)
        35449, // Icehowl (3)
        // 35511, // Acidmaw (1)
        // 35512, // Acidmaw (2)
        // 35513, // Acidmaw (3)
        // 35514, // Dreadscale (1)
        // 35515, // Dreadscale (2)
        // 35516, // Dreadscale (3)
        35615, // Anub'arak (2)
        35616, // Anub'arak (3)
        // 35662, // Alyssia Moonstalker (1)
        // 35663, // Alyssia Moonstalker (2)
        // 35664, // Alyssia Moonstalker (3)
        // 35665, // Anthar Forgemender (1)
        // 35666, // Anthar Forgemender (2)
        // 35667, // Anthar Forgemender (3)
        // 35668, // Baelnor Lightbearer (1)
        // 35669, // Baelnor Lightbearer (2)
        // 35670, // Baelnor Lightbearer (3)
        // 35671, // Birana Stormhoof (1)
        // 35672, // Birana Stormhoof (2)
        // 35673, // Birana Stormhoof (3)
        // 35680, // Broln Stouthorn (1)
        // 35681, // Broln Stouthorn (2)
        // 35682, // Broln Stouthorn (3)
        // 35683, // Caiphus the Stern (1)
        // 35684, // Caiphus the Stern (2)
        // 35685, // Caiphus the Stern (3)
        // 35686, // Erin Misthoof (1)
        // 35687, // Erin Misthoof (2)
        // 35688, // Erin Misthoof (3)
        // 35689, // Ginselle Blightslinger (1)
        // 35690, // Ginselle Blightslinger (2)
        // 35691, // Ginselle Blightslinger (3)
        // 35692, // Gorgrim Shadowcleave (1)
        // 35693, // Gorgrim Shadowcleave (2)
        // 35694, // Gorgrim Shadowcleave (3)
        // 35695, // Harkzog (1)
        // 35696, // Harkzog (2)
        // 35697, // Harkzog (3)
        // 35699, // Irieth Shadowstep (1)
        // 35700, // Irieth Shadowstep (2)
        // 35701, // Irieth Shadowstep (3)
        // 35702, // Kavina Grovesong (1)
        // 35703, // Kavina Grovesong (2)
        // 35704, // Kavina Grovesong (3)
        // 35705, // Liandra Suncaller (1)
        // 35706, // Liandra Suncaller (2)
        // 35707, // Liandra Suncaller (3)
        // 35708, // Malithas Brightblade (1)
        // 35709, // Malithas Brightblade (2)
        // 35710, // Malithas Brightblade (3)
        // 35711, // Maz'dinah (1)
        // 35712, // Maz'dinah (2)
        // 35713, // Maz'dinah (3)
        // 35714, // Melador Valestrider (1)
        // 35715, // Melador Valestrider (2)
        // 35716, // Melador Valestrider (3)
        // 35718, // Narrhok Steelbreaker (1)
        // 35719, // Narrhok Steelbreaker (2)
        // 35720, // Narrhok Steelbreaker (3)
        // 35721, // Noozle Whizzlestick (1)
        // 35722, // Noozle Whizzlestick (2)
        // 35723, // Noozle Whizzlestick (3)
        // 35724, // Ruj'kah (1)
        // 35725, // Ruj'kah (2)
        // 35726, // Ruj'kah (3)
        // 35728, // Saamul (1)
        // 35729, // Saamul (2)
        // 35730, // Saamul (3)
        // 35731, // Serissa Grimdabbler (1)
        // 35732, // Serissa Grimdabbler (2)
        // 35733, // Serissa Grimdabbler (3)
        // 35734, // Shaabad (1)
        // 35735, // Shaabad (2)
        // 35736, // Shaabad (3)
        // 35737, // Shocuul (1)
        // 35738, // Shocuul (2)
        // 35739, // Shocuul (3)
        // 35740, // Thrakgar (1)
        // 35741, // Thrakgar (2)
        // 35742, // Thrakgar (3)
        // 35743, // Tyrius Duskblade (1)
        // 35744, // Tyrius Duskblade (2)
        // 35745, // Tyrius Duskblade (3)
        // 35746, // Velanaa (1)
        // 35747, // Velanaa (2)
        // 35748, // Velanaa (3)
        // 35749, // Vivienne Blackwhisper (3)
        // 36538, // Onyxia (1)
        // 36597, // The Lich King
        // 36612, // Lord Marrowgar
        // 36626, // Festergut
        // 36627, // Rotface
        // 36678, // Professor Putricide
        // 36855, // Lady Deathwhisper
        // 36899, // Big Ooze
        // 36939, // High Overlord Saurfang
        // 36948, // Muradin Bronzebeard
        // 37504, // Festergut (1)
        // 37505, // Festergut (2)
        // 37506, // Festergut (3)
        // 37562, // Gas Cloud
        // 37813, // Deathbringer Saurfang
        // 37955, // Blood-Queen Lana'thel
        // 37957, // Lord Marrowgar (1)
        // 37958, // Lord Marrowgar (2)
        // 37959, // Lord Marrowgar (3)
        // 37970, // Prince Valanar
        // 37972, // Prince Keleseth
        // 37973, // Prince Taldaram
        // 38106, // Lady Deathwhisper (1)
        // 38123, // Big Ooze (1)
        // 38156, // High Overlord Saurfang (1)
        // 38157, // Muradin Bronzebeard (1)
        // 38216, // Mutated Professor Putricide
        // 38296, // Lady Deathwhisper (2)
        // 38297, // Lady Deathwhisper (3)
        // 38390, // Rotface (1)
        // 38399, // Prince Keleseth (1)
        // 38400, // Prince Taldaram (1)
        // 38401, // Prince Valanar (1)
        // 38402, // Deathbringer Saurfang (1)
        // 38431, // Professor Putricide (1)
        // 38433, // Toravon the Ice Watcher
        // 38434, // Blood-Queen Lana'thel (1)
        // 38435, // Blood-Queen Lana'thel (2)
        // 38436, // Blood-Queen Lana'thel (3)
        38462, // Toravon the Ice Watcher (1)
        // 38549, // Rotface (2)
        // 38550, // Rotface (3)
        // 38582, // Deathbringer Saurfang (2)
        // 38583, // Deathbringer Saurfang (3)
        // 38585, // Professor Putricide (2)
        // 38586, // Professor Putricide (3)
        // 38602, // Gas Cloud (1)
        // 38637, // High Overlord Saurfang (2)
        // 38638, // High Overlord Saurfang (3)
        // 38639, // Muradin Bronzebeard (2)
        // 38640, // Muradin Bronzebeard (3)
        // 38760, // Gas Cloud (2)
        // 38761, // Gas Cloud (3)
        // 38769, // Prince Keleseth (2)
        // 38770, // Prince Keleseth (3)
        // 38771, // Prince Taldaram (2)
        // 38772, // Prince Taldaram (3)
        // 38784, // Prince Valanar (2)
        // 38785, // Prince Valanar (3)
        // 38883, // ScottG Test
        // 39166, // The Lich King (1)
        // 39167, // The Lich King (2)
        // 39168, // The Lich King (3)
        // 39231, // The Lich King (Temp)
        // 39232, // The Lich King (Temp) (1)
        // 39233, // The Lich King (Temp) (2)
        // 39234, // The Lich King (Temp) (3)
        // 39863, // Halion
        // 39864, // Halion (1)
        // 39944, // Halion (2)
        // 39945, // Halion (3)
        // 40142, // Halion
        // 40143, // Halion (1)
        // 40144, // Halion (2)
        // 40145, // Halion (3)
        // ------------------------------
        // --  TBC
        // ------------------------------
        // 1748, // Highlord Bolvar Fordragon
        12397, // Lord Kazzak
        // 15550, // Attumen the Huntsman
        // 15608, // Medivh
        // 15687, // Moroes
        // 15690, // Prince Malchezaar
        // 15691, // The Curator
        // 16151, // Midnight
        // 16152, // Attumen the Huntsman
        // 16457, // Maiden of Virtue
        // 16524, // Shade of Aran
        // 16563, // Warchief Blackhand UNUSED
        // 16581, // King Llane UNUSED
        // 16775, // Spirit of Mograine
        // 17161, // Blizzard (Shade of Aran)
        // 17225, // Nightbane
        // 17256, // Hellfire Channeler
        // 17257, // Magtheridon
        // 17521, // The Big Bad Wolf
        // 17533, // Romulo
        // 17534, // Julianne
        // 17535, // Dorothee
        17711, // Doomwalker
        // 17767, // Rage Winterchill
        // 17772, // Lady Jaina Proudmoore
        // 17808, // Anetheron
        // 17842, // Azgalor
        // 17852, // Thrall
        // 17888, // Kaz'rogal
        // 17948, // Tyrande Whisperwind
        // 17949, // Malfurion Stormrage
        // 17968, // Archimonde
        // 18040, // Lich
        // 18041, // Doomguard Lord
        // 18060, // Fel Reaver Netherstorm
        // 18075, // Mannoroth
        // 18076, // Grom Hellscream
        // 18141, // Greatmother Geyah
        // 18168, // The Crone
        // 18412, // Cyclone (The Crone)
        // 18624, // Unkillable Test Dummy 73 Warrior
        18728, // Doom Lord Kazzak
        // 18780, // The Curator Transform Visual
        // 18805, // High Astromancer Solarian
        // 18831, // High King Maulgar
        // 18832, // Krosh Firehand
        // 18834, // Olm the Summoner
        // 18835, // Kiggler the Crazed
        // 18836, // Blindeye the Seer
        // 18847, // Wild Fel Stalker
        // 19044, // Gruul the Dragonkiller
        // 19514, // Al'ar
        // 19516, // Void Reaver
        // 19556, // Thrall
        // 19597, // Thrall's Hero Music
        // 19622, // Kael'thas Sunstrider
        // 19647, // Thrall
        // 20060, // Lord Sanguinar
        // 20062, // Grand Astromancer Capernian
        // 20063, // Master Engineer Telonicus
        // 20064, // Thaladred the Darkener
        // 20602, // Flame Patch (Al'ar)
        // 21003, // QA Test Dummy 73 Raid Debuff (High Armor)
        // 21174, // Magtheridon
        // 21212, // Lady Vashj
        // 21213, // Morogrim Tidewalker
        // 21214, // Fathom-Lord Karathress
        // 21215, // Leotheras the Blind
        // 21216, // Hydross the Unstable
        // 21217, // The Lurker Below
        // 21845, // Leotheras the Blind
        // 21875, // Shadow of Leotheras
        // 22641, // Drek'Thar (1)
        // 22644, // Vanndar Stormpike (1)
        // 22841, // Shade of Akama
        // 22856, // Reliquary of the Lost
        // 22871, // Teron Gorefiend
        // 22887, // High Warlord Naj'entus
        // 22898, // Supremus
        // 22917, // Illidan Stormrage
        // 22947, // Mother Shahraz
        // 22948, // Gurtogg Bloodboil
        // 22949, // Gathios the Shatterer
        // 22950, // High Nethermancer Zerevor
        // 22951, // Lady Malande
        // 22997, // Flame of Azzinoth
        // 23054, // Kael'thas Sunstrider
        // 23126, // UNUSED Boss Teron Gorefiend (Mounted)
        // 23191, // Akama
        // 23195, // Illidan Demon Form
        // 23197, // Maiev Shadowsong
        // 23418, // Essence of Suffering
        // 23419, // Essence of Desire
        // 23420, // Essence of Anger
        // 23467, // Illidan Stormrage
        // 23574, // Akil'zon
        // 23576, // Nalorakk
        // 23577, // Halazzi
        // 23578, // Jan'alai
        // 23812, // Lynx Spirit
        // 23863, // Zul'jin
        // 23877, // Amani Lynx Spirit
        // 23878, // Amani Bear Spirit
        // 23879, // Amani Dragonhawk Spirit
        // 23880, // Amani Eagle Spirit
        // 24144, // Halazzi
        // 24232, // Highlord Tirion Fordring
        // 24239, // Hex Lord Malacrass
        // 24505, // Unkillable Test Dummy 73 Paladin
        // 24850, // Kalecgos
        // 24882, // Brutallus
        // 24891, // Kalecgos
        // 24892, // Sathrovarr the Corruptor
        // 24895, // Madrigosa
        // 25038, // Felmyst
        // 25158, // Brutallus
        // 25160, // Madrigosa
        // 25165, // Lady Sacrolash
        // 25166, // Grand Warlock Alythess
        // 25315, // Kil'jaeden
        // 25319, // Kalecgos
        // 25741, // M'uru
        // 25840, // Entropius
        // 25960, // M'uru Sunwell
        // 26246, // Prophet Velen
        // 29075, // QA Test Dummy 73 Raid Debuff (Low Armor)
        // 29179, // Leonid Barthalomew the Revered
    };

    /**
     * @brief DENY_CREDIT_ENTRIES
     *
     * List of all credit entries that should not reset cooldowns
     *
     * The following functions use this:
     * - void OnAfterUpdateEncounterState() override
     *
     * The following credits should be uncommented:
     * - credits that should not reset CDs
     *
     **/
    constexpr uint32 DENY_CREDIT_ENTRIES[] =
    {
        // 464, // Shadowfang Keep (33) Rethilgore
        // 465, // Shadowfang Keep (33) Razorclaw the Butcher
        // 466, // Shadowfang Keep (33) Baron Silverlaine
        // 467, // Shadowfang Keep (33) Commander Springvale
        // 468, // Shadowfang Keep (33) Odo the Blindwatcher
        // 469, // Shadowfang Keep (33) Fenrus the Devourer
        // 470, // Shadowfang Keep (33) Wolf Master Nandos
        // 471, // Shadowfang Keep (33) Archmage Arugal
        // 536, // Stormwind Stockade (34) Targorr the Dread
        // 537, // Stormwind Stockade (34) Kam Deepfury
        // 538, // Stormwind Stockade (34) Hamhock
        // 540, // Stormwind Stockade (34) Dextren Ward
        // 539, // Stormwind Stockade (34) Bazil Thredd
        // 161, // Deadmines (36) Rhahk'zor
        // 162, // Deadmines (36) Sneed
        // 163, // Deadmines (36) Gilnid
        // 164, // Deadmines (36) Mr. Smite
        // 165, // Deadmines (36) Cookie
        // 166, // Deadmines (36) Captain Greenskin
        // 167, // Deadmines (36) Edwin VanCleef
        // 585, // Wailing Caverns (43) Lady Anacondra
        // 586, // Wailing Caverns (43) Lord Cobrahn
        // 587, // Wailing Caverns (43) Kresh
        // 588, // Wailing Caverns (43) Lord Pythas
        // 589, // Wailing Caverns (43) Skum
        // 590, // Wailing Caverns (43) Lord Serpentis
        // 591, // Wailing Caverns (43) Verdan the Everliving
        // 592, // Wailing Caverns (43) Mutanus the Devourer
        // 440, // Razorfen Kraul (47) Death Speaker Jargba
        // 438, // Razorfen Kraul (47) Roogug
        // 439, // Razorfen Kraul (47) Aggem Thorncurse
        // 441, // Razorfen Kraul (47) Overlord Ramtusk
        // 883, // Razorfen Kraul (47) Agathelos the Raging
        // 443, // Razorfen Kraul (47) Charlga Razorflank
        // 219, // Blackfathom Deeps (48) Ghamoo-ra
        // 220, // Blackfathom Deeps (48) Lady Sarevess
        // 221, // Blackfathom Deeps (48) Gelihast
        // 222, // Blackfathom Deeps (48) Lorgus Jett
        // 224, // Blackfathom Deeps (48) Old Serra'kis
        // 225, // Blackfathom Deeps (48) Twilight Lord Kelris
        // 226, // Blackfathom Deeps (48) Aku'mai
        // 547, // Uldaman (70) Revelosh
        // 548, // Uldaman (70) The Lost Dwarves
        // 549, // Uldaman (70) Ironaya
        // 551, // Uldaman (70) Ancient Stone Keeper
        // 552, // Uldaman (70) Galgann Firehammer
        // 553, // Uldaman (70) Grimlok
        // 554, // Uldaman (70) Archaedas
        // 379, // Gnomeregan (90) Grubbis
        // 378, // Gnomeregan (90) Viscous Fallout
        // 380, // Gnomeregan (90) Electrocutioner 6000
        // 381, // Gnomeregan (90) Crowd Pummeler 9-60
        // 382, // Gnomeregan (90) Mekgineer Thermaplugg
        // 485, // Sunken Temple (109) Atal'alarion
        // 488, // Sunken Temple (109) Jammal'an the Prophet
        // 486, // Sunken Temple (109) Dreamscythe
        // 487, // Sunken Temple (109) Weaver
        // 490, // Sunken Temple (109) Morphaz
        // 491, // Sunken Temple (109) Hazzas
        // 492, // Sunken Temple (109) Avatar of Hakkar
        // 493, // Sunken Temple (109) Shade of Eranikus
        // 434, // Razorfen Downs (129) Tuten'kash
        // 435, // Razorfen Downs (129) Mordresh Fire Eye
        // 436, // Razorfen Downs (129) Glutton
        // 437, // Razorfen Downs (129) Amnennar the Coldbringer
        // 444, // Scarlet Monastery (189) Interrogator Vishas
        // 445, // Scarlet Monastery (189) Bloodmage Thalnos
        // 446, // Scarlet Monastery (189) Houndmaster Loksey
        // 447, // Scarlet Monastery (189) Arcanist Doan
        // 448, // Scarlet Monastery (189) Herod
        // 449, // Scarlet Monastery (189) High Inquisitor Fairbanks
        // 450, // Scarlet Monastery (189) High Inquisitor Whitemane
        // 593, // Zul'Farrak (209) Hydromancer Velratha
        // 594, // Zul'Farrak (209) Ghaz'rilla
        // 595, // Zul'Farrak (209) Antu'sul
        // 596, // Zul'Farrak (209) Theka the Martyr
        // 597, // Zul'Farrak (209) Witch Doctor Zum'rah
        // 598, // Zul'Farrak (209) Nekrum Gutchewer
        // 599, // Zul'Farrak (209) Shadowpriest Sezz'ziz
        // 600, // Zul'Farrak (209) Chief Ukorz Sandscalp
        // 267, // Blackrock Spire (229) Highlord Omokk
        // 268, // Blackrock Spire (229) Shadow Hunter Vosh'gajin
        // 269, // Blackrock Spire (229) War Master Voone
        // 270, // Blackrock Spire (229) Mother Smolderweb
        // 271, // Blackrock Spire (229) Urok Doomhowl
        // 272, // Blackrock Spire (229) Quartermaster Zigris
        // 274, // Blackrock Spire (229) Halycon
        // 273, // Blackrock Spire (229) Gizrul the Slavener
        // 275, // Blackrock Spire (229) Overlord Wyrmthalak
        // 276, // Blackrock Spire (229) Pyroguard Emberseer
        // 277, // Blackrock Spire (229) Solakar Flamewreath
        // 278, // Blackrock Spire (229) Warchief Rend Blackhand
        // 279, // Blackrock Spire (229) The Beast
        // 280, // Blackrock Spire (229) General Drakkisath
        // 227, // Blackrock Depths (230) High Interrogator Gerstahn
        // 228, // Blackrock Depths (230) Lord Roccor
        // 229, // Blackrock Depths (230) Houndmaster Grebmar
        // 230, // Blackrock Depths (230) Ring of Law
        // 231, // Blackrock Depths (230) Pyromancer Loregrain
        // 232, // Blackrock Depths (230) Lord Incendius
        // 233, // Blackrock Depths (230) Warder Stilgiss
        // 234, // Blackrock Depths (230) Fineous Darkvire
        // 235, // Blackrock Depths (230) Bael'Gar
        // 236, // Blackrock Depths (230) General Angerforge
        // 237, // Blackrock Depths (230) Golem Lord Argelmach
        // 238, // Blackrock Depths (230) Hurley Blackbreath
        // 239, // Blackrock Depths (230) Phalanx
        // 240, // Blackrock Depths (230) Ribbly Screwspigot
        // 241, // Blackrock Depths (230) Plugger Spazzring
        // 242, // Blackrock Depths (230) Ambassador Flamelash
        // 243, // Blackrock Depths (230) The Seven
        // 244, // Blackrock Depths (230) Magmus
        // 245, // Blackrock Depths (230) Emperor Dagran Thaurissan
        // 707, // Onyxia's Lair (249) Onyxia
        // 708, // Onyxia's Lair (249) Onyxia
        // 287, // Opening of the Dark Portal (269) Chrono Lord Deja
        // 288, // Opening of the Dark Portal (269) Chrono Lord Deja
        // 289, // Opening of the Dark Portal (269) Temporus
        // 290, // Opening of the Dark Portal (269) Temporus
        // 291, // Opening of the Dark Portal (269) Aeonus
        // 292, // Opening of the Dark Portal (269) Aeonus
        // 451, // Scholomance (289) Kirtonos the Herald
        // 452, // Scholomance (289) Jandice Barov
        // 453, // Scholomance (289) Rattlegore
        // 454, // Scholomance (289) Marduk Blackpool
        // 455, // Scholomance (289) Vectus
        // 456, // Scholomance (289) Ras Frostwhisper
        // 457, // Scholomance (289) Instructor Malicia
        // 458, // Scholomance (289) Doctor Theolen Krastinov
        // 459, // Scholomance (289) Lorekeeper Polkelt
        // 460, // Scholomance (289) The Ravenian
        // 461, // Scholomance (289) Lord Alexei Barov
        // 462, // Scholomance (289) Lady Illucia Barov
        // 463, // Scholomance (289) Darkmaster Gandling
        // 785, // Zul'Gurub (309) High Priestess Jeklik
        // 784, // Zul'Gurub (309) High Priest Venoxis
        // 786, // Zul'Gurub (309) High Priestess Mar'li
        // 787, // Zul'Gurub (309) Bloodlord Mandokir
        // 788, // Zul'Gurub (309) Edge of Madness
        // 789, // Zul'Gurub (309) High Priest Thekal
        // 790, // Zul'Gurub (309) Gahz'ranka
        // 791, // Zul'Gurub (309) High Priestess Arlokk
        // 792, // Zul'Gurub (309) Jin'do the Hexxer
        // 793, // Zul'Gurub (309) Hakkar
        // 473, // Stratholme (329) Hearthsinger Forresten
        // 474, // Stratholme (329) Timmy the Cruel
        // 475, // Stratholme (329) Cannon Master Willey
        // 476, // Stratholme (329) Malor the Zealous
        // 477, // Stratholme (329) Archivist Galford
        // 478, // Stratholme (329) Balnazzar
        // 472, // Stratholme (329) The Unforgiven
        // 479, // Stratholme (329) Baroness Anastari
        // 480, // Stratholme (329) Nerub'enkan
        // 481, // Stratholme (329) Maleki the Pallid
        // 482, // Stratholme (329) Magistrate Barthilas
        // 483, // Stratholme (329) Ramnstein the Gorger
        // 484, // Stratholme (329) Baron Rivendare
        // 422, // Maraudon (349) Noxxion
        // 423, // Maraudon (349) Razorlash
        // 424, // Maraudon (349) Lord Vyletongue
        // 425, // Maraudon (349) Celebras the Cursed
        // 426, // Maraudon (349) Landslide
        // 427, // Maraudon (349) Tinkerer Gizlock
        // 428, // Maraudon (349) Rotgrip
        // 429, // Maraudon (349) Princess Theradras
        // 430, // Ragefire Chasm (389) Oggleflint
        // 432, // Ragefire Chasm (389) Jergosh the Invoker
        // 433, // Ragefire Chasm (389) Bazzalan
        // 431, // Ragefire Chasm (389) Taragaman the Hungerer
        // 663, // Molten Core (409) Lucifron
        // 664, // Molten Core (409) Magmadar
        // 665, // Molten Core (409) Gehennas
        // 666, // Molten Core (409) Garr
        // 667, // Molten Core (409) Shazzrah
        // 668, // Molten Core (409) Baron Geddon
        // 669, // Molten Core (409) Sulfuron Harbinger
        // 670, // Molten Core (409) Golemagg the Incinerator
        // 671, // Molten Core (409) Majordomo Executus
        // 672, // Molten Core (409) Ragnaros
        // 343, // Dire Maul (429) Zevrim Thornhoof
        // 344, // Dire Maul (429) Hydrospawn
        // 345, // Dire Maul (429) Lethtendris
        // 346, // Dire Maul (429) Alzzin the Wildshaper
        // 350, // Dire Maul (429) Tendris Warpwood
        // 347, // Dire Maul (429) Illyanna Ravenoak
        // 348, // Dire Maul (429) Magister Kalendris
        // 349, // Dire Maul (429) Immol'thar
        // 361, // Dire Maul (429) Prince Tortheldrin
        // 362, // Dire Maul (429) Guard Mol'dar
        // 363, // Dire Maul (429) Stomper Kreeg
        // 364, // Dire Maul (429) Guard Fengus
        // 365, // Dire Maul (429) Guard Slip'kik
        // 366, // Dire Maul (429) Captain Kromcrush
        // 367, // Dire Maul (429) Cho'Rush the Observer
        // 368, // Dire Maul (429) King Gordok
        // 610, // Blackwing Lair (469) Razorgore the Untamed
        // 611, // Blackwing Lair (469) Vaelastrasz the Corrupt
        // 612, // Blackwing Lair (469) Broodlord Lashlayer
        // 613, // Blackwing Lair (469) Firemaw
        // 614, // Blackwing Lair (469) Ebonroc
        // 615, // Blackwing Lair (469) Flamegor
        // 616, // Blackwing Lair (469) Chromaggus
        // 617, // Blackwing Lair (469) Nefarian
        // 718, // Ruins of Ahn'Qiraj (509) Kurinnaxx
        // 719, // Ruins of Ahn'Qiraj (509) General Rajaxx
        // 720, // Ruins of Ahn'Qiraj (509) Moam
        // 721, // Ruins of Ahn'Qiraj (509) Buru the Gorger
        // 722, // Ruins of Ahn'Qiraj (509) Ayamiss the Hunter
        // 723, // Ruins of Ahn'Qiraj (509) Ossirian the Unscarred
        // 709, // Ahn'Qiraj Temple (531) The Prophet Skeram
        // 710, // Ahn'Qiraj Temple (531) Silithid Royalty
        // 711, // Ahn'Qiraj Temple (531) Battleguard Sartura
        // 712, // Ahn'Qiraj Temple (531) Fankriss the Unyielding
        // 713, // Ahn'Qiraj Temple (531) Viscidus
        // 714, // Ahn'Qiraj Temple (531) Princess Huhuran
        // 715, // Ahn'Qiraj Temple (531) Twin Emperors
        // 716, // Ahn'Qiraj Temple (531) Ouro
        // 717, // Ahn'Qiraj Temple (531) C'thun
        // 652, // Karazhan (532) Attumen the Huntsman
        // 653, // Karazhan (532) Moroes
        // 654, // Karazhan (532) Maiden of the Virtue
        // 655, // Karazhan (532) Opera Event
        // 656, // Karazhan (532) The Curator
        // 657, // Karazhan (532) Terestian Illhoof
        // 658, // Karazhan (532) Shade of Aran
        // 659, // Karazhan (532) Netherspite
        // 660, // Karazhan (532) Chess Event
        // 661, // Karazhan (532) Prince Malchezaar
        // 662, // Karazhan (532) Nightbane
        // 673, // Naxxramas (533) Anub'Rekhan
        // 674, // Naxxramas (533) Anub'Rekhan
        // 677, // Naxxramas (533) Grand Widow Faerlina
        // 678, // Naxxramas (533) Grand Widow Faerlina
        // 679, // Naxxramas (533) Maexxna
        // 680, // Naxxramas (533) Maexxna
        // 681, // Naxxramas (533) Noth the Plaguebringer
        // 682, // Naxxramas (533) Noth the Plaguebringer
        // 683, // Naxxramas (533) Heigan the Unclean
        // 684, // Naxxramas (533) Heigan the Unclean
        // 685, // Naxxramas (533) Loatheb
        // 686, // Naxxramas (533) Loatheb
        // 687, // Naxxramas (533) Instructor Razuvious
        // 689, // Naxxramas (533) Instructor Razuvious
        // 690, // Naxxramas (533) Gothik the Harvester
        // 691, // Naxxramas (533) Gothik the Harvester
        // 692, // Naxxramas (533) The Four Horsemen
        // 693, // Naxxramas (533) The Four Horsemen
        // 694, // Naxxramas (533) Patchwerk
        // 695, // Naxxramas (533) Patchwerk
        // 696, // Naxxramas (533) Grobbulus
        // 697, // Naxxramas (533) Grobbulus
        // 698, // Naxxramas (533) Gluth
        // 699, // Naxxramas (533) Gluth
        // 700, // Naxxramas (533) Thaddius
        // 701, // Naxxramas (533) Thaddius
        // 702, // Naxxramas (533) Sapphiron
        // 703, // Naxxramas (533) Sapphiron
        // 704, // Naxxramas (533) Kel'Thuzad
        // 706, // Naxxramas (533) Kel'Thuzad
        // 618, // The Battle for Mount Hyjal (534) Rage Winterchill
        // 619, // The Battle for Mount Hyjal (534) Anetheron
        // 620, // The Battle for Mount Hyjal (534) Kaz'rogal
        // 621, // The Battle for Mount Hyjal (534) Azgalor
        // 622, // The Battle for Mount Hyjal (534) Archimonde
        // 407, // Hellfire Citadel: The Shattered Halls (540) Grand Warlock Nethekurse
        // 408, // Hellfire Citadel: The Shattered Halls (540) Grand Warlock Nethekurse
        // 410, // Hellfire Citadel: The Shattered Halls (540) Warbringer O'mrogg
        // 409, // Hellfire Citadel: The Shattered Halls (540) Blood Guard Porung
        // 412, // Hellfire Citadel: The Shattered Halls (540) Warchief Kargath Bladefist
        // 411, // Hellfire Citadel: The Shattered Halls (540) Warbringer O'mrogg
        // 413, // Hellfire Citadel: The Shattered Halls (540) Warchief Kargath Bladefist
        // 401, // Hellfire Citadel: The Blood Furnace (542) The Maker
        // 402, // Hellfire Citadel: The Blood Furnace (542) The Maker
        // 403, // Hellfire Citadel: The Blood Furnace (542) Broggok
        // 404, // Hellfire Citadel: The Blood Furnace (542) Broggok
        // 405, // Hellfire Citadel: The Blood Furnace (542) Keli'dan the Breaker
        // 406, // Hellfire Citadel: The Blood Furnace (542) Keli'dan the Breaker
        // 392, // Hellfire Citadel: Ramparts (543) Watchkeeper Gargolmar
        // 393, // Hellfire Citadel: Ramparts (543) Watchkeeper Gargolmar
        // 394, // Hellfire Citadel: Ramparts (543) Omor the Unscarred
        // 395, // Hellfire Citadel: Ramparts (543) Omor the Unscarred
        // 396, // Hellfire Citadel: Ramparts (543) Vazruden the Herald
        // 397, // Hellfire Citadel: Ramparts (543) Vazruden the Herald
        // 651, // Magtheridon's Lair (544) Magtheridon
        // 314, // Coilfang: The Steamvault (545) Hydromancer Thespia
        // 315, // Coilfang: The Steamvault (545) Hydromancer Thespia
        // 316, // Coilfang: The Steamvault (545) Mekgineer Steamrigger
        // 317, // Coilfang: The Steamvault (545) Mekgineer Steamrigger
        // 318, // Coilfang: The Steamvault (545) Warlord Kalithresh
        // 319, // Coilfang: The Steamvault (545) Warlord Kalithresh
        // 320, // Coilfang: The Underbog (546) Hungarfen
        // 321, // Coilfang: The Underbog (546) Hungarfen
        // 322, // Coilfang: The Underbog (546) Ghaz'an
        // 323, // Coilfang: The Underbog (546) Ghaz'an
        // 329, // Coilfang: The Underbog (546) Swamplord Musel'ek
        // 330, // Coilfang: The Underbog (546) Swamplord Musel'ek
        // 331, // Coilfang: The Underbog (546) The Black Stalker
        // 332, // Coilfang: The Underbog (546) The Black Stalker
        // 301, // Coilfang: The Slave Pens (547) Mennu the Betrayer
        // 304, // Coilfang: The Slave Pens (547) Mennu the Betrayer
        // 302, // Coilfang: The Slave Pens (547) Rokmar the Crackler
        // 305, // Coilfang: The Slave Pens (547) Rokmar the Crackler
        // 303, // Coilfang: The Slave Pens (547) Quagmirran
        // 306, // Coilfang: The Slave Pens (547) Quagmirran
        // 623, // Coilfang: Serpentshrine Cavern (548) Hydross the Unstable
        // 624, // Coilfang: Serpentshrine Cavern (548) The Lurker Below
        // 625, // Coilfang: Serpentshrine Cavern (548) Leotheras the Blind
        // 626, // Coilfang: Serpentshrine Cavern (548) Fathom-Lord Karathress
        // 627, // Coilfang: Serpentshrine Cavern (548) Morogrim Tidewalker
        // 628, // Coilfang: Serpentshrine Cavern (548) Lady Vashj
        // 730, // Tempest Keep (550) Al'ar
        // 731, // Tempest Keep (550) Void Reaver
        // 732, // Tempest Keep (550) High Astromancer Solarian
        // 733, // Tempest Keep (550) Kael'thas Sunstrider
        // 494, // Tempest Keep: The Arcatraz (552) Zereketh the Unbound
        // 495, // Tempest Keep: The Arcatraz (552) Zereketh the Unbound
        // 496, // Tempest Keep: The Arcatraz (552) Dalliah the Doomsayer
        // 497, // Tempest Keep: The Arcatraz (552) Dalliah the Doomsayer
        // 498, // Tempest Keep: The Arcatraz (552) Wrath-Scryer Soccothrates
        // 499, // Tempest Keep: The Arcatraz (552) Wrath-Scryer Soccothrates
        // 500, // Tempest Keep: The Arcatraz (552) Harbinger Skyriss
        // 501, // Tempest Keep: The Arcatraz (552) Harbinger Skyriss
        // 502, // Tempest Keep: The Botanica (553) Commander Sarannis
        // 504, // Tempest Keep: The Botanica (553) Commander Sarannis
        // 505, // Tempest Keep: The Botanica (553) High Botanist Freywinn
        // 506, // Tempest Keep: The Botanica (553) High Botanist Freywinn
        // 507, // Tempest Keep: The Botanica (553) Thorngrin the Tender
        // 508, // Tempest Keep: The Botanica (553) Thorngrin the Tender
        // 509, // Tempest Keep: The Botanica (553) Laj
        // 510, // Tempest Keep: The Botanica (553) Laj
        // 511, // Tempest Keep: The Botanica (553) Warp Splinter
        // 512, // Tempest Keep: The Botanica (553) Warp Splinter
        // 513, // Tempest Keep: The Mechanar (554) Mechano-Lord Capacitus
        // 514, // Tempest Keep: The Mechanar (554) Mechano-Lord Capacitus
        // 515, // Tempest Keep: The Mechanar (554) Nethermancer Sepethrea
        // 516, // Tempest Keep: The Mechanar (554) Nethermancer Sepethrea
        // 517, // Tempest Keep: The Mechanar (554) Pathaleon the Calculator
        // 518, // Tempest Keep: The Mechanar (554) Pathaleon the Calculator
        // 208, // Auchindoun: Shadow Labyrinth (555) Ambassador Hellmaw
        // 255, // Auchindoun: Shadow Labyrinth (555) Ambassador Hellmaw
        // 209, // Auchindoun: Shadow Labyrinth (555) Blackheart the Inciter
        // 256, // Auchindoun: Shadow Labyrinth (555) Blackheart the Inciter
        // 210, // Auchindoun: Shadow Labyrinth (555) Grandmaster Vorpil
        // 257, // Auchindoun: Shadow Labyrinth (555) Grandmaster Vorpil
        // 211, // Auchindoun: Shadow Labyrinth (555) Murmur
        // 258, // Auchindoun: Shadow Labyrinth (555) Murmur
        // 206, // Auchindoun: Sethekk Halls (556) Darkweaver Syth
        // 252, // Auchindoun: Sethekk Halls (556) Darkweaver Syth
        // 207, // Auchindoun: Sethekk Halls (556) Talon King Ikiss
        // 253, // Auchindoun: Sethekk Halls (556) Anzu
        // 254, // Auchindoun: Sethekk Halls (556) Talon King Ikiss
        // 203, // Auchindoun: Mana-Tombs (557) Pandemonius
        // 248, // Auchindoun: Mana-Tombs (557) Pandemonius
        // 204, // Auchindoun: Mana-Tombs (557) Tavarok
        // 249, // Auchindoun: Mana-Tombs (557) Tavarok
        // 250, // Auchindoun: Mana-Tombs (557) Yor
        // 205, // Auchindoun: Mana-Tombs (557) Nexus-Prince Shaffar
        // 251, // Auchindoun: Mana-Tombs (557) Nexus-Prince Shaffar
        // 201, // Auchindoun: Auchenai Crypts (558) Shirrak the Dead Watcher
        // 246, // Auchindoun: Auchenai Crypts (558) Shirrak the Dead Watcher
        // 202, // Auchindoun: Auchenai Crypts (558) Exarch Maladaar
        // 247, // Auchindoun: Auchenai Crypts (558) Exarch Maladaar
        // 286, // The Escape From Durnholde (560) Lieutenant Drake
        // 285, // The Escape From Durnholde (560) Lieutenant Drake
        // 283, // The Escape From Durnholde (560) Captain Skarloc
        // 284, // The Escape From Durnholde (560) Captain Skarloc
        // 281, // The Escape From Durnholde (560) Epoch Hunter
        // 282, // The Escape From Durnholde (560) Epoch Hunter
        // 601, // Black Temple (564) High Warlord Naj'entus
        // 602, // Black Temple (564) Supremus
        // 603, // Black Temple (564) Shade of Akama
        // 604, // Black Temple (564) Teron Gorefiend
        // 605, // Black Temple (564) Gurtogg Bloodboil
        // 606, // Black Temple (564) Reliquary of Souls
        // 607, // Black Temple (564) Mother Shahraz
        // 608, // Black Temple (564) The Illidari Council
        // 609, // Black Temple (564) Illidan Stormrage
        // 649, // Gruul's Lair (565) High King Maulgar
        // 650, // Gruul's Lair (565) Gruul the Dragonkiller
        // 778, // Zul'Aman (568) Akil'zon
        // 779, // Zul'Aman (568) Nalorakk
        // 780, // Zul'Aman (568) Jan'alai
        // 781, // Zul'Aman (568) Halazzi
        // 782, // Zul'Aman (568) Hex Lord Malacrass
        // 783, // Zul'Aman (568) Zul'jin
        // 571, // Utgarde Keep (574) Prince Keleseth
        // 572, // Utgarde Keep (574) Prince Keleseth
        // 573, // Utgarde Keep (574) Skarvold & Dalronn
        // 574, // Utgarde Keep (574) Skarvold & Dalronn
        // 575, // Utgarde Keep (574) Ingvar the Plunderer
        // 576, // Utgarde Keep (574) Ingvar the Plunderer
        // 577, // Utgarde Pinnacle (575) Svala Sorrowgrave
        // 578, // Utgarde Pinnacle (575) Svala Sorrowgrave
        // 579, // Utgarde Pinnacle (575) Gortok Palehoof
        // 580, // Utgarde Pinnacle (575) Gortok Palehoof
        // 581, // Utgarde Pinnacle (575) Skadi the Ruthless
        // 582, // Utgarde Pinnacle (575) Skadi the Ruthless
        // 583, // Utgarde Pinnacle (575) King Ymiron
        // 584, // Utgarde Pinnacle (575) King Ymiron
        // 519, // The Nexus (576) Frozen Commander
        // 520, // The Nexus (576) Grand Magus Telestra
        // 521, // The Nexus (576) Grand Magus Telestra
        // 522, // The Nexus (576) Anomalus
        // 523, // The Nexus (576) Anomalus
        // 524, // The Nexus (576) Ormorok the Tree-Shaper
        // 525, // The Nexus (576) Ormrok the Tree-Shaper
        // 526, // The Nexus (576) Keristrasza
        // 527, // The Nexus (576) Keristrasza
        // 528, // The Oculus (578) Drakos the Interrogator
        // 529, // The Oculus (578) Drakos the Interrogator
        // 530, // The Oculus (578) Varos Cloudstrider
        // 531, // The Oculus (578) Varos Cloudstrider
        // 532, // The Oculus (578) Mage-Lord Urom
        // 533, // The Oculus (578) Mage-Lord Urom
        // 534, // The Oculus (578) Ley-Guardian Eregos
        // 535, // The Oculus (578) Ley-Guardian Eregos
        // 724, // The Sunwell (580) Kalecgos
        // 725, // The Sunwell (580) Brutallus
        // 726, // The Sunwell (580) Felmyst
        // 727, // The Sunwell (580) Eredar Twins
        // 728, // The Sunwell (580) M'uru
        // 729, // The Sunwell (580) Kil'jaeden
        // 414, // Magister's Terrace (585) Selin Fireheart
        // 415, // Magister's Terrace (585) Selin Fireheart
        // 416, // Magister's Terrace (585) Vexallus
        // 417, // Magister's Terrace (585) Vexallus
        // 418, // Magister's Terrace (585) Priestess Delrissa
        // 419, // Magister's Terrace (585) Priestess Delrissa
        // 420, // Magister's Terrace (585) Kael'thas Sunstrider
        // 421, // Magister's Terrace (585) Kael'thas Sunstrider
        // 293, // The Culling of Stratholme (595) Meathook
        // 297, // The Culling of Stratholme (595) Meathook
        // 294, // The Culling of Stratholme (595) Salram the Fleshcrafter
        // 298, // The Culling of Stratholme (595) Salram the Fleshcrafter
        // 295, // The Culling of Stratholme (595) Chrono-Lord Epoch
        // 299, // The Culling of Stratholme (595) Chrono-Lord Epoch
        // 296, // The Culling of Stratholme (595) Mal'ganis
        // 300, // The Culling of Stratholme (595) Mal'ganis
        // 563, // Halls of Stone (599) Krystallus
        // 564, // Halls of Stone (599) Krystallus
        // 565, // Halls of Stone (599) Maiden of Grief
        // 566, // Halls of Stone (599) Maiden of Grief
        // 567, // Halls of Stone (599) Tribunal of Ages
        // 568, // Halls of Stone (599) Tribunal of Ages
        // 569, // Halls of Stone (599) Sjonnir the Ironshaper
        // 570, // Halls of Stone (599) Sjonnir the Ironshaper
        // 369, // Drak'Tharon Keep (600) Trollgore
        // 370, // Drak'Tharon Keep (600) Trollgore
        // 371, // Drak'Tharon Keep (600) Novos the Summoner
        // 372, // Drak'Tharon Keep (600) Novos the Summoner
        // 373, // Drak'Tharon Keep (600) King Dred
        // 374, // Drak'Tharon Keep (600) King Dred
        // 375, // Drak'Tharon Keep (600) The Prophet Tharon'ja
        // 376, // Drak'Tharon Keep (600) The Prophet Tharon'ja
        // 216, // Azjol-Nerub (601) Krik'thir the Gatewatcher
        // 264, // Azjol-Nerub (601) Krik'thir the Gatewatcher
        // 217, // Azjol-Nerub (601) Hadronox
        // 265, // Azjol-Nerub (601) Hadronox
        // 218, // Azjol-Nerub (601) Anub'arak
        // 266, // Azjol-Nerub (601) Anub'arak
        // 555, // Halls of Lightning (602) General Bjarngrim
        // 556, // Halls of Lightning (602) General Bjarngrim
        // 557, // Halls of Lightning (602) Volkhan
        // 558, // Halls of Lightning (602) Volkhan
        // 559, // Halls of Lightning (602) Ionar
        // 560, // Halls of Lightning (602) Ionar
        // 561, // Halls of Lightning (602) Loken
        // 562, // Halls of Lightning (602) Loken
        // 744, // Ulduar (603) Flame Leviathan
        // 758, // Ulduar (603) Flame Leviathan
        // 745, // Ulduar (603) Ignis the Furnace Master
        // 759, // Ulduar (603) Ignis the Furnace Master
        // 746, // Ulduar (603) Razorscale
        // 747, // Ulduar (603) XT-002 Deconstructor
        // 748, // Ulduar (603) The Iron Council
        // 760, // Ulduar (603) Razorscale
        // 749, // Ulduar (603) Kologarn
        // 761, // Ulduar (603) XT-002 Deconstructor
        // 750, // Ulduar (603) Auriaya
        // 762, // Ulduar (603) The Iron Council
        // 751, // Ulduar (603) Hodir
        // 763, // Ulduar (603) Kologarn
        // 752, // Ulduar (603) Thorim
        // 764, // Ulduar (603) Auriaya
        // 753, // Ulduar (603) Freya
        // 765, // Ulduar (603) Hodir
        // 754, // Ulduar (603) Mimiron
        // 766, // Ulduar (603) Thorim
        // 755, // Ulduar (603) General Vezax
        // 767, // Ulduar (603) Freya
        // 756, // Ulduar (603) Yogg-Saron
        // 768, // Ulduar (603) Mimiron
        // 757, // Ulduar (603) Algalon the Observer
        // 769, // Ulduar (603) General Vezax
        // 770, // Ulduar (603) Yogg-Saron
        // 771, // Ulduar (603) Algalon the Observer
        // 383, // Gundrak (604) Slad'ran
        // 384, // Gundrak (604) Slad'ran
        // 385, // Gundrak (604) Drakkari Colossus
        // 386, // Gundrak (604) Drakkari Colossus
        // 387, // Gundrak (604) Moorabi
        // 388, // Gundrak (604) Moorabi
        // 390, // Gundrak (604) Gal'darah
        // 389, // Gundrak (604) Eck the Ferocious
        // 391, // Gundrak (604) Gal'darah
        // 541, // Violet Hold (608) First Prisoner
        // 542, // Violet Hold (608) First Prisoner
        // 543, // Violet Hold (608) Second Prisoner
        // 544, // Violet Hold (608) Second Prisoner
        // 545, // Violet Hold (608) Cyanigosa
        // 546, // Violet Hold (608) Cyanigosa
        740, // The Obsidian Sanctum (615) Vesperon
        736, // The Obsidian Sanctum (615) Tenebron
        741, // The Obsidian Sanctum (615) Vesperon
        737, // The Obsidian Sanctum (615) Tenebron
        738, // The Obsidian Sanctum (615) Shadron
        739, // The Obsidian Sanctum (615) Shadron
        742, // The Obsidian Sanctum (615) Sartharion
        743, // The Obsidian Sanctum (615) Sartharion
        // 734, // The Eye of Eternity (616) Malygos
        // 735, // The Eye of Eternity (616) Malygos
        // 212, // Ahn'kahet: The Old Kingdom (619) Elder Nadox
        // 259, // Ahn'kahet: The Old Kingdom (619) Elder Nadox
        // 213, // Ahn'kahet: The Old Kingdom (619) Prince Taldaram
        // 260, // Ahn'kahet: The Old Kingdom (619) Prince Taldaram
        // 214, // Ahn'kahet: The Old Kingdom (619) Jedoga Shadowseeker
        // 261, // Ahn'kahet: The Old Kingdom (619) Jedoga Shadowseeker
        // 215, // Ahn'kahet: The Old Kingdom (619) Herald Volazj
        // 262, // Ahn'kahet: The Old Kingdom (619) Amanitar
        // 263, // Ahn'kahet: The Old Kingdom (619) Herald Volazj
        // 772, // Vault of Archavon (624) Archavon the Stone Watcher
        // 773, // Vault of Archavon (624) Archavon the Stone Watcher
        // 774, // Vault of Archavon (624) Emalon the Storm Watcher
        // 775, // Vault of Archavon (624) Emalon the Storm Watcher
        // 776, // Vault of Archavon (624) Koralon the Flame Watcher
        // 777, // Vault of Archavon (624) Koralon the Flame Watcher
        // 885, // Vault of Archavon (624) Toravon the Ice Watcher
        // 886, // Vault of Archavon (624) Toravon the Ice Watcher
        // 845, // Icecrown Citadel (631) Lord Marrowgar
        // 857, // Icecrown Citadel (631) Lord Marrowgar
        // 846, // Icecrown Citadel (631) Lady Deathwhisper
        // 858, // Icecrown Citadel (631) Lady Deathwhisper
        // 847, // Icecrown Citadel (631) Icecrown Gunship Battle
        // 859, // Icecrown Citadel (631) Icecrown Gunship Battle
        // 848, // Icecrown Citadel (631) Deathbringer Saurfang
        // 860, // Icecrown Citadel (631) Deathbringer Saurfang
        // 849, // Icecrown Citadel (631) Festergut
        // 861, // Icecrown Citadel (631) Festergut
        // 850, // Icecrown Citadel (631) Rotface
        // 862, // Icecrown Citadel (631) Rotface
        // 851, // Icecrown Citadel (631) Professor Putricide
        // 863, // Icecrown Citadel (631) Professor Putricide
        // 852, // Icecrown Citadel (631) Blood Council
        // 864, // Icecrown Citadel (631) Blood Council
        // 853, // Icecrown Citadel (631) Queen Lana'thel
        // 865, // Icecrown Citadel (631) Queen Lana'thel
        // 854, // Icecrown Citadel (631) Valithria Dreamwalker
        // 866, // Icecrown Citadel (631) Valithria Dreamwalker
        // 855, // Icecrown Citadel (631) Sindragosa
        // 867, // Icecrown Citadel (631) Sindragosa
        // 856, // Icecrown Citadel (631) The Lich King
        // 868, // Icecrown Citadel (631) The Lich King
        // 829, // The Forge of Souls (632) Bronjahm
        // 830, // The Forge of Souls (632) Bronjahm
        // 831, // The Forge of Souls (632) Devourer of Souls
        // 832, // The Forge of Souls (632) Devourer of Souls
        // 629, // Trial of the Crusader (649) Northrend Beasts
        // 630, // Trial of the Crusader (649) Northrend Beasts
        // 633, // Trial of the Crusader (649) Lord Jaraxxus
        // 631, // Trial of the Crusader (649) Northrend Beasts
        // 634, // Trial of the Crusader (649) Lord Jaraxxus
        // 637, // Trial of the Crusader (649) Faction Champions
        // 632, // Trial of the Crusader (649) Northrend Beasts
        // 635, // Trial of the Crusader (649) Lord Jaraxxus
        // 638, // Trial of the Crusader (649) Faction Champions
        // 641, // Trial of the Crusader (649) Val'kyr Twins
        // 636, // Trial of the Crusader (649) Lord Jaraxxus
        // 639, // Trial of the Crusader (649) Faction Champions
        // 642, // Trial of the Crusader (649) Val'kyr Twins
        // 645, // Trial of the Crusader (649) Anub'arak
        // 640, // Trial of the Crusader (649) Faction Champions
        // 643, // Trial of the Crusader (649) Val'kyr Twins
        // 646, // Trial of the Crusader (649) Anub'arak
        // 644, // Trial of the Crusader (649) Val'kyr Twins
        // 647, // Trial of the Crusader (649) Anub'arak
        // 648, // Trial of the Crusader (649) Anub'arak
        // 334, // Trial of the Champion (650) Grand Champions
        // 336, // Trial of the Champion (650) Grand Champions
        // 338, // Trial of the Champion (650) Argent Champion
        // 339, // Trial of the Champion (650) Argent Champion
        // 340, // Trial of the Champion (650) The Black Knight
        // 341, // Trial of the Champion (650) The Black Knight
        // 833, // Pit of Saron (658) Forgemaster Garfrost
        // 834, // Pit of Saron (658) Forgemaster Garfrost
        // 835, // Pit of Saron (658) Krick
        // 836, // Pit of Saron (658) Krick
        // 837, // Pit of Saron (658) Overlrod Tyrannus
        // 838, // Pit of Saron (658) Overlrod Tyrannus
        // 842, // Halls of Reflection (668) Falric
        // 841, // Halls of Reflection (668) Falric
        // 840, // Halls of Reflection (668) Marwyn
        // 839, // Halls of Reflection (668) Marwyn
        // 843, // Halls of Reflection (668) Escaped from Arthas
        // 844, // Halls of Reflection (668) Escaped from Arthas
        // 889, // The Ruby Sanctum (724) Baltharus the Warborn
        // 890, // The Ruby Sanctum (724) Baltharus the Warborn
        // 891, // The Ruby Sanctum (724) Saviana Ragefire
        // 892, // The Ruby Sanctum (724) Saviana Ragefire
        // 893, // The Ruby Sanctum (724) General Zarithrian
        // 894, // The Ruby Sanctum (724) General Zarithrian
        // 887, // The Ruby Sanctum (724) Halion
        // 888, // The Ruby Sanctum (724) Halion
    };

    inline bool IsEnabledForCreatureEntry(uint32 entry)
    {
        return std::binary_search(std::begin(ALLOW_ENTRIES), std::end(ALLOW_ENTRIES), entry);
    }

    inline bool IsDeniedForCreditEntry(uint32 entry)
    {
        return std::find(std::begin(DENY_CREDIT_ENTRIES), std::end(DENY_CREDIT_ENTRIES), entry) != std::end(DENY_CREDIT_ENTRIES);
    }
}

#endif // DEF_RESETRAIDCOOLDOWNS_CREATURE_ENTRIES_H

