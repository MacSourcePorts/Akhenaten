#include "city_overlay_education.h"

#include "building/building_type.h"
#include "figure/figure.h"
#include "game/state.h"
#include "grid/property.h"

static int show_figure_education(const figure* f) {
    return f->type == FIGURE_SCRIBER || f->type == FIGURE_LIBRARIAN || f->type == FIGURE_TEACHER;
}

static int show_figure_library(const figure* f) {
    return f->type == FIGURE_LIBRARIAN;
}

static int show_figure_academy(const figure* f) {
    return f->type == FIGURE_SCRIBER;
}

static int get_column_height_education(const building* b) {
    return b->house_size && b->data.house.education ? b->data.house.education * 3 - 1 : NO_COLUMN;
}

static int get_column_height_library(const building* b) {
    return b->house_size && b->data.house.library ? b->data.house.library / 10 : NO_COLUMN;
}

static int get_column_height_academy(const building* b) {
    return b->house_size && b->data.house.academy ? b->data.house.academy / 10 : NO_COLUMN;
}

static int get_tooltip_education(tooltip_context* c, const building* b) {
    switch (b->data.house.education) {
    case 0:
        return 100;
    case 1:
        return 101;
    case 2:
        return 102;
    case 3:
        return 103;
    default:
        return 0;
    }
}

static int get_tooltip_library(tooltip_context* c, const building* b) {
    if (b->data.house.library <= 0)
        return 23;
    else if (b->data.house.library >= 80)
        return 24;
    else if (b->data.house.library >= 20)
        return 25;
    else {
        return 26;
    }
}

static int get_tooltip_academy(tooltip_context* c, const building* b) {
    if (b->data.house.academy <= 0)
        return 27;
    else if (b->data.house.academy >= 80)
        return 28;
    else if (b->data.house.academy >= 20)
        return 29;
    else {
        return 30;
    }
}

struct city_overlay_education : public city_overlay {
    city_overlay_education() {
        type = OVERLAY_EDUCATION;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        show_figure_func = show_figure_education;
        get_column_height = get_column_height_education;
        get_tooltip_for_building = get_tooltip_education;
    }

    bool show_building(const building* b) const override {
        return b->type == BUILDING_SCRIBAL_SCHOOL || b->type == BUILDING_LIBRARY || b->type == BUILDING_ACADEMY;
    }
};

city_overlay_education g_city_overlay_education;

city_overlay* city_overlay_for_education() {
    return &g_city_overlay_education;
}

struct city_overlay_libraries : public city_overlay {
    city_overlay_libraries() {
        type = OVERLAY_LIBRARY;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        show_figure_func = show_figure_library;
        get_column_height = get_column_height_library;
        get_tooltip_for_building = get_tooltip_library;
    }

    bool show_building(const building* b) const override {
        return b->type == BUILDING_LIBRARY;
    }
};

city_overlay_libraries g_city_overlay_libraries;

city_overlay* city_overlay_for_library() {
    return &g_city_overlay_libraries;
}

struct city_overlay_academy : public city_overlay {
    city_overlay_academy() {
        type = OVERLAY_ACADEMY;
        column_type = COLUMN_TYPE_WATER_ACCESS;

        show_figure_func = show_figure_academy;
        get_column_height = get_column_height_academy;
        get_tooltip_for_building = get_tooltip_academy;
    }

    bool show_building(const building* b) const override {
        return b->type == BUILDING_ACADEMY;
    }
};

city_overlay_academy g_city_overlay_academy;

city_overlay* city_overlay_for_academy() {
    return &g_city_overlay_academy;
}
