#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "static/renderer.hpp"
#include "static/jersey.hpp"

#include "ui/ui_init.hpp"
#include "ui/main_menu.hpp"
#include "ui/components/sdl_event_handler.hpp"

#include "world/world.hpp"

#include "audio/audio.hpp"

#include "tbc/components/battle_character.hpp"
// FIXME: temporary :
#include "tbc/characters/zerachiel.hpp"

int main(void)
{
    Init_Renderer();
    Init_Jersey();
    Init_IMG();
    Init_MIX();

    MainMenu* main_menu = new MainMenu();

    // FIXME: Temporary party init (should be done when loading a battle) :
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
            case SDL_KEYUP:
                HandleKeyUp(event, &displayState, main_menu);
                std::cout << displayState << std::endl;
            }
        }
        //// States update ////

        //// Rendering ////
        SDL_SetRenderDrawColor(Get_Renderer(), 0, 0, 0, 255);
        SDL_RenderClear(Get_Renderer());
        switch (displayState)
        {
        case MAIN_MENU:
            main_menu->Render();
            break;
        case MAP:
            test_map.Render();
            break;
        case BATTLE:
            // FIXME: Temporary battle_background rendering
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
    delete main_menu;
    exit(0);
}
