#include "ttf.hpp"

static std::vector<std::pair<int, TTF_Font*>> *JerseyFonts = new std::vector<std::pair<int, TTF_Font*>>();
static std::vector<std::pair<int, TTF_Font*>> *RobotoFonts = new std::vector<std::pair<int, TTF_Font*>>();

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
        TTF_OpenFont("game/assets/fonts/Jersey/Jersey20-Regular.ttf", size);
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

TTF_Font *Init_Roboto(int size)
{
    TTF_Font *roboto =
        TTF_OpenFont("game/assets/fonts/Roboto/Roboto-Regular.ttf", size);
    if (roboto == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s",
                    TTF_GetError());
        exit(-1);
  }
    return roboto;
}

TTF_Font *Get_Roboto(int size)
{
    for (std::pair<int, TTF_Font*> &font : *RobotoFonts)
    {
        if (font.first == size)
        {
            return font.second;
        }
    }
    TTF_Font *roboto = Init_Roboto(size);
    (*RobotoFonts).push_back(std::make_pair(size, roboto));
    return roboto;
}

void Destroy_TTF(void)
{
    for (std::pair<int, TTF_Font*> &font : *JerseyFonts)
    {
        TTF_CloseFont(font.second);
    }
    for (std::pair<int, TTF_Font*> &font : *RobotoFonts)
    {
        TTF_CloseFont(font.second);
    }
    delete JerseyFonts;
    delete RobotoFonts;
    JerseyFonts = NULL;
}