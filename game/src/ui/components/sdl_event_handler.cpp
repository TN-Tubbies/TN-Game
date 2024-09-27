#include "sdl_event_handler.hpp"

void HandleKeyUp(SDL_Event event, DisplayState *display_state, MainMenu *main_menu)
{
    switch (*display_state)
    {
    case MAIN_MENU:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_z:
            if (main_menu->GetCurrentSelection() > 0)
            {
                main_menu->SetCurrentSelection(main_menu->GetCurrentSelection() - 1);
            }
            break;
        case SDLK_DOWN:
        case SDLK_s:
            if (main_menu->GetCurrentSelection() < main_menu->GetButtonsQuantity() - 1)
            {
                main_menu->SetCurrentSelection(main_menu->GetCurrentSelection() + 1);
            }
            break;
        case SDLK_RETURN:
            switch (main_menu->GetCurrentSelection())
            {
            case 0:
                *display_state = MAP;
                break;
            case 1:
                *display_state = BATTLE;
                break;
            }
            break;
        case SDLK_ESCAPE:
            exit(0);
        }
        break;
    case MAP:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *display_state = MAIN_MENU;
            break;
        }
    case BATTLE:    
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
            *display_state = MAIN_MENU;
            break;
        }
    }
}

bool isMouseHovering(int mouse_x, int mouse_y, MenuButton *button)
{
    return (mouse_x >= (*button).GetX() && mouse_x <= (*button).GetX() + (*button).GetWidth() && mouse_y >= (*button).GetY() && mouse_y <= (*button).GetY() + (*button).GetHeight());
}

int indexOfButtonHovered(int mouse_x, int mouse_y, MainMenu *main_menu)
{
    int i = 0;
    for (MenuButton &button : *main_menu->GetButtons())
    {
        if (isMouseHovering(mouse_x, mouse_y, &button))
        {
            return i;
        }
        i++;
    }
    return -1;
}

void HandleMouseHover(SDL_Event event, DisplayState *display_state, MainMenu *main_menu)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (MenuButton &button : *main_menu->GetButtons())
    {
        if (isMouseHovering(mouse_x, mouse_y, &button))
        {
            main_menu->SetCurrentSelection(indexOfButtonHovered(mouse_x, mouse_y, main_menu));
        }
    }
}

void HandleMouseClick(SDL_Event event, DisplayState *display_state, MainMenu *main_menu)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    for (MenuButton &button : *main_menu->GetButtons())
    {
        if (isMouseHovering(mouse_x, mouse_y, &button))
        {
            switch (main_menu->GetCurrentSelection())
            {
            case 0:
                *display_state = MAP;
                break;
            case 1:
                *display_state = BATTLE;
                break;
            }
        }
    }
}