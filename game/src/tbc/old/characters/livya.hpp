#ifndef LIVYA_HPP
#define LIVYA_HPP

#include <random>

#include "../components/battle_character.hpp"

class LivyaUnit : public BattleCharacter
{
public:
    LivyaUnit(bool isFriendly);
};

#endif