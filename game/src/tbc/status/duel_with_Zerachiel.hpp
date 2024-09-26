#ifndef DUEL_WITH_ZERACHIEL_HPP
#define DUEL_WITH_ZERACHIEL_HPP

#include "../components/battle_status.hpp"
#include "../components/battle_character.hpp"

class Status_DuelWithZerachiel : public BattleStatus
{
public:
    Status_DuelWithZerachiel(BattleCharacter linkedZerachiel);
};

#endif