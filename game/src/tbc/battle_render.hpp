#ifndef BATTLE_RENDER_HPP
#define BATTLE_RENDER_HPP

#include "../static/renderer.hpp"
#include "../static/ttf.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "battle_system.hpp"

void RenderBattle(Battle_System *battle);

#endif // BATTLE_RENDER_HPP