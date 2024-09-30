#include "battle_render.hpp"
#include <iostream>

void RenderBattle(Battle_System *battle)
{
    SDL_RenderClear(Get_Renderer());
    int x = 0;
    for (unsigned int i = 0; i < battle->playableCharacters->size(); i++)
    {
        battle->playableCharacters->at(i)->RenderHud(x, HEIGHT - battle->playableCharacters->at(i)->GetHudHeight());
        std::cout << "Rendered character n°" << i << " : "<< battle->playableCharacters->at(i)->GetName() << std::endl;
        x += 10 + battle->playableCharacters[i].at(i)->GetHudWidth();
    }
    x = WIDTH;
    for (unsigned int i = 0; i < battle->enemyCharacters->size(); i++)
    {
        battle->enemyCharacters[i].at(i)->RenderHud(x - battle->enemyCharacters->at(i)->GetHudWidth(), 0);
        std::cout << "Rendered character n°" << i << " : "<< battle->enemyCharacters->at(i)->GetName() << std::endl;
        x -= 10 + battle->enemyCharacters->at(i)->GetHudWidth();
    }

    if (battle->currentPriorityList->size > 0)
    {
        BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);
        currentCharacter->RenderButtons();
    } 
    else 
    {
        std::cout << "Priority list is empty" << std::endl;
    }    
}