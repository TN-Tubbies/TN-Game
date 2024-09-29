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
        SDL_Texture *texture;
        int button_width;
        int button_height;
        int text_height;
        int x;
        int y;
        int text_x;
        int text_y;
        SDL_Texture *key_texture;
        int key_width;
        int key_height;
        int key_x;
        int key_y;
        int key_text_x;
        int key_text_y;
        SDL_KeyCode key;

    public:
        BattleButton(std::string text, int x2, int y2, SDL_KeyCode key);
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

#endif // BATTLE_UI_HPP