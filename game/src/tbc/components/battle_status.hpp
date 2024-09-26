#ifndef BATTLE_STATUS_HPP
#define BATTLE_STATUS_HPP

#include <string>

class BattleCharacter;

class BattleStatus
{
public:
    BattleStatus();

    std::string GetName();
    BattleCharacter *GetLinkedCharacter();
    void CheckTimer();
    bool DoRemoveAfterBattle();
    bool IsActive();

protected:
    std::string statusName;
    bool isActive;
    bool hasTimer;
    int timerDuration;

    bool removeAfterBattle;
    BattleCharacter *linkedCharacter;
};

#endif