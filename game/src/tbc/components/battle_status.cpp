#include "battle_status.h"
#include "battle_character.h"

BattleStatus::BattleStatus(){}

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
std::string BattleStatus::GetName() { return statusName; }
BattleCharacter* BattleStatus::GetLinkedCharacter() { return linkedCharacter; }
bool BattleStatus::DoRemoveAfterBattle() { return removeAfterBattle; }
bool BattleStatus::IsActive() { return isActive; }