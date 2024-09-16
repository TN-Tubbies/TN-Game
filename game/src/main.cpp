#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "ui/ui_init.h"
#include "ui/ui.h"
#include "defs.h"

int main(void)
{
    SDL_Renderer *renderer = Init_SDL();
    TTF_Font *jersey = Init_TTF();
    Init_IMG();
    Init_MIX();

    SDL_Texture *modernUI = ModernUILoad(renderer);

    //FIXME: Temporary HUD init (should be done when loading a battle) :
    HUD *hud = Init_HUD(jersey, modernUI, renderer);
    // End of fix

    SDL_Event event;
    int running = 1;

    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = 0;
                continue;
            }
        }
        //// States update ////

        //// Rendering ////
        // FIXME: Temporary background :
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // End of fix

        Render_HUD(renderer, hud);

        SDL_RenderPresent(renderer);
    }

    Destroy_HUD(hud);
    SDL_DestroyTexture(modernUI);
    TTF_CloseFont(jersey);
    SDL_DestroyRenderer(renderer);
}
