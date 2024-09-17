#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "ui/ui_init.h"
#include "defs.h"
#include "tbc/components/battle_character.h"
//FIXME: temporary :
#include "tbc/characters/zerachiel.h"

extern TTF_Font *jersey;
extern SDL_Renderer *renderer;

int main(void)
{
    renderer = Init_SDL();
    jersey = Init_TTF();
    Init_IMG();
    Init_MIX();

    SDL_Texture *modernUI = ModernUILoad(renderer);
    
    //FIXME: Temporary party & HUD init (should be done when loading a battle) :
    std::vector<BattleCharacter> player_party;
    ZerachielUnit zerachiel(1);
    player_party.push_back(zerachiel);
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
        zerachiel.DrawHUD(0, 0);
        // End of fix
        

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(modernUI);
    TTF_CloseFont(jersey);
    SDL_DestroyRenderer(renderer);
}
