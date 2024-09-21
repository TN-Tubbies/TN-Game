#include "battle_hud.h"

HUD *Init_HUD(std::string bg_path, std::string char_name, bool isFriendly)
{
    HUD *hud = (HUD *)malloc(sizeof(HUD));

    SDL_Texture *bg = IMG_LoadTexture(Get_Renderer(), bg_path.c_str());
    if (bg == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in ui_init, bg load: %s", SDL_GetError());
        exit(-1);
    }
    hud->bg = bg;

    SDL_Surface *name_surf;
    if (isFriendly)
    {
        name_surf = TTF_RenderUTF8_Solid(Get_Jersey(), char_name.c_str(), (SDL_Color){255, 255, 255, 255});
    } 
    else 
    {
        name_surf = TTF_RenderUTF8_Solid(Get_Jersey(), char_name.c_str(), (SDL_Color){255, 0, 0, 255});
    }
    hud->name_h = name_surf->h;
    hud->name_w = name_surf->w;
    hud->name_disp = SDL_CreateTextureFromSurface(Get_Renderer(), name_surf);
    SDL_FreeSurface(name_surf);

    return hud;
}

void Render_HUD(HUD *hud, int x, int y) {
    SDL_Rect bg_rect = {x, y, 128, 128};
    SDL_RenderCopy(Get_Renderer(), hud->bg, NULL, &bg_rect);

    SDL_Rect name_rect = {x+10, y+10, hud->name_w, hud->name_h};
    SDL_RenderCopy(Get_Renderer(), hud->name_disp, NULL, &name_rect);
}

void Destroy_HUD(HUD *hud) {
    if (hud != NULL) {
        SDL_DestroyTexture(hud->bg);
        SDL_DestroyTexture(hud->name_disp);
    }
}