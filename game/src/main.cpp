#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "ui_init.h"
#include "defs.h"

int main(void) {
    SDL_Renderer *renderer = Init_SDL();
    TTF_Font *jersey = Init_TTF();
    Init_IMG();
    Init_MIX();


}

