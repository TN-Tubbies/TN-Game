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
#include "../static/ttf.hpp"

class MenuButton
{
public:
    MenuButton(std::string text);
    MenuButton(MenuButton &&);
    ~MenuButton();
    void Render();
    void RenderHover();
    int GetWidth() { return this->button_width; }
    int GetHeight() { return this->button_height; }
    int GetX() { return this->x; }
    int GetY() { return this->y; }
    void SetX(int x) { this->x = x; }
    void SetY(int y) { this->y = y; }

private:
    SDL_Texture *texture;
    int button_width;
    int button_height;
    int x;
    int y;
};

class MainMenu
{
private:
    SDL_Texture *title;
    int title_width;
    int title_height;
    std::vector<MenuButton> *buttons;
    int current_selection;
public:
    MainMenu();
    ~MainMenu();
    void Render();
    int GetCurrentSelection() { return this->current_selection; }
    void SetCurrentSelection(int selection) { this->current_selection = selection; }
    int GetButtonsQuantity() { return (*this->buttons).size(); }
    std::vector<MenuButton> *GetButtons() { return this->buttons; }
};

#endif // MAIN_MENU_HPP