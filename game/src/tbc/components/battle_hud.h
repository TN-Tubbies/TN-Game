#ifndef BATTLE_HUD_H
#define BATTLE_HUD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "../../static/renderer.h"
#include "../../static/jersey.h"

typedef struct HUD {
    SDL_Texture *bg;
    SDL_Texture *name_disp;
    int name_w;
    int name_h;
} HUD;

HUD *Init_HUD(std::string bg_path, std::string char_name, bool isFriendly);

void Render_HUD(HUD *hud, int x, int y);

void Destroy_HUD(HUD *hud);

#endif // BATTLE_HUD_H