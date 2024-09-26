#ifndef HEAL_BLOCKED_HPP
#define HEAL_BLOCKED_HPP

#include "../components/battle_status.hpp"

class Status_Heal_Blocked : public BattleStatus
{
public:
    Status_Heal_Blocked(int turnPersistence);
};

#endif