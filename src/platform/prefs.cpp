#include "platform/prefs.h"

#include "core/bstring.h"
#include "core/game_environment.h"
#include "platform/platform.h"

#include "SDL.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE* open_pref_file(const char* filename, const char* mode) {
    static_assert(SDL_VERSION_ATLEAST(2, 0, 1), "SDL version too old");
#if defined(GAME_PLATFORM_ANDROID)
    bstring512 dir_path = SDL_AndroidGetExternalStoragePath();
#else
#if defined(GAME_PLATFORM_MACOSX)
    char* tmp_path = SDL_GetPrefPath("", "Akhenaten");
#else
    char* tmp_path = SDL_GetBasePath();
#endif
    bstring512 dir_path(tmp_path);
    SDL_free(tmp_path);
#endif

    bstring512 file_path(dir_path,"/", filename); // write the full filename path into the char* buffer
    FILE* fp = fopen(file_path, mode);
    return fp;
}

const char* pref_get_gamepath() {
    static bstring1024 data_dir;
    FILE* fp = open_pref_file(get_engine_pref_path(), "r"); // open pref file for specific game
    if (fp) {
        size_t length = fread(data_dir.data(), 1, 1000, fp);
        fclose(fp);
        if (length > 0) {
            data_dir.data()[length] = 0;
            return data_dir.c_str(); // return path to game data
        }
    }
    return nullptr;
}

void pref_save_gamepath(const char* data_dir) {
    FILE* fp = open_pref_file(get_engine_pref_path(), "w");
    if (fp) {
        fwrite(data_dir, 1, strlen(data_dir), fp);
        fclose(fp);
    }
}
