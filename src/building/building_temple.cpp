#include "building_temple.h"

#include "building/building.h"
#include "city/object_info.h"
#include "game/resource.h"
#include "graphics/elements/panel.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "io/gamefiles/lang.h"
#include "config/config.h"
#include "window/building/common.h"
#include "window/building/figures.h"
#include "sound/sound_building.h"
#include "graphics/animation.h"
#include "game/game.h"
#include "city/labor.h"
#include "building/count.h"
#include "widget/city/ornaments.h"
#include "window/window_building_info.h"

buildings::model_t<building_temple_osiris> temple_osiris_m;
buildings::model_t<building_temple_ra> temple_ra_m;
buildings::model_t<building_temple_ptah> temple_ptah_m;
buildings::model_t<building_temple_seth> temple_seth_m;
buildings::model_t<building_temple_bast> temple_bast_m;

struct temple_info_window_t : public common_info_window {
    virtual void window_info_background(object_info &c) override {
        auto &ui = *this;
        c.ui = &ui;

        auto temple = building_get(c.building_id)->dcast_temple();

        int image_offset = 0;
        switch (temple->type()) {
        case BUILDING_TEMPLE_OSIRIS: image_offset = 21; break;
        case BUILDING_TEMPLE_RA: image_offset = 22; break;
        case BUILDING_TEMPLE_PTAH: image_offset = 23; break;
        case BUILDING_TEMPLE_SETH: image_offset = 24; break;
        case BUILDING_TEMPLE_BAST: image_offset = 25; break;
        }

        c.help_id = temple->params().meta.help_id;
        int group_id = temple->params().meta.text_id;

        window_building_play_sound(&c, temple->get_sound());

        ui["title"] = ui::str(group_id, 0);
        ui["god_image"].image({PACK_UNLOADED, 21, image_offset});

        draw_employment_details_ui(ui, c, &temple->base, -1);

        if (!c.has_road_access) {
            window_building_draw_description_at(c, 16 * c.bgsize.y - 128, 69, 25);
        }
    }
};

temple_info_window_t g_temple_info_window;

ANK_REGISTER_CONFIG_ITERATOR(config_load_building_temples);
void config_load_building_temples() {
    temple_osiris_m.load();
    temple_ra_m.load();
    temple_ptah_m.load();
    temple_seth_m.load();
    temple_bast_m.load();
    g_temple_info_window.load("temple_info_window");
}

e_overlay building_temple::get_overlay() const {
    switch(type()) {
    case BUILDING_TEMPLE_OSIRIS: return OVERLAY_RELIGION_OSIRIS;
    case BUILDING_TEMPLE_RA: return OVERLAY_RELIGION_RA;
    case BUILDING_TEMPLE_PTAH: return OVERLAY_RELIGION_PTAH;
    case BUILDING_TEMPLE_SETH: return OVERLAY_RELIGION_SETH;
    case BUILDING_TEMPLE_BAST: return OVERLAY_RELIGION_BAST;
    }

    return OVERLAY_NONE;
}

e_sound_channel_city building_temple::sound_channel() const {
    switch (type()) {
    case BUILDING_TEMPLE_OSIRIS: return SOUND_CHANNEL_CITY_TEMPLE_OSIRIS;
    case BUILDING_TEMPLE_RA: return SOUND_CHANNEL_CITY_TEMPLE_RA;
    case BUILDING_TEMPLE_PTAH: return SOUND_CHANNEL_CITY_TEMPLE_PTAH;
    case BUILDING_TEMPLE_SETH: return SOUND_CHANNEL_CITY_TEMPLE_SETH;
    case BUILDING_TEMPLE_BAST: return SOUND_CHANNEL_CITY_TEMPLE_BAST;
    }

    return SOUND_CHANNEL_CITY_NONE;
}

void building_temple::window_info_background(object_info &c) {
    g_temple_info_window.window_info_background(c);
}

void building_temple::spawn_figure() {
    if (is_main()) {
        common_spawn_roamer(FIGURE_PRIEST, 50, FIGURE_ACTION_125_ROAMING);
    }
}

bool building_temple::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    building_draw_normal_anim(ctx, point, &base, tile, anim("work"), color_mask);

    return true;
}

const building_impl::static_params &building_temple::params() const {
    switch(type()) {
    case BUILDING_TEMPLE_OSIRIS: return temple_osiris_m;
    case BUILDING_TEMPLE_RA: return temple_ra_m;
    case BUILDING_TEMPLE_PTAH: return temple_ptah_m;
    case BUILDING_TEMPLE_SETH: return temple_seth_m;
    case BUILDING_TEMPLE_BAST: return temple_bast_m;
    }

    return building_impl::params();
}

const animation_t &building_temple::anim(pcstr key) const {
    return params().anim[key];
}
