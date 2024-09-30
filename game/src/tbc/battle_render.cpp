#include "battle_render.hpp"
#include <SDL2/SDL_render.h>

void RenderBattle(Battle_System *battle)
{
    SDL_SetRenderDrawColor(Get_Renderer(), 150, 150, 150, 255);
    SDL_RenderClear(Get_Renderer());
    int x = 0;
    for (unsigned int i = 0; i < battle->playableCharacters->size(); i++)
    {
        battle->playableCharacters->at(i)->RenderHud(x, HEIGHT - battle->playableCharacters->at(i)->GetHudHeight());
        x += 10 + battle->playableCharacters[i].at(i)->GetHudWidth();
    }
    x = WIDTH;
    for (unsigned int i = 0; i < battle->enemyCharacters->size(); i++)
    {
        battle->enemyCharacters[i].at(i)->RenderHud(x - battle->enemyCharacters->at(i)->GetHudWidth(), 0);
        x -= 10 + battle->enemyCharacters->at(i)->GetHudWidth();
    }

    if (battle->currentPriorityList->size > 0)
    {
        BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);
        if (currentCharacter->IsFriendly())
        {
            currentCharacter->RenderButtons();
        }
    } 
}

void BattleHandleKeyUp(Battle_System *battle, SDL_Event event, DisplayState *displayState)
{
    if (battle->currentPriorityList->size > 0)
    {
        BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);
        if (currentCharacter->IsFriendly()) {
            currentCharacter->HandleKeyUp(event, displayState);
        }
    }
}

void BattleHandleMouseHover(Battle_System *battle, SDL_Event event)
{
    if (battle->currentPriorityList->size > 0)
    {
        BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);
        if (currentCharacter->IsFriendly())
        {
            currentCharacter->HandleMouseHover(event);
        }
    }
}

void BattleHandleMouseClick(Battle_System *battle, SDL_Event event)
{
    if (battle->currentPriorityList->size > 0)
    {
        BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);
        if (currentCharacter->IsFriendly())
        {
            currentCharacter->HandleMouseClick(event);
        }
    }
}