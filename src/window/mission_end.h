#pragma once

#include "autoconfig_window.h"

namespace ui {

    struct mission_end_window : public autoconfig_window_t<mission_end_window> {
        virtual int handle_mouse(const mouse *m) override;
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override;
        virtual int draw_background(UiFlags flags) override;
        virtual int ui_handle_mouse(const mouse *m) override;

        autoconfig_window &getui();

        virtual void init() override;
    };

    struct mission_won_window : public autoconfig_window_t<mission_won_window> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override;

        virtual void init() override {}
    };

    struct mission_lost_window : public autoconfig_window_t<mission_lost_window> {
        virtual int handle_mouse(const mouse *m) override { return 0; }
        virtual int get_tooltip_text() override { return 0; }
        virtual void draw_foreground(UiFlags flags) override {}
        virtual int draw_background(UiFlags flags) override { return 0; }

        virtual void init() override {}
    };

}

void window_mission_end_show_won(void);
void window_mission_end_show_fired(void);
