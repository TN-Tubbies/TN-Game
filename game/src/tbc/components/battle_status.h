#ifndef BATTLE_STATUS_H
#define BATTLE_STATUS_H

#include <string>

#include "battle_character.h"

class BattleStatus
{
public:
    BattleStatus();

    std::string GetName();
    BattleCharacter* GetLinkedCharacter();
    void CheckTimer();
    bool DoRemoveAfterBattle();
    bool IsActive();

protected:
    std::string statusName;
    bool isActive;
    bool hasTimer;
    int timerDuration;

    bool removeAfterBattle;
    BattleCharacter* linkedCharacter;
};

#endif