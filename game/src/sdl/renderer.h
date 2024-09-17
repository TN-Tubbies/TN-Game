#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static SDL_Renderer *renderer;

SDL_Renderer *Init_Renderer(void);
SDL_Renderer *Get_Renderer(void);
void Destroy_Renderer(SDL_Renderer *renderer);

#endif