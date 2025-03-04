#include "building_house.h"

#include "building/count.h"
#include "city/city.h"
#include "city/warnings.h"
#include "city/population.h"
#include "city/city_resource.h"
#include "core/object_property.h"
#include "core/game_environment.h"
#include "core/custom_span.hpp"
#include "city/labor.h"
#include "game/resource.h"
#include "game/tutorial.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/building_tiles.h"
#include "grid/grid.h"
#include "grid/tiles.h"
#include "grid/image.h"
#include "grid/gardens.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include "config/config.h"
#include "io/gamefiles/lang.h"

#include "dev/debug.h"
#include <iostream>

#define MAX_DIR 4

namespace buildings {
template<typename T>
struct house_model_t : public model_t<T> {
    using inherited = model_t<T>;

    using inherited::load;
    virtual void load(archive arch) override {
        num_types = arch.r_int("num_types");
    }

    int num_types;
};

}

declare_console_command_p(houseup, game_cheat_houseup)
declare_console_command_p(housedown, game_cheat_housedown)
void game_cheat_houseup(std::istream &is, std::ostream &os) {
    std::string args; is >> args;

    buildings_house_do([] (building &b) {
        building_house *house = b.dcast_house();
        e_building_type next_level = (e_building_type)(BUILDING_HOUSE_VACANT_LOT + house->house_level() + 1);
        house->change_to(next_level);
    });
};

void game_cheat_housedown(std::istream &is, std::ostream &os) {
    std::string args; is >> args;

    buildings_house_do([] (building &b) {
        building_house *house = b.dcast_house();
        e_building_type prev_level = (e_building_type)(BUILDING_HOUSE_VACANT_LOT + house->house_level() - 1);
        if (prev_level < BUILDING_HOUSE_VACANT_LOT) {
            prev_level = BUILDING_HOUSE_VACANT_LOT;
        }
        house->change_to(prev_level);
    });
};

using house_model = buildings::house_model_t<building_house>;
buildings::house_model_t<building_house_crude_hut> house_crude_hut_m;
buildings::house_model_t<building_house_sturdy_hut> house_sturdy_hut_m;
buildings::house_model_t<building_house_meager_shanty> house_meager_shanty_m;
buildings::house_model_t<building_house_common_shanty> house_common_shanty_m;
buildings::house_model_t<building_house_rough_cottage> house_rough_cottage_m;
buildings::house_model_t<building_house_ordinary_cottage> house_ordinary_cottage_m;
buildings::house_model_t<building_house_modest_homestead> house_modest_homestead_m;
buildings::house_model_t<building_house_spacious_homestead> house_spacious_homestead_m;
buildings::house_model_t<building_house_modest_apartment> house_modest_apartment_m;
buildings::house_model_t<building_house_spacious_apartment> house_spacious_apartment_m;
buildings::house_model_t<building_house_common_residence> house_common_residence_m;
buildings::house_model_t<building_house_spacious_residence> house_spacious_residence_m;
buildings::house_model_t<building_house_elegant_residence> house_elegant_residence_m;
buildings::house_model_t<building_house_fancy_residence> house_fancy_residence_m;
buildings::house_model_t<building_house_common_manor> house_common_manor_m;
buildings::house_model_t<building_house_spacious_manor> house_spacious_manor_m;
buildings::house_model_t<building_house_elegant_manor> house_elegant_manor_m;
buildings::house_model_t<building_house_stately_manor> house_stately_manor_m;
buildings::house_model_t<building_house_modest_estate> house_modest_estate_m;
buildings::house_model_t<building_house_palatial_estate> house_palatial_estate_m;

static const int HOUSE_TILE_OFFSETS_PH[] = {
  GRID_OFFSET(0, 0),
  GRID_OFFSET(1, 0),
  GRID_OFFSET(0, 1),
  GRID_OFFSET(1, 1), // 2x2
  GRID_OFFSET(2, 0),
  GRID_OFFSET(2, 1),
  GRID_OFFSET(2, 2),
  GRID_OFFSET(1, 2),
  GRID_OFFSET(0, 2), // 3x3
  GRID_OFFSET(3, 0),
  GRID_OFFSET(3, 1),
  GRID_OFFSET(3, 2),
  GRID_OFFSET(3, 3),
  GRID_OFFSET(2, 3),
  GRID_OFFSET(1, 3),
  GRID_OFFSET(0, 3) // 4x4
};

struct house_image_t : public image_desc {
    int num_types;
};

struct expand_direction_t {
    int x;
    int y;
    int offset;
};

expand_direction_t expand_direction;

const expand_direction_t EXPAND_DIRECTION_DELTA_PH[MAX_DIR] = {
    {0, 0, 0}, {-1, -1, -GRID_LENGTH - 1}, {-1, 0, -1}, {0, -1, -GRID_LENGTH}
};

struct merge_data_t {
    tile2i tile;
    int inventory[INVENTORY_MAX];
    int foods[INVENTORY_MAX];
    int population;
};

merge_data_t g_merge_data;

int house_tile_offsets(int i) {
    return HOUSE_TILE_OFFSETS_PH[i];
}
expand_direction_t expand_delta(int i) {
    return EXPAND_DIRECTION_DELTA_PH[i];
}

void building_house::on_undo() {
    /*nothing*/
}

void building_house::update_count() const {
    building_increase_type_count(type(), runtime_data().hsize > 0);
}

void building_house::bind_dynamic(io_buffer *iob, size_t version) {
    auto &d = runtime_data();

    for (int i = 0; i < 4; ++i) {
        iob->bind(BIND_SIGNATURE_UINT16, &d.foods[i]);
    }

    uint16_t tmp;
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);
    iob->bind(BIND_SIGNATURE_UINT16, &tmp);

    for (int i = 0; i < 4; ++i) {
        iob->bind(BIND_SIGNATURE_UINT16, &d.inventory[i + 4]);
    }

    iob->bind(BIND_SIGNATURE_UINT8, &d.booth_juggler);
    iob->bind(BIND_SIGNATURE_UINT8, &d.bandstand_juggler);
    iob->bind(BIND_SIGNATURE_UINT8, &d.bandstand_musician);
    iob->bind(BIND_SIGNATURE_UINT8, &d.senet_player);
    iob->bind(BIND_SIGNATURE_UINT8, &d.magistrate);
    iob->bind(BIND_SIGNATURE_UINT8, &d.bullfighter);
    iob->bind(BIND_SIGNATURE_UINT8, &d.school);
    iob->bind(BIND_SIGNATURE_UINT8, &d.library);
    iob->bind(BIND_SIGNATURE_UINT8, &d.academy);
    iob->bind(BIND_SIGNATURE_UINT8, &d.apothecary);
    iob->bind(BIND_SIGNATURE_UINT8, &d.dentist);
    iob->bind(BIND_SIGNATURE_UINT8, &d.mortuary);
    iob->bind(BIND_SIGNATURE_UINT8, &d.physician);
    iob->bind(BIND_SIGNATURE_UINT8, &d.temple_osiris);
    iob->bind(BIND_SIGNATURE_UINT8, &d.temple_ra);
    iob->bind(BIND_SIGNATURE_UINT8, &d.temple_ptah);
    iob->bind(BIND_SIGNATURE_UINT8, &d.temple_seth);
    iob->bind(BIND_SIGNATURE_UINT8, &d.temple_bast);
    iob->bind(BIND_SIGNATURE_UINT8, &d.no_space_to_expand);
    iob->bind(BIND_SIGNATURE_UINT8, &d.num_foods);
    iob->bind(BIND_SIGNATURE_UINT8, &d.entertainment);
    iob->bind(BIND_SIGNATURE_UINT8, &d.education);
    iob->bind(BIND_SIGNATURE_UINT8, &d.health);
    iob->bind(BIND_SIGNATURE_UINT8, &d.num_gods);
    iob->bind(BIND_SIGNATURE_UINT8, &d.devolve_delay);
    iob->bind(BIND_SIGNATURE_UINT8, &d.evolve_text_id);
    iob->bind(BIND_SIGNATURE_UINT8, &d.shrine_access);
    iob->bind(BIND_SIGNATURE_UINT8, &d.bazaar_access);
    iob->bind(BIND_SIGNATURE_UINT8, &d.water_supply);
    iob->bind(BIND_SIGNATURE_UINT8, &d.pavillion_dancer);
    iob->bind(BIND_SIGNATURE_UINT8, &d.pavillion_musician);
    iob->bind(BIND_SIGNATURE_UINT8, &d.house_happiness);
    iob->bind(BIND_SIGNATURE_UINT8, &d.is_merged);
    iob->bind(BIND_SIGNATURE_UINT8, &d.criminal_active);
    iob->bind(BIND_SIGNATURE_INT16, &d.highest_population);
    iob->bind(BIND_SIGNATURE_INT16, &d.population);
    iob->bind(BIND_SIGNATURE_UINT8, &d.tax_coverage);
    iob->bind(BIND_SIGNATURE_UINT16, &d.tax_collector_id);
    iob->bind(BIND_SIGNATURE_INT16, &d.tax_income_or_storage);
    iob->bind(BIND_SIGNATURE_UINT8, &d.days_without_food);
    iob->bind(BIND_SIGNATURE_UINT8, &d.hsize);
}

int building_house::get_fire_risk(int value) const {
    const bool is_empty = (house_level() == HOUSE_CRUDE_HUT) && is_vacant_lot();
    if (is_empty) {
        return 0;
    }

    return value;
}

void building_house::highlight_waypoints() {
    // nothing
}

bvariant building_house::get_property(const xstring &domain, const xstring &name) const {
    auto &d = runtime_data();
    if (domain == tags().house && name == tags().level_name) {
        int level = base.type - 10;
        return bvariant((pcstr)lang_get_string(29, level));
    }

    if (domain == tags().building && name == tags().tax_income_or_storage) {
        return bvariant(d.tax_income_or_storage);
    }

    return building_impl::get_property(domain, name);
}

void building_house::create_vacant_lot(tile2i tile, int image_id) {
    building* b = building_create(BUILDING_HOUSE_VACANT_LOT, tile, 0);
    
    b->distance_from_entry = 0;
    map_building_tiles_add(b->id, b->tile, 1, image_id, TERRAIN_BUILDING);
}

void building_house::consume_resources() {
    auto consume_resource = [this] (int inventory, int amount) {
        if (amount <= 0) {
            return;
        }

        auto &d = runtime_data();
        if (amount > d.inventory[inventory]) {
            d.inventory[inventory] = 0;
        } else {
            d.inventory[inventory] -= amount;
        }
    };

    const model_house* model = model_get_house(house_level());
    consume_resource(INVENTORY_GOOD1, model->pottery);
    consume_resource(INVENTORY_GOOD2, model->jewelry);
    consume_resource(INVENTORY_GOOD3, model->linen);
    consume_resource(INVENTORY_GOOD4, model->beer);
}

template<bool use_offset>
static int house_image_group(int level) {
    const e_building_type btype = e_building_type(BUILDING_HOUSE_VACANT_LOT + level);
    const auto &params = building_impl::params(btype);
    const auto anim = params.anim["house"];
    int image_id = image_id_from_group(anim.pack, anim.iid);

    return image_id + (use_offset ? anim.offset : 0);
}

void building_house::add_population(int num_people) {
    int max_people = model_get_house(house_level())->max_people;

    if (is_merged()) {
        max_people *= 4;
    }

    int room = std::max(max_people - house_population(), 0);
    if (room < num_people) {
        num_people = room;
    }

    if (house_population() <= 0) {
        change_to(BUILDING_HOUSE_CRUDE_HUT);
    }

    auto &d = runtime_data();
    d.population += num_people;
    g_city.population.add(num_people);
    base.remove_figure(2);
}

void building_house::change_to(e_building_type type) {
    tutorial_on_house_evolve((e_house_level)(type - BUILDING_HOUSE_VACANT_LOT));
    base.type = type;

    auto &d = runtime_data();
    d.level = (e_house_level)(base.type - BUILDING_HOUSE_VACANT_LOT);
    
    int image_id = house_image_group<false>(d.level);
    const house_model &model = static_cast<const house_model&>(params());

    const int img_offset = model.anim["house"].offset;
    if (is_merged()) {
        image_id += 4;
        if (img_offset) {
            image_id += 1;
        }
    } else {
        image_id += img_offset;
        image_id += map_random_get(base.tile.grid_offset()) & (model.num_types - 1);
    }

    map_building_tiles_add(base.id, base.tile, base.size, image_id, TERRAIN_BUILDING);
}

int16_t building_house::population_room() const {
    int max_people = model_get_house(house_level())->max_people;

    if (is_merged()) {
        max_people *= 4;
    }

    int room = std::max(max_people - house_population(), 0);
    max_people -= house_population();

    return max_people;
}

void building_house::change_to_vacant_lot() {
    auto &d = runtime_data();
    base.type = BUILDING_HOUSE_VACANT_LOT;

    d.population = 0;
    d.level = (e_house_level)(base.type - BUILDING_HOUSE_VACANT_LOT);
    const house_model &model = static_cast<const house_model&>(params());
    int vacant_lot_id = model.anim["house"].first_img();

    if (is_merged()) {
        map_building_tiles_remove(base.id, base.tile);
        d.is_merged = 0;
        d.hsize = 1;
        base.size = 1;
        map_building_tiles_add(base.id, base.tile, 1, vacant_lot_id, TERRAIN_BUILDING);

        building_house::create_vacant_lot(base.tile.shifted(1, 0), vacant_lot_id);
        building_house::create_vacant_lot(base.tile.shifted(0, 1), vacant_lot_id);
        building_house::create_vacant_lot(base.tile.shifted(1, 1), vacant_lot_id);
    } else {
        map_image_set(base.tile, vacant_lot_id);
    }
}

bool building_house::is_vacant_lot() const {
    return house_population() == 0;
}

static void prepare_for_merge(int building_id, int num_tiles) {
    for (int i = 0; i < INVENTORY_MAX; i++) {
        g_merge_data.inventory[i] = 0;
        g_merge_data.foods[i] = 0;
    }

    g_merge_data.population = 0;
    int grid_offset = MAP_OFFSET(g_merge_data.tile);
    for (int i = 0; i < num_tiles; i++) {
        int house_offset = grid_offset + house_tile_offsets(i);
        if (map_terrain_is(house_offset, TERRAIN_BUILDING)) {
            auto house = building_at(house_offset)->dcast_house();
            if (house && house->id() != building_id && house->runtime_data().hsize) {
                g_merge_data.population += house->house_population();
                for (int inv = 0; inv < INVENTORY_MAX; inv++) {
                    auto &housed = house->runtime_data();
                    g_merge_data.inventory[inv] += housed.inventory[inv];
                    g_merge_data.foods[inv] += housed.foods[inv];
                    housed.population = 0;
                    house->base.state = BUILDING_STATE_DELETED_BY_GAME;
                }
            }
        }
    }
}

void building_house::merge_impl() {
    prepare_for_merge(id(), 4);

    auto &d = runtime_data();
    base.size = 2;
    d.hsize = 2;
    d.population += g_merge_data.population;

    for (int i = 0; i < INVENTORY_MAX; i++) {
        d.foods[i] += g_merge_data.foods[i];
        d.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<false>(house_level()) + 4;

    const house_model &model = static_cast<const house_model&>(params());
    if (model.anim["house"].offset) {
        image_id += 1;
    }

    map_building_tiles_remove(id(), tile());
    base.tile = g_merge_data.tile;

    d.is_merged = true;
    map_building_tiles_add(id(), tile(), 2, image_id, TERRAIN_BUILDING);
}

void building_house::merge() {
    if (is_merged()) {
        return;
    }

    if (!config_get(CONFIG_GP_CH_ALL_HOUSES_MERGE)) {
        if ((map_random_get(base.tile) & 7) >= 5)
            return;
    }

    int num_house_tiles = 0;
    for (int i = 0; i < 4; i++) {
        int tile_offset = base.tile.grid_offset() + house_tile_offsets(i);
        if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
            auto other_house = building_at(tile_offset)->dcast_house();
            if (!other_house) {
                continue;
            }

            if (other_house->id() == base.id) {
                num_house_tiles++;
            } else if (other_house->state() == BUILDING_STATE_VALID && other_house->runtime_data().hsize
                     && (other_house->house_level() == house_level())
                     && !other_house->is_merged()) {
                num_house_tiles++;
            }
        }
    }

    if (num_house_tiles == 4) {
        g_merge_data.tile = tile2i(tilex() + expand_delta(0).x, tiley() + expand_delta(0).y);
        merge_impl();
    }
}

e_house_progress building_house::check_requirements(house_demands* demands) {
    e_house_progress status = check_evolve_desirability();
    if (!has_required_goods_and_services(0, demands)) { // check if it will devolve to previous step
        status = e_house_decay;
    } else if (status == e_house_evolve) { // check if it can evolve to the next step
        status = has_required_goods_and_services(1, demands);
    }

    return status;
}

e_house_progress building_house::has_required_goods_and_services(int for_upgrade, house_demands* demands) {
    int level = house_level();
    if (for_upgrade) {
        ++level;
    }

    const model_house* model = model_get_house(level);
    // water
    int water = model->water;
    if (!base.has_water_access) {
        if (water >= 2) {
            ++demands->missing.fountain;
            return e_house_none;
        }
        if (water == 1 && !base.has_well_access) {
            ++demands->missing.well;
            return e_house_none;
        }
    }
    // entertainment
    int entertainment = model->entertainment;
    auto &d = runtime_data();
    if (d.entertainment < entertainment) {
        if (d.entertainment)
            ++demands->missing.more_entertainment;
        else {
            ++demands->missing.entertainment;
        }
        return e_house_none;
    }
    // education
    int education = model->education;
    if (d.education < education) {
        if (d.education)
            ++demands->missing.more_education;
        else {
            ++demands->missing.education;
        }
        return e_house_none;
    }
    if (education == 2) {
        ++demands->requiring.school;
        ++demands->requiring.library;
    } else if (education == 1)
        ++demands->requiring.school;

    // religion
    int religion = model->religion;
    if (d.num_gods < religion) {
        if (religion == 1) {
            ++demands->missing.religion;
            return e_house_none;
        } else if (religion == 2) {
            ++demands->missing.second_religion;
            return e_house_none;
        } else if (religion == 3) {
            ++demands->missing.third_religion;
            return e_house_none;
        }
    } else if (religion > 0)
        ++demands->requiring.religion;

    // dentist
    int dentist = model->dentist;
    if (d.dentist < dentist) {
        ++demands->missing.dentist;
        return e_house_none;
    }
    if (dentist == 1) {
        ++demands->requiring.dentist;
    }

    // physician
    int magistrate = model->physician;
    if (d.magistrate < magistrate) {
        ++demands->missing.magistrate;
        return e_house_none;
    }
    if (magistrate == 1) {
        ++demands->requiring.magistrate;
    }

    // health
    int health_need = model->health;
    if (d.health < health_need) {
        if (health_need < 2)
            ++demands->missing.dentist;
        else {
            ++demands->missing.physician;
        }
        return e_house_none;
    }
    if (health_need >= 1) {
        ++demands->requiring.physician;
    }

    // food types
    int foodtypes_required = model->food_types;
    int foodtypes_available = 0;
    for (int i = INVENTORY_MIN_FOOD; i < INVENTORY_MAX_FOOD; i++) {
        foodtypes_available += (d.foods[i] > 0) ? 1 : 0;
    }

    if (foodtypes_available < foodtypes_required) {
        ++demands->missing.food;
        return e_house_none;
    }

    // goods
    if (d.inventory[INVENTORY_GOOD1] < model->pottery)
        return e_house_none;

    if (d.inventory[INVENTORY_GOOD3] < model->linen)
        return e_house_none;

    if (d.inventory[INVENTORY_GOOD2] < model->jewelry)
        return e_house_none;

    int wine = model->beer;
    if (wine && d.inventory[INVENTORY_GOOD4] <= 0)
        return e_house_none;

    if (wine > 1 && !city_resource_multiple_wine_available()) {
        ++demands->missing.second_wine;
        return e_house_none;
    }
    return e_house_evolve;
}

bool building_house::has_devolve_delay(int status) {
    auto &d = runtime_data();
    if (status == e_house_decay && d.devolve_delay < 2) {
        d.devolve_delay++;
        return true;
    } else {
        d.devolve_delay = 0;
        return false;
    }
}

bool building_house::can_expand(int num_tiles) {
    auto &d = runtime_data();
    // merge with other houses
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + base.tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                auto other_house = building_at(tile_offset)->dcast_house();
                if (other_house->id() == id()) {
                    ok_tiles++;
                } else if (other_house->state() == BUILDING_STATE_VALID && other_house->runtime_data().hsize) {
                    if (other_house->house_level() <= house_level()) {
                        ok_tiles++;
                    }
                }
            }
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.tile = tile2i(tilex() + expand_delta(dir).x, tiley() + expand_delta(dir).y);
            return true;
        }
    }
    // merge with houses and empty terrain
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + base.tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (!map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR))
                ok_tiles++;
            else if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                auto other_house = building_at(tile_offset)->dcast_house();
                if (other_house->id() == id())
                    ok_tiles++;
                else if (other_house->state() == BUILDING_STATE_VALID && other_house->runtime_data().hsize) {
                    if (other_house->house_level() <= house_level())
                        ok_tiles++;
                }
            }
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.tile = tile2i(tilex() + expand_delta(dir).x, tiley() + expand_delta(dir).y);
            return true;
        }
    }
    // merge with houses, empty terrain and gardens
    for (int dir = 0; dir < MAX_DIR; dir++) {
        int base_offset = expand_delta(dir).offset + base.tile.grid_offset();
        int ok_tiles = 0;
        for (int i = 0; i < num_tiles; i++) {
            int tile_offset = base_offset + house_tile_offsets(i);
            if (!map_terrain_is(tile_offset, TERRAIN_NOT_CLEAR)) {
                ok_tiles++;
            } else if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
                auto other_house = building_at(tile_offset)->dcast_house();
                if (other_house->id() == id()) {
                    ok_tiles++;
                } else if (other_house->state() == BUILDING_STATE_VALID && other_house->runtime_data().hsize) {
                    if (other_house->house_level() <= house_level())
                        ok_tiles++;
                }
            } else if (map_terrain_is(tile_offset, TERRAIN_GARDEN) && !config_get(CONFIG_GP_CH_HOUSES_DONT_EXPAND_INTO_GARDENS)) {
                ok_tiles++;
            }
        }
        if (ok_tiles == num_tiles) {
            g_merge_data.tile = tile2i(tilex() + expand_delta(dir).x, tiley() + expand_delta(dir).y);
            return true;
        }
    }

    runtime_data().no_space_to_expand = 1;
    return false;
}

e_house_progress building_house::check_evolve_desirability() {
    int level = house_level();
    const model_house* model = model_get_house(level);
    int evolve_des = model->evolve_desirability;
    if (level >= HOUSE_PALATIAL_ESTATE) {
        evolve_des = 1000;
    }

    int current_des = base.desirability;
    e_house_progress status;
    if (current_des <= model->devolve_desirability) {
        status = e_house_decay;
    } else if (current_des >= evolve_des)
        status = e_house_evolve;
    else {
        status = e_house_none;
    }

    runtime_data().evolve_text_id = status; // BUG? -1 in an unsigned char?
    return status;
}

static void create_house_tile(e_building_type type, tile2i tile, int image_id, int population, custom_span<int> inventory, custom_span<int> foods) {
    auto house = building_create(type, tile, 0)->dcast_house();

    auto &housed = house->runtime_data();
    housed.population = population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] = foods[i];
        housed.inventory[i] = inventory[i];
    }
    house->base.distance_from_entry = 0;
    map_building_tiles_add(house->id(), house->tile(), 1, image_id + (map_random_get(house->tile()) & 1), TERRAIN_BUILDING);
}

static void split_size2(building* b, e_building_type new_type) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto &housed = b->dcast_house()->runtime_data();
    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 4;
        inventory_remainder[i] = housed.inventory[i] % 4;
        foods_per_tile[i] = housed.foods[i] / 4;
        foods_remainder[i] = housed.foods[i] % 4;
    }

    int population_per_tile = housed.population / 4;
    int population_remainder = housed.population % 4;

    map_building_tiles_remove(b->id, b->tile);

    // main tile
    b->type = new_type;
    housed.level = (e_house_level)(b->type - BUILDING_HOUSE_VACANT_LOT);
    b->size = 1;
    housed.hsize = 1;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
        housed.foods[i] = foods_per_tile[i] + foods_remainder[i];
    }
    b->distance_from_entry = 0;

    int image_id = house_image_group<true>(housed.level);
    map_building_tiles_add(b->id, b->tile, b->size, image_id + (map_random_get(b->tile) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(b->type, b->tile.shifted(1, 0), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(0, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(1, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

static void split_size3(building* b) {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto &housed = b->dcast_house()->runtime_data();
    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 9;
        inventory_remainder[i] = housed.inventory[i] % 9;
        foods_per_tile[i] = housed.foods[i] / 9;
        foods_remainder[i] = housed.foods[i] % 9;
    }

    int population_per_tile = housed.population / 9;
    int population_remainder = housed.population % 9;

    map_building_tiles_remove(b->id, b->tile);

    // main tile
    b->type = BUILDING_HOUSE_SPACIOUS_APARTMENT;
    housed.level = (e_house_level)(b->type - BUILDING_HOUSE_VACANT_LOT);
    b->size = 1;
    housed.hsize = 1;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
        housed.foods[i] = foods_per_tile[i] + foods_remainder[i];
    }
    b->distance_from_entry = 0;

    int image_id = house_image_group<true>(housed.level);
    map_building_tiles_add(b->id, b->tile, b->size, image_id + (map_random_get(b->tile) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    create_house_tile(b->type, b->tile.shifted(0, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(1, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(2, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(0, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(1, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(b->type, b->tile.shifted(2, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

void building_house::split(int num_tiles) {
    int grid_offset = MAP_OFFSET(g_merge_data.tile);
    for (int i = 0; i < num_tiles; i++) {
        int tile_offset = grid_offset + house_tile_offsets(i);
        if (map_terrain_is(tile_offset, TERRAIN_BUILDING)) {
            auto other_house = building_at(tile_offset)->dcast_house();
            if (other_house->id() != id() && other_house->runtime_data().hsize) {
                if (other_house->is_merged()) {
                    split_size2(&other_house->base, other_house->type());
                } else if (other_house->runtime_data().hsize == 2) {
                    split_size2(&other_house->base, BUILDING_HOUSE_SPACIOUS_APARTMENT);
                } else if (other_house->runtime_data().hsize == 3) {
                    split_size3(&other_house->base);
                }
            }
        }
    }
}

void building_house_common_manor::devolve_to_fancy_residence() {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto &housed = runtime_data();

    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 6;
        inventory_remainder[i] = housed.inventory[i] % 6;
        foods_per_tile[i] = housed.foods[i] / 6;
        foods_remainder[i] = housed.foods[i] % 6;
    }

    int population_per_tile = house_population() / 6;
    int population_remainder = house_population() % 6;

    map_building_tiles_remove(id(), tile());

    // main tile
    base.type = BUILDING_HOUSE_FANCY_RESIDENCE;
    base.size = 2;
    housed.level = (e_house_level)(base.type - BUILDING_HOUSE_VACANT_LOT);
    housed.hsize = 2;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
        housed.foods[i] = foods_per_tile[i] + foods_remainder[i];
    }
    base.distance_from_entry = 0;

    int image_id = house_image_group<true>(house_level());
    map_building_tiles_add(id(), tile(), size(), image_id + (map_random_get(tile()) & 1), TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group<true>(HOUSE_SPACIOUS_APARTMENT);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 0), image_id, population_per_tile,inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(0, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(1, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

void building_house_modest_estate::devolve_to_statel_manor() {
    int inventory_per_tile[INVENTORY_MAX];
    int inventory_remainder[INVENTORY_MAX];
    int foods_per_tile[INVENTORY_MAX];
    int foods_remainder[INVENTORY_MAX];

    auto &housed = runtime_data();

    for (int i = 0; i < INVENTORY_MAX; i++) {
        inventory_per_tile[i] = housed.inventory[i] / 8;
        inventory_remainder[i] = housed.inventory[i] % 8;
        foods_per_tile[i] = housed.foods[i] / 8;
        foods_remainder[i] = housed.foods[i] % 8;
    }
    int population_per_tile = house_population() / 8;
    int population_remainder = house_population() % 8;

    map_building_tiles_remove(id(), tile());

    // main tile
    base.type = BUILDING_HOUSE_STATELY_MANOR;
    base.size = 3;
    housed.level = (e_house_level)(base.type - BUILDING_HOUSE_VACANT_LOT);
    housed.hsize = 3;
    housed.is_merged = false;
    housed.population = population_per_tile + population_remainder;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.inventory[i] = inventory_per_tile[i] + inventory_remainder[i];
    }
    base.distance_from_entry = 0;

    int image_id = house_image_group<true>(house_level());
    map_building_tiles_add(id(), tile(), size(), image_id, TERRAIN_BUILDING);

    // the other tiles (new buildings)
    image_id = house_image_group<true>(HOUSE_SPACIOUS_APARTMENT);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 0), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 1), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 2), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(0, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(1, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(2, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
    create_house_tile(BUILDING_HOUSE_SPACIOUS_APARTMENT, tile().shifted(3, 3), image_id, population_per_tile, inventory_per_tile, foods_per_tile);
}

void building_house::check_for_corruption() {
    //data.house.no_space_to_expand = 0;
    //
    //// house offset is corrupted??
    //if (tile().grid_offset() != MAP_OFFSET(tilex(), tiley())
    //    || map_building_at(tile().grid_offset()) != house->id) {
    //    int map_width = scenario_map_data()->width;
    //    int map_height = scenario_map_data()->height;
    //    //        int map_width, map_height;
    //    //        map_grid_size(&map_width, &map_height); // get map size and store in temp vars
    //
    //    // go through tiles and find tile belonging to the house
    //    for (int y = 0; y < map_height; y++) {
    //        for (int x = 0; x < map_width; x++) {
    //            int grid_offset = MAP_OFFSET(x, y); // get offset of current tile (global map tile offset)
    //            if (map_building_at(grid_offset) == house->id) { // does this tile belong to the house I'm searching for??
    //                house->tile.set(grid_offset);
    //                //                    house->tile.grid_offset() = grid_offset; // set house offset to this tile's
    //                //                    offset (i.e. lowest x & y; north-west corner) house->tile.x() =
    //                //                    MAP_X(grid_offset); // set house coords (x) to tile's coords (x)
    //                //                    house->tile.y() = MAP_Y(grid_offset); // set house coords (y) to tile's coords
    //                //                    (y) building_totals_add_corrupted_house(0);
    //                return;
    //            }
    //        }
    //    }
    //    //        building_totals_add_corrupted_house(1);
    //    house->state = BUILDING_STATE_RUBBLE;
    //}
}

void building_house::on_create(int orientation) {
    auto &d = runtime_data();
    d.health = 100;
    d.house_happiness = 50;
    d.level = (e_house_level)(type() - BUILDING_HOUSE_VACANT_LOT);

    if (d.level == 0) {
        d.population = 0;
    }

    d.hsize = 0;
    if (type() >= BUILDING_HOUSE_CRUDE_HUT && type() <= BUILDING_HOUSE_SPACIOUS_APARTMENT) {
        d.hsize = 1;
    } else if (type() >= BUILDING_HOUSE_COMMON_RESIDENCE && type() <= BUILDING_HOUSE_FANCY_RESIDENCE) {
        d.hsize = 2;
    } else if (type() >= BUILDING_HOUSE_COMMON_MANOR && type() <= BUILDING_HOUSE_STATELY_MANOR) {
        d.hsize = 3;
    } else if (type() >= BUILDING_HOUSE_MODEST_ESTATE && type() <= BUILDING_HOUSE_PALATIAL_ESTATE) {
        d.hsize = 4;
    }
}

void building_house::on_place_checks() {
    if (building_construction_has_warning()) {
        return;
    }
        
    if (type() != BUILDING_HOUSE_VACANT_LOT) {
        return;
    }

    if (city_population() >= 200 && !scenario_property_kingdom_supplies_grain()) {
        if (city_resource_food_percentage_produced() <= 95) {
            building_construction_warning_show(WARNING_MORE_FOOD_NEEDED);
        }
    }
}

bool building_house_crude_hut::evolve(house_demands* demands) {
    if (house_population() > 0) {
        merge();
        int status = check_requirements(demands);
        if (status == e_house_evolve) {
            change_to(BUILDING_HOUSE_STURDY_HUT);
        }
    }

    return false;
}

bool building_house_sturdy_hut::evolve(house_demands* demands) {
    if (house_population() > 0) {
        merge();
        e_house_progress status = check_requirements(demands);
        if (!has_devolve_delay(status)) {
            if (status == e_house_evolve)
                change_to(BUILDING_HOUSE_MEAGER_SHANTY);
            else if (status == e_house_decay)
                change_to(BUILDING_HOUSE_CRUDE_HUT);
        }
    }

    return false;
}

bool building_house_meager_shanty::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_COMMON_SHANTY);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_STURDY_HUT);
    }

    return false;
}

bool building_house_common_shanty::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_ROUGH_COTTAGE);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_MEAGER_SHANTY);
    }

    return false;
}

bool building_house_rough_cottage::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_ORDINARY_COTTAGE);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_COMMON_SHANTY);
    }
    return false;
}

bool building_house_ordinary_cottage::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_MODEST_HOMESTEAD);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_ROUGH_COTTAGE);
    }
    return false;
}

bool building_house_modest_homestead::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_ORDINARY_COTTAGE);
    }
    return false;
}

bool building_house_spacious_homestead::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_MODEST_APARTMENT);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_MODEST_HOMESTEAD);
    }
    return false;
}

bool building_house_modest_apartment::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            change_to(BUILDING_HOUSE_SPACIOUS_APARTMENT);
        } else if (status == e_house_decay) {
            change_to(BUILDING_HOUSE_SPACIOUS_HOMESTEAD);
        }
    }
    return false;
}

void building_house_spacious_apartment::expand_to_common_residence() {
    split(4);
    prepare_for_merge(id(), 4);

    auto &housed = runtime_data();

    base.type = BUILDING_HOUSE_COMMON_RESIDENCE;
    base.size = 2;
    housed.level = HOUSE_COMMON_RESIDENCE;
    housed.hsize = 2;
    housed.population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] += g_merge_data.foods[i];
        housed.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<true>(house_level()) + (map_random_get(tile().grid_offset()) & 1);
    map_building_tiles_remove(id(), tile());
    base.tile = g_merge_data.tile;
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
}

bool building_house_spacious_apartment::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            if (can_expand(4)) {
                runtime_data().is_merged = false;
                expand_to_common_residence();
                map_tiles_gardens_update_all();
                return true;
            }
        } else if (status == e_house_decay) {
            change_to(BUILDING_HOUSE_MODEST_APARTMENT);
        }
    }
    return false;
}

bool building_house_common_residence::evolve(house_demands* demands) {
    merge();
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_SPACIOUS_RESIDENCE);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_SPACIOUS_APARTMENT);
    }
    return 0;
}

bool building_house_spacious_residence::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_ELEGANT_RESIDENCE);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_COMMON_RESIDENCE);
    }
    return false;
}

bool building_house_elegant_residence::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_FANCY_RESIDENCE);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_SPACIOUS_RESIDENCE);
    }
    return 0;
}

void building_house_fancy_residence::expand_to_common_manor() {
    split(9);
    prepare_for_merge(id(), 9);

    auto &housed = runtime_data();
    base.type = BUILDING_HOUSE_COMMON_MANOR;
    base.size = 3;
    housed.level = HOUSE_COMMON_MANOR;
    housed.hsize = 3;
    housed.population += g_merge_data.population;

    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] += g_merge_data.foods[i];
        housed.inventory[i] += g_merge_data.inventory[i];
    }

    int image_id = house_image_group<true>(housed.level);
    map_building_tiles_remove(id(), base.tile);
    base.tile = g_merge_data.tile;
    map_building_tiles_add(id(), base.tile, base.size, image_id, TERRAIN_BUILDING);
}

bool building_house_fancy_residence::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            if (can_expand(9)) {
                expand_to_common_manor();
                map_tiles_gardens_update_all();
                return true;
            }
        } else if (status == e_house_decay) {
            change_to(BUILDING_HOUSE_ELEGANT_RESIDENCE);
        }
    }
    return false;
}

bool building_house_common_manor::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            change_to(BUILDING_HOUSE_SPACIOUS_MANOR);
        } else if (status == e_house_decay) {
            devolve_to_fancy_residence();
        }
    }
    return false;
}

bool building_house_spacious_manor::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_ELEGANT_MANOR);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_COMMON_MANOR);
    }
    return false;
}

bool building_house_elegant_manor::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_STATELY_MANOR);
        else if (status == e_house_decay)
            change_to(BUILDING_HOUSE_SPACIOUS_MANOR);
    }
    return 0;
}

void building_house_stately_manor::expand_to_modest_estate() {
    split(16);
    prepare_for_merge(id(), 16);

    auto &housed = runtime_data();

    base.type = BUILDING_HOUSE_MODEST_ESTATE;
    base.size = 4;
    housed.level = HOUSE_MODEST_ESTATE;
    housed.hsize = 4;
    housed.population += g_merge_data.population;
    for (int i = 0; i < INVENTORY_MAX; i++) {
        housed.foods[i] += g_merge_data.foods[i];
        housed.inventory[i] += g_merge_data.inventory[i];
    }
    int image_id = house_image_group<true>(housed.level);
    map_building_tiles_remove(id(), tile());
    base.tile = g_merge_data.tile;
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_BUILDING);
}

bool building_house_stately_manor::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve) {
            if (can_expand(16)) {
                expand_to_modest_estate();
                map_tiles_gardens_update_all();
                return true;
            }
        } else if (status == e_house_decay) {
            change_to(BUILDING_HOUSE_ELEGANT_MANOR);
        }
    }
    return false;
}

bool building_house_modest_estate::evolve(house_demands* demands) {
    e_house_progress status = check_requirements(demands);
    if (!has_devolve_delay(status)) {
        if (status == e_house_evolve)
            change_to(BUILDING_HOUSE_PALATIAL_ESTATE);
        else if (status == e_house_decay)
           devolve_to_statel_manor();
    }
    return false;
}

bool building_house_palatial_estate::evolve(house_demands* demands) {
    e_house_progress status = check_evolve_desirability();
    if (!has_required_goods_and_services(0, demands)) {
        status = e_house_decay;
    }

    if (!has_devolve_delay(status) && status == e_house_decay)
        change_to(BUILDING_HOUSE_MODEST_ESTATE);

    return 0;
}