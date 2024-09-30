#include "battle_render.hpp"

void RenderBattle(Battle_System *battle)
{
    SDL_RenderClear(Get_Renderer());
    int x = 0;
    for (unsigned int i = 0; i < battle->playableCharacters.size(); i++)
    {
        battle->playableCharacters[i]->RenderHud(x, HEIGHT - battle->playableCharacters[i]->GetHudHeight());
        x += 10 + battle->playableCharacters[i]->GetHudWidth();
    }
    x = WIDTH;
    for (unsigned int i = 0; i < battle->enemyCharacters.size(); i++)
    {
        battle->enemyCharacters[i]->RenderHud(x - battle->enemyCharacters[i]->GetHudWidth(), 0);
        x -= 10 + battle->enemyCharacters[i]->GetHudWidth();
    }

    BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);
    currentCharacter->RenderButtons();
}