#include "battle_render.hpp"
#include "battle_declarations.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

void RenderBattle(Battle_System *battle)
{
    SDL_SetRenderDrawColor(Get_Renderer(), 150, 150, 150, 255);
    SDL_RenderClear(Get_Renderer());
    int x = 0;
    for (unsigned int i = 0; i < battle->playableCharacters->size(); i++)
    {
        battle->playableCharacters->at(i)->RenderHud(x, HEIGHT - battle->playableCharacters->at(i)->GetHudHeight());
        x += 10 + battle->playableCharacters->at(i)->GetHudWidth();

        battle->playableCharacters->at(i)->RenderSprite();
    }
    x = WIDTH;
    for (unsigned int i = 0; i < battle->enemyCharacters->size(); i++)
    {
        battle->enemyCharacters[i].at(i)->RenderHud(x - battle->enemyCharacters->at(i)->GetHudWidth(), 0);
        x -= 10 + battle->enemyCharacters->at(i)->GetHudWidth();

        battle->enemyCharacters->at(i)->RenderSprite();
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
        std::cout << "Handling key up" << std::endl;
        BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);
        if (currentCharacter->IsFriendly()) {
            currentCharacter->HandleKeyUp(event, displayState);
            SetTargets(battle);
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
            SetTargets(battle);
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

void OrganizeSpritesCoordinates(Battle_System *battle) {
    int sprite_size = 250; 
    int spacing = 10;


    int players_x = 0;

    for (BattleCharacter *character : *battle->playableCharacters) {
        float img_ratio = (float)(character->GetSprite()->GetWidth()) / (float)(character->GetSprite()->GetHeight());
        if (img_ratio >= 1) {
            character->GetSprite()->SetHeight(sprite_size);
            character->GetSprite()->SetWidth(sprite_size * img_ratio);
        } else {
            character->GetSprite()->SetWidth(sprite_size);
            character->GetSprite()->SetHeight(sprite_size / img_ratio);
        }

        character->GetSprite()->SetX(players_x);
        character->GetSprite()->SetY(HEIGHT/2);
        players_x += character->GetSprite()->GetWidth() + spacing;
    }


    int enemies_x = WIDTH;

    for (BattleCharacter *character : *battle->enemyCharacters) {
        float img_ratio = (float)(character->GetSprite()->GetWidth()) / (float)(character->GetSprite()->GetHeight());
        if (img_ratio >= 1) {
            character->GetSprite()->SetHeight(sprite_size);
            character->GetSprite()->SetWidth(sprite_size * img_ratio);
        } else {
            character->GetSprite()->SetWidth(sprite_size);
            character->GetSprite()->SetHeight(sprite_size / img_ratio);
        }

        character->GetSprite()->SetX(enemies_x - character->GetSprite()->GetWidth());
        character->GetSprite()->SetY(HEIGHT/2 - character->GetSprite()->GetHeight());
        enemies_x -= character->GetSprite()->GetWidth() + spacing;
    }
}

void SetTargets(Battle_System *battle) {
    BattleCharacter *currentCharacter = GetCharacterFromList(battle->currentPriorityList, 1);

    if (currentCharacter->GetCurrentBattleButton()) {
        for (BattleCharacter *character : *battle->playableCharacters)
        {
            character->SetIsTarget(IsNotTarget);
        }
        for (BattleCharacter *character : *battle->enemyCharacters)
        {
            character->SetIsTarget(IsNotTarget);
        }
        switch (currentCharacter->GetCurrentBattleButton()->GetMove()->getMoveTarget()) {
            case MoveTargetCategory_Self:
                currentCharacter->SetLastTarget(currentCharacter);
                currentCharacter->SetIsTarget(IsPrimaryTarget);
                break;
            case MoveTargetCategory_AllEnemies:
                for (BattleCharacter *enemy : *battle->enemyCharacters) {
                    enemy->SetIsTarget(IsPrimaryTarget);
                }
                currentCharacter->SetLastTarget(battle->enemyCharacters->at(0));
                break;
            case MoveTargetCategory_AllAlly:
                for (BattleCharacter *ally : *battle->playableCharacters) {
                    ally->SetIsTarget(IsPrimaryTarget);
                }
                currentCharacter->SetLastTarget(battle->playableCharacters->at(0));
                break;
            case MoveTargetCategory_OneAlly:
                if (currentCharacter->GetLastTarget()) {
                    if (currentCharacter->GetLastTarget()->IsFriendly()) {
                        currentCharacter->GetLastTarget()->SetIsTarget(IsPrimaryTarget);
                    } else {
                        currentCharacter->SetLastTarget(battle->playableCharacters->at(0));
                    }
                }
            case MoveTargetCategory_OneEnemy:
                if (currentCharacter->GetLastTarget()) {
                    if (!currentCharacter->GetLastTarget()->IsFriendly()) {
                        currentCharacter->GetLastTarget()->SetIsTarget(IsPrimaryTarget);
                    } else {
                        currentCharacter->SetLastTarget(battle->enemyCharacters->at(0));
                    }
                }
            case MoveTargetCategory_None:
                break;
        }
    }
}