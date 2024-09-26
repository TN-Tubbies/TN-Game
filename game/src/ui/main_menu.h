#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <vector>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../static/renderer.h"
#include "../static/jersey.h"

class MenuButton {
    public:
        MenuButton(std::string text);
        MenuButton(MenuButton&&);
        ~MenuButton();
        void Render(int x, int y);
        int GetWidth() { return this->button_width; }
        int GetHeight() { return this->button_height; }
        SDL_Texture *GetTexture() { return this->button; }
    private:
        SDL_Texture *button;
        int button_width;
        int button_height;
};

class MainMenu {
    public:
        MainMenu();
        ~MainMenu();
        void Render();
        int GetCurrentSelection() { return this->current_selection; }
        void SetCurrentSelection(int selection) { this->current_selection = selection; }
    private:
        SDL_Texture *title;
        int title_width;
        int title_height;
        std::vector<MenuButton> buttons;
        int current_selection;
};

#endif