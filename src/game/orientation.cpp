#include "orientation.h"

#include "city/warning.h"
#include "core/direction.h"
#include "graphics/view/view.h"
#include "grid/orientation.h"
#include "widget/widget_minimap.h"

void game_orientation_rotate_left(void) {
    city_view_rotate_left();
    map_orientation_change(0);
    widget_minimap_invalidate();
    city_warning_show(WARNING_ORIENTATION);
}

void game_orientation_rotate_right(void) {
    city_view_rotate_right();
    map_orientation_change(1);
    widget_minimap_invalidate();
    city_warning_show(WARNING_ORIENTATION);
}

void game_orientation_rotate_north(void) {
    switch (city_view_orientation()) {
    case DIR_2_BOTTOM_RIGHT:
        city_view_rotate_left();
        map_orientation_change(1);
        break;
    case DIR_4_BOTTOM_LEFT:
        city_view_rotate_right();
        map_orientation_change(0);
        // fallthrough
    case DIR_6_TOP_LEFT:
        city_view_rotate_right();
        map_orientation_change(0);
        break;
    default: // already north
        return;
    }
    widget_minimap_invalidate();
    city_warning_show(WARNING_ORIENTATION);
}
