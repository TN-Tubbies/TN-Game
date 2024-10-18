#ifndef BATTLE_RENDER_HPP
#define BATTLE_RENDER_HPP

#include "../static/renderer.hpp"
#include "../static/ttf.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "battle_system.hpp"
#include "battle_enumerators.hpp"

void RenderBattle(Battle_System *battle);

void BattleHandleKeyUp(Battle_System *battle, SDL_Event event, DisplayState *displayState);
void BattleHandleMouseHover(Battle_System *battle, SDL_Event event);
void BattleHandleMouseClick(Battle_System *battle, SDL_Event event);

void OrganizeSpritesCoordinates(Battle_System *battle);

void SetTargets(Battle_System *battle);

#endif // BATTLE_RENDER_HPP