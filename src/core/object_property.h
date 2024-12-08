#pragma once

#include "core/xstring.h"

struct id_property_t {
    static const xstring stored;
    static const xstring building;
    static const xstring figure;
    static const xstring city;
    static const xstring rating;
    static const xstring model;
    static const xstring farm;
    static const xstring name;
    static const xstring class_name;
    static const xstring laborers;
    static const xstring house;
    static const xstring level_name;
    static const xstring text;
    static const xstring industry;
    static const xstring progress;
    static const xstring tax_income_or_storage;
    static const xstring num_workers;
    static const xstring output_resource;
    static const xstring first_material;
    static const xstring first_material_stored;
    static const xstring tax_percentage;
    static const xstring total_stored;
    static const xstring free_space;
    static const xstring population;
    static const xstring treasury;
    static const xstring culture;
    static const xstring prosperity;
    static const xstring monument;
    static const xstring kingdom;
    static const xstring fertility;
    static const xstring rank_name;
    static const xstring player;
    static const xstring salary_amount;
    static const xstring months_since_festival;
};

const id_property_t &tags();