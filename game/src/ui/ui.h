#ifndef UI_H
#define UI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

typedef struct HUD {
    SDL_Texture *bg;
} HUD;

HUD *Init_HUD(TTF_Font *jersey, SDL_Texture *modernUI, SDL_Renderer *renderer);

void Render_HUD(SDL_Renderer *renderer, HUD *hud);

void Destroy_HUD(HUD *hud);

#endif // UI_H