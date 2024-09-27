#include "sdl_event_handler.hpp"

void HandleKeyUp(SDL_Event event, DisplayState *display_state, MainMenu *main_menu)
{
    switch (*display_state)
    {
    case MAIN_MENU:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            if (main_menu->GetCurrentSelection() > 0)
            {
                main_menu->SetCurrentSelection(main_menu->GetCurrentSelection() - 1);
            }
            break;
        case SDLK_DOWN:
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