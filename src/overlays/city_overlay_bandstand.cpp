#include "city_overlay_juggler.h"

#include "figure/figure.h"
#include "grid/property.h"
#include "grid/building.h"
#include "graphics/elements/tooltip.h"
#include "figuretype/figure_musician.h"
#include "city_overlay_bandstand.h"

city_overlay_bandstand g_city_overlay_bandstand;

city_overlay* city_overlay_for_bandstand() {
    return &g_city_overlay_bandstand;
}

city_overlay_bandstand::city_overlay_bandstand() {
    type = OVERLAY_BANDSTAND;
}

xstring city_overlay_bandstand::get_tooltip_for_building(tooltip_context *c, const building *b) const {
    if (b->data.house.bandstand_musician <= 0)
        return ui::str(66, 79);
    else if (b->data.house.bandstand_musician >= 80)
        return ui::str(66, 80);
    else if (b->data.house.bandstand_musician >= 20)
        return ui::str(66, 81);

    return ui::str(66, 82);
}

bool city_overlay_bandstand::show_figure(const figure *f) const {
    figure_musician *musician = ((figure *)f)->dcast_musician();
    return musician
             ? musician->current_destination()->type == BUILDING_BANDSTAND
             : false;
}

int city_overlay_bandstand::get_column_height(const building *b) const {
    if (b->house_size) {
        if (b->data.house.bandstand_musician) {
            return b->data.house.bandstand_musician / 10;
        }
    }

    return NO_COLUMN;
}
