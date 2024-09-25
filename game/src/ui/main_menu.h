#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../static/renderer.h"
#include "../static/jersey.h"

class MainMenu {
    public:
        MainMenu();
        ~MainMenu();
        void Render();
    private:
        SDL_Texture *title;
        int title_width;
        int title_height;
        SDL_Texture *map_txt;
        int map_txt_width;
        int map_txt_height;
        SDL_Texture *battle_txt;
        int battle_txt_width;
        int battle_txt_height;
};

#endif