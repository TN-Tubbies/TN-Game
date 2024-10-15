#ifndef DELTA_TIME_HPP
#define DELTA_TIME_HPP

#include <SDL2/SDL.h>

void InitDeltaTime(Uint64 delta);
void SetDeltaTime(Uint64 delta);
Uint64 GetDeltaTime();

#endif