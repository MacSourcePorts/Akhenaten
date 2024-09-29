#include "trade_prices.h"

#include "empire/trade_prices.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "graphics/elements/lang_text.h"
#include "graphics/view/view.h"
#include "graphics/elements/panel.h"
#include "graphics/screen.h"
#include "graphics/text.h"
#include "graphics/window.h"
#include "input/input.h"
#include "window/advisors.h"
#include "window/autoconfig_window.h"
#include "io/gamefiles/lang.h"
#include "game/game.h"

struct trade_prices_window : autoconfig_window_t<trade_prices_window> {
    virtual int handle_mouse(const mouse *m) override { return 0; }
    virtual int get_tooltip_text() override { return 0; }
    virtual void draw_foreground() override {}
    virtual int draw_background() override;
    virtual void ui_draw_foreground() override;
    virtual int ui_handle_mouse(const mouse *m) override;
    virtual void init() {}

    virtual void load(archive arch, pcstr section) override {
        autoconfig_window::load(arch, section);

        next_row_offset = arch.r_vec2i("next_row_offset");
        next_item_offset = arch.r_vec2i("next_item_offset");
        receive_offset = arch.r_vec2i("receive_offset");
        buyer_offset = arch.r_vec2i("buyer_offset");
        next = arch.r_int("next");
    }

    vec2i next_row_offset;
    vec2i next_item_offset;
    vec2i receive_offset;
    vec2i buyer_offset;
    int next;
};

trade_prices_window trade_prices_w;

int trade_prices_window::draw_background() {
    window_draw_underlying_window();

    return 0;
}

void trade_prices_window::ui_draw_foreground() {
    ui.begin_widget(ui.pos);
    ui.draw();

    vec2i items_pos = ui["items"].pos;
    vec2i current_pos = items_pos;
    int start_i = 0;
    for (int i = 1; (start_i + i) < RESOURCES_MAX; i++) {
        int image_offset = i;
        if (i >= next) {
            start_i += next;
            i = 0;
            items_pos += next_row_offset;
            current_pos = items_pos;
        }

        e_resource resource = e_resource(start_i + i);
        if (resource == RESOURCE_UNUSED12) {
            continue;
        }

        ui.icon(current_pos, resource);

        const int buy_price = trade_price_buy(i);
        const int sell_price = trade_price_sell(i);
        ui.label(bstring32(buy_price), current_pos + buyer_offset , FONT_NORMAL_BLACK_ON_LIGHT);
        ui.label(bstring32(sell_price), current_pos + receive_offset, FONT_NORMAL_BLACK_ON_LIGHT);

        current_pos += next_item_offset;
    }

    ui.end_widget();
}

int trade_prices_window::ui_handle_mouse(const mouse *m) {
    const hotkeys *h = hotkey_state();
    if (input_go_back_requested(m, h)) {
        window_advisors_show();
        return 0;
    }

    return autoconfig_window::ui_handle_mouse(m);
}

static int get_tooltip_resource(tooltip_context* c) {
    int x_base = screen_dialog_offset_x() + 124;
    int y = screen_dialog_offset_y() + 192;
    int x_mouse = c->mpos.x;
    int y_mouse = c->mpos.y;

    for (int i = 1; i < 16; i++) {
        int x = x_base + 30 * i;
        if (x <= x_mouse && x + 24 > x_mouse && y <= y_mouse && y + 24 > y_mouse)
            return i;
    }
    return 0;
}

static void get_tooltip(tooltip_context* c) {
    int resource = get_tooltip_resource(c);
    if (!resource) {
        return;
    }

    c->text = (pcstr)lang_get_string(0, 131 + resource);
}

void window_trade_prices_show(void) {
    static window_type window = {
        WINDOW_TRADE_PRICES,
        [] { trade_prices_w.draw_background(); },
        [] { trade_prices_w.ui_draw_foreground(); },
        [] (const mouse *m, const hotkeys *h) { trade_prices_w.ui_handle_mouse(m); },
        nullptr
    };

    window_show(&window);
}
