#ifndef JERSEY_HPP
#define JERSEY_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <vector>

void Init_TTF(void);
TTF_Font *Get_Jersey(int size);
void Destroy_Jersey(void);

#endif