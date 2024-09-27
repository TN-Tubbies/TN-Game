#include "ttf.hpp"

std::vector<std::pair<int, TTF_Font*>> *JerseyFonts = new std::vector<std::pair<int, TTF_Font*>>();

void Init_TTF(void)
{
    if (TTF_Init() == -1)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in SDL_ttf initialization: %s", TTF_GetError());
        exit(-1);
    }
    atexit(TTF_Quit);
}


TTF_Font *Init_Jersey(int size)
{
    TTF_Font *jersey =
        TTF_OpenFont("game/assets/fonts/Jersey/Jersey20-Regular.ttf", 64);
    if (jersey == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s",
                    TTF_GetError());
        exit(-1);
  }
    return jersey;
}

TTF_Font *Get_Jersey(int size)
{
    for (std::pair<int, TTF_Font*> &font : *JerseyFonts)
    {
        if (font.first == size)
        {
            return font.second;
        }
    }
    TTF_Font *jersey = Init_Jersey(size);
    (*JerseyFonts).push_back(std::make_pair(size, jersey));
    return jersey;
}


void Destroy_Jersey(void)
{
    for (std::pair<int, TTF_Font*> &font : *JerseyFonts)
    {
        TTF_CloseFont(font.second);
    }
    delete JerseyFonts;
    JerseyFonts = NULL;
}