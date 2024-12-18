#ifndef BATTLE_STATUS_HPP
#define BATTLE_STATUS_HPP

#include <string>

#include "../battle_enumerators.hpp"

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

    enum PassiveTriggerCategory trigger;

    bool removeAfterBattle;
    BattleCharacter *linkedCharacter;
};

#endif