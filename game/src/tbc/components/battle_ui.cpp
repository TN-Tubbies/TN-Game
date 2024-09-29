#include "battle_ui.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_render.h>

BattleButton::BattleButton(std::string text, int x2, int y2, SDL_KeyCode key)
{   
    this->text = text;
    SDL_Surface *button_surf = TTF_RenderUTF8_Blended(Get_Roboto(32), text.c_str(), {255, 255, 255});
    this->texture = SDL_CreateTextureFromSurface(Get_Renderer(), button_surf);
    this->button_width = button_surf->w;
    this->button_height = button_surf->w;
    this->text_height = button_surf->h;
    this->x = x2- button_width / 2;
    this->y = y2 - button_width / 2;
    this->text_x = x2 - button_width;
    this->text_y = y2 - button_height / 2 - text_height / 2;
    SDL_FreeSurface(button_surf);
    this->key = key;
    SDL_Surface *key_surf = TTF_RenderUTF8_Blended(Get_Roboto(16), SDL_GetKeyName(key), {255, 255, 255});
    this->key_texture = SDL_CreateTextureFromSurface(Get_Renderer(), key_surf);
    this->key_width = key_surf->w;
    this->key_height = key_surf->h;
    this->key_x = x + button_width / 2.5 - key_width / 2;
    this->key_y = y - button_height / 2.5 - key_width / 2;
    this->key_text_x = x + button_width / 2.5 - key_width/1.25;
    this->key_text_y = y - button_height / 2.5 - key_width / 2 - key_height / 2;
    SDL_FreeSurface(key_surf);
}

BattleButton::~BattleButton()
{
    SDL_DestroyTexture(this->texture);
    SDL_DestroyTexture(this->key_texture);
}

void BattleButton::Render()
{
    filledCircleRGBA(Get_Renderer(), x, y, (button_width+10) / 2, 0, 0, 0, 255);
    SDL_Rect text_rect = {text_x, text_y, this->button_width, this->text_height};
    SDL_RenderCopy(Get_Renderer(), this->texture, NULL, &text_rect);
    filledCircleRGBA(Get_Renderer(), key_x, key_y, key_width + 2, 0, 0, 0, 255);
    SDL_Rect key_text_rect = {key_text_x, key_text_y, this->key_width, this->key_height};
    SDL_RenderCopy(Get_Renderer(), this->key_texture, NULL, &key_text_rect);
}

void BattleButton::RenderHover()
{
    filledCircleRGBA(Get_Renderer(), x, y, (button_width + 18) / 2, 255, 0, 0, 150);
}

int BattleButton::GetX()
{
    return (this->x - this->button_width / 2);
}

int BattleButton::GetY()
{
    return (this->y - this->button_height / 2);
}