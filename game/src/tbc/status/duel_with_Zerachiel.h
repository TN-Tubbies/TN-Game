#ifndef DUEL_WITH_ZERACHIEL_H
#define DUEL_WITH_ZERACHIEL_H

#include "../components/battle_status.h"
#include "../components/battle_character.h"

class Status_DuelWithZerachiel : public BattleStatus
{
public:
    Status_DuelWithZerachiel(BattleCharacter linkedZerachiel);
};

#endif