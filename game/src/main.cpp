#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <vector>

#include "static/renderer.hpp"
#include "static/ttf.hpp"

#include "tbc/characters/livya.hpp"
#include "ui/ui_init.hpp"
#include "ui/main_menu.hpp"

#include "world/world.hpp"

#include "audio/audio.hpp"

#include "tbc/battle_system.hpp"
#include "tbc/battle_render.hpp"

#include "tbc/all_characters.hpp"

int main(void)
{
    Init_Renderer();
    Init_TTF();
    Init_IMG();
    Init_MIX();

    MainMenu *main_menu = new MainMenu();

    //FIXME: Temporary :
    std::vector<BattleCharacter*> *playableCharacters = new std::vector<BattleCharacter*>();
    ZerachielUnit *zerachiel = new ZerachielUnit(1);
    playableCharacters->push_back(zerachiel);
    std::vector<BattleCharacter*> *enemyCharacters = new std::vector<BattleCharacter*>();
    LivyaUnit *livya = new LivyaUnit(0);
    enemyCharacters->push_back(livya);

    Battle_System *battle = StartBattle(playableCharacters, enemyCharacters,"game/assets/images/maps/entrance/full_img.png" , 10);
    
    // FIXME: Temporary Map init
    Map test_map("entrance");
    //test_map.PlayTheme();
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
                switch (displayState) 
                {
                    case BATTLE:
                        break;
                    case MAIN_MENU:
                        main_menu->HandleKeyUp(event, &displayState);
                        break;
                    case MAP:
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            displayState = MAIN_MENU;
                        }
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch (displayState) {
                    case BATTLE:
                        break;
                    case MAIN_MENU:
                        main_menu->HandleMouseHover(event);
                        break;
                    case MAP:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (displayState) {
                    case BATTLE:
                        break;
                    case MAIN_MENU:
                        main_menu->HandleMouseClick(event, &displayState);
                        break;
                    case MAP:
                        break;
                }
                break;
            }
        }
        //// States update ////
        RunBattleManager(battle);

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
            RenderBattle(battle);
            break;
        }
        SDL_RenderPresent(Get_Renderer());
    }

    // SDL_DestroyTexture(modernUI);
    Destroy_TTF();
    Destroy_Renderer();
    delete zerachiel;
    delete livya;
    delete main_menu;
    DestroyBattle(battle);
    exit(0);
}
