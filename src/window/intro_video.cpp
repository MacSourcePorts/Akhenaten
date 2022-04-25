#include "intro_video.h"

#include "graphics/graphics.h"
#include "graphics/screen.h"
#include "graphics/video.h"
#include "graphics/window.h"
#include "sound/music.h"
#include "core/game_environment.h"

static struct {
    int width;
    int height;
    int current_video;
} data;

static const char *C3_INTRO_VIDEOS[] = {"smk/logo.smk", "smk/intro.smk", "smk/credits.smk"};
static const char *PH_INTRO_VIDEOS[] = {"BINKS/high/Intro_big.bik"};

static int start_next_video(void) {
    int videos_num = 0;
    const char **videos;
    switch (GAME_ENV) {
        case ENGINE_ENV_PHARAOH:
            videos_num = 1;
            videos = PH_INTRO_VIDEOS;
            break;
    }
    while (data.current_video < 3) {
        if (videos && video_start(C3_INTRO_VIDEOS[data.current_video++])) {
            video_size(&data.width, &data.height);
            video_init();
            return 1;
        }
    }
    return 0;
}
static int init(void) {
    data.current_video = 0;
    return start_next_video();
}
static void draw_background(void) {
    graphics_clear_screens();
}
static void draw_foreground(void) {
    video_draw((screen_width() - data.width) / 2, (screen_height() - data.height) / 2);
}
static void handle_input(const mouse *m, const hotkeys *h) {
    if (m->left.went_up || m->right.went_up || video_is_finished() || h->enter_pressed) {
        sound_music_stop();
        video_stop();
        if (!start_next_video()) {
            sound_music_play_intro();
            window_go_back();
        }
    }
}

void window_intro_video_show(void) {
    if (init()) {
        window_type window = {
                WINDOW_INTRO_VIDEO,
                draw_background,
                draw_foreground,
                handle_input
        };
        window_show(&window);
    }
}
