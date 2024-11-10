#pragma once

#include "city_overlay.h"

struct city_overlay_labor : public city_overlay_t<OVERLAY_LABOR> {
    virtual bool show_figure(const figure *f) const override;
    virtual int get_column_height(const building *b) const override;
    virtual xstring get_tooltip_for_building(tooltip_context *c, const building *b) const override;
    virtual bool show_building(const building *b) const override;
};

city_overlay* city_overlay_for_labor();