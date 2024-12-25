log_info("akhenaten: building sounds started")

building_sounds = [
  { type: BUILDING_TAX_COLLECTOR,						sound: "Wavs/taxfarm.wav"},
  { type: BUILDING_TAX_COLLECTOR_UPGRADED,	sound: "Wavs/taxfarm.wav"},
  { type: BUILDING_VILLAGE_PALACE, 					sound: "Wavs/palace.wav"},
  { type: BUILDING_TOWN_PALACE, 						sound: "Wavs/palace.wav"},
  { type: BUILDING_CITY_PALACE, 						sound: "Wavs/palace.wav"},
  { type: BUILDING_GARDENS,									sound: "Wavs/park1.wav"},
  { type: BUILDING_PLAZA, 									sound: "Wavs/FANFARE1.wav"},
  { type: BUILDING_SMALL_STATUE, 						sound: "Wavs/statue1.wav"},
  { type: BUILDING_MEDIUM_STATUE, 					sound: "Wavs/statue1.wav"},
  { type: BUILDING_LARGE_STATUE,						sound: "Wavs/statue1.wav"},
  { type: BUILDING_BARLEY_FARM, 						sound: "Wavs/barleyfarm.wav"},
  { type: BUILDING_FLAX_FARM, 							sound: "Wavs/flaxfarm.wav"},
  { type: BUILDING_GRAIN_FARM,							sound: "Wavs/farm1.wav"},
  { type: BUILDING_LETTUCE_FARM,						sound: "Wavs/lettucefarm.wav"},
  { type: BUILDING_POMEGRANATES_FARM,				sound: "Wavs/pomfarm.wav"},
	{ type: BUILDING_CHICKPEAS_FARM,					sound: "Wavs/chickfarm.wav"},
	{ type: BUILDING_FIGS_FARM,								sound: "Wavs/figs_farm.wav"},
	{ type: BUILDING_HENNA_FARM,							sound: "Wavs/farm2.wav"},
	{ type: BUILDING_HUNTING_LODGE, 					sound: "Wavs/lo_hunt.wav" },
	{ type: BUILDING_GRANITE_QUARRY, 					sound: "Wavs/marble.wav" },
	{ type: BUILDING_COPPER_MINE, 						sound: "Wavs/gold.wav" },
	{ type: BUILDING_GOLD_MINE, 							sound: "Wavs/gold.wav" },
	{ type: BUILDING_WOOD_CUTTERS, 						sound: "Wavs/lumber.wav" },
	{ type: BUILDING_CLAY_PIT, 								sound: "Wavs/clay.wav" },
	{ type: BUILDING_REED_GATHERER, 					sound: "Wavs/reedfarm.wav" },
	{ type: BUILDING_BREWERY_WORKSHOP,				sound: "Wavs/brewery.wav"},
	{ type: BUILDING_WEAVER_WORKSHOP,	  			sound: "Wavs/flaxfarm.wav"},
	{ type: BUILDING_WEAPONSMITH,							sound: "Wavs/weapon.wav"},
	{ type: BUILDING_JEWELS_WORKSHOP,	  			sound: "Wavs/gem_r.wav"},
	{ type: BUILDING_POTTERY_WORKSHOP,  			sound: "Wavs/pottery.wav"},
	{ type: BUILDING_BRICKS_WORKSHOP,					sound: "Wavs/brick.wav"},
	{ type: BUILDING_WORK_CAMP,				 				sound: "Wavs/eng_r.wav"},
	{ type: BUILDING_FISHING_WHARF,		  			sound: "Wavs/shipyrd_r.wav"},
	{ type: BUILDING_SHIPWRIGHT,							sound: "Wavs/shipyrd.wav"},
	{ type: BUILDING_ARCHITECT_POST, 					sound: "Wavs/eng.wav"},
	{ type: BUILDING_SHRINE_OSIRIS, 					sound: "Wavs/shr_osiris.wav"},
	{ type: BUILDING_SHRINE_RA, 							sound: "Wavs/SHR_RA.wav"},
	{ type: BUILDING_SHRINE_PTAH, 						sound: "Wavs/SHR_PTAH.wav"},
	{ type: BUILDING_SHRINE_SETH, 						sound: "Wavs/SHR_SETH.wav"},
	{ type: BUILDING_SHRINE_BAST, 						sound: "Wavs/SHR_BAST.wav"},
	{ type: BUILDING_TEMPLE_OSIRIS, 					sound: "Wavs/tem_osiris_l.wav"},
	{ type: BUILDING_TEMPLE_RA, 							sound: "Wavs/tem_RA_L.wav"},
	{ type: BUILDING_TEMPLE_PTAH, 						sound: "Wavs/tem_ptah_l.wav"},
	{ type: BUILDING_TEMPLE_SETH, 						sound: "Wavs/tem_seth_l.wav"},
	{ type: BUILDING_TEMPLE_BAST, 						sound: "Wavs/tem_bast_l.wav"},
	{ type: BUILDING_BOOTH, 									sound: "Wavs/jugger_r.wav"},
	{ type: BUILDING_BANDSTAND, 							sound: "Wavs/music_r.wav"},
	{ type: BUILDING_PAVILLION,  							sound: "Wavs/music_r.wav"},
	{ type: BUILDING_JUGGLER_SCHOOL,					sound: "Wavs/juggler_school.wav"},
	{ type: BUILDING_CONSERVATORY, 						sound: "Wavs/music_school.wav"},
	{ type: BUILDING_DANCE_SCHOOL, 						sound: "Wavs/dance_school.wav"},
	{ type: BUILDING_SENET_MASTER, 						sound: "Wavs/bullfight_school.wav"},
	{ type: BUILDING_APOTHECARY, 							sound: "Wavs/apothecary.wav"},
	{ type: BUILDING_DENTIST, 								sound: "Wavs/dentist.wav"},
	{ type: BUILDING_MORTUARY, 								sound: "Wavs/mortuary.wav"},
	{ type: BUILDING_PHYSICIAN, 							sound: "Wavs/physician.wav"},
	{ type: BUILDING_SCRIBAL_SCHOOL,					sound: "Wavs/school_scribe.wav"},
	{ type: BUILDING_PAPYRUS_WORKSHOP,  			sound: "Wavs/paper.wav"},
	{ type: BUILDING_CATTLE_RANCH,						sound: "Wavs/cowfarm_r.wav"},
	{ type: BUILDING_FESTIVAL_SQUARE,					sound: "Wavs/prefecture.wav"},
	{ type: BUILDING_BAZAAR,									sound: "Wavs/MARKET.WAV"},
	{ type: BUILDING_FIREHOUSE,								sound: "Wavs/prefecture.wav"},
	{ type: BUILDING_HOUSE_CRUDE_HUT,					sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_STURDY_HUT,				sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_MEAGER_SHANTY,			sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_COMMON_SHANTY,			sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_ROUGH_COTTAGE,			sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_ORDINARY_COTTAGE,	sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_MODEST_HOMESTEAD,	sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_SPACIOUS_HOMESTEAD,sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_MODEST_APARTMENT,	sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_SPACIOUS_APARTMENT,sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_COMMON_RESIDENCE,	sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_SPACIOUS_RESIDENCE,sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_ELEGANT_RESIDENCE,	sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_FANCY_RESIDENCE,		sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_COMMON_MANOR,			sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_SPACIOUS_MANOR,		sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_ELEGANT_MANOR,			sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_STATELY_MANOR,			sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_MODEST_ESTATE,			sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_HOUSE_PALATIAL_ESTATE,		sound: "Wavs/housing_r.wav"},
	{ type: BUILDING_WATER_SUPPLY,						sound: "Wavs/WELL.WAV"},
	{ type: BUILDING_WELL,										sound: "Wavs/WELL.WAV"},
  { type: BUILDING_GRANARY,          				sound: "Wavs/GRANARY1.wav"},
  { type: BUILDING_STORAGE_YARD,     				sound: "Wavs/warehouse1.wav"},
  { type: BUILDING_DOCK,             				sound: "Wavs/DOCK1.WAV"},
  { type: BUILDING_RECRUITER,        				sound: "Wavs/barracks.WAV"},
  { type: BUILDING_COURTHOUSE,       				sound: "Wavs/forum.WAV"},
  { type: BUILDING_PERSONAL_MANSION,       	sound: "Wavs/GOV_MAN1.WAV"},
  { type: BUILDING_FAMILY_MANSION, 	      	sound: "Wavs/GOV_MAN2.WAV"},
  { type: BUILDING_DYNASTY_MANSION,       	sound: "Wavs/GOV_MAN3.WAV"},
  { type: BUILDING_SMALL_MASTABA,     	  	sound: "Wavs/rock3.wav"},
  { type: BUILDING_MEDIUM_MASTABA,     	  	sound: "Wavs/rock3.wav"},
]
