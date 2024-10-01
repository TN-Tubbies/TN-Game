#ifndef BATTLE_UI_HPP
#define BATTLE_UI_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include <string>
#include <vector>

#include "../../static/renderer.hpp"
#include "../../static/ttf.hpp"

class BattleButton
{
    private:
        std::string text;
        SDL_Texture *img_texture;
        int button_width;
        int button_height;
        int x;
        int y;
        int img_x;
        int img_y;
        SDL_Texture *key_texture;
        int key_width;
        int key_height;
        int key_x;
        int key_y;
        int key_text_x;
        int key_text_y;
        SDL_KeyCode key;

    public:
        BattleButton(std::string logo_path, int x2, int y2, SDL_KeyCode key);
        ~BattleButton();
        
        void Render();
        void RenderHover();
        
        int GetWidth() { return this->button_width; }
        int GetHeight() { return this->button_height; }
        SDL_KeyCode GetKey() { return this->key; }
        std::string GetText() { return this->text; }
        int GetX();
        int GetY();
};

class UltimateButton : public BattleButton
{
    public:
        UltimateButton(std::string logo_path, int x2, int y2, SDL_KeyCode key) : BattleButton(logo_path, x2, y2, key) {}
        ~UltimateButton();
        void Render();

};

#endif // BATTLE_UI_HPP