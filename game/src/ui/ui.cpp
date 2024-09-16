#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "ui.h"
#include "../defs.h"

HUD *Init_HUD(TTF_Font *jersey, SDL_Texture *modernUI, SDL_Renderer *renderer) {
    HUD *hud = (HUD *)malloc(sizeof(HUD));
    SDL_Texture *bg = IMG_LoadTexture(renderer, "game/assets/images/ui/faded_bg.png");
    if (bg == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in ui_init, bg load: %s", SDL_GetError());
        exit(-1);
    }
    hud->bg = bg;
    return hud;
}

void Render_HUD(SDL_Renderer *renderer, HUD *hud){
    SDL_Rect bgRect = {0, HEIGHT-128, 512, 128};
    SDL_RenderCopy(renderer, hud->bg, NULL, &bgRect);
}

void Destroy_HUD(HUD *hud) {
    SDL_DestroyTexture(hud->bg);
    free(hud);
}