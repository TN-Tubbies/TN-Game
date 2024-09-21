#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "ui/ui_init.h"
#include "static/renderer.h"
#include "static/jersey.h"
#include "world/world.h"
#include "tbc/components/battle_character.h"
//FIXME: temporary :
#include "tbc/characters/zerachiel.h"

int main(void)
{
    Init_Renderer();
    Init_Jersey();
    Init_IMG();
    Init_MIX();

    // SDL_Texture *modernUI = ModernUILoad(Get_Renderer());
    
    //FIXME: Temporary party & HUD init (should be done when loading a battle) :
    std::vector<BattleCharacter> player_party;
    ZerachielUnit zerachiel(1);
    player_party.push_back(zerachiel);
    // End of fix

    // FIXME: Temporary Map init
    Map test_map("Test Map", 100, 100, "game/assets/images/maps/entrance");

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
        SDL_SetRenderDrawColor(Get_Renderer(), 255, 255, 255, 255);
        SDL_RenderClear(Get_Renderer());
        SDL_SetRenderDrawColor(Get_Renderer(), 0, 0, 0, 255);
        test_map.Render();
        zerachiel.DrawHUD(0, 0);
        // End of fix
        
        SDL_RenderPresent(Get_Renderer());
    }

    // SDL_DestroyTexture(modernUI);
    Destroy_Jersey();
    Destroy_Renderer();
}
