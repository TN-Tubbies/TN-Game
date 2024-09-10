#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <iostream>
#include <vector>

#include "battle_character.h"

typedef struct _Battle_System
{
    std::vector<BattleCharacter> playableCharacters;
    std::vector<BattleCharacter> enemyCharacters;

    int TurnCount;
    int MaxTurnCount;

    // BattleCharacter* CurrentCharacter;

} Battle_System;

#endif