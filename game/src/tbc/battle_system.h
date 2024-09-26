#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <iostream>
#include <vector>

#include "../defs.h"
#include "battle_enumerators.h"
#include "components/battle_character.h"

typedef struct _Battle_System
{
    std::vector<BattleCharacter> playableCharacters;
    std::vector<BattleCharacter> enemyCharacters;
    std::vector<BattleCharacter> battlefield;

    bool isBattleOver;
    int currentTurn;
    int maxTurnCount;

    enum BattleState currentState;

    unsigned int currentCharacterIndex;
    std::vector<BattleCharacter> currentCharacterOrder;

} Battle_System;

Battle_System *StartBattle(std::vector<BattleCharacter> playableCharacters, std::vector<BattleCharacter> enemyCharacters, int MaxTurnCount);
void DestroyBattle(Battle_System *Battle);

void RunBattleManager(Battle_System *CurrentBattle);

#endif