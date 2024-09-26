#include "main_menu.h"

MenuButton::MenuButton(std::string text) {
    std::cout << "MenuButton constructor" << std::endl;
    SDL_Surface *button_surf = TTF_RenderUTF8_Solid(Get_Jersey(), text.c_str(), {255, 255, 255});
    this->button = SDL_CreateTextureFromSurface(Get_Renderer(), button_surf);
    this->button_width = button_surf->w;
    this->button_height = button_surf->h;
    SDL_FreeSurface(button_surf);
}

MenuButton::MenuButton(MenuButton&& other) {
    std::cout << "MenuButton move constructor" << std::endl;
    this->button = other.button;
    this->button_width = other.button_width;
    this->button_height = other.button_height;
    other.button = NULL;
}

MenuButton::~MenuButton() {
    if(this->button == NULL) {
        std::cout << "this->button is NULL" << std::endl;
    } else {
        std::cout << "this->button is not NULL" << std::endl;
        SDL_DestroyTexture(this->button);
    }
    std::cout << "MenuButton destructor" << std::endl;
}

void MenuButton::Render(int x, int y) {
    SDL_Rect button_rect = {x, y, this->button_width, this->button_height};
    SDL_RenderCopy(Get_Renderer(), this->button, NULL, &button_rect);
}

MainMenu::MainMenu() {
    SDL_Surface *title_surf = TTF_RenderUTF8_Solid(Get_Jersey(), "TN-Game", {255, 255, 255});
    this->title = SDL_CreateTextureFromSurface(Get_Renderer(), title_surf);
    this->title_width = title_surf->w;
    this->title_height = title_surf->h;
    SDL_FreeSurface(title_surf);

    this->buttons.push_back(MenuButton("Map"));
    this->buttons.push_back(MenuButton("Battle"));
}

MainMenu::~MainMenu() {
    SDL_DestroyTexture(this->title);
    for (MenuButton &button : this->buttons) {
        button.~MenuButton();
    }
}

void MainMenu::Render() {
    SDL_Rect title_rect = {WIDTH / 2 - (this->title_width / 2)*2, HEIGHT / 5, (this->title_width)*2, (this->title_height)*2};
    SDL_RenderCopy(Get_Renderer(), this->title, NULL, &title_rect);

    int y = HEIGHT / 3;
    for (MenuButton &button : this->buttons) {
        if (button.GetTexture() == NULL) {
            std::cout << "button.GetTexture() is NULL" << std::endl;
        }

        button.Render(WIDTH / 2 - (button.GetWidth() / 2), y);
        y += button.GetHeight() + 10;
    }

}