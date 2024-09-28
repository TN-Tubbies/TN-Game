#ifndef ZERACHIEL_HPP
#define ZERACHIEL_HPP

#include "../components/battle_character.hpp"
#include "../status/duel_with_Zerachiel.hpp"
#include "../status/heal_blocked.hpp"

class ZerachielUnit : public BattleCharacter
{
public:
    ZerachielUnit(bool isFriendly);
};

#endif