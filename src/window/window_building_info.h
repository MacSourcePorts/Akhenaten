#pragma once

#include "window_info.h"
#include "core/typename.h"

struct building;

struct building_info_window : public common_info_window {
    e_advisor first_advisor = ADVISOR_NONE;
    building_info_window();

    using widget::load;
    virtual void load(archive arch, pcstr section) override;
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) override;
    virtual void window_info_foreground(object_info &c) override;
    virtual void window_info_background(object_info &c) override;
    virtual textid get_tooltip(object_info &c) override;
    
    virtual void init(object_info &c) override;
    virtual void update_buttons(object_info &c) override;

    building *building_get(object_info &c);

    void common_info_background(object_info& c);
    void fill_employment_details(object_info &c);
};

template<typename T>
struct building_info_window_t : public building_info_window {
    virtual pcstr section() const override {
        static type_name_holder<T> _impl;
        static pcstr _section = strstr(_impl.value.data(), "::") ? strstr(_impl.value.data(), "::") + 2
                                : strstr(_impl.value.data(), "struct ") ? strstr(_impl.value.data(), "struct ") + 7
                                : strstr(_impl.value.data(), "class ") ? strstr(_impl.value.data(), "class ") + 6
                                : _impl.value.data();
        return _section;
    }
};