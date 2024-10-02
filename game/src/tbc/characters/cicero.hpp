#ifndef CICERO_HPP
#define CICERO_HPP

#include <random>

#include "../components/battle_character.hpp"

class CiceroUnit : public BattleCharacter
{
public:
    CiceroUnit(bool isFriendly);
};

#endif