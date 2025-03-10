#pragma once

#include <stdint.h>

typedef uint32_t color;

#define COLOR_BLACK 0xff000000
#define COLOR_BLUE 0xff0055ff
#define COLOR_RED 0xffff0000
#define COLOR_GREEN 0xff18ff18
#define COLOR_YELLOW 0xffffff18
#define COLOR_WHITE 0xffffffff

#define COLOR_LIGHT_RED 0xffff6568
#define COLOR_LIGHT_GREEN 0xff48ff48
#define COLOR_LIGHT_BLUE 0xff48a5ff

#define COLOR_SG2_TRANSPARENT 0xfff700ff
// #define COLOR_TOOLTIP_TEXT 0xff424242
#define COLOR_TOOLTIP_TEXT 0xffffe7d6
#define COLOR_TOOLTIP_SHADOW 0xff392410
#define COLOR_TOOLTIP_BORDER 0xff5A1400
#define COLOR_TOOLTIP_FILL 0xffbd7142
#define COLOR_SIDEBAR 0xffbdb592

#define COLOR_FONT_RED COLOR_RED
#define COLOR_FONT_BLUE 0xff0055ff
#define COLOR_FONT_YELLOW 0xffe7e75a
#define COLOR_FONT_ORANGE 0xffff5a08
#define COLOR_FONT_ORANGE_LIGHT 0xffffa500
#define COLOR_FONT_LIGHT_GRAY 0xffb3b3b3
#define COLOR_FONT_MEDIUM_GRAY 0xff777777
#define COLOR_FONT_DARK_RED 0xff803820
#define COLOR_FONT_SHITTY_BROWN 0xffa86050

#define COLOR_FONT_PLAIN 0xff180800

#define COLOR_INSET_LIGHT 0xffffffff
#define COLOR_INSET_DARK 0xff848484

#define COLOR_NULL 0x00000000
#define COLOR_MASK_NONE 0xffffffff
#define COLOR_MASK_RED 0xffff0818
#define COLOR_MASK_RED_30 0x30ff0818
#define COLOR_MASK_GREEN 0xff18ff18
#define COLOR_MASK_GREEN_30 0x3018ff18
#define COLOR_MASK_BLUE 0x663377ff
#define COLOR_MASK_LEGION_HIGHLIGHT 0x66ff3300

#define COLOR_MINIMAP_VIEWPORT 0xffe7e75a
#define COLOR_MINIMAP_DARK 0xff424242
#define COLOR_MINIMAP_LIGHT 0xffc6c6c6
#define COLOR_MINIMAP_SOLDIER 0xfff70000
constexpr uint32_t COLOR_MINIMAP_ANIMAL = 0xff00f700;
#define COLOR_MINIMAP_ENEMY_CENTRAL 0xff7b0000
#define COLOR_MINIMAP_ENEMY_NORTHERN 0xff1800ff
#define COLOR_MINIMAP_ENEMY_DESERT 0xff08007b
#define COLOR_MINIMAP_WOLF COLOR_BLACK

#define COLOR_MOUSE_DARK_GRAY 0xff3f3f3f
#define COLOR_MOUSE_MEDIUM_GRAY 0xff737373
#define COLOR_MOUSE_LIGHT_GRAY 0xffb3b3b3

#define ALPHA_OPAQUE 0xff000000
#define ALPHA_FONT_SEMI_TRANSPARENT 0x99000000
#define ALPHA_MASK_SEMI_TRANSPARENT 0x48ffffff
#define ALPHA_TRANSPARENT 0x00000000

#define COLOR_BITSHIFT_ALPHA 24

#define COLOR_CHANNEL_ALPHA 0xff000000
#define COLOR_CHANNEL_RED 0x00ff0000
#define COLOR_CHANNEL_GREEN 0x0000ff00
#define COLOR_CHANNEL_BLUE 0x000000ff

#define COLOR_BITSHIFT_ALPHA 24
#define COLOR_BITSHIFT_RED 16
#define COLOR_BITSHIFT_GREEN 8
#define COLOR_BITSHIFT_BLUE 0

#define COLOR_COMPONENT(c, shift) ((c >> shift) & 0xff)

#define COLOR_MIX_ALPHA(alpha_src, alpha_dst) ((alpha_src) + (((alpha_dst) * (0xff - (alpha_src))) >> 8))
#define COLOR_BLEND_CHANNEL_TO_OPAQUE(src, dst, alpha, channel)                                                        \
    (((((src) & (channel)) * (alpha) + ((dst) & (channel)) * (0xff - (alpha))) >> 8) & (channel))
#define COLOR_BLEND_CHANNEL(src, dst, alpha_src, alpha_dst, alpha_mix, channel)                                        \
    ((((((src) & (channel)) * (alpha_src) + ((((dst) & (channel)) * (0xff - (alpha_src))) >> 8) * (alpha_dst)))        \
      / (alpha_mix))                                                                                                   \
     & (channel))

#define COLOR_BLEND_ALPHA_TO_OPAQUE(src, dst, alpha)                                                                   \
    (ALPHA_OPAQUE | COLOR_BLEND_CHANNEL_TO_OPAQUE(src, dst, alpha, COLOR_CHANNEL_RED | COLOR_CHANNEL_BLUE)             \
     | COLOR_BLEND_CHANNEL_TO_OPAQUE(src, dst, alpha, COLOR_CHANNEL_GREEN))

#define COLOR_BLEND_ALPHAS(src, dst, alpha_src, alpha_dst, alpha_mix)                                                  \
    ((alpha_mix) << COLOR_BITSHIFT_ALPHA                                                                               \
     | COLOR_BLEND_CHANNEL(src, dst, alpha_src, alpha_dst, alpha_mix, COLOR_CHANNEL_RED)                               \
     | COLOR_BLEND_CHANNEL(src, dst, alpha_src, alpha_dst, alpha_mix, COLOR_CHANNEL_GREEN)                             \
     | COLOR_BLEND_CHANNEL(src, dst, alpha_src, alpha_dst, alpha_mix, COLOR_CHANNEL_BLUE))
