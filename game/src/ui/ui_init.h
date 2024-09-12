#ifndef SDLINIT
#define SDLINIT
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer *Init_SDL(void);
TTF_Font* Init_TTF(void);
void Init_IMG(void);
void Init_MIX(void);

SDL_Texture *ModernUILoad(SDL_Renderer *renderer);

#endif
