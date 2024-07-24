#include "building_fishing_wharf.h"

#include "js/js_game.h"
#include "city/labor.h"
#include "grid/water.h"
#include "grid/building.h"
#include "city/buildings.h"
#include "city/warnings.h"
#include "building/count.h"
#include "config/config.h"
#include "figure/figure.h"
#include "core/random.h"
#include "grid/image.h"
#include "widget/city/ornaments.h"
#include "sound/sound_building.h"
#include "game/game.h"
#include "graphics/elements/ui.h"
#include "graphics/graphics.h"

#include "dev/debug.h"
#include <iostream>

struct fishing_wharf_model : public buildings::model_t<building_fishing_wharf> {
} fishing_wharf_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_fishing_wharf);
void config_load_building_fishing_wharf() {
    fishing_wharf_m.load();
}

declare_console_command_p(killfishboats, game_cheat_kill_fish_boats);
void game_cheat_kill_fish_boats(std::istream &is, std::ostream &os) {
    figure_valid_do([] (figure &f) { f.poof(); }, FIGURE_FISHING_BOAT);
}

void building_fishing_wharf::on_create(int orientation) {
    data.industry.orientation = orientation;
    base.output_resource_first_id = RESOURCE_FISH;
}

void building_fishing_wharf::on_place_update_tiles(int orientation, int variant) {
    int orientation_rel = city_view_relative_orientation(orientation);
    int img_id = fishing_wharf_m.anim["base"].first_img();
    map_water_add_building(id(), tile(), fishing_wharf_m.building_size, img_id + orientation_rel);
}

void building_fishing_wharf::update_count() const {
    if (num_workers() > 0 && base.has_open_water_access) {
        const figure *boat = get_figure(BUILDING_SLOT_BOAT);
        city_buildings_add_working_wharf(boat->is_valid());
    }

    building_increase_industry_count(RESOURCE_FISH, num_workers() > 0);
}

void building_fishing_wharf::update_day() {
    building_impl::update_day();

    int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
    if (boat_id > 0) {
        figure *f = get_figure(BUILDING_SLOT_BOAT);
        if (!f->is_valid() || f->type != FIGURE_FISHING_BOAT) {
            base.set_figure(BUILDING_SLOT_BOAT, 0);
        }
    }
}

void building_fishing_wharf::update_graphic() {
    if (!can_play_animation()) {
        set_animation(animkeys().none);
        return;
    }
    
    figure *f = base.get_figure(BUILDING_SLOT_BOAT);
    if (!f->is_valid()) {
        set_animation(animkeys().none);
        return;
    }

    int image_warf = map_image_at(tile());
    int image_warf_base = anim(animkeys().base).first_img();
    xstring animkey;
    if (f->action_state != FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF) {
        if (image_warf == image_warf_base) animkey = animkeys().wait_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().wait_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().wait_s;
        else animkey = animkeys().wait_e;
    } else {
        if (image_warf == image_warf_base) animkey = animkeys().work_n;
        else if (image_warf == image_warf_base + 1) animkey = animkeys().work_w;
        else if (image_warf == image_warf_base + 2) animkey = animkeys().work_s;
        else animkey = animkeys().work_e;
    }

    set_animation(animkey);
}

void building_fishing_wharf::on_tick(bool refresh_only) {
    auto &anim_wharf = base.anim;
    if (anim_wharf.valid()) {
        data.dock.docker_anim_frame++;
        data.dock.docker_anim_frame %= (anim_wharf.max_frames * anim_wharf.frame_duration);
    }
}

void building_fishing_wharf::spawn_figure() {
    check_labor_problem();

    if (has_road_access()) {
        common_spawn_labor_seeker(100);
        int pct_workers = worker_percentage();
        int spawn_delay = figure_spawn_timer();
        if (spawn_delay == -1) {
            ; // nothing
        } else {
            base.figure_spawn_delay++;
            int boat_id = base.get_figure_id(BUILDING_SLOT_BOAT);
            if (!boat_id && base.figure_spawn_delay > spawn_delay) {
                base.figure_spawn_delay = 0;

                int dock_tile = data.dock.dock_tiles[0];
                if (config_get(CONFIG_GP_CH_FISHING_WHARF_SPAWN_BOATS) && dock_tile > 0) {
                    figure* f = figure_create(FIGURE_FISHING_BOAT, tile2i(dock_tile), DIR_4_BOTTOM_LEFT);
                    f->action_state = FIGURE_ACTION_190_FISHING_BOAT_CREATED;
                    f->set_home(id());
                    base.set_figure(BUILDING_SLOT_BOAT, f);
                    random_generate_next();
                    f->wait_ticks = random_short() % 30; // ok
                    f->allow_move_type = EMOVE_WATER;
                }
            }
        }
    }

    bool cart_spawned = base.common_spawn_goods_output_cartpusher();
    if (cart_spawned) {
        if (data.industry.has_fish) {
            data.industry.has_fish = (base.stored_full_amount > 0);
        }
    }
}

void building_fishing_wharf::on_place_checks() {
    building_impl::on_place_checks();

    if (!city_buildings_has_working_shipyard()) {
        building_construction_warning_show(WARNING_SHIPWRIGHT_NEEDED);
    }
}

void building_fishing_wharf::on_undo() {
    base.set_figure(BUILDING_SLOT_BOAT, 0);
}

void building_fishing_wharf::update_map_orientation(int orientation) {
    int image_offset = city_view_relative_orientation(data.industry.orientation);
    int image_id = fishing_wharf_m.anim["base"].first_img() + image_offset;
    map_water_add_building(id(), tile(), fishing_wharf_m.building_size, image_id);
}

bool building_fishing_wharf::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    auto &anim_wharf = base.anim;
    if (anim_wharf.valid()) {
        int img_id = anim_wharf.base + (data.dock.docker_anim_frame / anim_wharf.frame_duration) * 4;
        const image_t *img = image_get(img_id);
        ImageDraw::img_generic(ctx, img_id, point + anim_wharf.pos, color_mask, 1.f, true);
    }
    return true;
}

void building_fishing_wharf::window_info_background(object_info &c) {
    painter ctx = game.painter();

    c.help_id = 84;
    window_building_play_sound(&c, snd::get_building_info_sound("wharf"));
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(102, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    ImageDraw::img_generic(ctx, image_id_resource_icon(RESOURCE_FIGS) + resource_image_offset(RESOURCE_FIGS, RESOURCE_IMAGE_ICON), c.offset.x + 10, c.offset.y + 10);

    building* b = building_get(c.building_id);

    if (!c.has_road_access) {
        window_building_draw_description(c, 69, 25);
    } else if (!get_figure(BUILDING_SLOT_BOAT)->is_valid()) {
        window_building_draw_description(c, 102, 2);
    } else {
        int text_id;
        figure *boat = get_figure(BUILDING_SLOT_BOAT);
        switch (boat->action_state) {
        case FIGURE_ACTION_191_FISHING_BOAT_GOING_TO_FISH:
            text_id = 3;
            break;
        case FIGURE_ACTION_192_FISHING_BOAT_FISHING:
            text_id = 4;
            break;
        case FIGURE_ACTION_193_FISHING_BOAT_GOING_TO_WHARF:
            text_id = 5;
            break;
        case FIGURE_ACTION_194_FISHING_BOAT_AT_WHARF:
            text_id = 6;
            break;
        case FIGURE_ACTION_195_FISHING_BOAT_RETURNING_WITH_FISH:
            text_id = 7;
            break;
        default:
            text_id = 8;
            break;
        }
        window_building_draw_description(c, 102, text_id);
    }

    inner_panel_draw(c.offset.x + 16, c.offset.y + 136, c.bgsize.x - 2, 4);
    window_building_draw_employment(&c, 142);
}

void building_fishing_wharf::highlight_waypoints() {
    building_impl::highlight_waypoints();

    map_highlight_set(data.dock.dock_tiles[0], 3);
    map_highlight_set(data.dock.dock_tiles[1], 3);
}
