#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../defs.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void Init_Renderer(void);
SDL_Renderer *Get_Renderer(void);
void Destroy_Renderer(void);

#endif