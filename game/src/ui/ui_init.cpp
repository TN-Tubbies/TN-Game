#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "ui_init.h"
#include "../defs.h"

SDL_Renderer *Init_SDL(void) {
    // SDL Initialisation //
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in init: %s", SDL_GetError());
        exit(-1);
    }
    atexit(SDL_Quit);

    // Creation fenetre et attribution moteur rendu //
    SDL_Window *window;
    window = SDL_CreateWindow("SDLWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_INPUT_FOCUS);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in window init : %s", SDL_GetError());
        exit(-1);
    }
    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in renderer init : %s", SDL_GetError());
        exit(-1);
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    return renderer;
}

TTF_Font* Init_TTF(void) {
    if (TTF_Init() == -1) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in SDL_ttf initialization: %s", TTF_GetError());
        exit(-1);
    }
    atexit(TTF_Quit);

    TTF_Font* jersey = TTF_OpenFont("game/assets/fonts/Jersey/Jersey20-Regular.ttf", 32);
    if (jersey == NULL){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font: %s", TTF_GetError());
        exit(-1);
    }

    return jersey;
}

void Init_IMG(void) {
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in SDL_image initialization: %s", IMG_GetError());
        exit(-1);
    }
    atexit(IMG_Quit);
}

void Init_MIX(void) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in SDL_mixer initialization: %s", Mix_GetError());
        exit(-1);
    }
    Mix_AllocateChannels(16); // Allocation of 16 channels for mixing audio
    atexit(Mix_Quit);
}

SDL_Texture* ModernUILoad(SDL_Renderer* renderer) {
    SDL_Surface *ModernUI_full = IMG_Load("game/assets/images/modernuserinterface-win/48x48/Modern_UI_Style_2_48x48.png");
    if (ModernUI_full == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load image: %s", IMG_GetError());
        exit(-1);
    }
    SDL_Texture *texModernUI_full = SDL_CreateTextureFromSurface(renderer, ModernUI_full);
    SDL_FreeSurface(ModernUI_full);
    return texModernUI_full;
}