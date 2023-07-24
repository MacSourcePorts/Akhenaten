#include "translation/common.h"
#include "translation/translation.h"

static translation_string all_strings[] = {
        {TR_NO_PATCH_TITLE,                             "Патч 1.0.1.0 не установлен"},
        {TR_NO_PATCH_MESSAGE,
                                                        "Патч 1.0.1.0 в вашей версии игры Цезарь 3 отсутствует. "
                                                        "Вы можете скачать патч здесь:\n"
                                                        URL_PATCHES "\n"
                                                        "Продолжайте на свой страх и риск."},
        {TR_NO_EDITOR_TITLE,                            "Редактор карт не установлен"},
        {TR_NO_EDITOR_MESSAGE,
                                                        "Файлы редактора карт в вашей версии игры Цезарь 3 отсутствуют. "
                                                        "Вы можете скачать их здесь:\n"
                                                        URL_EDITOR},
        {TR_INVALID_LANGUAGE_TITLE,                     "Неправильная языковая директория"},
        {TR_INVALID_LANGUAGE_MESSAGE,
                                                        "В указанной папке языковые пакеты отсутствуют. "
                                                        "Пожалуйста, проверьте записи журнала игры (log)."},
        {TR_BUTTON_OK,                                  "Ок"},
        {TR_BUTTON_CANCEL,                              "Отмена"},
        {TR_BUTTON_RESET_DEFAULTS,                      "По умолчанию"},
        {TR_BUTTON_CONFIGURE_HOTKEYS,                   "Горячие клавиши"},
        {TR_CONFIG_TITLE,                               "Настройки Ozzy"},
        {TR_CONFIG_LANGUAGE_LABEL,                      "Язык:"},
        {TR_CONFIG_LANGUAGE_DEFAULT,                    "(по умолчанию)"},
        {TR_CONFIG_PAGE_LABEL,                          "Страница"},
        {TR_CONFIG_HEADER_UI_CHANGES,                   "Изменения пользовательского интерфейса"},
        {TR_CONFIG_HEADER_GAMEPLAY_CHANGES,             "Изменения игрового процесса"},
        {TR_CONFIG_SHOW_INTRO_VIDEO,                    "Проигрывать вступительные видеоролики"},
        {TR_CONFIG_SIDEBAR_INFO,                        "Дополнительная информация на панели управления"},
        {TR_CONFIG_SMOOTH_SCROLLING,                    "Включить плавную прокрутку карты"},
        {TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE,           "Улучшить наглядность очистки земли"},
        {TR_CONFIG_ALLOW_CYCLING_TEMPLES,               "Разрешить строительство каждого храма по очереди"},
        {TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE,          "Отображать область водоснабжения при строительстве зданий водоснабжения"},
        {TR_CONFIG_SHOW_CONSTRUCTION_SIZE,              "Отображать размер здания при строительстве с зажатой клавишей мыши"},
        {TR_CONFIG_FIX_IMMIGRATION_BUG,                 "Исправлять ошибку иммиграции на 'Очень сложной' сложности игры"},
        {TR_CONFIG_FIX_100_YEAR_GHOSTS,                 "Исправлять ошибку '100-летних призраков' населения"},
        {TR_CONFIG_FIX_EDITOR_EVENTS,                   "Исправлять запросы Императора и время выживания в польз. миссиях"},
        {TR_CONFIG_DRAW_WALKER_WAYPOINTS,               "Отображать маршрут ходоков по правому щелчку на здании"},
        {TR_CONFIG_ZOOM_STEPPED,                         "Включить функцию зума (возможно замедление)"},
        {TR_CONFIG_COMPLETE_RATING_COLUMNS,             "Исправить незавершенные колонны рейтинга"},
        {TR_CONFIG_GRANDFESTIVAL,                       "Великий фестиваль разрешает дополнительное благословение от божества"},
        {TR_CONFIG_JEALOUS_GODS,                        "Отключить ревность божеств"},
        {TR_CONFIG_GLOBAL_LABOUR,                       "Включить глобальный пул работников"},
        {TR_CONFIG_SCHOOL_WALKERS,                      "Увеличить зону покрытия школ"},
        {TR_CONFIG_RETIRE_AT_60,                        "Изменить возраст выхода на пенсию с 50 до 60 лет"},
        {TR_CONFIG_FIXED_WORKERS,                       "Фиксированный размер пула работников в 38% от населения"},
        {TR_CONFIG_EXTRA_FORTS,                         "Разрешить строительство 4-х дополнительных фортов"},
        {TR_CONFIG_WOLVES_BLOCK,                        "Запретить строительство около волков"},
        {TR_CONFIG_DYNAMIC_GRANARIES,                   "Блокировать тупиковые выходы из амбара"},
        {TR_CONFIG_MORE_STOCKPILE,                      "Дома запасают больше товаров с рынка"},
        {TR_CONFIG_NO_BUYER_DISTRIBUTION,               "Закупщицы с рынка не продают товары"},
        {TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS,        "Мгновенное разрушение зданий"},
        {TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD,        "Тележки в амбар могут покидать дорогу"},
        {TR_CONFIG_GRANARIES_GET_DOUBLE,                "Удвоить вместимость тележек распределяющих еду между амбарами"},
        {TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD,           "Башенные часовые не нуждаются в дороге"},
        {TR_CONFIG_FARMS_DELIVER_CLOSE,                 "Фермы и причалы доставляют еду только в близкорасположенные амбары"},
        {TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES, "Не доставлять еду в амбары с включенной доставкой"},
        {TR_CONFIG_ALL_HOUSES_MERGE,                    "Разрешить слияние всех домов"},
        {TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE,     "Торговые пути увеличивают разнообразие вина"},
        {TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY,         "Вместо разрушения, разрушающаяся шахта заберет часть денег"},
        {TR_CONFIG_MULTIPLE_BARRACKS,                   "Разрешить постройку нескольких казарм"},
        {TR_HOTKEY_TITLE,                               "Настройки горячих клавиш Ozzy"},
        {TR_HOTKEY_LABEL,                               "Основная"},
        {TR_HOTKEY_ALTERNATIVE_LABEL,                   "Альтернативная"},
        {TR_HOTKEY_HEADER_ARROWS,                       "Кнопки стрелок"},
        {TR_HOTKEY_HEADER_GLOBAL,                       "Глобальные горячие клавиши"},
        {TR_HOTKEY_HEADER_CITY,                         "Городские горячие клавиши"},
        {TR_HOTKEY_HEADER_ADVISORS,                     "Советники"},
        {TR_HOTKEY_HEADER_OVERLAYS,                     "Слои"},
        {TR_HOTKEY_HEADER_BOOKMARKS,                    "Закладки городской карты"},
        {TR_HOTKEY_HEADER_EDITOR,                       "Редактор"},
        {TR_HOTKEY_ARROW_UP,                            "Вверх"},
        {TR_HOTKEY_ARROW_DOWN,                          "Вниз"},
        {TR_HOTKEY_ARROW_LEFT,                          "Влево"},
        {TR_HOTKEY_ARROW_RIGHT,                         "Вправо"},
        {TR_HOTKEY_TOGGLE_FULLSCREEN,                   "Переключить на полный экран"},
        {TR_HOTKEY_CENTER_WINDOW,                       "Окно по центру"},
        {TR_HOTKEY_RESIZE_TO_640,                       "Задать размер окна 640x480"},
        {TR_HOTKEY_RESIZE_TO_800,                       "Задать размер окна 800x600"},
        {TR_HOTKEY_RESIZE_TO_1024,                      "Задать размер окна 1024x768"},
        {TR_HOTKEY_SAVE_SCREENSHOT,                     "Сохранить скриншот"},
        {TR_HOTKEY_SAVE_CITY_SCREENSHOT,                "Сохранить скриншот всего города"},
        {TR_HOTKEY_LOAD_FILE,                           "Загрузить файл"},
        {TR_HOTKEY_SAVE_FILE,                           "Сохранить файл"},
        {TR_HOTKEY_INCREASE_GAME_SPEED,                 "Увеличить скорость игры"},
        {TR_HOTKEY_DECREASE_GAME_SPEED,                 "Уменьшить скорость игры"},
        {TR_HOTKEY_TOGGLE_PAUSE,                        "Пауза"},
        {TR_HOTKEY_CYCLE_LEGION,                        "Следующий легион"},
        {TR_HOTKEY_ROTATE_MAP_LEFT,                     "Повернуть карту влево"},
        {TR_HOTKEY_ROTATE_MAP_RIGHT,                    "Повернуть карту вправо"},
        {TR_HOTKEY_SHOW_ADVISOR_LABOR,                  "Советник по труду"},
        {TR_HOTKEY_SHOW_ADVISOR_MILITARY,               "Военный советник"},
        {TR_HOTKEY_SHOW_ADVISOR_IMPERIAL,               "Советник по делам империи"},
        {TR_HOTKEY_SHOW_ADVISOR_RATINGS,                "Советник по рейтингам"},
        {TR_HOTKEY_SHOW_ADVISOR_TRADE,                  "Торговый советник"},
        {TR_HOTKEY_SHOW_ADVISOR_POPULATION,             "Советник по населению"},
        {TR_HOTKEY_SHOW_ADVISOR_HEALTH,                 "Советник по здоровью"},
        {TR_HOTKEY_SHOW_ADVISOR_EDUCATION,              "Советник по образованию"},
        {TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT,          "Советник по развлечениям"},
        {TR_HOTKEY_SHOW_ADVISOR_RELIGION,               "Советник по религии"},
        {TR_HOTKEY_SHOW_ADVISOR_FINANCIAL,              "Финансовый советник"},
        {TR_HOTKEY_SHOW_ADVISOR_CHIEF,                  "Главный советник"},
        {TR_HOTKEY_TOGGLE_OVERLAY,                      "Переключить текущий слой"},
        {TR_HOTKEY_SHOW_OVERLAY_WATER,                  "Включить слой водоснабжения"},
        {TR_HOTKEY_SHOW_OVERLAY_FIRE,                   "Включить слой риска пожара"},
        {TR_HOTKEY_SHOW_OVERLAY_DAMAGE,                 "Включить слой риска разрушения"},
        {TR_HOTKEY_SHOW_OVERLAY_CRIME,                  "Включить слой риска преступлений"},
        {TR_HOTKEY_SHOW_OVERLAY_PROBLEMS,               "Слой проблем"},
        {TR_HOTKEY_GO_TO_BOOKMARK_1,                    "Перейти к закладке 1"},
        {TR_HOTKEY_GO_TO_BOOKMARK_2,                    "Перейти к закладке 2"},
        {TR_HOTKEY_GO_TO_BOOKMARK_3,                    "Перейти к закладке 3"},
        {TR_HOTKEY_GO_TO_BOOKMARK_4,                    "Перейти к закладке 4"},
        {TR_HOTKEY_SET_BOOKMARK_1,                      "Назначить закладку 1"},
        {TR_HOTKEY_SET_BOOKMARK_2,                      "Назначить закладку 2"},
        {TR_HOTKEY_SET_BOOKMARK_3,                      "Назначить закладку 3"},
        {TR_HOTKEY_SET_BOOKMARK_4,                      "Назначить закладку 4"},
        {TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO,           "Информация боя"},
        {TR_HOTKEY_EDIT_TITLE,                          "Нажмите клавишу"},
        {TR_BUILDING_ROADBLOCK,                         "Дорожный блок"},
        {TR_BUILDING_ROADBLOCK_DESC,                    "Блокирует проход бесцельно бродящим ходокам"}
};

void translation_russian(const translation_string **strings, int *num_strings) {
    *strings = all_strings;
    *num_strings = sizeof(all_strings) / sizeof(translation_string);
}
