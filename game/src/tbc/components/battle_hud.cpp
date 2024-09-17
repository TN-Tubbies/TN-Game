#include "battle_hud.h"

extern SDL_Renderer *renderer;
extern TTF_Font *jersey;

HUD *Init_HUD(std::string bg_path, std::string char_name, bool isFriendly)
{
    HUD *hud = (HUD *)malloc(sizeof(HUD));

    SDL_Texture *bg = IMG_LoadTexture(renderer, bg_path.c_str());
    if (bg == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in ui_init, bg load: %s", SDL_GetError());
        exit(-1);
    }
    hud->bg = bg;

    SDL_Surface *name_surf;
    if (isFriendly) 
    {
        name_surf = TTF_RenderUTF8_Solid(jersey, char_name.c_str(), (SDL_Color){255, 255, 255, 255});
    } 
    else 
    {
        name_surf = TTF_RenderUTF8_Solid(jersey, char_name.c_str(), (SDL_Color){255, 0, 0, 255});
    }
    hud->name_h = name_surf->h;
    hud->name_w = name_surf->w;
    hud->name_disp = SDL_CreateTextureFromSurface(renderer, name_surf);
    SDL_FreeSurface(name_surf);

    return hud;
}