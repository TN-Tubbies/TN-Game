#ifndef HEAL_BLOCKED_H
#define HEAL_BLOCKED_H

#include "../components/battle_status.h"

class Status_Heal_Blocked : public BattleStatus
{
public:
    Status_Heal_Blocked(int turnPersistence);
};

#endif