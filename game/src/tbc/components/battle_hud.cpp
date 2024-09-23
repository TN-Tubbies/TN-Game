#include "battle_hud.h"

BattleHUD::BattleHUD(std::string bg_path, std::string char_name, bool isFriendly)
{
    this->bg = IMG_LoadTexture(Get_Renderer(), bg_path.c_str());
    if (this->bg == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in ui_init, bg load: %s", SDL_GetError());
        exit(-1);
    }

    SDL_Surface *name_surf;
    if (isFriendly)
    {
        name_surf = TTF_RenderUTF8_Solid(Get_Jersey(), char_name.c_str(), (SDL_Color){255, 255, 255, 255});
    } 
    else 
    {
        name_surf = TTF_RenderUTF8_Solid(Get_Jersey(), char_name.c_str(), (SDL_Color){255, 0, 0, 255});
    }
    if (name_surf == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in ui_init, name render: %s", SDL_GetError());
        exit(-1);
    }
    this->name_h = name_surf->h;
    this->name_w = name_surf->w;
    this->name_disp = SDL_CreateTextureFromSurface(Get_Renderer(), name_surf);
    SDL_FreeSurface(name_surf);
}

void BattleHUD::render(int x, int y) {
    SDL_Rect bg_rect = {x, y, 128, 128};
    SDL_RenderCopy(Get_Renderer(), bg, NULL, &bg_rect);

    SDL_Rect name_rect = {x+10, y+10, name_w, name_h};
    SDL_RenderCopy(Get_Renderer(), name_disp, NULL, &name_rect);
}

BattleHUD::~BattleHUD() {
    SDL_DestroyTexture(bg);
    SDL_DestroyTexture(name_disp);
}