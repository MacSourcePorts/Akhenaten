#pragma once

#include "overlays/city_overlay.h"

struct city_overlay_schools : public city_overlay {
    city_overlay_schools();

    virtual bool show_figure(const figure *f) const override;
    virtual void draw_custom_top(vec2i pixel, tile2i point, painter &ctx) const override;
    virtual int get_column_height(const building *b) const override;
    virtual int get_tooltip_for_building(tooltip_context *c, const building *b) const override;
    virtual bool show_building(const building *b) const override;
};