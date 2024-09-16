#include "duel_with_Zerachiel.h"

Status_DuelWithZerachiel::Status_DuelWithZerachiel(BattleCharacter linkedZerachiel)
{
    statusName = "DuelWithZerachiel";
    isActive = true;
    hasTimer = false;
    timerDuration = -1;
    removeAfterBattle = true;
    linkedZerachiel = linkedZerachiel;
}