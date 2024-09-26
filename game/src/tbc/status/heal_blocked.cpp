#include "heal_blocked.hpp"

Status_Heal_Blocked::Status_Heal_Blocked(int turnPersistence)
{
    statusName = "HealBlocked";
    isActive = true;
    hasTimer = true;
    timerDuration = turnPersistence;
    removeAfterBattle = true;
}