#include "main_menu.hpp"

MenuButton::MenuButton(std::string text)
{
    SDL_Surface *button_surf = TTF_RenderUTF8_Solid(Get_Jersey(), text.c_str(), {255, 255, 255});
    this->texture = SDL_CreateTextureFromSurface(Get_Renderer(), button_surf);
    this->button_width = button_surf->w;
    this->button_height = button_surf->h;
    SDL_FreeSurface(button_surf);
}

MenuButton::MenuButton(MenuButton &&other)
{
    this->texture = other.texture;
    this->button_width = other.button_width;
    this->button_height = other.button_height;
    other.texture = NULL;
}

MenuButton::~MenuButton()
{
    if (this->texture)
    {
        SDL_DestroyTexture(this->texture);
    }
}

void MenuButton::Render(int x, int y)
{
    SDL_Rect button_rect = {x, y, this->button_width, this->button_height};
    SDL_RenderCopy(Get_Renderer(), this->texture, NULL, &button_rect);
}

void MenuButton::RenderHover(int x, int y)
{
    SDL_Rect button_rect = {x, y, this->button_width, this->button_height};
    roundedBoxColor(Get_Renderer(), x - 5, y - 5, x + this->button_width + 5, y + this->button_height + 5, 8, 0xFF0000FF);
}

MainMenu::MainMenu()
{
    SDL_Surface *title_surf = TTF_RenderUTF8_Solid(Get_Jersey(), "TN-Game", {255, 255, 255});
    this->title = SDL_CreateTextureFromSurface(Get_Renderer(), title_surf);
    this->title_width = title_surf->w;
    this->title_height = title_surf->h;
    SDL_FreeSurface(title_surf);

    this->buttons.push_back(MenuButton("Map"));
    this->buttons.push_back(MenuButton("Battle"));

    this->current_selection = 0;
}

MainMenu::~MainMenu()
{
    SDL_DestroyTexture(this->title);
    for (MenuButton &button : this->buttons)
    {
        button.~MenuButton();
    }
}

void MainMenu::Render()
{
    SDL_Rect title_rect = {WIDTH / 2 - (this->title_width / 2) * 2, HEIGHT / 5, (this->title_width) * 2, (this->title_height) * 2};
    SDL_RenderCopy(Get_Renderer(), this->title, NULL, &title_rect);

    int y = 2*HEIGHT / 5;
    for (MenuButton &button : this->buttons)
    {
        if (&buttons.at(this->current_selection) == &button)
        {
            button.RenderHover(WIDTH / 2 - (button.GetWidth() / 2), y);
        }
        button.Render(WIDTH / 2 - (button.GetWidth() / 2), y);
        y += button.GetHeight() + 25;
    }
}