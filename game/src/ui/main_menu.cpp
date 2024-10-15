#include "main_menu.hpp"

MenuButton::MenuButton(std::string text)
{
    SDL_Surface *button_surf = TTF_RenderUTF8_Blended(Get_Roboto(64), text.c_str(), {255, 255, 255});
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

void MenuButton::Render()
{
    SDL_Rect button_rect = {x, y, this->button_width, this->button_height};
    SDL_RenderCopy(Get_Renderer(), this->texture, NULL, &button_rect);
}

void MenuButton::RenderHover()
{
    roundedBoxColor(Get_Renderer(), x - 5, y - 5, x + this->button_width + 5, y + this->button_height + 5, 8, 0xFF0000FF);
}

MainMenu::MainMenu()
{
    SDL_Surface *title_surf = TTF_RenderUTF8_Solid(Get_Jersey(128), "TN-Game", {255, 255, 255});
    this->title = SDL_CreateTextureFromSurface(Get_Renderer(), title_surf);
    this->title_width = title_surf->w;
    this->title_height = title_surf->h;
    SDL_FreeSurface(title_surf);

    this->buttons = new std::vector<MenuButton>();

    (*this->buttons).push_back(MenuButton("Map"));
    (*this->buttons).push_back(MenuButton("Battle"));

    int y = 2 * HEIGHT / 5;
    for (MenuButton &button : *this->buttons)
    {
        button.SetX(WIDTH / 2 - (button.GetWidth() / 2));
        button.SetY(y);
        y += button.GetHeight() + 25;
    }

    this->current_selection = 0;
}

MainMenu::~MainMenu()
{
    SDL_DestroyTexture(this->title);
    for (MenuButton &button : *this->buttons)
    {
        button.~MenuButton();
    }
    delete this->buttons;
}

void MainMenu::Render()
{
    SDL_Rect title_rect = {WIDTH / 2 - this->title_width / 2, HEIGHT / 5, this->title_width, this->title_height};
    SDL_RenderCopy(Get_Renderer(), this->title, NULL, &title_rect);

    
    for (MenuButton &button : *this->buttons)
    {
        if (&(*buttons).at(this->current_selection) == &button)
        {
            button.RenderHover();
        }
        button.Render();
    }
}

void MainMenu::HandleKeyUp(SDL_Event event, DisplayState *displayState)
{
    switch (event.key.keysym.sym) {
    case SDLK_UP:
    case SDLK_z:
    if (this->current_selection > 0) 
    {
        this->current_selection--;
    }
    break;
    case SDLK_DOWN:
    case SDLK_s:
    if (this->current_selection < this->buttons->size() - 1) 
    {
        this->current_selection++;
    } 
    break;
    case SDLK_RETURN:
    switch (this->current_selection) {
    case 0:
        *displayState = MAP;
        break;
    case 1:
        *displayState = BATTLE;
        break;
    }
    break;
    case SDLK_ESCAPE:
        *displayState = QUIT;
        break;
    }
}

bool isMouseHovering(int mouse_x, int mouse_y, MenuButton *button) {
  return (mouse_x >= (*button).GetX() &&
          mouse_x <= (*button).GetX() + (*button).GetWidth() &&
          mouse_y >= (*button).GetY() &&
          mouse_y <= (*button).GetY() + (*button).GetHeight());
}

void MainMenu::HandleMouseHover(SDL_Event event)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (MenuButton &button : *this->buttons)
    {
        if (isMouseHovering(mouse_x, mouse_y, &button))
        {
            this->current_selection = &button - &(*buttons).at(0);
        }
    }
}

void MainMenu::HandleMouseClick(SDL_Event event, DisplayState *displayState)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (MenuButton &button : *this->buttons)
    {
        if (isMouseHovering(mouse_x, mouse_y, &button))
        {
            switch (this->current_selection)
            {
            case 0:
                *displayState = MAP;
                break;
            case 1:
                *displayState = BATTLE;
                break;
            }
        }
    }
}