#ifndef UI_INIT_HPP
#define UI_INIT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

void Init_IMG(void);
void Init_MIX(void);

SDL_Texture *ModernUILoad(SDL_Renderer *renderer);

#endif // UI_INIT_HPP
