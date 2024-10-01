#ifndef DEFS_HPP
#define DEFS_HPP

#include <SDL2/SDL.h>

#define DEBUG_MODE true

#define WIDTH 1707
#define HEIGHT 960

#define TILE_SIZE 64 // In pixels
#define PATH_TO_EMPTY_TILE "game/assets/images/empty_tile.png"

enum DisplayState
{
    MAIN_MENU,
    MAP,
    BATTLE,
    QUIT
};

#endif
