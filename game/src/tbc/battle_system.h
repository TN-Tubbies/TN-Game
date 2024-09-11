#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <iostream>
#include <vector>

#include "battle_enumerators.h"
#include "components/battle_character.h"

typedef struct _Battle_System
{
    std::vector<BattleCharacter> playableCharacters;
    std::vector<BattleCharacter> enemyCharacters;

    bool isBattleOver;
    int currentTurn;
    int maxTurnCount;

    enum BattleState currentState;
    enum BattleTurnState currentTurnState;

    BattleCharacter *CurrentCharacter;
    std::vector<BattleCharacter> currentCharacterOrder;

    std::vector<BattleCharacter> battlefield;
} Battle_System;

Battle_System *StartBattle(std::vector<BattleCharacter> playableCharacters, std::vector<BattleCharacter> enemyCharacters, int MaxTurnCount);
void DestroyBattle(Battle_System *Battle);

void RunBattleAction(Battle_System *CurrentBattle);
void HandleTurnSystem(Battle_System *CurrentBattle);

#endif