#include "building_dance_school.h"
#include "building_dance_school.h"

#include "building/building.h"
#include "building/count.h"
#include "city/object_info.h"
#include "city/labor.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "widget/city/ornaments.h"
#include "graphics/animation.h"
#include "figuretype/figure_entertainer.h"
#include "js/js_game.h"

buildings::model_t<building_dancer_school> dancer_school_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_dancer_school);
void config_load_building_dancer_school() {
    dancer_school_m.load();
}

void building_dancer_school::spawn_figure() {
    if (common_spawn_figure_trigger(50)) {
        int building_id = figure_entertainer::determine_venue_destination(base.road_access, {BUILDING_PAVILLION});
        building* dest= building_get(building_id);
        if (dest->id > 0) {
            create_figure_with_destination(FIGURE_DANCER, dest, FIGURE_ACTION_92_ENTERTAINER_GOING_TO_VENUE);
        } else {
            common_spawn_roamer(FIGURE_DANCER, 50, FIGURE_ACTION_90_ENTERTAINER_AT_SCHOOL_CREATED);
        }
    }
}

bool building_dancer_school::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    const auto &anim = dancer_school_m.anim["work"];
    building_draw_normal_anim(ctx, point, &base, tile, anim, color_mask);

    return true;
}

