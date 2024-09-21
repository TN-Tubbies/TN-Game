#include "jersey.h"

static TTF_Font* Jersey = NULL;

void Init_Jersey(void) {
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

    Jersey = jersey;
}
TTF_Font* Get_Jersey(void){ return Jersey;}
void Destroy_Jersey(void) {
    TTF_CloseFont(Jersey);
}