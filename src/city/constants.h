#ifndef CITY_CONSTANTS_H
#define CITY_CONSTANTS_H

enum e_advisor {
    ADVISOR_NONE = 0,
    ADVISOR_LABOR = 1,
    ADVISOR_MILITARY = 2,
    ADVISOR_IMPERIAL = 3,
    ADVISOR_RATINGS = 4,
    ADVISOR_TRADE = 5,
    ADVISOR_POPULATION = 6,
    ADVISOR_HEALTH = 7,
    ADVISOR_EDUCATION = 8,
    ADVISOR_ENTERTAINMENT = 9,
    ADVISOR_RELIGION = 10,
    ADVISOR_FINANCIAL = 11,
    ADVISOR_CHIEF = 12,
    ADVISOR_MONUMENTS = 13,
    ADVISOR_HOUSING = 19,
};

enum {
    int_NONE = 0,
    int_NO_FOOD = 1,
    int_NO_JOBS = 2,
    int_HIGH_TAXES = 3,
    int_LOW_WAGES = 4,
    int_MANY_TENTS = 5,
};

enum {
    NO_IMMIGRATION_LOW_WAGES = 0,
    NO_IMMIGRATION_NO_JOBS = 1,
    NO_IMMIGRATION_NO_FOOD = 2,
    NO_IMMIGRATION_HIGH_TAXES = 3,
    NO_IMMIGRATION_MANY_TENTS = 4,
    NO_IMMIGRATION_LOW_MOOD = 5
};

enum {
    FESTIVAL_NONE = 0,
    FESTIVAL_SMALL = 1,
    FESTIVAL_LARGE = 2,
    FESTIVAL_GRAND = 3,
    FESTIVAL_BAST_SPECIAL = 4,
};

enum e_god {
    GOD_OSIRIS = 0, // GOD_CERES = 0,
    GOD_RA = 1,     // GOD_NEPTUNE = 1,
    GOD_PTAH = 2,   // GOD_MERCURY = 2,
    GOD_SETH = 3,   // GOD_MARS = 3,
    GOD_BAST = 4,   // GOD_VENUS = 4
};

template<typename ...Args>
inline int make_gods_mask(Args... args) {
    auto gods = {args...};
    int mask = 0;
    for (const auto &g : gods) { mask |= (1 << g); }
    return mask;
}

inline bool is_god_available(int mask, e_god g) { int god_mask = (1 << g); return ((mask & god_mask) == god_mask); }

enum {
    GOD_STATUS_UNKNOWN = 0,
    GOD_STATUS_KNOWN = 1,
    GOD_STATUS_PATRON = 2
};

enum {
    TRADE_STATUS_NONE = 0,
    TRADE_STATUS_IMPORT = 1,
    TRADE_STATUS_EXPORT = 2,
    TRADE_STATUS_IMPORT_AS_NEEDED = 3,
    TRADE_STATUS_EXPORT_SURPLUS = 4,
};

#endif // CITY_CONSTANTS_H
