#pragma once

#include "city/object_info.h"
#include "building/building.h"
#include "window/window_building_info.h"

class building_firehouse : public building_impl {
public:
    BUILDING_METAINFO(BUILDING_FIREHOUSE, building_firehouse)

    building_firehouse(building &b) : building_impl(b) {}
    virtual building_firehouse *dcast_firehouse() override { return this; }

    virtual void spawn_figure() override;
    virtual e_overlay get_overlay() const override { return OVERLAY_FIRE; }
    virtual void update_graphic() override;
    virtual int animation_speed(int speed) const override { return 4; }
    virtual bool draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) override;
};

struct info_window_firehouse : public building_info_window_t<info_window_firehouse> {
    virtual void window_info_background(object_info &c) override {
        building_info_window::common_info_background(c);
    }

    virtual bool check(object_info &c) override {
        return c.building_get()->dcast_firehouse();
    }
};