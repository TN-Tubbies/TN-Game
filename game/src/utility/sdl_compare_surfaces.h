#ifndef SDL_COMPARE_SURFACES_H
#define SDL_COMPARE_SURFACES_H

#include <SDL2/SDL.h>

int SDL_Surfaces_equal(SDL_Surface *s1, SDL_Surface *s2);
bool AreSurfacesEqual(SDL_Surface *s1, SDL_Surface *s2);

#endif