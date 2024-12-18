#include "duel_with_zerachiel.hpp"

Status_DuelWithZerachiel::Status_DuelWithZerachiel(BattleCharacter *linkedZerachiel)
{
    statusName = "DuelWithZerachiel";
    isActive = true;
    hasTimer = false;
    timerDuration = -1;
    removeAfterBattle = true;
    trigger = PassiveTriggerCategory_None;
    linkedCharacter = linkedZerachiel;
}