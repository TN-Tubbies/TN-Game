#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <vector>

#include "defs.hpp"
#include "static/delta_time.hpp"
#include "static/renderer.hpp"
#include "static/ttf.hpp"

#include "tbc/characters/cicero.hpp"
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
    InitDeltaTime(SDL_GetTicks64());

    MainMenu *main_menu = new MainMenu();

    int player_x = 0;
    int player_y = 0;
    int player_speed = 7; // In pixels per frame
    std::string player_sprite_path = "game/assets/images/sprites/Conference_woman_32x32.bmp";
    Player *player = new Player(player_x, player_y, player_speed, player_sprite_path, SPRITE_SHEET_MAIN_CHARACTER);
    World *hub_world = new World("game/data/worlds/hub.json", player);
    World *current_world = hub_world;
    player->TeleportTo(DEFAULT_POSITION_X, DEFAULT_POSITION_Y);
    std::cout << "Player at " << player->GetXTile() << ", " << player->GetYTile() << std::endl;

    // FIXME: Temporary :
    std::vector<BattleCharacter *> *playableCharacters = new std::vector<BattleCharacter *>();
    ZerachielUnit *zerachiel = new ZerachielUnit(1);
    CiceroUnit *cicero = new CiceroUnit(1);
    playableCharacters->push_back(zerachiel);
    playableCharacters->push_back(cicero);

    std::vector<BattleCharacter *> *enemyCharacters = new std::vector<BattleCharacter *>();
    LivyaUnit *livya = new LivyaUnit(0);
    enemyCharacters->push_back(livya);
    Battle_System *battle = StartBattle(playableCharacters, enemyCharacters, "game/assets/images/maps/entrance/full_img.png", 10);

    //  End of fix
    OrganizeSpritesCoordinates(battle);

    SDL_Event event;
    bool running = true;
    DisplayState displayState = DISPLAY_STATE_MENU;

    while (running)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                continue;
            case SDL_KEYUP:
                switch (displayState)
                {
                case BATTLE:
                    BattleHandleKeyUp(battle, event, &displayState);
                    break;
                case DISPLAY_STATE_MENU:
                    main_menu->HandleKeyUp(event, &displayState);
                    break;
                case MAP:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        displayState = DISPLAY_STATE_MENU;
                    }
                    else
                    {
                        current_world->HandleKeyUp(event);
                    }
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYDOWN:
                switch (displayState)
                {
                case MAP:
                    if (event.key.keysym.sym != SDLK_ESCAPE)
                    {
                        current_world->HandleKeyDown(event);
                    }
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                switch (displayState)
                {
                case BATTLE:
                    BattleHandleMouseHover(battle, event);
                    break;
                case DISPLAY_STATE_MENU:
                    main_menu->HandleMouseHover();
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (displayState)
                {
                case BATTLE:
                    BattleHandleMouseClick(battle, event);
                    break;
                case DISPLAY_STATE_MENU:
                    main_menu->HandleMouseClick(&displayState);
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (displayState)
                {
                default:
                    break;
                }
                break;
            }
        }
        //// States update ////
        switch (displayState)
        {
        case QUIT:
            running = 0;
            break;
        case BATTLE:
            RunBattleManager(battle);
        default:
            break;
        }
        if (current_world->GetPlayer()->GetIsWalking())
        {
            current_world->GetPlayer()->Move();
        }

        //// Rendering ////
        SDL_SetRenderDrawColor(Get_Renderer(), 0, 0, 0, 255);
        SDL_RenderClear(Get_Renderer());
        switch (displayState)
        {
        case DISPLAY_STATE_MENU:
            main_menu->Render();
            break;
        case MAP:
            player->GetCurrentMap()->Render();
            player->Render();
            break;
        case BATTLE:
            RenderBattle(battle);
            break;
        default:
            break;
        }
        SDL_RenderPresent(Get_Renderer());

        //// Update Delta ////
        SetDeltaTime(SDL_GetTicks64());
    }

    // SDL_DestroyTexture(modernUI);
    Destroy_TTF();
    Destroy_Renderer();
    delete zerachiel;
    delete livya;
    delete hub_world;
    delete player;
    delete main_menu;
    DestroyBattle(battle);
    exit(0);
}
