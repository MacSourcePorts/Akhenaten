#include "game/tutorial.h"

#include "building/building_menu.h"
#include "city/message.h"

#include "city/city.h"
#include "city/finance.h"
#include "game/game.h"

void tutorial_2_on_build_temple(event_building_create ev) {
    if (g_tutorials_flags.tutorial_2.temples_built) {
        return;
    }

    building *b = building_get(ev.bid);
    if (!building_is_temple(b->type)) {
        return;
    }

    g_city_events.removeListener(typeid(event_building_create), &tutorial_2_on_build_temple);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    g_tutorials_flags.tutorial_2.temples_built = true;
    building_menu_update(tutorial_stage.tutorial_entertainment);
    city_message_post(true, MESSAGE_TUTORIAL_ENTERTAINMENT, 0, 0);
}

void tutorial_2_on_gold_extracted(event_gold_extract ev) {
    if (g_tutorials_flags.tutorial_2.gold_mined_500) {
        return;
    }

    if (g_city.finance.this_year.income.gold_extracted < 500) {
        return;
    }

    g_city_events.removeListener(typeid(event_gold_extract), &tutorial_2_on_gold_extracted);
    g_tutorials_flags.pharaoh.last_action = game.simtime.absolute_day();
    g_tutorials_flags.tutorial_2.gold_mined_500 = true;
    building_menu_update(tutorial_stage.tutorial_gods);
    city_message_post(true, MESSAGE_TUTORIAL_GODS_OF_EGYPT, 0, 0);
}

bool tutorial2_is_success() {
    auto &tut = g_tutorials_flags.tutorial_2;
    const bool may_finish = (tut.gold_mined_500 && tut.temples_built);
    const bool some_days_after_last_action = (game.simtime.absolute_day() - g_tutorials_flags.pharaoh.last_action) > 3;
    return may_finish && some_days_after_last_action;
}

void tutorial_2::init() {
    if (g_tutorials_flags.tutorial_2.gold_mined_500) building_menu_update(tutorial_stage.tutorial_gods);
    else g_city_events.appendListener(typeid(event_gold_extract), &tutorial_2_on_gold_extracted);

    if (g_tutorials_flags.tutorial_2.temples_built) building_menu_update(tutorial_stage.tutorial_entertainment);
    else g_city_events.appendListener(typeid(event_building_create), &tutorial_2_on_build_temple);

    g_city.victory_state.add_condition(&tutorial2_is_success);
}

void tutorial_2::reset() {
    g_tutorials_flags.tutorial_2.started = 0;
    g_tutorials_flags.tutorial_2.gold_mined_500 = 0;
    g_tutorials_flags.tutorial_2.temples_built = 0;
}