#ifndef BATTLE_STATUS_H
#define BATTLE_STATUS_H

#include <string>

class BattleStatus
{
public:
    BattleStatus();

    std::string getName();
    void CheckTimer();
    bool DoRemoveAfterBattle();
    bool IsActive();

protected:
    std::string statusName;
    bool isActive;
    bool hasTimer;
    int timerDuration;

    bool removeAfterBattle;
};

#endif