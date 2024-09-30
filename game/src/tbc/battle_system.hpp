#ifndef BATTLE_SYSTEM_HPP
#define BATTLE_SYSTEM_HPP

#include <iostream>
#include <vector>

#include "../defs.hpp"
#include "battle_enumerators.hpp"
#include "components/battle_character.hpp"
#include "components/priority_list.hpp"
#include "../static/renderer.hpp"

typedef struct _Battle_System
{
    std::vector<BattleCharacter *> playableCharacters;
    std::vector<BattleCharacter *> enemyCharacters;
    std::vector<BattleCharacter *> battlefield;

    SDL_Texture *backgroundTexture;
    int backgroundWidth, backgroundHeight;

    bool isBattleOver;
    int currentTurn;
    int maxTurnCount;

    enum BattleState currentState;

    unsigned int actionMadeAmount;
    PriorityList *currentPriorityList;

} Battle_System;

Battle_System *StartBattle(std::vector<BattleCharacter> playableCharacters, std::vector<BattleCharacter> enemyCharacters, std::string background_path, int MaxTurnCount);
void DestroyBattle(Battle_System *Battle);

void RunBattleManager(Battle_System *CurrentBattle);

#endif