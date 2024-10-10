#ifndef DEFS_HPP
#define DEFS_HPP

#include <SDL2/SDL.h>

#define DEBUG_MODE true

#define WIDTH 1707
#define HEIGHT 960

#define TILE_SIZE 64 // In pixels
#define PATH_TO_EMPTY_TILE "game/assets/images/empty_tile.png"

#define DEFAULT_POSITION_X 5 * TILE_SIZE
#define DEFAULT_POSITION_Y 5 * TILE_SIZE

enum DisplayState
{
    DISPLAY_STATE_MENU,
    MAP,
    BATTLE
};

enum SpriteDirection
{
    SpriteDirection_Left,
    SpriteDirection_Right,
    SpriteDirection_Up,
    SpriteDirection_Down
};

enum SpriteSheetTypes
{
    SPRITE_SHEET_MAIN_CHARACTER
};

#endif
