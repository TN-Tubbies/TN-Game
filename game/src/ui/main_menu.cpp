#include "main_menu.h"

MainMenu::MainMenu() {
    SDL_Surface *title_surf = TTF_RenderUTF8_Solid(Get_Jersey(), "TN-Game", {255, 255, 255});
    this->title = SDL_CreateTextureFromSurface(Get_Renderer(), title_surf);
    this->title_width = title_surf->w;
    this->title_height = title_surf->h;
    SDL_FreeSurface(title_surf);

    SDL_Surface *map_txt_surf = TTF_RenderUTF8_Solid(Get_Jersey(), "Map", {255, 255, 255});
    this->map_txt = SDL_CreateTextureFromSurface(Get_Renderer(), map_txt_surf);
    this->map_txt_width = map_txt_surf->w;
    this->map_txt_height = map_txt_surf->h;
    SDL_FreeSurface(map_txt_surf);

    SDL_Surface *battle_txt_surf = TTF_RenderUTF8_Solid(Get_Jersey(), "Battle", {255, 255, 255});
    this->battle_txt = SDL_CreateTextureFromSurface(Get_Renderer(), battle_txt_surf);
    this->battle_txt_width = battle_txt_surf->w;
    this->battle_txt_height = battle_txt_surf->h;
    SDL_FreeSurface(battle_txt_surf);
}

MainMenu::~MainMenu() {
    SDL_DestroyTexture(this->title);
    SDL_DestroyTexture(this->map_txt);
    SDL_DestroyTexture(this->battle_txt);
}

void MainMenu::Render() {
    SDL_Rect title_rect = {WIDTH / 2 - (this->title_width / 2)*2, HEIGHT / 5, (this->title_width)*2, (this->title_height)*2};
    SDL_RenderCopy(Get_Renderer(), this->title, NULL, &title_rect);

    SDL_Rect map_txt_rect = {WIDTH / 2 - this->map_txt_width / 2, HEIGHT / 2, this->map_txt_width, this->map_txt_height};
    SDL_RenderCopy(Get_Renderer(), this->map_txt, NULL, &map_txt_rect);

    SDL_Rect battle_txt_rect = {WIDTH / 2 - this->battle_txt_width / 2, HEIGHT / 2 + this->map_txt_height, this->battle_txt_width, this->battle_txt_height};
    SDL_RenderCopy(Get_Renderer(), this->battle_txt, NULL, &battle_txt_rect);
}