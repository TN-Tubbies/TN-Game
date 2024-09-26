#include "ui_init.hpp"

void Init_IMG(void)
{
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in SDL_image initialization: %s", IMG_GetError());
        exit(-1);
    }
    atexit(IMG_Quit);
}

void Init_MIX(void)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in SDL_mixer initialization: %s", Mix_GetError());
        exit(-1);
    }
    Mix_AllocateChannels(16); // Allocation of 16 channels for mixing audio
    atexit(Mix_Quit);
}

SDL_Texture *ModernUILoad(SDL_Renderer *renderer)
{
    SDL_Surface *ModernUI_full = IMG_Load("game/assets/images/modernuserinterface-win/48x48/Modern_UI_Style_2_48x48.png");
    if (ModernUI_full == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", IMG_GetError());
        exit(-1);
    }
    SDL_Texture *texModernUI_full = SDL_CreateTextureFromSurface(renderer, ModernUI_full);
    SDL_FreeSurface(ModernUI_full);
    return texModernUI_full;
}