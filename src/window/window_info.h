#pragma once

#include "grid/point.h"
#include "city/city.h"
#include "core/variant.h"
#include "graphics/elements/ui.h"

struct object_info;
struct tooltip_context;

struct common_info_window : public ui::widget {
    virtual pcstr section() const { return ""; }
    virtual bool check(object_info &c) { return false; }
    virtual int get_height_id(object_info &c) { return 0; }
    virtual void window_info_background(object_info &c) { update_buttons(c); }
    virtual void window_info_foreground(object_info &c);
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) { return 0; }
    virtual textid get_tooltip(object_info &c) { return {0, 0}; }
    virtual void update_buttons(object_info &c);

    using widget::load;
    virtual void load(archive arch, pcstr section) override;
    virtual void init(object_info &c);

    void draw_tooltip(tooltip_context *c);

    svector<xstring, 4> open_sounds;

    static pcstr parse_config_name(pcstr data)
    {
        return strstr(data, "::") ? strstr(data, "::") + 2
                : strstr(data, "struct ") ? strstr(data, "struct ") + 7
                : strstr(data, "class ") ? strstr(data, "class ") + 6
                : data;
    }
};

void window_info_show(const tile2i& point, bool avoid_mouse = false);
int window_building_info_get_type();
void window_building_info_show_storage_orders();
void window_building_register_handler(common_info_window *handler);
void window_figure_register_handler(common_info_window *handler);