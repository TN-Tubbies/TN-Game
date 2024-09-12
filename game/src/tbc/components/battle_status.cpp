#include "battle_status.h"

void BattleStatus::CheckTimer()
{
    if (hasTimer)
    {
        timerDuration--;
        if (timerDuration <= 0)
        {
            hasTimer = false;
            isActive = false;
            return;
        }
    }
}
std::string BattleStatus::getName() { return statusName; }
bool BattleStatus::DoRemoveAfterBattle() { return removeAfterBattle; }
bool BattleStatus::IsActive() { return isActive; }