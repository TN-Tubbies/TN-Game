#include "battle_ui.hpp"

BattleButton::BattleButton(std::string logo_path, int x2, int y2, SDL_KeyCode key)
{   
    this->img_texture = IMG_LoadTexture(Get_Renderer(), logo_path.c_str());
    if (this->img_texture == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", logo_path.c_str());
    }
    this->button_width = 80;
    this->button_height = 80;
    this->x = x2- button_width / 2;
    this->y = y2 - button_width / 2;
    this->img_x = x2 - button_width;
    this->img_y = y2 - button_height;
    this->key = key;
    SDL_Surface *key_surf = TTF_RenderUTF8_Blended(Get_Roboto(16), SDL_GetKeyName(key), {255, 255, 255});
    if (key_surf == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to render text: %s", SDL_GetError());
    }
    this->key_texture = SDL_CreateTextureFromSurface(Get_Renderer(), key_surf);
    if (this->key_texture == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture: %s", SDL_GetError());
    }
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
    SDL_DestroyTexture(this->img_texture);
    SDL_DestroyTexture(this->key_texture);
}

void BattleButton::Render()
{
    filledCircleRGBA(Get_Renderer(), x, y, (button_width+10) / 2, 0, 0, 0, 255);
    //ATTENTION : Les marges sont hardcodées (10 de chaque coté, c'est lié aux images)
    SDL_Rect img_rect = {img_x-25, img_y-25, this->button_width+50, this->button_height+50};
    SDL_RenderCopy(Get_Renderer(), this->img_texture, NULL, &img_rect);
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