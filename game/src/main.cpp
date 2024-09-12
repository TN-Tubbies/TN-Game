#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "ui/ui_init.h"
#include "defs.h"

int main(void) {
    SDL_Renderer *renderer = Init_SDL();
    TTF_Font *jersey = Init_TTF();
    Init_IMG();
    Init_MIX();

    SDL_Texture *modernUI = ModernUILoad(renderer);

    SDL_Event event;
    int running = 1;

    while (running) {
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    continue;
            }
        }
        //States update

        // Rendering
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(modernUI);
    TTF_CloseFont(jersey);
    SDL_DestroyRenderer(renderer);
}

