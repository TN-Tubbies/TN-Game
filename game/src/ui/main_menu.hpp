#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <vector>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "../static/renderer.hpp"
#include "../static/jersey.hpp"

class MenuButton
{
public:
    MenuButton(std::string text);
    MenuButton(MenuButton &&);
    ~MenuButton();
    void Render(int x, int y);
    void RenderHover(int x, int y);
    int GetWidth() { return this->button_width; }
    int GetHeight() { return this->button_height; }

private:
    SDL_Texture *texture;
    int button_width;
    int button_height;
};

class MainMenu
{
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