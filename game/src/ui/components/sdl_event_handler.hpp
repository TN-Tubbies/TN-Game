#ifndef SDL_EVENT_HANDLER_HPP
#define SDL_EVENT_HANDLER_HPP

#include <SDL2/SDL.h>

#include "../../defs.hpp"
#include "../main_menu.hpp"

void HandleKeyUp(SDL_Event event, DisplayState *display_state, MainMenu *main_menu);

#endif // SDL_EVENT_HANDLER_HPP