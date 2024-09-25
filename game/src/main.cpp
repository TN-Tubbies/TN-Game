#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "ui/ui_init.h"
#include "ui/main_menu.h"
#include "static/renderer.h"
#include "static/jersey.h"
#include "world/world.h"
#include "audio/audio.h"
#include "tbc/components/battle_character.h"
//FIXME: temporary :
#include "tbc/characters/zerachiel.h"

int main(void)
{
    Init_Renderer();
    Init_Jersey();
    Init_IMG();
    Init_MIX();

    MainMenu main_menu;
    
    //FIXME: Temporary party init (should be done when loading a battle) :
    std::vector<BattleCharacter> player_party;
    ZerachielUnit zerachiel(1);
    player_party.push_back(zerachiel);
    // End of fix

    // FIXME: Temporary Map init
    Map test_map("entrance");
    test_map.PlayTheme();
    // End of fix

    SDL_Event event;
    int running = 1;
    DisplayState displayState = MAIN_MENU;

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
        SDL_SetRenderDrawColor(Get_Renderer(), 0, 0, 0, 255);
        SDL_RenderClear(Get_Renderer());
        switch(displayState) {
            case MAIN_MENU:
                main_menu.Render();
                break;
            case MAP:
                test_map.Render();
                break;
            case BATTLE:
                //FIXME: Temporary battle_background rendering
                SDL_SetRenderDrawColor(Get_Renderer(), 255, 255, 255, 255);
                SDL_RenderClear(Get_Renderer());
                SDL_SetRenderDrawColor(Get_Renderer(), 0, 0, 0, 255);
                // End of fix
                zerachiel.DrawHud(0, HEIGHT - 128);
                break;
        }
        SDL_RenderPresent(Get_Renderer());
    }

    // SDL_DestroyTexture(modernUI);
    Destroy_Jersey();
    Destroy_Renderer();
    exit(0);
}
