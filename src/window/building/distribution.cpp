#include "distribution.h"

#include "graphics/elements/image_button.h"
#include "graphics/elements/scrollbar.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "building/building_dock.h"
#include "building/storage.h"
#include "building/building_storage_yard.h"
#include "city/buildings.h"
#include "city/resource.h"
#include "figure/figure.h"
#include "game/resource.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/generic_button.h"
#include "graphics/elements/lang_text.h"
#include "graphics/elements/panel.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "scenario/property.h"
#include "window/window_building_info.h"
#include "game/game.h"

static void go_to_orders(int param1, int param2);
static void toggle_resource_state(int index, int param2);
static void toggle_resource_state_backwards(int index, int param2);
static void order_quantity_increase_decrease(int index, int param2);
static void granary_orders(int param1, int param2);
static void warehouse_orders(int index, int param2);
static void market_orders(int index, int param2);
static void storage_toggle_permissions(int index, int param2);

window_building_distribution::window_building_distribution() {
    orders_resource_buttons = {
        generic_button{0, 20 * 0, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 1, 0},
        generic_button{0, 20 * 1, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 2, 0},
        generic_button{0, 20 * 2, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 3, 0},
        generic_button{0, 20 * 3, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 4, 0},
        generic_button{0, 20 * 4, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 5, 0},
        generic_button{0, 20 * 5, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 6, 0},
        generic_button{0, 20 * 6, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 7, 0},
        generic_button{0, 20 * 7, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 8, 0},
        generic_button{0, 20 * 8, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 9, 0},
        generic_button{0, 20 * 9, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 10, 0},
        generic_button{0, 20 * 10, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 11, 0},
        generic_button{0, 20 * 11, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 12, 0},
        generic_button{0, 20 * 12, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 13, 0},
        generic_button{0, 20 * 13, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 14, 0},
        generic_button{0, 20 * 14, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 15, 0},
        generic_button{0, 20 * 15, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 16, 0},
        generic_button{0, 20 * 16, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 17, 0},
        generic_button{0, 20 * 17, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 18, 0},
        generic_button{0, 20 * 18, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 19, 0},
        generic_button{0, 20 * 19, 235, 22, toggle_resource_state, toggle_resource_state_backwards, 20, 0},
    };

    orders_decrease_arrows = {
        image_button{0, 20 * 0,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 1,  0, true},
        image_button{0, 20 * 1,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 2,  0, true},
        image_button{0, 20 * 2,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 3,  0, true},
        image_button{0, 20 * 3,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 4,  0, true},
        image_button{0, 20 * 4,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 5,  0, true},
        image_button{0, 20 * 5,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 6,  0, true},
        image_button{0, 20 * 6,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 7,  0, true},
        image_button{0, 20 * 7,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 8,  0, true},
        image_button{0, 20 * 8,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 9,  0, true},
        image_button{0, 20 * 9,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 10, 0, true},
        image_button{0, 20 * 10, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 11, 0, true},
        image_button{0, 20 * 11, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 12, 0, true},
        image_button{0, 20 * 12, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 13, 0, true},
        image_button{0, 20 * 13, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 14, 0, true},
        image_button{0, 20 * 14, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 15, 0, true},
        image_button{0, 20 * 15, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 16, 0, true},
        image_button{0, 20 * 16, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 17, 0, true},
        image_button{0, 20 * 17, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 18, 0, true},
        image_button{0, 20 * 18, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 19, 0, true},
        image_button{0, 20 * 19, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 3, order_quantity_increase_decrease, order_quantity_increase_decrease, 20, 0, true},
    };

    orders_increase_arrows = {
        image_button{0, 20 * 0,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 1,  1, true},
        image_button{0, 20 * 1,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 2,  1, true},
        image_button{0, 20 * 2,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 3,  1, true},
        image_button{0, 20 * 3,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 4,  1, true},
        image_button{0, 20 * 4,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 5,  1, true},
        image_button{0, 20 * 5,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 6,  1, true},
        image_button{0, 20 * 6,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 7,  1, true},
        image_button{0, 20 * 7,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 8,  1, true},
        image_button{0, 20 * 8,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 9,  1, true},
        image_button{0, 20 * 9,  17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 10, 1, true},
        image_button{0, 20 * 10, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 11, 1, true},
        image_button{0, 20 * 11, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 12, 1, true},
        image_button{0, 20 * 12, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 13, 1, true},
        image_button{0, 20 * 13, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 14, 1, true},
        image_button{0, 20 * 14, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 15, 1, true},
        image_button{0, 20 * 15, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 16, 1, true},
        image_button{0, 20 * 16, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 17, 1, true},
        image_button{0, 20 * 17, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 18, 1, true},
        image_button{0, 20 * 18, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 19, 1, true},
        image_button{0, 20 * 19, 17, 17, IB_NORMAL, GROUP_TINY_ARROWS, 0, order_quantity_increase_decrease, order_quantity_increase_decrease, 20, 1, true},
    };

    go_to_orders_button = {
        {0, 0, 304, 20, go_to_orders, button_none, 0, 0}
    };
}

static generic_button warehouse_distribution_permissions_buttons[] = {
  {0, 0, 20, 22, storage_toggle_permissions, button_none, 1, 0},
  {96, 0, 20, 22, storage_toggle_permissions, button_none, 2, 0},
  {228, 0, 20, 22, storage_toggle_permissions, button_none, 3, 0},
};

static generic_button granary_order_buttons[] = {
  {0, -15 * 16, 304, 20, granary_orders, button_none, 0, 0},
  {0, -22 - 15 * 16, 304, 20, warehouse_orders, button_none, 1, 0},
  {314, -15 * 16, 20, 20, granary_orders, button_none, 2, 0},
};

static generic_button market_order_buttons[] = {
  {314, -15 * 16, 20, 20, market_orders, button_none, 0, 0},
};

static generic_button warehouse_order_buttons[] = {
  {0, 5 * 16, 304, 20, warehouse_orders, button_none, 0, 0},
  {0, -22 + 5 * 16, 304, 20, warehouse_orders, button_none, 1, 0},
  {314, 5 * 16, 20, 20, warehouse_orders, button_none, 2, 0}, //
};

window_building_distribution g_window_building_distribution;

uint8_t warehouse_full_button_text[] = "32";
uint8_t warehouse_3quarters_button_text[] = "24";
uint8_t warehouse_half_button_text[] = "16";
uint8_t warehouse_quarter_button_text[] = "8";

uint8_t granary_full_button_text[] = "24";
uint8_t granary_3quarters_button_text[] = "18";
uint8_t granary_half_button_text[] = "12";
uint8_t granary_quarter_button_text[] = "6";

void window_building_draw_order_instruction(int instr_kind, const building_storage* storage, int resource, int x, int y, int market_order) {
    e_font font_nope = FONT_NORMAL_BLACK_ON_DARK;
    e_font font_yes = FONT_NORMAL_WHITE_ON_DARK;
    e_font font_get = FONT_NORMAL_YELLOW;

    if (storage != nullptr) {
        switch (storage->resource_state[resource]) {
        case STORAGE_STATE_PHARAOH_ACCEPT: {
            int width = lang_text_draw(99, 18, x, y, font_yes);
            int max_accept = storage->resource_max_accept[resource];
            if (max_accept == 3200)
                width += lang_text_draw(99, 28, x + width, y, font_yes);
            else if (max_accept == 2400)
                width += lang_text_draw(99, 27, x + width, y, font_yes);
            else if (max_accept == 1600)
                width += lang_text_draw(99, 26, x + width, y, font_yes);
            else if (max_accept == 800)
                width += lang_text_draw(99, 25, x + width, y, font_yes);
            else
                width += text_draw_number(max_accept, '@', " ", x + width, y, font_yes);
            if (max_accept == 2400 || max_accept == 1600 || max_accept == 800)
                lang_text_draw(99, 29, x + width, y, font_yes);
            break;
        }
        case STORAGE_STATE_PHARAOH_REFUSE:
            lang_text_draw(99, 8, x, y, font_nope);
            break;

        case STORAGE_STATE_PHARAOH_GET: {
            int width = lang_text_draw(99, 19, x, y, font_get);
            int max_get = storage->resource_max_get[resource];
            if (max_get == 3200)
                width += lang_text_draw(99, 31, x + width, y, font_get);
            else if (max_get == 2400)
                width += lang_text_draw(99, 27, x + width, y, font_get);
            else if (max_get == 1600)
                width += lang_text_draw(99, 26, x + width, y, font_get);
            else if (max_get == 800)
                width += lang_text_draw(99, 25, x + width, y, font_get);
            else
                width += text_draw_number(max_get, '@', " ", x + width, y, font_get);
            if (max_get == 2400 || max_get == 1600 || max_get == 800)
                lang_text_draw(99, 29, x + width, y, font_get);
            break;
        }
        case STORAGE_STATE_PHARAOH_EMPTY:
            lang_text_draw(99, 21, x, y, font_nope);
            break;
        }
    } else {
        switch (market_order) {
        case BAZAAR_ORDER_STATE_BUY:
            lang_text_draw(97, 8, x, y, font_yes);
            break;

        case BAZAAR_ORDER_STATE_DONT_BUY:
            lang_text_draw(97, 9, x, y, font_nope);
            break;
        }
    }
}

void draw_accept_none_button(int x, int y, int focused) {
    //    return; // temp - todo: fix buttons
    uint8_t refuse_button_text[] = {'x', 0};
    button_border_draw(x, y, 20, 20, focused ? 1 : 0);
    text_draw_centered(refuse_button_text, x + 1, y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
}

void draw_permissions_buttons(int x, int y, int buttons) {
    auto &data = g_window_building_distribution;
    return; // temp - todo: fix buttons
    uint8_t permission_button_text[] = {'x', 0};
    int offsets[] = {96, 132, 96};
    for (int i = 0; i < buttons; i++) {
        button_border_draw(x, y, 20, 20, data.permission_focus_button_id == i + 1 ? 1 : 0);
        if (building_storage_get_permission(i, building_get(data.building_id))) {
            text_draw_centered(permission_button_text, x + 1, y + 4, 20, FONT_NORMAL_BLACK_ON_LIGHT, 0);
        }

        x += offsets[i];
    }
}

int window_building_handle_mouse_dock(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    return generic_buttons_handle_mouse(m, c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 34, data.go_to_orders_button.data(), 1, &data.focus_button_id);
}

int window_building_handle_mouse_dock_orders(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28);

    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->offset.x + 180, y_offset + 46, data.orders_resource_buttons.data(), 15, &data.resource_focus_button_id)) {
        return 1;
    }
    return generic_buttons_handle_mouse(m, c->offset.x + 80, y_offset + 404, market_order_buttons, 1, &data.orders_focus_button_id);
}

#define Y_FOODS 90           // 234
#define Y_GOODS Y_FOODS + 20 // 174 //274

int window_building_handle_mouse_granary(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    data.building_id = c->building_id;
    generic_buttons_handle_mouse(m, c->offset.x + 58, c->offset.y + 19 * c->height_blocks - 82, warehouse_distribution_permissions_buttons, 1, &data.permission_focus_button_id);
    generic_buttons_handle_mouse(m, c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 34, data.go_to_orders_button.data(), 1, &data.focus_button_id);
    return 0;
}

int window_building_handle_mouse_granary_orders(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28 - 15);
    data.resource_focus_button_id = 0;

    // arrows
    bool handled = false;
    if (image_buttons_handle_mouse(m, c->offset.x + 165, y_offset + 49, data.orders_decrease_arrows.data(), 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (image_buttons_handle_mouse(m, c->offset.x + 165 + 18, y_offset + 49, data.orders_increase_arrows.data(), 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (handled) {
        return 1;
    }

    // resources
    int num_resources = city_resource_get_available_foods()->size;
    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->offset.x + 205, y_offset + 46, data.orders_resource_buttons.data(), num_resources, &data.resource_focus_button_id)) {
        return 1;
    }

    // extra instructions
    return generic_buttons_handle_mouse(m, c->offset.x + 80, y_offset + 404, granary_order_buttons, 2, &data.orders_focus_button_id);
}

std::pair<int, int> window_building_get_tooltip_granary_orders() {
    auto &data = g_window_building_distribution;
    if (data.orders_focus_button_id == 2) {
        return {143, 1};
    }

    return {-1, -1};
}

static void on_scroll(void) {
    //    window_invalidate();
}
static scrollbar_type scrollbar = {590, 52, 336, on_scroll};

int window_building_handle_mouse_warehouse(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    data.building_id = c->building_id;
    if (generic_buttons_handle_mouse(m, c->offset.x + 80, c->offset.y + 16 * c->height_blocks - 34, data.go_to_orders_button.data(), 1, &data.focus_button_id)) {
    }
    // temp - todo: fix buttons
    //    if (generic_buttons_handle_mouse(m, c->offset.x + 64, c->offset.y + 16 * c->height_blocks - 75,
    //                                     warehouse_distribution_permissions_buttons, 3,
    //                                     &data.permission_focus_button_id)) {
    //    }
    return 0;
}

int window_building_handle_mouse_warehouse_orders(const mouse* m, object_info* c) {
    auto &data = g_window_building_distribution;
    int y_offset = window_building_get_vertical_offset(c, 28 + 5);
    data.resource_focus_button_id = 0;

    bool handled = false;
    //    bool handled = scrollbar_handle_mouse(&scrollbar, m);
    //    if (handled)
    //        return handled;

    // arrows
    if (image_buttons_handle_mouse(m, c->offset.x + 165, y_offset + 49, data.orders_decrease_arrows.data(), 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (image_buttons_handle_mouse(m, c->offset.x + 165 + 18, y_offset + 49, data.orders_increase_arrows.data(), 20, &data.decr_arrow_focus_button_id)) {
        handled = true;
    }

    if (handled)
        return 1;

    // resources
    int num_resources = city_resource_get_available()->size;
    if (num_resources > 20) {
        num_resources = 20;
    }
    data.building_id = c->building_id;

    if (generic_buttons_handle_mouse(m, c->offset.x + 205, y_offset + 46, data.orders_resource_buttons.data(), num_resources, &data.resource_focus_button_id)) {
        return 1;
    }

    // extra instructions
    return generic_buttons_handle_mouse(m, c->offset.x + 80, y_offset + 404, warehouse_order_buttons, 2, &data.orders_focus_button_id);
}

void window_building_get_tooltip_warehouse_orders(int* group_id, int* text_id) {
    auto &data = g_window_building_distribution;
    if (data.orders_focus_button_id == 1) {
        *group_id = 99;
        *text_id = 6;
    }

    if (data.orders_focus_button_id == 2) {
        *group_id = 15;
        *text_id = 1;
    }
}

static void go_to_orders(int param1, int param2) {
    window_building_info_show_storage_orders();
}

static void storage_toggle_permissions(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    building_storage_set_permission(index - 1, b);
    //    window_invalidate();
}

static void toggle_resource_state(int index, int param2) {
    auto &data = g_window_building_distribution;
    building *b = building_get(data.building_id);
    int resource;

    building_bazaar *bazaar = b->dcast_bazaar();
    if (bazaar) {
        bazaar->toggle_good_accepted(index - 1);
        return;
    } 
    
    building_dock *dock = b->dcast_dock();
    if (dock) {
        dock->toggle_good_accepted(index - 1);
        return;
    }

    if (b->type == BUILDING_STORAGE_YARD)
        resource = city_resource_get_available()->items[index - 1];
    else
        resource = city_resource_get_available_foods()->items[index - 1];

    building_storage_cycle_resource_state(b->storage_id, resource, false);
}

static void toggle_resource_state_backwards(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    int resource;
    building_bazaar *bazaar = b->dcast_bazaar();
    if (bazaar) {
        bazaar->toggle_good_accepted(index - 1);
        return;
    }
    
    building_dock *dock = b->dcast_dock();
    if (dock) {
        dock->toggle_good_accepted(index - 1);
        return;
    } 

    if (b->type == BUILDING_STORAGE_YARD)
        resource = city_resource_get_available()->items[index - 1];
    else
        resource = city_resource_get_available_foods()->items[index - 1];

    building_storage_cycle_resource_state(b->storage_id, resource, true);
}

static void order_quantity_increase_decrease(int index, int param2) {
    auto &data = g_window_building_distribution;
    building* b = building_get(data.building_id);
    int resource;

    building_bazaar *bazaar = b->dcast_bazaar();
    if (bazaar) {
        return;
    }

    building_dock *dock = b->dcast_dock();
    if (dock) {
        return;
    }

    if (b->type == BUILDING_STORAGE_YARD)
        resource = city_resource_get_available()->items[index - 1];
    else
        resource = city_resource_get_available_foods()->items[index - 1];
    building_storage_increase_decrease_resource_state(b->storage_id, resource, param2);
}

static void market_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    building_bazaar* bazaar = building_get(data.building_id)->dcast_bazaar();
    if (index == 0) {
        bazaar->unaccept_all_goods();
    }
}

static void granary_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    int storage_id = building_get(data.building_id)->storage_id;
    if (index == 0)
        building_storage_toggle_empty_all(storage_id);
    else if (index == 1)
        building_storage_accept_none(storage_id);

    //    window_invalidate();
}
static void warehouse_orders(int index, int param2) {
    auto &data = g_window_building_distribution;
    if (index == 0) {
        int storage_id = building_get(data.building_id)->storage_id;
        building_storage_toggle_empty_all(storage_id);
    } else if (index == 1) {
        int storage_id = building_get(data.building_id)->storage_id;
        building_storage_accept_none(storage_id);
    } else if (index == 2) {
        int storage_id = building_get(data.building_id)->storage_id;
        building_storage_accept_none(storage_id);
    }
    //    window_invalidate();
}
