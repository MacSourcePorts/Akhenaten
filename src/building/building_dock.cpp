#include "building_dock.h"

#include "building/building_bazaar.h"
#include "building/building.h"
#include "building/building_type.h"
#include "grid/water.h"
#include "city/buildings.h"
#include "city/resource.h"
#include "core/profiler.h"
#include "empire/empire_city.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "grid/sprite.h"
#include "grid/image.h"
#include "grid/routing/routing.h"
#include "grid/terrain.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "scenario/map.h"
#include "game/game.h"
#include "window/building/distribution.h"
#include "graphics/elements/lang_text.h"
#include "city/labor.h"

buildings::model_t<building_dock> dock_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_dock);
void config_load_building_dock() {
    dock_m.load();
}

void building_dock::on_create(int orientation) {
    data.dock.orientation = orientation;
}

void building_dock::on_destroy() {
    city_buildings_remove_dock();
}

bool building_dock::can_play_animation() const {
    if (data.dock.num_ships > 0) {
        return true;
    }

    map_sprite_animation_set(tile(), 1);
    return false;
}

void building_dock::update_count() const {
    if (base.num_workers > 0 && base.has_open_water_access) {
        city_buildings_add_working_dock(id());
    }
}

void building_dock::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.dock.orientation);
    int image_id = image_group(IMG_BUILDING_DOCK) + image_offset;
    map_water_add_building(id(), tile(), 3, image_id);
}

void building_dock::spawn_figure() {
    //    check_labor_problem();
    //    map_point road;
    //    if (map_has_road_access(x, y, size, &road)) {
    //        spawn_labor_seeker(50);
    //        int pct_workers = worker_percentage();
    //        int max_dockers;
    //        if (pct_workers >= 75)
    //            max_dockers = 3;
    //        else if (pct_workers >= 50)
    //            max_dockers = 2;
    //        else if (pct_workers > 0)
    //            max_dockers = 1;
    //        else {
    //            max_dockers = 0;
    //        }
    //        // count existing dockers
    //        int existing_dockers = 0;
    //        for (int i = 0; i < 3; i++) {
    //            if (data.dock.docker_ids[i]) {
    //                if (figure_get(data.dock.docker_ids[i])->type == FIGURE_DOCKER)
    //                    existing_dockers++;
    //                else {
    //                    data.dock.docker_ids[i] = 0;
    //                }
    //            }
    //        }
    //        if (existing_dockers > max_dockers) {
    //            // too many dockers, poof one of them
    //            for (int i = 2; i >= 0; i--) {
    //                if (data.dock.docker_ids[i]) {
    //                    figure_get(data.dock.docker_ids[i])->poof();
    //                    break;
    //                }
    //            }
    //        } else if (existing_dockers < max_dockers) {
    //            figure *f = figure_create(FIGURE_DOCKER, road.x, road.y, DIR_4_BOTTOM_LEFT);
    //            f->action_state = FIGURE_ACTION_132_DOCKER_IDLING;
    //            f->home() = b;
    //            for (int i = 0; i < 3; i++) {
    //                if (!data.dock.docker_ids[i]) {
    //                    data.dock.docker_ids[i] = f->id;
    //                    break;
    //                }
    //            }
    //        }
    //    }
}

void draw_dock_workers(building* b, int x, int y, color color_mask, painter &ctx) {
    building_dock *dock = b->dcast_dock();

    int num_dockers = dock->count_idle_dockers();
    if (num_dockers > 0) {
        int image_dock = map_image_at(dock->tile());
        int image_dockers = image_id_from_group(GROUP_BUILDING_DOCK_DOCKERS);
        if (image_dock == image_group(IMG_BUILDING_DOCK))
            image_dockers += 0;
        else if (image_dock == image_group(IMG_BUILDING_DOCK) + 1)
            image_dockers += 3;
        else if (image_dock == image_group(IMG_BUILDING_DOCK) + 2)
            image_dockers += 6;
        else
            image_dockers += 9;

        if (num_dockers == 2)
            image_dockers += 1;
        else if (num_dockers == 3)
            image_dockers += 2;

        const image_t* img = image_get(image_dockers);
        ImageDraw::img_generic(ctx, image_dockers, x + img->animation.sprite_offset.x, y + img->animation.sprite_offset.y, color_mask);
    }
}

void window_building_draw_dock_orders(object_info* c) {
    c->help_id = 83;
    int y_offset = window_building_get_vertical_offset(c, 28);
    outer_panel_draw(vec2i{c->offset.x, y_offset}, 29, 28);
    lang_text_draw_centered(101, 0, c->offset.x, y_offset + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);
    inner_panel_draw(c->offset.x + 16, y_offset + 42, c->width_blocks - 2, 21);
}

void window_building_draw_dock(object_info* c) {
    c->help_id = 83;
    window_building_play_sound(c, "wavs/dock.wav");
    outer_panel_draw(c->offset, c->width_blocks, c->height_blocks);
    lang_text_draw_centered(101, 0, c->offset.x, c->offset.y + 10, 16 * c->width_blocks, FONT_LARGE_BLACK_ON_LIGHT);

    building* b = building_get(c->building_id);

    if (!c->has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (b->data.dock.trade_ship_id) {
        if (c->worker_percentage <= 0)
            window_building_draw_description(c, 101, 2);
        else if (c->worker_percentage < 50)
            window_building_draw_description(c, 101, 3);
        else if (c->worker_percentage < 75)
            window_building_draw_description(c, 101, 4);
        else {
            window_building_draw_description(c, 101, 5);
        }
    } else {
        if (c->worker_percentage <= 0)
            window_building_draw_description(c, 101, 6);
        else if (c->worker_percentage < 50)
            window_building_draw_description(c, 101, 7);
        else if (c->worker_percentage < 75)
            window_building_draw_description(c, 101, 8);
        else {
            window_building_draw_description(c, 101, 9);
        }
    }

    inner_panel_draw(c->offset.x + 16, c->offset.y + 136, c->width_blocks - 2, 4);
    window_building_draw_employment(c, 142);
}

void window_building_draw_dock_orders_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    painter ctx = game.painter();
    int y_offset = window_building_get_vertical_offset(c, 28);
    int line_x = c->offset.x + 215;

    draw_accept_none_button(c->offset.x + 394, y_offset + 404, data.orders_focus_button_id == 1);

    building_dock* dock = building_get(c->building_id)->dcast_dock();
    if (!dock) {
        return;
    }

    for (int i = 0; i < 15; i++) {
        int line_y = 20 * i;
        int resource = i + 1;
        int image_id= image_id_resource_icon(resource) + resource_image_offset(resource, RESOURCE_IMAGE_ICON);
        ImageDraw::img_generic(ctx, image_id, c->offset.x + 32, y_offset + 46 + line_y);
        ImageDraw::img_generic(ctx, image_id, c->offset.x + 408, y_offset + 46 + line_y);
        lang_text_draw(23, resource, c->offset.x + 72, y_offset + 50 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        button_border_draw(c->offset.x + 180, y_offset + 46 + line_y, 210, 22, data.resource_focus_button_id == i + 1);
        int state = dock->is_good_accepted(i);
        if (state)
            lang_text_draw(99, 7, line_x, y_offset + 51 + line_y, FONT_NORMAL_WHITE_ON_DARK);
        else
            lang_text_draw(99, 8, line_x, y_offset + 51 + line_y, FONT_NORMAL_YELLOW);
    }
}

void window_building_draw_dock_foreground(object_info* c) {
    auto &data = g_window_building_distribution;
    button_border_draw(c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 34, 16 * (c->width_blocks - 10), 20, data.focus_button_id == 1 ? 1 : 0);
    lang_text_draw_centered(98, 5, c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 30, 16 * (c->width_blocks - 10), FONT_NORMAL_BLACK_ON_LIGHT);
}

void building_dock::window_info_background(object_info &c) {
    if (c.storage_show_special_orders)
        window_building_draw_dock_orders(&c);
    else
        window_building_draw_dock(&c);
}

void building_dock::window_info_foreground(object_info &c) {
    if (c.storage_show_special_orders)
        window_building_draw_dock_orders_foreground(&c);
    else
        window_building_draw_dock_foreground(&c);
}

int building_dock::window_info_handle_mouse(const mouse *m, object_info &c) {
    return 0;
}

bool building_dock::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    draw_dock_workers(&base, point.x, point.y, color_mask, ctx);
    return false;
}

int building_dock::count_idle_dockers() const {
    int num_idle = 0;
    for (int i = 0; i < 3; i++) {
        if (data.dock.docker_ids[i]) {
            figure* f = figure_get(data.dock.docker_ids[i]);
            if (f->action_state == FIGURE_ACTION_132_DOCKER_IDLING
                || f->action_state == FIGURE_ACTION_133_DOCKER_IMPORT_QUEUE) {
                num_idle++;
            }
        }
    }
    return num_idle;
}

void building_river_update_open_water_access() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Oper Water Access Update");
    tile2i river_entry = scenario_map_river_entry();
    map_routing_calculate_distances_water_boat(river_entry);

    buildings_valid_do([] (building &b) {
        bool found = map_terrain_is_adjacent_to_open_water(b.tile, 3);
        if (found) {
            b.has_water_access = true;
            b.has_open_water_access = true;
            auto ppoints = map_water_docking_points(&b);
            b.data.dock.dock_tiles[0] = ppoints.point_a.grid_offset();
            b.data.dock.dock_tiles[1] = ppoints.point_b.grid_offset();
        } else {
            b.has_water_access = false;
            b.has_open_water_access = false;
            b.data.dock.dock_tiles[0] = -1;
            b.data.dock.dock_tiles[1] = -1;
        }
    }, BUILDING_DOCK, BUILDING_FISHING_WHARF, BUILDING_SHIPWRIGHT);
}

bool map_tile_is_connected_to_open_water(tile2i tile) {
    tile2i river_entry = scenario_map_river_entry();
    map_routing_calculate_distances_water_boat(river_entry);
    return map_terrain_is_adjacent_to_open_water(tile, 3);
}

bool building_dock::is_good_accepted(int index) {
    int goods_bit = 1 << index;
    return !(base.subtype.market_goods & goods_bit);
}

void building_dock::toggle_good_accepted(int index) {
    int goods_bit = (1 << index);
    base.subtype.market_goods ^= goods_bit;
}

int building_dock_accepts_ship(int ship_id, int dock_id) {
    building_dock* dock = building_get(dock_id)->dcast_dock();
    if (!dock) {
        return 0;
    }

    figure* f = figure_get(ship_id);

    empire_city* city = empire_city_get(f->empire_city_id);
    for (int resource = RESOURCE_GRAIN; resource < RESOURCES_MAX; resource++) {
        if (city->sells_resource[resource] || city->buys_resource[resource]) {
            if (!dock->is_good_accepted(resource - 1)) {
                dock_id = 0;
                return 0;
            }
        }
    }
    return 1;
}

building_dest map_get_free_destination_dock(int ship_id) {
    if (!city_buildings_has_working_dock())
        return {0, map_point_invalid};

    int dock_id = 0;
    for (int i = 0; i < 10; i++) {
        dock_id = city_buildings_get_working_dock(i);
        if (!dock_id)
            continue;
        if (!building_dock_accepts_ship(ship_id, dock_id)) {
            dock_id = 0;
            continue;
        }

        building* dock = building_get(dock_id);
        if (!dock->data.dock.trade_ship_id || dock->data.dock.trade_ship_id == ship_id)
            break;
    }
    // BUG: when 10 docks in city, always takes last one... regardless of whether it is free
    if (dock_id <= 0)
        return {0, map_point_invalid};

    building* dock = building_get(dock_id);
    int dx, dy;
    switch (dock->data.dock.orientation) {
    case 0:
        dx = 1;
        dy = -1;
        break;
    case 1:
        dx = 3;
        dy = 1;
        break;
    case 2:
        dx = 1;
        dy = 3;
        break;
    default:
        dx = -1;
        dy = 1;
        break;
    }
    tile2i dock_tile = dock->tile.shifted(dx, dy);
    tile2i dest_tile;
    map_point_store_result(dock_tile, dest_tile);
    dock->data.dock.trade_ship_id = ship_id;
    return {dock_id, dest_tile};
}

building_dest map_get_queue_destination_dock(int ship_id) {
    if (!city_buildings_has_working_dock())
        return {0, map_point_invalid};

    // first queue position
    for (int i = 0; i < 10; i++) {
        int dock_id = city_buildings_get_working_dock(i);
        if (!dock_id)
            continue;

        if (!building_dock_accepts_ship(ship_id, dock_id)) {
            dock_id = 0;
            continue;
        }
        building* dock = building_get(dock_id);
        int dx, dy;
        switch (dock->data.dock.orientation) {
        case 0:
            dx = 2;
            dy = -2;
            break;
        case 1:
            dx = 4;
            dy = 2;
            break;
        case 2:
            dx = 2;
            dy = 4;
            break;
        default:
            dx = -2;
            dy = 2;
            break;
        }
        tile2i dock_tile = dock->tile.shifted(dx, dy);
        tile2i dest_dock;
        map_point_store_result(dock_tile, dest_dock);

        if (!map_has_figure_at(dest_dock)) {
            return {dock_id, dest_dock};
        }
    }

    // second queue position
    for (int i = 0; i < 10; i++) {
        int dock_id = city_buildings_get_working_dock(i);
        if (!dock_id)
            continue;

        if (!building_dock_accepts_ship(ship_id, dock_id)) {
            dock_id = 0;
            continue;
        }
        building* dock = building_get(dock_id);
        int dx, dy;
        switch (dock->data.dock.orientation) {
        case 0:
            dx = 2;
            dy = -3;
            break;
        case 1:
            dx = 5;
            dy = 2;
            break;
        case 2:
            dx = 2;
            dy = 5;
            break;
        default:
            dx = -3;
            dy = 2;
            break;
        }
        
        tile2i dock_tile = dock->tile.shifted(dx, dy);
        tile2i dest_dock;
        map_point_store_result(dock_tile, dest_dock);
        if (!map_has_figure_at(dest_dock)) {
            return {dock_id, dest_dock};
        }
    }
    return {0, map_point_invalid};
}
