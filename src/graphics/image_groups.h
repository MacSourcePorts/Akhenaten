#pragma once

enum e_pack {
    PACK_UNLOADED,
    PACK_GENERAL,
    PACK_SPR_MAIN,
    PACK_TERRAIN,
    PACK_SPR_AMBIENT,
    PACK_EMPIRE,
    //
    PACK_FONT,
    //
    PACK_TEMPLE,
    PACK_MONUMENT,
    PACK_ENEMY,
    //
    PACK_EXPANSION,
    PACK_EXPANSION_SPR,
    //
    PACK_CUSTOM,
};

////////////////// FONT

#define GROUP_FONT PACK_FONT, 1

////////////////// EMPIRE MAP

#define GROUP_EMPIRE_MAP PACK_EMPIRE, 1

////////////////// TERRAIN

#define GROUP_TERRAIN_BLACK PACK_TERRAIN, 1
#define GROUP_TERRAIN_SHRUB PACK_TERRAIN, 2
#define GROUP_TERRAIN_UGLY_GRASS PACK_TERRAIN, 3
#define GROUP_TERRAIN_TREE PACK_TERRAIN, 4
#define GROUP_TERRAIN_WATER PACK_TERRAIN, 5
#define GROUP_TERRAIN_EARTHQUAKE PACK_TERRAIN, 6
#define GROUP_TERRAIN_EMPTY_LAND_ALT PACK_TERRAIN, 7
#define GROUP_TERRAIN_ROCK PACK_TERRAIN, 8           // 239
#define GROUP_TERRAIN_ELEVATION_ROCK PACK_TERRAIN, 8 // this isn't in Pharaoh
#define GROUP_BUILDING_AQUEDUCT PACK_TERRAIN, 9      // 19
#define GROUP_TERRAIN_ELEVATION PACK_TERRAIN, 9      // this isn't in Pharaoh
#define GROUP_TERRAIN_EMPTY_LAND PACK_TERRAIN, 10
#define GROUP_TERRAIN_REEDS PACK_TERRAIN, 11
// #define GROUP_BUILDING_TRANSPORT_WHARF  PACK_TERRAIN,  17
#define GROUP_BUILDING_FISHING_WHARF PACK_TERRAIN, 18 // 79
#define GROUP_SUNKEN_TILE PACK_TERRAIN, 20
#define GROUP_TERRAIN_OVERLAY_FLAT PACK_TERRAIN, 20
#define GROUP_TERRAIN_OVERLAY_COLORED PACK_TERRAIN, 21
#define GROUP_DEBUG_ARROWPOST PACK_TERRAIN, 24
#define GROUP_BUILDING_WALL PACK_TERRAIN, 24 // TODO
#define GROUP_TERRAIN_ENTRY_EXIT_FLAGS PACK_TERRAIN, 24
#define GROUP_BUILDING_FERRY PACK_TERRAIN, 23
#define GROUP_BUILDING_SHIPYARD PACK_TERRAIN, 26 // 77
#define GROUP_BUILDING_DOCK_UNUSED PACK_TERRAIN, 27
// #define GROUP_BUILDING_WARSHIP_WHARF  PACK_TERRAIN,  28
#define GROUP_TERRAIN_TREE_STUMPS PACK_TERRAIN, 30
#define GROUP_TERRAIN_FLOODPLAIN PACK_TERRAIN, 31
#define GROUP_TERRAIN_FLOODSYSTEM PACK_TERRAIN, 33
#define GROUP_TERRAIN_REEDS_GROWN PACK_TERRAIN, 32
#define GROUP_TERRAIN_ROAD PACK_TERRAIN, 33              // 112
#define GROUP_TERRAIN_RUBBLE PACK_TERRAIN, 34            // 114
#define GROUP_TERRAIN_RUBBLE_TENT PACK_TERRAIN, 35       // 119
#define GROUP_TERRAIN_RUBBLE_GENERAL PACK_TERRAIN, 36    // 120
#define GROUP_TERRAIN_MEADOW_WITH_GRASS PACK_TERRAIN, 37 // 138
#define GROUP_DEBUG_WIREFRAME_TILE PACK_TERRAIN, 41
#define GROUP_TERRAIN_ORE_ROCK PACK_TERRAIN, 42
#define GROUP_TERRAIN_DIRT_ROAD PACK_TERRAIN, 43
#define GROUP_TERRAIN_DESIRABILITY PACK_TERRAIN, 45 // 135
#define GROUP_TERRAIN_GRASS_PH PACK_TERRAIN, 46     // terrain
#define GROUP_BUILDING_DOCK PACK_TERRAIN, 49        // 78
#define GROUP_BUILDING_WATER_LIFT PACK_TERRAIN, 50  // 25
#define GROUP_TERRAIN_MEADOW_STATIC_TALLGRASS PACK_TERRAIN, 54
#define GROUP_TERRAIN_MEADOW_STATIC_INNER PACK_TERRAIN, 55
#define GROUP_TERRAIN_OVERLAY_WATER PACK_TERRAIN, 59
#define GROUP_TERRAIN_OVERLAY_WATER_HOUSE PACK_TERRAIN, 60
#define GROUP_TERRAIN_DEEPWATER PACK_TERRAIN, 61
#define GROUP_BUILDING_BRIDGE PACK_TERRAIN, 63
#define GROUP_TERRAIN_GRASS_PH_EDGES PACK_TERRAIN, 64
#define GROUP_TERRAIN_GREEN_WATER_EDGES PACK_TERRAIN, 65 // ?????
#define GROUP_TERRAIN_MEADOW_STATIC_OUTER PACK_TERRAIN, 66
#define GROUP_TERRAIN_WATER_SHORE PACK_TERRAIN, 207 // TODO?
#define GROUP_TERRAIN_ACCESS_RAMP PACK_TERRAIN, 216 // this isn't in Pharaoh

////////////////// GENERAL

#define GROUP_TOP_MENU_SIDEBAR PACK_GENERAL, 11
#define GROUP_PANEL_BUTTON PACK_GENERAL, 15
// #define GROUP_BUILDING_TOWER  PACK_GENERAL,  17
#define GROUP_SIDEBAR_ADVISORS_EMPIRE PACK_GENERAL, 89 // 13
#define GROUP_BUILDING_MARKET PACK_GENERAL, 22
//#define GROUP_BUILDING_WELL PACK_GENERAL, 23
//#define GROUP_BUILDING_HOUSE_HUT PACK_GENERAL, 26
//#define GROUP_BUILDING_HOUSE_SHANTY PACK_GENERAL, 27
//#define GROUP_BUILDING_HOUSE_COTTAGE PACK_GENERAL, 28
//#define GROUP_BUILDING_HOUSE_HOMESTEAD PACK_GENERAL, 29
//#define GROUP_BUILDING_HOUSE_APARTMENT PACK_GENERAL, 30
#define GROUP_BUILDING_HOUSE_RESIDENCE PACK_GENERAL, 31
#define GROUP_BUILDING_HOUSE_MANOR PACK_GENERAL, 32
#define GROUP_BUILDING_HOUSE_ELEGANT_MANOR PACK_GENERAL, 33
#define GROUP_BUILDING_HOUSE_ESTATE PACK_GENERAL, 34
#define GROUP_BUILDING_HOUSE_PALATIAL PACK_GENERAL, 35
#define GROUP_BUILDING_HOUSE_VACANT_LOT PACK_GENERAL, 36
#define GROUP_BUILDING_FARM_HOUSE PACK_GENERAL, 225 // 37
#define GROUP_BUILDING_CLAY_PIT PACK_GENERAL, 40
//#define GROUP_BUILDING_SCRIBAL_SCHOOL PACK_GENERAL, 42  // 41
#define GROUP_BUILDING_LIBRARY PACK_GENERAL, 43 // 42
#define GROUP_BUILDING_ACADEMY PACK_GENERAL, 43 // this isn't in Pharaoh
#define GROUP_BUILDING_PAPYRUS_WORKSHOP PACK_GENERAL, 44
//#define GROUP_BUILDING_BANDSTAND PACK_GENERAL, 92 // 45
//#define GROUP_BUILDING_BOOTH PACK_GENERAL, 114    // 46
#define GROUP_BUILDING_PAVILLION PACK_GENERAL, 48
//#define GROUP_BUILDING_CONSERVATORY PACK_GENERAL, 51   // 49
#define GROUP_BUILDING_DANCE_SCHOOL PACK_GENERAL, 52   // 50
#define GROUP_BUILDING_JUGGLER_SCHOOL PACK_GENERAL, 46 // 51
#define GROUP_BUILDING_FOUNTAIN_4 PACK_GENERAL, 53     // this isn't in Pharaoh
#define GROUP_BUILDING_FOUNTAIN_1 PACK_GENERAL, 54     // this isn't in Pharaoh
#define GROUP_BUILDING_FOUNTAIN_2 PACK_GENERAL, 55     // this isn't in Pharaoh
#define GROUP_BUILDING_FOUNTAIN_3 PACK_GENERAL, 56     // this isn't in Pharaoh
#define GROUP_TERRAIN_PLAZA PACK_GENERAL, 168          // 58
#define GROUP_TERRAIN_GARDEN PACK_GENERAL, 59
#define GROUP_BUILDING_WORKSHOP_RAW_MATERIAL PACK_GENERAL, 60
//#define GROUP_BUILDING_STATUE_SMALL_1 PACK_GENERAL, 61
//#define GROUP_BUILDING_STATUE_MEDIUM_1 PACK_GENERAL, 8
//#define GROUP_BUILDING_STATUE_LARGE_1 PACK_GENERAL, 7
#define GROUP_BUILDING_PALACE PACK_GENERAL, 62 // this isn't in Pharaoh
//#define GROUP_BUILDING_TAX_COLLECTOR PACK_GENERAL, 63
#define GROUP_BUILDING_POLICE_STATION PACK_GENERAL, 64
#define GROUP_BUILDING_TIMBER_YARD PACK_GENERAL, 65
#define GROUP_BUILDING_FORT PACK_GENERAL, 66
#define GROUP_BUILDING_DENTIST PACK_GENERAL, 67
#define GROUP_BUILDING_APOTHECARY PACK_GENERAL, 68
//#define GROUP_BUILDING_WATER_SUPPLY PACK_GENERAL, 69
//#define GROUP_BUILDING_PHYSICIAN PACK_GENERAL, 70
#define GROUP_BUILDING_MORTUARY PACK_GENERAL, 175     // 70
#define GROUP_BUILDING_TEMPLE_OSIRIS PACK_GENERAL, 25 // 71
#define GROUP_BUILDING_TEMPLE_RA PACK_GENERAL, 21     // 72
#define GROUP_BUILDING_TEMPLE_PTAH PACK_GENERAL, 20   // 73
#define GROUP_BUILDING_TEMPLE_SETH PACK_GENERAL, 19   // 74
#define GROUP_BUILDING_TEMPLE_BAST PACK_GENERAL, 76   // 75
#define GROUP_BUILDING_SHRINE_OSIRIS PACK_GENERAL, 75
#define GROUP_BUILDING_SHRINE_RA PACK_GENERAL, 74
#define GROUP_BUILDING_SHRINE_PTAH PACK_GENERAL, 73
#define GROUP_BUILDING_SHRINE_SETH PACK_GENERAL, 72
#define GROUP_BUILDING_SHRINE_BAST PACK_GENERAL, 71
#define GROUP_BUILDING_ORACLE PACK_GENERAL, 76 // this isn't in Pharaoh
#define GROUP_BUILDING_ENGINEERS_POST PACK_GENERAL, 81
#define GROUP_BUILDING_STORAGE_YARD PACK_GENERAL, 82
#define GROUP_BUILDING_STORAGE_YARD_SPACE_EMPTY PACK_GENERAL, 83
#define GROUP_BUILDING_STORAGE_YARD_SPACE_FILLED PACK_GENERAL, 84
#define GROUP_BUILDING_GOVERNORS_HOUSE PACK_GENERAL, 85
#define GROUP_BUILDING_GOVERNORS_VILLA PACK_GENERAL, 86
#define GROUP_BUILDING_GOVERNORS_PALACE PACK_GENERAL, 87
#define GROUP_SIDEBAR_BRIEFING_ROTATE_BUTTONS PACK_GENERAL, 89
#define GROUP_MESSAGE_ICON PACK_GENERAL, 90
#define GROUP_SIDEBAR_BUTTONS PACK_GENERAL, 136 // 92
#define GROUP_LABOR_PRIORITY_LOCK PACK_GENERAL, 94
#define GROUP_OK_CANCEL_SCROLL_BUTTONS PACK_GENERAL, 96
//#define GROUP_BUILDING_GRANARY PACK_GENERAL, 99
#define GROUP_BUILDING_FARMLAND PACK_GENERAL, 37 // 100
#define GROUP_OVERLAY_COLUMN PACK_GENERAL, 103
#define GROUP_SIDEBAR_UPPER_BUTTONS PACK_GENERAL, 110
#define GROUP_BUILDING_BEER_WORKSHOP PACK_GENERAL, 116 // 44
#define GROUP_BUILDING_CHARIOT_MAKER PACK_GENERAL, 120 // 52
//#define GROUP_SIDE_PANEL PACK_GENERAL, 121             // 12
#define GROUP_BUILDING_LINEN_WORKSHOP PACK_GENERAL, 122
#define GROUP_BUILDING_WEAPONS_WORKSHOP PACK_GENERAL, 123
#define GROUP_BUILDING_JEWELS_WORKSHOP PACK_GENERAL, 119 // 124
//#define GROUP_BUILDING_BRICKS_WORKSHOP PACK_GENERAL, 124
//#define GROUP_BUILDING_POTTERY_WORKSHOP PACK_GENERAL, 125
#define GROUP_FIGURE_FORT_FLAGS PACK_GENERAL, 126
#define GROUP_FIGURE_FORT_STANDARD_ICONS PACK_GENERAL, 127
#define GROUP_ADVISOR_ICONS PACK_GENERAL, 128
//#define GROUP_RESOURCE_ICONS PACK_GENERAL, 129 // 267
#define GROUP_DIALOG_BACKGROUND PACK_GENERAL, 132
#define GROUP_SUNKEN_TEXTBOX_BACKGROUND PACK_GENERAL, 133
#define GROUP_CONTEXT_ICONS PACK_GENERAL, 134
#define GROUP_EDITOR_SIDEBAR_BUTTONS PACK_GENERAL, 137
#define GROUP_FIGURE_MAP_FLAG_FLAGS PACK_GENERAL, 139
#define GROUP_FIGURE_MAP_FLAG_ICONS PACK_GENERAL, 140
#define GROUP_MINIMAP_EMPTY_LAND PACK_GENERAL, 141
#define GROUP_MINIMAP_WATER PACK_GENERAL, 142
#define GROUP_MINIMAP_TREE PACK_GENERAL, 143
#define GROUP_MINIMAP_ROCK PACK_GENERAL, 145
#define GROUP_MINIMAP_MEADOW PACK_GENERAL, 146
#define GROUP_MINIMAP_ROAD PACK_GENERAL, 147
#define GROUP_MINIMAP_HOUSE PACK_GENERAL, 148
//#define GROUP_MINIMAP_BUILDING PACK_GENERAL, 149
#define GROUP_MINIMAP_WALL PACK_GENERAL, 150
#define GROUP_MINIMAP_AQUEDUCT PACK_GENERAL, 151
#define GROUP_MINIMAP_BLACK PACK_GENERAL, 152
#define GROUP_POPULATION_GRAPH_BAR PACK_GENERAL, 157
#define GROUP_BULLET PACK_GENERAL, 158
//#define GROUP_BUILDING_BARRACKS PACK_GENERAL, 166
#define GROUP_EMPIRE_PANELS PACK_GENERAL, 172
//#define GROUP_RESOURCE_STOCK_GAMEMEAT_5 PACK_GENERAL, 205 // 173
//#define GROUP_RESOURCE_STOCK_STRAW_2 PACK_GENERAL, 206
#define GROUP_RESOURCE_STOCK_WEAPONS_2 PACK_GENERAL, 207
//#define GROUP_RESOURCE_STOCK_CLAY_2 PACK_GENERAL, 208
#define GROUP_RESOURCE_STOCK_BARLEY_2 PACK_GENERAL, 208
#define GROUP_RESOURCE_STOCK_BEER_3 PACK_GENERAL, 198
#define GROUP_RESOURCE_STOCK_FLAX_2 PACK_GENERAL, 210
#define GROUP_RESOURCE_STOCK_LINEN_5 PACK_GENERAL, 199
#define GROUP_RESOURCE_STOCK_GEMS_2 PACK_GENERAL, 200
#define GROUP_RESOURCE_STOCK_WOOD_5 PACK_GENERAL, 202
#define GROUP_RESOURCE_STOCK_REEDS_5 PACK_GENERAL, 206
#define GROUP_RESOURCE_STOCK_PAPYRUS_3 PACK_GENERAL, 60
#define GROUP_RESOURCE_STOCK_CHARIOTS_2 PACK_GENERAL, 209
#define GROUP_RESOURCE_STOCK_COPPER_2 PACK_GENERAL, 203
#define GROUP_EMPIRE_CITY PACK_GENERAL, 177 // 174
#define GROUP_EMPIRE_CITY_PH_PHARAOH PACK_GENERAL, 175
#define GROUP_EMPIRE_CITY_PH_OURS PACK_GENERAL, 176
#define GROUP_EMPIRE_TRADE_ROUTE_TYPE PACK_GENERAL, 179
#define GROUP_BUILDING_NATIVE PACK_GENERAL, 183
#define GROUP_BUILDING_MISSION_POST PACK_GENERAL, 184
//#define GROUP_BUILDING_BATHHOUSE_NO_WATER PACK_GENERAL, 185
#define GROUP_RATINGS_COLUMN PACK_GENERAL, 189
#define GROUP_MESSAGE_ADVISOR_BUTTONS PACK_GENERAL, 106           // 199
#define GROUP_BUILDING_MILITARY_ACADEMY PACK_GENERAL, 173         // 201
#define GROUP_BUILDING_FORT_JAVELIN PACK_GENERAL, 66              // 202
#define GROUP_BUILDING_FORT_LEGIONARY PACK_GENERAL, 66            // 204
#define GROUP_BUILDING_TRIUMPHAL_ARCH PACK_GENERAL, 205           // this isn't in Pharaoh
#define GROUP_BORDERED_BUTTON PACK_GENERAL, 174                   // 208
#define GROUP_BUILDING_MARKET_FANCY PACK_GENERAL, 45              // 210
#define GROUP_BUILDING_SENET_HOUSE PACK_GENERAL, 17               // 213 //GROUP_BUILDING_HIPPODROME_1
#define GROUP_BUILDING_HIPPODROME_2 PACK_GENERAL, 214             // this isn't in Pharaoh
#define GROUP_BUILDING_PALACE_FANCY PACK_GENERAL, 221             // this isn't in Pharaoh
#define GROUP_FORT_ICONS PACK_GENERAL, 222                        // TODO?
#define GROUP_EMPIRE_FOREIGN_CITY PACK_GENERAL, 223               // this isn't in Pharaoh
#define GROUP_GOD_BOLT PACK_GENERAL, 111                          // 225
#define GROUP_PLAGUE_SKULL PACK_GENERAL, 97                       // 227
#define GROUP_FIGURE_FORT_MOUNTED PACK_GENERAL, 66                // 232
#define GROUP_BUILDING_TRADE_CENTER_FLAG PACK_GENERAL, 238        // this isn't in Pharaoh
#define GROUP_FIGURE_FORT_STANDARD_POLE PACK_GENERAL, 241
//#define GROUP_TRADE_AMOUNT PACK_GENERAL, 171           // 243
#define GROUP_BULIDING_GATEHOUSE PACK_GENERAL, 248     // this isn't in Pharaoh
#define GROUP_BUILDING_VILLAGE_PALACE PACK_GENERAL, 47 // general
#define GROUP_BUILDING_TOWN_PALACE PACK_GENERAL, 39
#define GROUP_BUILDING_CITY_PALACE PACK_GENERAL, 18
#define GROUP_BUILDING_FARM_CROPS_PH PACK_GENERAL, 100
//#define GROUP_BUILDING_CATTLE_RANCH PACK_GENERAL, 105
#define GROUP_BUILDING_REEDS_COLLECTOR PACK_GENERAL, 24
#define GROUP_SINGLE_SQUARE PACK_GENERAL, 107
//#define GROUP_BOOTH_SQUARE PACK_GENERAL, 112
//#define GROUP_BANDSTAND_SQUARE PACK_GENERAL, 58
#define GROUP_PAVILLION_SQUARE PACK_GENERAL, 50
#define GROUP_FESTIVAL_SQUARE PACK_GENERAL, 49
#define GROUP_BUILDING_GRANITE_QUARY PACK_GENERAL, 38
//#define GROUP_BUILDING_GOLD_MINE PACK_GENERAL, 185
#define GROUP_BUILDING_GEMSTONE_MINE PACK_GENERAL, 188
//#define GROUP_BUILDING_STONE_QUARRY PACK_GENERAL, 187 // 38
#define GROUP_BUILDING_UNUSED_BEIGE_MINE PACK_GENERAL, 186
//#define GROUP_BUILDING_COPPER_MINE PACK_GENERAL, 196
//#define GROUP_BUILDING_SANDSTONE_MINE PACK_GENERAL, 197
#define GROUP_BUILDING_MARBLE_QUARRY PACK_GENERAL, 162
#define GROUP_BUILDING_LIMESTONE_QUARRY PACK_GENERAL, 170 // 39
#define GROUP_BUILDING_HUNTING_LODGE PACK_GENERAL, 176
#define GROUP_BUILDING_ROADBLOCK PACK_GENERAL, 98
#define GROUP_BUILDING_FIREHOUSE PACK_GENERAL, 78
#define GROUP_BUILDING_WORKCAMP PACK_GENERAL, 77
//#define GROUP_BUILDING_WATER_SUPPLY PACK_GENERAL, 69
#define GROUP_BUILDING_COURTHOUSE PACK_GENERAL, 62
#define GROUP_BUILDING_WALLS PACK_GENERAL, 138
#define GROUP_BUILDING_GATEHOUSE PACK_GENERAL, 161
#define GROUP_BUILDING_GATEHOUSE_2 PACK_GENERAL, 220
// Warning already redefined. Is it maybe a good idea to get rid of the defines complete and use constexpr ?
#define GROUP_BUILDING_TOWER PACK_GENERAL, 135
// Warning already redefined. Is it maybe a good idea to get rid of the defines complete and use constexpr ?
#define GROUP_BUILDING_TRANSPORT_WHARF PACK_GENERAL, 17 // TODO
// Warning already redefined. Is it maybe a good idea to get rid of the defines complete and use constexpr ?
#define GROUP_BUILDING_WARSHIP_WHARF PACK_GENERAL, 28 // TODO
#define GROUP_BUILDING_GUILD_CARPENTERS PACK_GENERAL, 91
#define GROUP_BUILDING_GUILD_STONEMASONS PACK_GENERAL, 88
#define GROUP_BUILDING_GUILD_BRICKLAYERS PACK_GENERAL, 57

#define GROUP_SELECT_MISSION_BUTTON PACK_GENERAL, 254 // TODO
#define GROUP_BUTTON_EXCLAMATION PACK_GENERAL, 193
#define GROUP_MENU_ADVISOR_BUTTONS PACK_GENERAL, 159
#define GROUP_MENU_ADVISOR_LAYOUT PACK_GENERAL, 160
#define GROUP_TINY_ARROWS PACK_GENERAL, 212
#define GROUP_GOD_ANGEL PACK_GENERAL, 9
#define GROUP_BUILD_MENU_CATEGORIES PACK_GENERAL, 117
#define GROUP_MINIMAP_REEDS PACK_GENERAL, 144
#define GROUP_MINIMAP_FLOODPLAIN PACK_GENERAL, 146
#define GROUP_MINIMAP_DUNES PACK_GENERAL, 211

////////////////// UNLOADED

#define GROUP_SYSTEM_GRAPHICS PACK_UNLOADED, 0
#define GROUP_FORT_FORMATIONS PACK_UNLOADED, 1            // 197
#define GROUP_ADVISOR_RATINGS_BACKGROUND PACK_UNLOADED, 2 // 195
#define GROUP_BIGPEOPLE PACK_UNLOADED, 3
#define GROUP_PROMO_3 PACK_UNLOADED, 4           // 188
#define GROUP_PROMO_2 PACK_UNLOADED, 5           // 187
#define GROUP_PROMO_1 PACK_UNLOADED, 6           // 186
#define GROUP_LOGO PACK_UNLOADED, 7              // 162
#define GROUP_CONFIG_BACKGROUND PACK_UNLOADED, 8 // 161
#define GROUP_SCORES_BACKGROUND PACK_UNLOADED, 9
#define GROUP_WIN_GAME_BACKGROUND PACK_UNLOADED, 9        // 160
#define GROUP_MESSAGE_IMAGES PACK_UNLOADED, 10            // 159
#define GROUP_ADVISOR_BACKGROUND PACK_UNLOADED, 11        // 136
#define GROUP_SELECT_MISSION_BACKGROUND PACK_UNLOADED, 12 // 244
#define GROUP_MAIN_MENU_BACKGROUND PACK_UNLOADED, 14
#define GROUP_MAP_SELECTION_CCK PACK_UNLOADED, 15     // 246
#define GROUP_NEXT_MISSION_SELECT PACK_UNLOADED, 16   // 245 <----- ?????????????????
#define GROUP_LOADING_SCREEN PACK_UNLOADED, 17        // 251
#define GROUP_INTERMEZZO_BACKGROUND PACK_UNLOADED, 18 // 252
#define GROUP_PANEL_WINDOWS_DESERT PACK_UNLOADED, 19  // 253
#define GROUP_PANEL_WINDOWS PACK_UNLOADED, 21         // 95
#define GROUP_PANEL_GODS_DIALOGDRAW PACK_UNLOADED, 16  // offset 473
// #define ?????  PACK_UNLOADED,  22 //80
#define GROUP_PORTRAITS PACK_UNLOADED, 25      // 190
#define GROUP_SCENARIO_IMAGE PACK_UNLOADED, 28 // 247
#define GROUP_PLAYER_SELECTION PACK_UNLOADED, 29
#define GROUP_MAP_SELECTION_CAMPAIGN PACK_UNLOADED, 30
#define GROUP_GAME_MENU PACK_UNLOADED, 31
#define GROUP_MAP_SELECTION_CUSTOM PACK_UNLOADED, 32
#define GROUP_MAP_SELECTION_HISTORY PACK_UNLOADED, 33

////////////////// SPRMAIN

#define FIGURE_MOVEMENT_96_FRAMES 96

#define GROUP_FIGURE_BATHHOUSE_WORKER PACK_SPR_MAIN, 71 // 88
//#define GROUP_FIGURE_CARTPUSHER_CART PACK_SPR_MAIN, 77  // 97
//#define GROUP_FIGURE_JUGGLER PACK_SPR_MAIN, 130         // 98

//#define GROUP_FIGURE_TAX_COLLECTOR PACK_SPR_MAIN, 41    // 104

//#define GROUP_FIGURE_CARTPUSHER PACK_SPR_MAIN, 43       // 107

#define GROUP_FIGURE_DANCER_WHIP PACK_SPR_MAIN, 109     // this isn't in Pharaoh
//#define GROUP_FIGURE_MUSICIAN PACK_SPR_MAIN, 191        // 111
#define GROUP_FIGURE_HUNTER_ARROW PACK_SPR_MAIN, 0
#define GROUP_FIGURE_HUNTER_ARROW_SHADOW PACK_SPR_MAIN, 1         // 33
//#define GROUP_FIGURE_EMIGRANT PACK_SPR_MAIN, 2                    // 65
//#define GROUP_FIGURE_EMIGRANT_DEATH PACK_SPR_MAIN, 3              // 161
//#define GROUP_FIGURE_ENGINEER PACK_SPR_MAIN, 4                    //  169
//#define GROUP_FIGURE_ENGINEER_DEATH PACK_SPR_MAIN, 5              // 265
//#define GROUP_FIGURE_FIREMAN PACK_SPR_MAIN, 6                     // 273
#define GROUP_FIGURE_FIREMAN_DEATH PACK_SPR_MAIN, 7               // 369
#define GROUP_FIGURE_FIREMAN_ATFIRE PACK_SPR_MAIN, 8              // 377
#define GROUP_FIGURE_GRANARY_BOY PACK_SPR_MAIN, 9                 // 673
#define GROUP_FIGURE_GRANARY_BOY_DEATH PACK_SPR_MAIN, 10          // 769
#define GROUP_FIGURE_HUNTER_STICK PACK_SPR_MAIN, 11               // 777
//#define GROUP_FIGURE_VAGRANT PACK_SPR_MAIN, 12                    // 782 -- homeless
//#define GROUP_FIGURE_VAGRANT_DEATH PACK_SPR_MAIN, 13              // 878
//#define GROUP_FIGURE_IMMIGRANT PACK_SPR_MAIN, 14                  // 886
//#define GROUP_FIGURE_IMMIGRANT_DEATH PACK_SPR_MAIN, 15            // 982
#define GROUP_FIGURE_MARKET_BUYER PACK_SPR_MAIN, 16               // 990
#define GROUP_FIGURE_MARKET_BUYER_DEATH PACK_SPR_MAIN, 17         // 1086
#define GROUP_FIGURE_MARKET_TRADER PACK_SPR_MAIN, 18              // 1094
#define GROUP_FIGURE_MARKET_TRADER_DEATH PACK_SPR_MAIN, 19        // 1190
#define GROUP_FIGURE_VIGILE PACK_SPR_MAIN, 20                     // 1198
#define GROUP_FIGURE_VIGILE_DEATH PACK_SPR_MAIN, 21               // 1294
#define GROUP_FIGURE_VIGILE_FIGHT PACK_SPR_MAIN, 22               // 1302
#define GROUP_FIGURE_CROCODILE PACK_SPR_MAIN, 23                  // 1374
#define GROUP_FIGURE_CROCODILE_DEATH PACK_SPR_MAIN, 24            // 1470
#define GROUP_FIGURE_CROCODILE_ATTACK PACK_SPR_MAIN, 25           // 1478
#define GROUP_FIGURE_CROCODILE_SWIM PACK_SPR_MAIN, 26             // 1534
#define GROUP_FIGURE_CROCODILE_WATER_IDLE PACK_SPR_MAIN, 27       // 1622
#define GROUP_FIGURE_PHARAOH_WALK PACK_SPR_MAIN, 28               // 1710
#define GROUP_FIGURE_RIOTER_WALK PACK_SPR_MAIN, 29                // 1806
#define GROUP_FIGURE_RIOTER_DEATH PACK_SPR_MAIN, 30               // 1902
#define GROUP_FIGURE_RIOTER_ATTACK PACK_SPR_MAIN, 31              // 1910
#define GROUP_FIGURE_THIEF_WALK PACK_SPR_MAIN, 32                 // 1974
#define GROUP_FIGURE_THIEF_DEATH PACK_SPR_MAIN, 33                // 2070
#define GROUP_FIGURE_VESSEL_TRASPORT PACK_SPR_MAIN, 34            // 2078
#define GROUP_FIGURE_VESSEL_TRASPORT_DEATH PACK_SPR_MAIN, 35      // 2110
#define GROUP_FIGURE_VESSEL_REED_WORKER PACK_SPR_MAIN, 36         // 2121
#define GROUP_FIGURE_TAXMAN_WALK PACK_SPR_MAIN, 37                // 2129
#define GROUP_FIGURE_TAXMAN_DEATH PACK_SPR_MAIN, 38               // 2225
#define GROUP_FIGURE_PUSHER_WORK PACK_SPR_MAIN, 39                // 2233
#define GROUP_FIGURE_PUSHER_MOVE PACK_SPR_MAIN, 40                // 2353
#define GROUP_FIGURE_HUNTER_OSTRICH PACK_SPR_MAIN, 41             // 2449
#define GROUP_FIGURE_HUNTER_OSTRICH_DEATH PACK_SPR_MAIN, 42       // 2545
#define GROUP_FIGURE_HUNTER_OSTRICH_HID PACK_SPR_MAIN, 43         // 2553
#define GROUP_FIGURE_HUNTER_OSTRICH_HID_DEATH PACK_SPR_MAIN, 44   // 2649
#define GROUP_FIGURE_HUNTER_OSTRICH_MOVE PACK_SPR_MAIN, 45        // 2657
#define GROUP_FIGURE_HUNTER_OSTRICH_MOVE_DEATH PACK_SPR_MAIN, 46  // 2753
#define GROUP_FIGURE_HUNTER_OSTRICH_HUNT PACK_SPR_MAIN, 47        // 2761
#define GROUP_FIGURE_HUNTER_OSTRICH_FIGHT PACK_SPR_MAIN, 48       // 2857
#define GROUP_FIGURE_HUNTER_OSTRICH_UNPACK PACK_SPR_MAIN, 49      // 2953
#define GROUP_FIGURE_HUNTER_OSTRICH_PACK PACK_SPR_MAIN, 50        // 3049
#define GROUP_FIGURE_HUNTER_OSTRICH_MOVE_PACKED PACK_SPR_MAIN, 51 // 3193
#define GROUP_FIGURE_DONKEY PACK_SPR_MAIN, 52                     // 3289
#define GROUP_FIGURE_DONKEY_DEATH PACK_SPR_MAIN, 53               // 3385
#define GROUP_FIGURE_WALL_GUY PACK_SPR_MAIN, 54                   // 3393
#define GROUP_FIGURE_WALL_GUY_DEATH PACK_SPR_MAIN, 55             // 3489
#define GROUP_FIGURE_WALL_GUY_SHOOT PACK_SPR_MAIN, 56             // 3497
#define GROUP_FIGURE_LIBRARIAN PACK_SPR_MAIN, 57                  // 3593
#define GROUP_FIGURE_LIBRARIAN_DEATH PACK_SPR_MAIN, 58            // 3689
#define GROUP_FIGURE_WATER_CARRIER PACK_SPR_MAIN, 59              // 3697
#define GROUP_FIGURE_WATER_CARRIER_DEATH PACK_SPR_MAIN, 60        // 3793
#define GROUP_FIGURE_LEGIONER_MISSILE PACK_SPR_MAIN, 61           // 3801
#define GROUP_FIGURE_LEGIONER_MISSILE_DEATH PACK_SPR_MAIN, 62     // 3897
#define GROUP_FIGURE_LEGIONER_MISSILE_SHOOT PACK_SPR_MAIN, 63     // 3905
#define GROUP_FIGURE_LEGIONER_AUX PACK_SPR_MAIN, 64               // 4001
#define GROUP_FIGURE_LEGIONER_AUX_DEATH PACK_SPR_MAIN, 65         // 4097
#define GROUP_FIGURE_LEGIONER_AUX_FIGHT PACK_SPR_MAIN, 66         // 4105
#define GROUP_FIGURE_LEGIONER_HEAVY PACK_SPR_MAIN, 67             // 4169
#define GROUP_FIGURE_LEGIONER_HEAVY_DEATH PACK_SPR_MAIN, 68       // 4265
#define GROUP_FIGURE_LEGIONER_HEAVY_RIDE PACK_SPR_MAIN, 69        // 4273
#define GROUP_FIGURE_LEGIONER_HEAVY_WAIT PACK_SPR_MAIN, 70        // 4369
#define GROUP_FIGURE_DOCTOR PACK_SPR_MAIN, 71                     // 4377
#define GROUP_FIGURE_DOCTOR_DEATH PACK_SPR_MAIN, 72               // 4473
#define GROUP_FIGURE_LUMBERJACK PACK_SPR_MAIN, 73                 // 4481
#define GROUP_FIGURE_LUMBERJACK_DEATH PACK_SPR_MAIN, 74           // 4577
#define GROUP_FIGURE_LUMBERJACK_WORK PACK_SPR_MAIN, 75            // 4585
#define GROUP_FIGURE_LUMBERJACK_WALK_WITH_LOG PACK_SPR_MAIN, 76   // 4681
#define GROUP_FIGURE_CART_EMPTY PACK_SPR_MAIN, 77                 // 4777
#define GROUP_FIGURE_CART_REED PACK_SPR_MAIN, 78                  // 4785
#define GROUP_FIGURE_CART_MEAT PACK_SPR_MAIN, 79                  // 4809

#define GROUP_FIGURE_BRICK_WALKER PACK_SPR_MAIN, 109          // 5417
#define GROUP_FIGURE_BRICK_WALKER_DEATH PACK_SPR_MAIN, 110    // 5513
#define GROUP_FIGURE_BRICK_WALKER_WORK PACK_SPR_MAIN, 111     // 5521
#define GROUP_FIGURE_BRICK_WALKER_WORK_END PACK_SPR_MAIN, 112 // 5705

#define GROUP_FIGURE_LEGIONARY_HORSE PACK_SPR_MAIN, 113 // 5777
#define GROUP_FIGURE_BIRDS PACK_SPR_MAIN, 114           // 5873
#define GROUP_FIGURE_BIRDS2 PACK_SPR_MAIN, 115          // 5898

#define GROUP_FIGURE_PEASANT PACK_SPR_MAIN, 116       // 5923
#define GROUP_FIGURE_PEASANT_DEATH PACK_SPR_MAIN, 117 // 6019

#define GROUP_FIGURE_TRADE_BOAT_WORKER PACK_SPR_MAIN, 118 // 6027
#define GROUP_FIGURE_DOCK_PUSHER PACK_SPR_MAIN, 119       // 6131
#define GROUP_FIGURE_DANCE_WALKER PACK_SPR_MAIN, 120      // 6235

#define GROUP_FIGURE_JUGGLER_WALK_UP PACK_SPR_MAIN, 121   // 6355
#define GROUP_FIGURE_JUGGLER_WALK_LINE PACK_SPR_MAIN, 122 // 6451

#define GROUP_FIGURE_SENET PACK_SPR_MAIN, 123       // 6547
#define GROUP_FIGURE_SENET_DEATH PACK_SPR_MAIN, 124 // 6579

#define GROUP_FIGURE_DANCER PACK_SPR_MAIN, 128          // 101

#define GROUP_FIGURE_FERRY_BOAT PACK_SPR_MAIN, 138       // 7137
#define GROUP_FIGURE_FERRY_BOAT_DEATH PACK_SPR_MAIN, 139 // 7169
#define GROUP_FIGURE_FERRY_BOAT_IDLE PACK_SPR_MAIN, 140  // 7180

#define GROUP_FIGURE_WAR_BOAT PACK_SPR_MAIN, 141       // 7188
#define GROUP_FIGURE_WAR_BOAT_DEATH PACK_SPR_MAIN, 142 // 7220
#define GROUP_FIGURE_WAR_BOAT_IDLE PACK_SPR_MAIN, 143  // 7231

#define GROUP_FIGURE_CARPENTER PACK_SPR_MAIN, 145       // 7247
#define GROUP_FIGURE_CARPENTER_DEATH PACK_SPR_MAIN, 146 // 7343

#define GROUP_FIGURE_STONEWALKER_WORK_DOWN PACK_SPR_MAIN, 147   // 7351
#define GROUP_FIGURE_STONEWALKER_WORK_UP PACK_SPR_MAIN, 148     // 7407
#define GROUP_FIGURE_STONEWALKER_WORK_SLIDE PACK_SPR_MAIN, 149  // 7463
#define GROUP_FIGURE_STONEWALKER_WALK PACK_SPR_MAIN, 150        // 7487
#define GROUP_FIGURE_STONEWALKER_DEATH PACK_SPR_MAIN, 151       // 7583
#define GROUP_FIGURE_STONEWALKER_WORK_DOWN2 PACK_SPR_MAIN, 152  // 7591
#define GROUP_FIGURE_STONEWALKER_WORK_UP2 PACK_SPR_MAIN, 153    // 7647
#define GROUP_FIGURE_STONEWALKER_WORK_SLIDE2 PACK_SPR_MAIN, 154 // 7703


//#define GROUP_FIGURE_OSTRICH_WALK PACK_SPR_MAIN, 156   // 7823 - 0
#define GROUP_FIGURE_OSTRICH_DEATH PACK_SPR_MAIN, 157  // 7919 - 96
#define GROUP_FIGURE_OSTRICH_ATTACK PACK_SPR_MAIN, 158 // 7927 - 104
#define GROUP_FIGURE_OSTRICH_EATING PACK_SPR_MAIN, 159 // 7983 - 160
#define GROUP_FIGURE_OSTRICH_IDLE PACK_SPR_MAIN, 160   // 8047

#define GROUP_FIGURE_HYENA_WALK PACK_SPR_MAIN, 161   // 8111
#define GROUP_FIGURE_HYENA_ATTACK PACK_SPR_MAIN, 162 // 8207
#define GROUP_FIGURE_HYENA_DEATH PACK_SPR_MAIN, 163  // 8255
#define GROUP_FIGURE_HYENA_IDLE PACK_SPR_MAIN, 164   // 8261
#define GROUP_FIGURE_HYENA_EATING PACK_SPR_MAIN, 165 // 8309

#define GROUP_FIGURE_SLED_EMPTY PACK_SPR_MAIN, 166 // 8357

#define GROUP_FIGURE_HERBALIST PACK_SPR_MAIN, 180       // 8469
#define GROUP_FIGURE_HERBALIST_DEATH PACK_SPR_MAIN, 181 // 8565

#define GROUP_FIGURE_DENTIST PACK_SPR_MAIN, 182       // 8573
#define GROUP_FIGURE_DENTIST_DEATH PACK_SPR_MAIN, 183 // 8669

#define GROUP_FIGURE_HUNTERBIRD PACK_SPR_MAIN, 184       // 8677
#define GROUP_FIGURE_HUNTERBIRD_DEATH PACK_SPR_MAIN, 185 // 8773
#define GROUP_FIGURE_HUNTERBIRD_WORK PACK_SPR_MAIN, 186  // 8781

#define GROUP_FIGURE_PTAH_PRIEST PACK_SPR_MAIN, 187       // 8877
#define GROUP_FIGURE_PTAH_PRIEST_DEATH PACK_SPR_MAIN, 188 // 8973

#define GROUP_FIGURE_GOVERNOR PACK_SPR_MAIN, 189       // 8981
#define GROUP_FIGURE_GOVERNOR_DEATH PACK_SPR_MAIN, 190 // 9077

#define GROUP_FIGURE_MUSIC_WALKER PACK_SPR_MAIN, 191       // 9085
#define GROUP_FIGURE_MUSIC_WALKER_DEATH PACK_SPR_MAIN, 192 // 9181

#define GROUP_FIGURE_SETH_PRIEST PACK_SPR_MAIN, 193       // 9189
#define GROUP_FIGURE_SETH_PRIEST_DEATH PACK_SPR_MAIN, 194 // 9285

#define GROUP_FIGURE_EMBALMER PACK_SPR_MAIN, 195       // 9293
#define GROUP_FIGURE_EMBALMER_DEATH PACK_SPR_MAIN, 196 // 9389

#define GROUP_FIGURE_OSIRIS_PRIEST PACK_SPR_MAIN, 197       // 9397
#define GROUP_FIGURE_OSIRIS_PRIEST_DEATH PACK_SPR_MAIN, 198 // 9493

//#define GROUP_FIGURE_SCRIBER PACK_SPR_MAIN, 199       // 9501
//#define GROUP_FIGURE_SCRIBER_DEATH PACK_SPR_MAIN, 200 // 9597

//#define GROUP_FIGURE_TEACHER PACK_SPR_MAIN, 201       // 9605
//#define GROUP_FIGURE_TEACHER_DEATH PACK_SPR_MAIN, 202 // 9701

#define GROUP_FIGURE_DESEASED PACK_SPR_MAIN, 203       // 9709
#define GROUP_FIGURE_DESEASED_A PACK_SPR_MAIN, 204     // 9805
#define GROUP_FIGURE_DESEASED_DEATH PACK_SPR_MAIN, 205 // 9901

//#define GROUP_FIGURE_LABOR_SEEKER PACK_SPR_MAIN, 206       // 9909
//#define GROUP_FIGURE_LABOR_SEEKER_DEATH PACK_SPR_MAIN, 207 // 10005

#define GROUP_FIGURE_NOBLE PACK_SPR_MAIN, 208           // 10013
#define GROUP_FIGURE_NOBLE_DEATH PACK_SPR_MAIN, 209     // 10109

#define GROUP_FIGURE_RA_PRIEST PACK_SPR_MAIN, 210       // 10117
#define GROUP_FIGURE_RA_PRIEST_DEATH PACK_SPR_MAIN, 211 // 10213

#define GROUP_FIGURE_MAGISTRATE PACK_SPR_MAIN, 212       // 10221
#define GROUP_FIGURE_MAGISTRATE_DEATH PACK_SPR_MAIN, 213 // 10317

#define GROUP_FIGURE_IMMIGRANT_CART PACK_SPR_MAIN, 52      // 131
#define GROUP_FIGURE_LION PACK_SPR_MAIN, 161               // 163
//#define GROUP_FIGURE_SHIP PACK_SPR_MAIN, 34                // 165
#define GROUP_FIGURE_TOWER_SENTRY PACK_SPR_MAIN, 194       // TODO
#define GROUP_FIGURE_MISSILE PACK_SPR_MAIN, 198            // TODO
#define GROUP_FIGURE_BALLISTA PACK_SPR_MAIN, 200           // TODO
#define GROUP_FIGURE_CHARIOTEER PACK_SPR_MAIN, 215         // this isn't in Pharaoh
#define GROUP_FIGURE_HIPPODROME_HORSE_1 PACK_SPR_MAIN, 217 // // this isn't in Pharaoh this isn't in Pharaoh
#define GROUP_FIGURE_HIPPODROME_HORSE_2 PACK_SPR_MAIN, 218 // this isn't in Pharaoh
#define GROUP_FIGURE_HIPPODROME_CART_1 PACK_SPR_MAIN, 219  // this isn't in Pharaoh
#define GROUP_FIGURE_HIPPODROME_CART_2 PACK_SPR_MAIN, 220  // this isn't in Pharaoh
#define GROUP_FIGURE_SHIPWRECK PACK_SPR_MAIN, 226          // this isn't in Pharaoh
#define GROUP_FIGURE_MISSIONARY PACK_SPR_MAIN, 230         // this isn't in Pharaoh
#define GROUP_FIGURE_SHEEP PACK_SPR_MAIN, 233              // TODO
#define GROUP_FIGURE_HYENA PACK_SPR_MAIN, 157
#define GROUP_FIGURE_SCRAPER_EMPTY PACK_SPR_MAIN, 158

#define GROUP_FIGURE_SCRAPER_BLOCK_LIMESTONE PACK_SPR_MAIN, 159
#define GROUP_FIGURE_SCRAPER_BLOCK_SANDSONE PACK_SPR_MAIN, 160
#define GROUP_FIGURE_SCRAPER_BLOCK_GRANITE PACK_SPR_MAIN, 161
#define GROUP_FIGURE_SCRAPER_BLOCK_PLAINSTONE PACK_SPR_MAIN, 162
#define GROUP_FIGURE_SCRAPER_BLOCK_COPPER PACK_SPR_MAIN, 163
#define GROUP_FIGURE_SCRAPER_BLOCK_CLAY PACK_SPR_MAIN, 164
#define GROUP_FIGURE_SCRAPER_EMPTY_UP PACK_SPR_MAIN, 165
#define GROUP_FIGURE_SCRAPER_BLOCK_LIMESTONE_UP PACK_SPR_MAIN, 166
#define GROUP_FIGURE_SCRAPER_BLOCK_SANDSONE_UP PACK_SPR_MAIN, 167
#define GROUP_FIGURE_SCRAPER_BLOCK_GRANITE_UP PACK_SPR_MAIN, 168
#define GROUP_FIGURE_SCRAPER_BLOCK_PLAINSTONE_UP PACK_SPR_MAIN, 169
#define GROUP_FIGURE_SCRAPER_BLOCK_COPPER_UP PACK_SPR_MAIN, 170
#define GROUP_FIGURE_SCRAPER_BLOCK_CLAY_UP PACK_SPR_MAIN, 171
#define GROUP_FIGURE_CITIZEN_172 PACK_SPR_MAIN, 172
#define GROUP_FIGURE_CITIZEN_173 PACK_SPR_MAIN, 173
#define GROUP_FIGURE_CITIZEN_174 PACK_SPR_MAIN, 174
#define GROUP_FIGURE_CITIZEN_175 PACK_SPR_MAIN, 175

#define GROUP_FIGURE_CROCODILE PACK_SPR_MAIN, 23                          // 235
#define GROUP_FIGURE_CAESAR_LEGIONARY PACK_SPR_MAIN, 236                  // this isn't in Pharaoh
#define GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_FOOD PACK_SPR_MAIN, 237     // this isn't in Pharaoh
#define GROUP_FIGURE_CARTPUSHER_CART_MULTIPLE_RESOURCE PACK_SPR_MAIN, 250 // this isn't in Pharaoh
#define GROUP_PRIEST_RA PACK_SPR_MAIN, 210
#define GROUP_PRIEST_SETH PACK_SPR_MAIN, 193
#define GROUP_PRIEST_PTAH PACK_SPR_MAIN, 187
#define GROUP_PRIEST_BAST PACK_SPR_MAIN, 208
#define GROUP_FIGURE_MARKET_LADY_2 PACK_SPR_MAIN, 18
#define GROUP_FIGURE_POLICEMAN PACK_SPR_MAIN, 20
#define GROUP_FIGURE_REED_GATHERER PACK_SPR_MAIN, 37

//#define GROUP_FIGURE_TRADE_CARAVAN_DONKEY PACK_SPR_MAIN, 52
//#define GROUP_FIGURE_WATER_CARRIER PACK_SPR_MAIN, 59
#define GROUP_FIGURE_WORKER_PH PACK_SPR_MAIN, 116
#define GROUP_FIGURE_MORTUARY PACK_SPR_MAIN, 195
#define GROUP_FIGURE_MAGISTRATE PACK_SPR_MAIN, 212
#define GROUP_FIGURE_ARCHER_PH PACK_SPR_MAIN, 62
#define GROUP_FIGURE_INFANTRY_PH PACK_SPR_MAIN, 65
#define GROUP_FIGURE_CHARIOTEER_PH PACK_SPR_MAIN, 68
#define GROUP_FIGURE_LUMBERJACK PACK_SPR_MAIN, 73

////////////////// SPRAMBIENT

//#define GROUP_FIGURE_CARGO_FLOTSAM PACK_SPR_AMBIENT, 0  // 1 + 15831
#define GROUP_BUILDING_DOCK_DOCKERS PACK_SPR_AMBIENT, 55 // 171
#define GROUP_FIGURE_SHAD_NE PACK_SPR_AMBIENT, 1  // 37 + 15831
#define GROUP_FIGURE_SHAD_SE PACK_SPR_AMBIENT, 2  // 50 + 15831
#define GROUP_FIGURE_SHAD_SW PACK_SPR_AMBIENT, 3  // 63 + 15831
#define GROUP_FIGURE_SHAD_NW PACK_SPR_AMBIENT, 4  // 76 + 15831
#define GROUP_FIGURE_EXPLOSION_SMALL PACK_SPR_AMBIENT, 5  // 89 + 15831
#define GROUP_DANCERS_SHOW PACK_SPR_AMBIENT, 6           // 104 + 15831
//#define GROUP_JUGGLERS_SHOW_ALONE PACK_SPR_AMBIENT, 7    // 140 + 15831
//#define GROUP_FIGURE_FISH_JUMPING PACK_SPR_AMBIENT, 8    // 166 + 15831
//#define GROUP_MUSICIANS_SHOW2 PACK_SPR_AMBIENT, 9        // 191 + 15831
//#define GROUP_MUSICIANS_SHOW1 PACK_SPR_AMBIENT, 10       // 203 + 15831
//#define GROUP_WATER_BUBBLES PACK_SPR_AMBIENT, 11         // 215 + 15831
//#define GROUP_FIGURE_EXPLOSION PACK_SPR_AMBIENT, 12             // 238 + 15831
#define GROUP_FIGURE_BEDOUIN PACK_SPR_AMBIENT, 13        // 258 + 15831
#define GROUP_FIGURE_BEDOUIN_DEATH PACK_SPR_AMBIENT, 14  // 354 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE PACK_SPR_AMBIENT, 15  // 362 + 15831
#define GROUP_FIGURE_JAVELIN_SHADOW PACK_SPR_AMBIENT, 16  // 458 + 15831
#define GROUP_FIGURE_JAVELIN_ITSELF PACK_SPR_AMBIENT, 17  // 470 + 15831
#define GROUP_FIGURE_JAVELIN_ITSELF_DEATH PACK_SPR_AMBIENT, 18  // 566 + 15831
#define GROUP_FIGURE_JAVELIN_ITSELF_ATTACK PACK_SPR_AMBIENT, 19  // 574 + 15831
//#define GROUP_FIGURE_TRADE_CARAVAN PACK_SPR_AMBIENT, 20  // 130
#define GROUP_FIGURE_YARD_WAR PACK_SPR_AMBIENT, 20  // 670 + 15831
#define GROUP_FIGURE_YARD_WAR_DEATH PACK_SPR_AMBIENT, 21  // 766 + 15831
#define GROUP_FIGURE_HIPPO_WALK PACK_SPR_AMBIENT, 22      // 774 + 15831
#define GROUP_FIGURE_HIPPO_DEATH PACK_SPR_AMBIENT, 23     // 870 + 15831
#define GROUP_FIGURE_HIPPO_ATTACK PACK_SPR_AMBIENT, 24     // 878 + 15831
#define GROUP_FIGURE_HIPPO_SWEEMS PACK_SPR_AMBIENT, 25     // 934 + 15831
#define GROUP_FIGURE_HIPPO_SWEAM_ATTACK PACK_SPR_AMBIENT, 26  // 1030 + 15831
#define GROUP_FIGURE_HIPPO_SWEAM_IDLE PACK_SPR_AMBIENT, 27  // 1126 + 15831
#define GROUP_FIGURE_HIPPO_EATING PACK_SPR_AMBIENT, 28  // 1222 + 15831
#define GROUP_FIGURE_HIPPO_FUNNY_DANCE PACK_SPR_AMBIENT, 29  // 1318 + 15831
#define GROUP_FIGURE_ANTELOPE_WALK PACK_SPR_AMBIENT, 30  // 1355 + 15831
#define GROUP_FIGURE_ANTELOPE_DEATH PACK_SPR_AMBIENT, 31  // 1451 + 15831
#define GROUP_FIGURE_ANTELOPE_ATTACK PACK_SPR_AMBIENT, 32  // 1459 + 15831
#define GROUP_FIGURE_ANTELOPE_EATING PACK_SPR_AMBIENT, 33  // 1555 + 15831
#define GROUP_FIGURE_ANTELOPE_IDLE PACK_SPR_AMBIENT, 34  // 1683 + 15831
#define GROUP_FIGURE_ANTELOPE_RUN PACK_SPR_AMBIENT, 35  // 1779 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE_WALK PACK_SPR_AMBIENT, 36  // 1843 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE_DEATH PACK_SPR_AMBIENT, 37  // 1939 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE_HUNT PACK_SPR_AMBIENT, 38  // 1947 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE_PACK_PREPARE PACK_SPR_AMBIENT, 39  // 2043 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE_PACK_PREPARE2 PACK_SPR_AMBIENT, 40  // 2139 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE_PACK PACK_SPR_AMBIENT, 41  // 2235 + 15831
#define GROUP_FIGURE_HUNTER_ANTELOPE_PACK_WALK PACK_SPR_AMBIENT, 42  // 2379 + 15831
#define GROUP_FIGURE_HUNTER_JAVELIN_SHADOW PACK_SPR_AMBIENT, 43  // 2475 + 15831
#define GROUP_FIGURE_HUNTER_JAVELIN PACK_SPR_AMBIENT, 44  // 2507 + 15831
#define GROUP_YARD_WAR_ANIM PACK_SPR_AMBIENT, 45  // 2539 + 15831
//#define GROUP_FISH_WHARF_ANIM PACK_SPR_AMBIENT, 47  // 2551 + 15831
#define GROUP_MINING_ANIM PACK_SPR_AMBIENT, 47  // 2647 + 15831
#define GROUP_QUARY_WORNING_1_ANIM PACK_SPR_AMBIENT, 48  // 2671 + 15831
#define GROUP_QUARY_WORNING_2_ANIM PACK_SPR_AMBIENT, 49  // 2688 + 15831
#define GROUP_WAREHOUSE_ANIM PACK_SPR_AMBIENT, 50  // 2695 + 15831
#define GROUP_YARD_CARGO_ANIM PACK_SPR_AMBIENT, 51  // 2702 + 15831
#define GROUP_YARD_FERRY_ANIM PACK_SPR_AMBIENT, 52  // 2718 + 15831
#define GROUP_YARD_REED_ANIM PACK_SPR_AMBIENT, 53  // 2730 + 15831
#define GROUP_DOCK_DUDE_1_ANIM PACK_SPR_AMBIENT, 54  // 2742 + 15831
#define GROUP_DOCK_DUDE_2_ANIM PACK_SPR_AMBIENT, 55  // 2754 + 15831
#define GROUP_DOCK_DUDE_3_ANIM PACK_SPR_AMBIENT, 56  // 2854 + 15831

#define GROUP_WATER_LIFT_ANIM PACK_SPR_AMBIENT, 1        // sprambient
#define GROUP_GRANARY_ANIM_PH PACK_SPR_AMBIENT, 47
#define GROUP_WAREHOUSE_ANIM_PH PACK_SPR_AMBIENT, 51
//   #define GROUP_DOCK_WAITING  PACK_SPR_AMBIENT,  55
//   #define GROUP_DOCK_UNLOADING  PACK_SPR_AMBIENT,  56
//#define GROUP_MINES PACK_SPR_AMBIENT, 48

#define GROUP_FIGURE_ANTILOPE PACK_SPR_AMBIENT, 30
#define GROUP_FIGURE_HUNTER2 PACK_SPR_AMBIENT, 36
#define GROUP_SHIP_BUILDING_1 PACK_SPR_AMBIENT, 45
#define GROUP_SHIP_BUILDING_2 PACK_SPR_AMBIENT, 52
#define GROUP_SHIP_BUILDING_3 PACK_SPR_AMBIENT, 53
#define GROUP_SHIP_BUILDING_4 PACK_SPR_AMBIENT, 54

////////////////// MONUMENT

#define GROUP_MONUMENT_BLOCKS PACK_MONUMENT, 1
#define GROUP_MONUMENT_TERRAIN PACK_MONUMENT, 2
#define GROUP_MONUMENT_DITCHES_PHASE_1 PACK_MONUMENT, 3
#define GROUP_MONUMENT_DITCHES_PHASE_2 PACK_MONUMENT, 4
#define GROUP_MONUMENT_DITCHES_PHASE_3 PACK_MONUMENT, 5
#define GROUP_MONUMENT_DITCHES_PHASE_4 PACK_MONUMENT, 6
#define GROUP_MONUMENT_TOMB_FLOOR PACK_MONUMENT, 7
#define GROUP_MONUMENT_CORNER_POLES PACK_MONUMENT, 8
#define GROUP_MONUMENT_EXTERIORS_END_DRY PACK_MONUMENT, 9
#define GROUP_MONUMENT_EXTERIORS_RUNS PACK_MONUMENT, 10
#define GROUP_MONUMENT_EXTERIORS_END_WET PACK_MONUMENT, 11
#define GROUP_MONUMENT_EXTRA_BLOCKS PACK_MONUMENT, 12

////////////////// TEMPLE

#define GROUP_BUILDING_TEMPLE_COMPLEX_MAIN PACK_TEMPLE, 1
#define GROUP_BUILDING_TEMPLE_COMPLEX_ORACLE PACK_TEMPLE, 2
#define GROUP_BUILDING_TEMPLE_COMPLEX_ALTAR PACK_TEMPLE, 3
#define GROUP_BUILDING_TEMPLE_COMPLEX_FLOORING PACK_TEMPLE, 4
#define GROUP_BUILDING_TEMPLE_COMPLEX_STATUE_1 PACK_TEMPLE, 5
#define GROUP_BUILDING_TEMPLE_COMPLEX_STATUE_2 PACK_TEMPLE, 6
#define GROUP_BUILDING_TEMPLE_COMPLEX_UPGRADES PACK_TEMPLE, 7

////////////////// EXPANSION

#define GROUP_BIG_PEOPLE_2 PACK_EXPANSION, 1
#define GROUP_SCORPION_ICON PACK_EXPANSION, 2
#define GROUP_RESOURCE_ICONS_2 PACK_EXPANSION, 3
#define GROUP_BUILDING_WAREHOUSE_STORAGE_FILLED_2 PACK_EXPANSION, 4
#define GROUP_BUILDING_FARM_CROPS_HENNA PACK_EXPANSION, 5
#define GROUP_BUILDING_ZOO PACK_EXPANSION, 6
#define GROUP_BLOOD_TILES PACK_EXPANSION, 7
#define GROUP_BLOOD_FLOODPLAIN PACK_EXPANSION, 8
#define GROUP_BLOOD_FLOODSYSTEM PACK_EXPANSION, 9
#define GROUP_BLOOD_MARSHLANDS PACK_EXPANSION, 11
#define GROUP_BLOOD_TRANSPORT PACK_EXPANSION, 13
#define GROUP_BLOOD_WELL PACK_EXPANSION, 24
#define GROUP_BLOOD_WATER_SUPPLY PACK_EXPANSION, 25
#define GROUP_BUILDING_LAMP_WORKSHOP PACK_EXPANSION, 26
#define GROUP_BUILDING_PAINT_WORKSHOP PACK_EXPANSION, 27
#define GROUP_BUILDING_GUILD_ARTISANS PACK_EXPANSION, 31
#define GROUP_FROG_ICON PACK_EXPANSION, 32
#define GROUP_TERRAIN_CLIFF PACK_EXPANSION, 33
//#define GROUP_BUILDING_STATUE_LARGE_2 PACK_EXPANSION, 35
//#define GROUP_BUILDING_STATUE_MEDIUM_2 PACK_EXPANSION, 36
//#define GROUP_BUILDING_STATUE_SMALL_2 PACK_EXPANSION, 37
#define GROUP_MISSION_SELECT_2 PACK_EXPANSION, 38      // ????
#define GROUP_HISTORY_INFO_2 PACK_EXPANSION, 39        // ????
#define GROUP_BLOOD_EDGES PACK_EXPANSION, 40           // ????
#define GROUP_BREAKAWAY_SPLASH_LOGO PACK_EXPANSION, 41 // ????

////////////////// TODO? (editor image groups)

#define GROUP_EDITOR_SCENARIO_IMAGE 0, 22
#define GROUP_EDITOR_BUILDING_CROPS 0, 23
#define GROUP_EDITOR_EMPIRE_MAP 0, 47
//#define GROUP_EDITOR_SIDE_PANEL 0, 80
#define GROUP_EDITOR_RESOURCE_ICONS 0, 129
#define GROUP_EDITOR_EMPIRE_PANELS 0, 172
#define GROUP_EDITOR_EMPIRE_RESOURCES 0, 173
#define GROUP_EDITOR_BUILDING_NATIVE 0, 183
#define GROUP_EDITOR_EMPIRE_FOREIGN_CITY 0, 223
#define GROUP_EDITOR_TRADE_AMOUNT 0, 243
