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

class BattleMoveActive;

class BattleButton
{
    protected:
        BattleMoveActive *move;
        SDL_Texture *img_texture;
        SDL_Texture *bg_texture;
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
        BattleButton(std::string logo_path, std::string bg_path, int x2, int y2, SDL_KeyCode key, BattleMoveActive *move);
        ~BattleButton();
        
        virtual void Render();
        void RenderHover();
        
        int GetWidth() { return this->button_width; }
        int GetHeight() { return this->button_height; }
        SDL_KeyCode GetKey() { return this->key; }
        BattleMoveActive *GetMove() { return this->move; }
        int GetX();
        int GetY();
};

class UltimateButton : public BattleButton
{
    public:
        UltimateButton(std::string logo_path, std::string bg_path, int x2, int y2, SDL_KeyCode key, BattleMoveActive *move) : BattleButton(logo_path, bg_path, x2, y2, key, move) {}
        ~UltimateButton();
        void Render(int charge);

};

#endif // BATTLE_UI_HPP