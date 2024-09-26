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

BattleMoveActive GetZerachielBaseMove(void);
BattleMoveActive GetZerachielMove1(void);
BattleMoveActive GetZerachielMove2(void);
BattleMoveActive GetZerachielUltimate(void);
BattleMovePassive GetZerachielPassive1(void);

#endif