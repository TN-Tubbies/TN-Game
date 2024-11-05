#ifndef OPTIMAL_TEXT_CHUNK_HPP
#define OPTIMAL_TEXT_CHUNK_HPP

#include <vector>
#include <string>
#include <chrono>

#include <SDL2/SDL_ttf.h>

#include "../defs.hpp"

#define MAX_CHUNK_SIZE 5
// In letters

int SetOptimalTextChunk(int TextMaxWidth, int TextMaxHeight, TTF_Font *Font);
int GetOptimalTextChunk();

#endif