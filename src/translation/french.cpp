#include "translation/common.h"
#include "translation/translation.h"

#include "translation/common.h"
#include "translation/translation.h"

static translation_string all_strings[] = {
        {TR_NO_PATCH_TITLE,                             "Patch 1.0.1.0 manquant"},
        {TR_NO_PATCH_MESSAGE,
                                                        "Votre installation de Cesar 3 ne contient pas le patch 1.0.1.0. "
                                                        "Vous pouvez le télécharger depuis : \n"
                                                        URL_PATCHES "\n"
                                                        "Procédez à vos propres risques."},
        {TR_MISSING_FONTS_TITLE,                        "Polices manquantes"},
        {TR_MISSING_FONTS_MESSAGE,
                                                        "Votre installation de Cesar 3 requiert des polices d'écriture supplémentaires. "
                                                        "Vous pouvez les télécharger pour votre langue depuis : \n"
                                                        URL_PATCHES},
        {TR_NO_EDITOR_TITLE,                            "Éditeur manquant"},
        {TR_NO_EDITOR_MESSAGE,
                                                        "Votre installation de Cesar 3 ne contient pas le fichier éditeur. "
                                                        "Vous pouvez le télécharger depuis : \n"
                                                        URL_EDITOR},
        {TR_INVALID_LANGUAGE_TITLE,                     "Répertoire de langue invalide"},
        {TR_INVALID_LANGUAGE_MESSAGE,
                                                        "Le répertoire que vous avez sélectionné ne contient pas de pack de langue valide. "
                                                        "Veuillez consulter les erreurs dans le fichier de log."},
        {TR_BUTTON_OK,                                  "OK"},
        {TR_BUTTON_CANCEL,                              "Annuler"},
        {TR_BUTTON_RESET_DEFAULTS,                      "Réinitialiser"},
        {TR_BUTTON_CONFIGURE_HOTKEYS,                   "Contrôles du clavier"},
        {TR_BUTTON_NEXT,                                "+"},
        {TR_BUTTON_PREV,                                "-"},
        {TR_CONFIG_TITLE,                               "Options de configuration d'Ozzy"},
        {TR_CONFIG_LANGUAGE_LABEL,                      "Langue :"},
        {TR_CONFIG_LANGUAGE_DEFAULT,                    "(par défaut)"},
        {TR_CONFIG_PAGE_LABEL,                          "Page"},
        {TR_CONFIG_HEADER_UI_CHANGES,                   "Configuration de l'interface"},
        {TR_CONFIG_HEADER_GAMEPLAY_CHANGES,             "Configuration du jeu"},
        {TR_CONFIG_SHOW_INTRO_VIDEO,                    "Jouer la vidéo d'introduction"},
        {TR_CONFIG_SIDEBAR_INFO,                        "Informations supplémentaires dans le panneau latéral"},
        {TR_CONFIG_SMOOTH_SCROLLING,                    "Activer le défilement doux"},
        {TR_CONFIG_VISUAL_FEEDBACK_ON_DELETE,           "Améliore le retour visuel durant le dégagement du terrain"},
        {TR_CONFIG_ALLOW_CYCLING_TEMPLES,               "Permet de construire tous les temples successivement"},
        {TR_CONFIG_SHOW_WATER_STRUCTURE_RANGE,          "Voir la zone d'effet en plaçant des réservoirs, des fontaines et des puits"},
        {TR_CONFIG_SHOW_CONSTRUCTION_SIZE,              "Voir la taille des constructions durant le glissement de la souris"},
        {TR_CONFIG_HIGHLIGHT_LEGIONS,                   "Mettre en surbrillance les légions au survol du curseur"},
        {TR_CONFIG_ROTATE_MANUALLY,                     "Rotation corps de garde et l'arc de triomphe par raccourci clavier"},
        {TR_CONFIG_FIX_IMMIGRATION_BUG,                 "Corrige le bug d'immigration en mode très difficile"},
        {TR_CONFIG_FIX_100_YEAR_GHOSTS,                 "Corrige le bug des fantômes de 100 ans"},
        {TR_CONFIG_FIX_EDITOR_EVENTS,                   "Corrige \"Nouvel Empereur\" et la survie des parties créees avec l'éditeur"},
        {TR_CONFIG_DRAW_WALKER_WAYPOINTS,               "Affiche l'itinéraire du marcheur en cliquant droit sur un bâtiment"},
        {TR_CONFIG_ZOOM_STEPPED,                         "Active le zoom (peut être lent et utilise plus de RAM)"},
        {TR_CONFIG_COMPLETE_RATING_COLUMNS,             "Corrige les colonnes d'évaluation incomplètes"},
        {TR_CONFIG_GRANDFESTIVAL,                       "Les grandes fêtes permettent une bénédiction supplémentaire d'un dieu"},
        {TR_CONFIG_JEALOUS_GODS,                        "Déactive la jalousie des dieux"},
        {TR_CONFIG_GLOBAL_LABOUR,                       "Active la main-d'œuvre globale"},
        {TR_CONFIG_SCHOOL_WALKERS,                      "Augmente la couverture des écoliers"},
        {TR_CONFIG_RETIRE_AT_60,                        "Change l'âge de retraitre des citoyens de 50 à 60"},
        {TR_CONFIG_FIXED_WORKERS,                       "Corrige la force travail - 38% de la population"},
        {TR_CONFIG_EXTRA_FORTS,                         "Autorise la construction de 4 forts supplémentaires"},
        {TR_CONFIG_WOLVES_BLOCK,                        "Bloque la construction autour des loups"},
        {TR_CONFIG_DYNAMIC_GRANARIES,                   "Bloque les routes des greniers non connectées"},
        {TR_CONFIG_MORE_STOCKPILE,                      "Les maisons stockent plus de marchandises du marché"},
        {TR_CONFIG_NO_BUYER_DISTRIBUTION,               "Les vendeuses du marché ne distribuent pas les marchandises"},
        {TR_CONFIG_IMMEDIATELY_DELETE_BUILDINGS,        "Destruction immédiate des bâtiments"},
        {TR_CONFIG_GETTING_GRANARIES_GO_OFFROAD,        "Les charretiers peuvent faire du hors route"},
        {TR_CONFIG_GRANARIES_GET_DOUBLE,                "Double la capacité des charretiers sortant des greniers"},
        {TR_CONFIG_TOWER_SENTRIES_GO_OFFROAD,           "Les sentinelles de la tour n'ont plus besoin de route"},
        {TR_CONFIG_FARMS_DELIVER_CLOSE,                 "Fermes et Quais ne livrent plus qu'aux grenier à proximité"},
        {TR_CONFIG_DELIVER_ONLY_TO_ACCEPTING_GRANARIES, "La nourriture n'est pas livrée depuis/vers les greniers"},
        {TR_CONFIG_ALL_HOUSES_MERGE,                    "Toutes les maisons fusionnent"},
        {TR_CONFIG_WINE_COUNTS_IF_OPEN_TRADE_ROUTE,     "Ouvre des routes commerciales qui founissent différents types de vins"},
        {TR_CONFIG_RANDOM_COLLAPSES_TAKE_MONEY,         "Les mines coûtent de l'argent au lieu d'être détruites."},
        {TR_CONFIG_MULTIPLE_BARRACKS,                   "Autorise la construction de plusieurs casernes."},
        {TR_CONFIG_NOT_ACCEPTING_WAREHOUSES,            "Les entrepôts n'acceptent rien une fois construits"},
        {TR_CONFIG_HOUSES_DONT_EXPAND_INTO_GARDENS,     "Les maisons ne s'étendent pas sur les jardins"},
        {TR_HOTKEY_TITLE,                               "Configuration Raccourcis clavier"},
        {TR_HOTKEY_LABEL,                               "Raccourcis clavier"},
        {TR_HOTKEY_ALTERNATIVE_LABEL,                   "Alternative"},
        {TR_HOTKEY_HEADER_ARROWS,                       "Flèches directionnelles"},
        {TR_HOTKEY_HEADER_GLOBAL,                       "Contrôles globaux"},
        {TR_HOTKEY_HEADER_CITY,                         "Contrôles de la cité"},
        {TR_HOTKEY_HEADER_ADVISORS,                     "Rapports des conseillers"},
        {TR_HOTKEY_HEADER_OVERLAYS,                     "Cartes de visualisation"},
        {TR_HOTKEY_HEADER_BOOKMARKS,                    "Points d'intérêt de la cité"},
        {TR_HOTKEY_HEADER_EDITOR,                       "Editeur"},
        {TR_HOTKEY_HEADER_BUILD,                        "Raccourcis de construction"},
        {TR_HOTKEY_ARROW_UP,                            "Haut"},
        {TR_HOTKEY_ARROW_DOWN,                          "Bas"},
        {TR_HOTKEY_ARROW_LEFT,                          "Gauche"},
        {TR_HOTKEY_ARROW_RIGHT,                         "Droite"},
        {TR_HOTKEY_TOGGLE_FULLSCREEN,                   "Basculer en plein écran"},
        {TR_HOTKEY_CENTER_WINDOW,                       "Centrer la fenêtre"},
        {TR_HOTKEY_RESIZE_TO_640,                       "Redimensionner en 640x480"},
        {TR_HOTKEY_RESIZE_TO_800,                       "Redimensionner en 800x600"},
        {TR_HOTKEY_RESIZE_TO_1024,                      "Redimensionner en 1024x768"},
        {TR_HOTKEY_SAVE_SCREENSHOT,                     "Capturer l'écran de jeu"},
        {TR_HOTKEY_SAVE_CITY_SCREENSHOT,                "Capturer la cité entière"},
        {TR_HOTKEY_LOAD_FILE,                           "Charger une partie"},
        {TR_HOTKEY_SAVE_FILE,                           "Sauvegarder une partie"},
        {TR_HOTKEY_INCREASE_GAME_SPEED,                 "Augmenter la vitesse du jeu"},
        {TR_HOTKEY_DECREASE_GAME_SPEED,                 "Diminuer la vitesse du jeu"},
        {TR_HOTKEY_TOGGLE_PAUSE,                        "Activer la pause"},
        {TR_HOTKEY_CYCLE_LEGION,                        "Parcourir les légions en boucle"},
        {TR_HOTKEY_ROTATE_MAP_LEFT,                     "Tourner la carte vers la gauche"},
        {TR_HOTKEY_ROTATE_MAP_RIGHT,                    "Tourner la carte vers la droite"},
        {TR_HOTKEY_SHOW_ADVISOR_LABOR,                  "Main-d'œuvre"},
        {TR_HOTKEY_SHOW_ADVISOR_MILITARY,               "Légion"},
        {TR_HOTKEY_SHOW_ADVISOR_IMPERIAL,               "Empereur"},
        {TR_HOTKEY_SHOW_ADVISOR_RATINGS,                "Évaluation"},
        {TR_HOTKEY_SHOW_ADVISOR_TRADE,                  "Commerce"},
        {TR_HOTKEY_SHOW_ADVISOR_POPULATION,             "Population"},
        {TR_HOTKEY_SHOW_ADVISOR_HEALTH,                 "Hygiène"},
        {TR_HOTKEY_SHOW_ADVISOR_EDUCATION,              "Éducation"},
        {TR_HOTKEY_SHOW_ADVISOR_ENTERTAINMENT,          "Loisirs"},
        {TR_HOTKEY_SHOW_ADVISOR_RELIGION,               "Religion"},
        {TR_HOTKEY_SHOW_ADVISOR_FINANCIAL,              "Finances"},
        {TR_HOTKEY_SHOW_ADVISOR_CHIEF,                  "Conseiller personnel"},
        {TR_HOTKEY_SHOW_ADVISOR_HOUSING,                "Conseiller en logement"},
        {TR_HOTKEY_TOGGLE_OVERLAY,                      "Basculer sur la carte précédente"},
        {TR_HOTKEY_SHOW_OVERLAY_WATER,                  "Eau"},
        {TR_HOTKEY_SHOW_OVERLAY_FIRE,                   "Incendies"},
        {TR_HOTKEY_SHOW_OVERLAY_DAMAGE,                 "Dégats"},
        {TR_HOTKEY_SHOW_OVERLAY_CRIME,                  "Criminalité"},
        {TR_HOTKEY_ROTATE_BUILDING,                     "Rotation de bâtiment"},
        {TR_HOTKEY_SHOW_OVERLAY_PROBLEMS,               "Problèmes"},
        {TR_HOTKEY_GO_TO_BOOKMARK_1,                    "Aller au point d'intérêt 1"},
        {TR_HOTKEY_GO_TO_BOOKMARK_2,                    "Aller au point d'intérêt 2"},
        {TR_HOTKEY_GO_TO_BOOKMARK_3,                    "Aller au point d'intérêt 3"},
        {TR_HOTKEY_GO_TO_BOOKMARK_4,                    "Aller au point d'intérêt 4"},
        {TR_HOTKEY_SET_BOOKMARK_1,                      "Définir comme point d'intérêt 1"},
        {TR_HOTKEY_SET_BOOKMARK_2,                      "Définir comme point d'intérêt 2"},
        {TR_HOTKEY_SET_BOOKMARK_3,                      "Définir comme point d'intérêt 3"},
        {TR_HOTKEY_SET_BOOKMARK_4,                      "Définir comme point d'intérêt 4"},
        {TR_HOTKEY_EDITOR_TOGGLE_BATTLE_INFO,           "Afficher les infos de bataille"},
        {TR_HOTKEY_EDIT_TITLE,                          "Appuyez sur une touche"},
        {TR_BUILDING_ROADBLOCK,                         "Barrages"},
        {TR_BUILDING_ROADBLOCK_DESC,                    "Barrages arrêtent les citoyens errants"},
        {TR_HEADER_HOUSING,                             "Logement"},
        {TR_ADVISOR_HOUSING_ROOM,                       "Le logement en ville a de la place pour"},
        {TR_ADVISOR_HOUSING_NO_ROOM,                    "Il n'y a plus de chambre disponible dans les logements."},
        {TR_ADVISOR_RESIDENCES_DEMANDING_POTTERY,       "Résidences exigeant de la poterie"},
        {TR_ADVISOR_RESIDENCES_DEMANDING_FURNITURE,     "Résidences exigeantes en mobilier"},
        {TR_ADVISOR_RESIDENCES_DEMANDING_OIL,           "Résidences exigeantes en huile"},
        {TR_ADVISOR_RESIDENCES_DEMANDING_WINE,          "Résidences exigeant du vin"},
        {TR_ADVISOR_TOTAL_NUM_HOUSES,                   "Total des résidences :"},
        {TR_ADVISOR_AVAILABLE_HOUSING_CAPACITY,         "Capacité totale :"},
        {TR_ADVISOR_TOTAL_HOUSING_CAPACITY,             "Capacité totale :"},
        {TR_ADVISOR_ADVISOR_HEADER_HOUSING,             "Population - Logement"},
        {TR_ADVISOR_BUTTON_GRAPHS,                      "Graphiques"},
        {TR_ADVISOR_HOUSING_PROSPERITY_RATING,          "La cote de prospérité du logement est"},
        {TR_ADVISOR_PERCENTAGE_IN_VILLAS_PALACES,       "Pourcentage de votre population dans les villas et palais est"},
        {TR_ADVISOR_PERCENTAGE_IN_TENTS_SHACKS,         "Pourcentage de votre population dans les tentes et cabanes est"},
        {TR_ADVISOR_AVERAGE_TAX,                        "Le revenu fiscal moyen par résidence est"},
        {TR_ADVISOR_AVERAGE_AGE,                        "L'âge moyen de votre population est"},
        {TR_ADVISOR_PERCENT_IN_WORKFORCE,               "Pourcentage de votre population active est"},
        {TR_ADVISOR_BIRTHS_LAST_YEAR,                   "Naissances l'an dernier :"},
        {TR_ADVISOR_DEATHS_LAST_YEAR,                   "Morts l'an dernier :"},
        {TR_ADVISOR_TOTAL_POPULATION,                   "résidents total"}
};

void translation_french(const translation_string **strings, int *num_strings) {
    *strings = all_strings;
    *num_strings = sizeof(all_strings) / sizeof(translation_string);
}

