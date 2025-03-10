#include "population.h"

#include "building/building_house.h"
#include "city/city_house_population.h"
#include "building/model.h"
#include "city/city.h"
#include "core/calc.h"
#include "core/random.h"
#include "config/config.h"

static const int BIRTHS_PER_AGE_DECENNIUM[10] = {0, 3, 16, 9, 2, 0, 0, 0, 0, 0};

static const int DEATHS_PER_HEALTH_PER_AGE_DECENNIUM[11][10] = {{20, 10, 5, 10, 20, 30, 50, 85, 100, 100},
                                                                {15, 8, 4, 8, 16, 25, 45, 70, 90, 100},
                                                                {10, 6, 2, 6, 12, 20, 30, 55, 80, 90},
                                                                {5, 4, 0, 4, 8, 15, 25, 40, 65, 80},
                                                                {3, 2, 0, 2, 6, 12, 20, 30, 50, 70},
                                                                {2, 0, 0, 0, 4, 8, 15, 25, 40, 60},
                                                                {1, 0, 0, 0, 2, 6, 12, 20, 30, 50},
                                                                {0, 0, 0, 0, 0, 4, 8, 15, 20, 40},
                                                                {0, 0, 0, 0, 0, 2, 6, 10, 15, 30},
                                                                {0, 0, 0, 0, 0, 0, 4, 5, 10, 20},
                                                                {0, 0, 0, 0, 0, 0, 0, 2, 5, 10}};

static auto &city_data = g_city;
int city_population(void) {
    return city_data.population.current;
}

int city_population_school_age(void) {
    return city_data.population.school_age;
}

int city_population_academy_age(void) {
    return city_data.population.academy_age;
}

int city_population_last_used_house_add(void) {
    return city_data.population.last_used_house_add;
}

void city_population_set_last_used_house_add(int building_id) {
    city_data.population.last_used_house_add = building_id;
}

int city_population_last_used_house_remove(void) {
    return city_data.population.last_used_house_remove;
}

void city_population_set_last_used_house_remove(int building_id) {
    city_data.population.last_used_house_remove = building_id;
}

void city_population_t::recalculate() {
    int save_value = current;
    current = 0;
    for (int i = 0; i < 100; i++) {
        current += at_age[i];
    }

    highest_ever = std::max(current, highest_ever);
}

void city_population_clear_capacity(void) {
    city_data.population.total_capacity = 0;
    city_data.population.room_in_houses = 0;
}

void city_population_add_capacity(int people_in_house, int max_people) {
    city_data.population.total_capacity += max_people;
    city_data.population.room_in_houses += max_people - people_in_house;
}

static void add_to_census(int num_people) {
    int odd = 0;
    int index = 0;
    for (int i = 0; i < num_people; i++, odd = 1 - odd) {
        int age = random_from_pool(index++) & 0x3f; // 63
        if (age > 50)
            age -= 30;
        else if (age < 10 && odd)
            age += 20;

        city_data.population.at_age[age]++;
    }
}

static void remove_from_census(int num_people) {
    int index = 0;
    int empty_buckets = 0;
    // remove people randomly up to age 63
    while (num_people > 0 && empty_buckets < 100) {
        int age = random_from_pool(index++) & 0x3f;
        if (city_data.population.at_age[age] <= 0)
            empty_buckets++;
        else {
            city_data.population.at_age[age]--;
            num_people--;
            empty_buckets = 0;
        }
    }
    // if random didn't work: remove from age 10 and up
    empty_buckets = 0;
    int age = 10;
    while (num_people > 0 && empty_buckets < 100) {
        if (city_data.population.at_age[age] <= 0)
            empty_buckets++;
        else {
            city_data.population.at_age[age]--;
            num_people--;
            empty_buckets = 0;
        }
        age++;
        if (age >= 100)
            age = 0;
    }
}

static void remove_from_census_in_age_decennium(int decennium, int num_people) {
    int empty_buckets = 0;
    int age = 0;
    while (num_people > 0 && empty_buckets < 10) {
        if (city_data.population.at_age[10 * decennium + age] <= 0)
            empty_buckets++;
        else {
            city_data.population.at_age[10 * decennium + age]--;
            num_people--;
            empty_buckets = 0;
        }
        age++;
        if (age >= 10)
            age = 0;
    }
}

static int get_people_in_age_decennium(int decennium) {
    int pop = 0;
    for (int i = 0; i < 10; i++) {
        pop += city_data.population.at_age[10 * decennium + i];
    }
    return pop;
}

int city_population_t::average_age() {
    recalculate();
    if (!current) {
        return 0;
    }

    int age_sum = 0;
    for (int i = 0; i < 100; i++) {
        age_sum += (at_age[i] * i);
    }
    return age_sum / current;
}

void city_population_t::add(int num_people) {
    last_change = num_people;
    add_to_census(num_people);
    recalculate();
}

void city_population_t::remove(int num_people) {
    last_change = -num_people;
    remove_from_census(num_people);
    recalculate();
}

void city_population_t::add_homeless(int num_people) {
    lost_homeless -= num_people;
    add_to_census(num_people);
    recalculate();
}

void city_population_t::remove_homeless(int num_people) {
    lost_homeless += num_people;
    remove_from_census(num_people);
    recalculate();
}

void city_population_t::remove_home_removed(int num_people) {
    lost_removal += num_people;
    remove_from_census(num_people);
    recalculate();
}

void city_population_t::remove_for_troop_request(int num_people) {
    int removed = house_population_remove_from_city(num_people);
    remove_from_census(removed);
    lost_troop_request += num_people;
    recalculate();
}

int city_population_people_of_working_age() {
    if (config_get(CONFIG_GP_CH_RETIRE_AT_60)) {
        return get_people_in_age_decennium(2) + get_people_in_age_decennium(3) + get_people_in_age_decennium(4)
               + get_people_in_age_decennium(5);
    } else {
        return get_people_in_age_decennium(2) + get_people_in_age_decennium(3) + get_people_in_age_decennium(4);
    }
}

int city_population_percent_in_workforce(void) {
    if (!city_data.population.current)
        return 0;

    if (config_get(CONFIG_GP_CH_FIXED_WORKERS))
        return 38;

    return calc_percentage(city_data.labor.workers_available, city_data.population.current);
}

static int get_people_aged_between(int min, int max) {
    int pop = 0;
    for (int i = min; i < max; i++) {
        pop += city_data.population.at_age[i];
    }
    return pop;
}

void city_population_calculate_educational_age(void) {
    city_data.population.school_age = get_people_aged_between(0, 14);
    city_data.population.academy_age = get_people_aged_between(14, 21);
}

void city_population_t::record_monthly() {
    int save_value = monthly.values[monthly.next_index];
    monthly.values[monthly.next_index++] = current;
    if (monthly.next_index >= 2400)
        monthly.next_index = 0;

    ++monthly.count;

    if (save_value != current) {
        g_city_events.enqueue(event_population_changed{ current });
    }
}

int city_population_monthly_count() {
    return city_data.population.monthly.count;
}

int city_population_at_month(int max_months, int month) {
    int start_offset = 0;
    if (city_data.population.monthly.count > max_months)
        start_offset = city_data.population.monthly.count + 2400 - max_months;

    int index = (start_offset + month) % 2400;
    return city_data.population.monthly.values[index];
}

int city_population_at_age(int age) {
    return city_data.population.at_age[age];
}

int city_population_at_level(int house_level) {
    return city_data.population.at_level[house_level];
}

static void yearly_advance_ages_and_calculate_deaths(void) {
    int aged100 = city_data.population.at_age[99];
    for (int age = 99; age > 0; age--) {
        city_data.population.at_age[age] = city_data.population.at_age[age - 1];
    }
    city_data.population.at_age[0] = 0;
    city_data.population.yearly_deaths = 0;
    for (int decennium = 9; decennium >= 0; decennium--) {
        int people = get_people_in_age_decennium(decennium);
        int death_percentage = DEATHS_PER_HEALTH_PER_AGE_DECENNIUM[city_data.health.value / 10][decennium];
        int deaths = calc_adjust_with_percentage(people, death_percentage);
        int removed = house_population_remove_from_city(deaths + aged100);
        if (config_get(CONFIG_GP_FIX_100_YEAR_GHOSTS))
            remove_from_census_in_age_decennium(decennium, deaths);
        else {
            // Original C3 removes both deaths and aged100, which creates "ghosts".
            // It should be deaths only; now aged100 are removed from census while
            // they weren't *in* the census anymore
            remove_from_census_in_age_decennium(decennium, removed);
        }
        city_data.population.yearly_deaths += removed;
        aged100 = 0;
    }
}

static void yearly_calculate_births(void) {
    city_data.population.yearly_births = 0;
    for (int decennium = 9; decennium >= 0; decennium--) {
        int people = get_people_in_age_decennium(decennium);
        int births = calc_adjust_with_percentage(people, BIRTHS_PER_AGE_DECENNIUM[decennium]);
        int added = house_population_add_to_city(births);
        city_data.population.at_age[0] += added;
        city_data.population.yearly_births += added;
    }
}

void city_population_t::yearly_recalculate() {
    yearly_update_requested = 0;
    last_year = current;
    recalculate();

    lost_removal = 0;
    total_all_years += current;
    total_years++;
    average_per_year = total_all_years / total_years;
}

int calculate_total_housing_buildings(void) {
    int total = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (!house) {
            continue;
        }

        const e_building_state state = house->state();
        if (state == BUILDING_STATE_UNUSED || state == BUILDING_STATE_UNDO
            || state == BUILDING_STATE_DELETED_BY_GAME || state == BUILDING_STATE_DELETED_BY_PLAYER) {
            continue;
        }

        total += (house->house_population() > 0) ? 1 : 0;
    }

    return total;
}

int* calculate_number_of_each_housing_type(void) {
    static int housing_type_counts[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i <= 19; i++) {
        housing_type_counts[i] = 0;
    }

    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();

        if (!house) {
            continue;
        }

        if (house->state() == BUILDING_STATE_UNUSED || house->state() == BUILDING_STATE_UNDO
            || house->state() == BUILDING_STATE_DELETED_BY_GAME || house->state() == BUILDING_STATE_DELETED_BY_PLAYER) {
            continue;
        }

        if (house->house_population() > 0) {
            housing_type_counts[house->house_level()] += 1;
        }
    }

    return housing_type_counts;
}

int* calculate_houses_demanding_goods(int* housing_type_counts) {
    static int houses_demanding_goods[4] = {0, 0, 0, 0};

    for (int i = 0; i <= 3; i++) {
        houses_demanding_goods[i] = 0;
    }

    for (int i = 0; i <= 19; i++) {
        const auto &model = model_get_house(i);
        if (model.pottery)
            houses_demanding_goods[0] += housing_type_counts[i];

        if (model.jewelry)
            houses_demanding_goods[1] += housing_type_counts[i];

        if (model.linen)
            houses_demanding_goods[2] += housing_type_counts[i];

        if (model.beer)
            houses_demanding_goods[3] += housing_type_counts[i];
    }

    return houses_demanding_goods;
}

static int calculate_people_per_house_type(void) {
    city_data.population.people_in_shanties = 0;
    city_data.population.people_in_manors = 0;
    city_data.population.people_in_huts = 0;
    city_data.population.people_in_residences = 0;
    int total = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (!house) {
            continue;
        }

        if (house->state() == BUILDING_STATE_UNUSED || house->state() == BUILDING_STATE_UNDO
            || house->state() == BUILDING_STATE_DELETED_BY_GAME || house->state() == BUILDING_STATE_DELETED_BY_PLAYER) {
            continue;
        }

        if (house->house_population()) {
            auto &housed = house->runtime_data();
            int pop = housed.population;
            total += pop;

            e_house_level hlevel = house->house_level();
            if (hlevel <= HOUSE_STURDY_HUT) {
                city_data.population.people_in_huts += pop;
            }

            if (hlevel <= HOUSE_COMMON_SHANTY) {
                city_data.population.people_in_shanties += pop;
            }

            if (hlevel >= HOUSE_COMMON_RESIDENCE) {
                city_data.population.people_in_residences += pop;
            }

            if (hlevel >= HOUSE_COMMON_MANOR) {
                city_data.population.people_in_manors += pop;
            }
        }
    }
    return total;
}

void city_population_request_yearly_update(void) {
    city_data.population.yearly_update_requested = 1;
    calculate_people_per_house_type();
}

void city_population_t::yearly_update() {
    if (yearly_update_requested) {
        yearly_advance_ages_and_calculate_deaths();
        yearly_calculate_births();
        yearly_recalculate();
    }
}

void city_population_check_consistency(void) {
    int people_in_houses = calculate_people_per_house_type();
    if (people_in_houses < city_data.population.current)
        remove_from_census(city_data.population.current - people_in_houses);
}

int city_population_graph_order(void) {
    return city_data.population.graph_order;
}

void city_population_set_graph_order(int order) {
    city_data.population.graph_order = order;
}

int city_population_open_housing_capacity(void) {
    return city_data.population.room_in_houses;
}

int city_population_total_housing_capacity(void) {
    return city_data.population.total_capacity;
}

int city_population_yearly_deaths(void) {
    return city_data.population.yearly_deaths;
}

int city_population_yearly_births() {
    return city_data.population.yearly_births;
}

int city_population_t::percentage_in_shanties() {
    if (!current) {
        return 0;
    }

    return calc_percentage(people_in_shanties, city_data.population.current);
}

int city_population_t::percentage_in_manors() {
    if (!current) {
        return 0;
    }

    return calc_percentage(people_in_manors, current);
}
