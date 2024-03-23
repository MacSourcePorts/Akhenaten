#pragma once

#include "core/buffer.h"
#include "grid/point.h"

/**
 * @file
 * Grid to store bridge/animation sprites.
 * For the lack of better naming. This grid stores:
 * 1) for bridges: which bridge part is where
 * 2) for buildings: which offset in the animation cycle is currently shown
 */

int map_sprite_animation_at(int grid_offset);
void map_sprite_animation_set(int grid_offset, int value);
inline void map_sprite_animation_set(tile2i tile, int value) { map_sprite_animation_set(tile.grid_offset(), value); }

void map_sprite_clear_tile(int grid_offset);
void map_sprite_clear();

void map_sprite_backup();
void map_sprite_restore();
