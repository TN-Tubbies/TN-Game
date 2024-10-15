#include "cicero_allin.hpp"

Status_CiceroAllIn::Status_CiceroAllIn()
{
    statusName = "CiceroAllIn";
    linkedCharacter = nullptr;
    removeAfterBattle = true;
    isActive = true;
    hasTimer = true;
    timerDuration = 1;
    trigger = PassiveTriggerCategory_OnDamageReceived;
}