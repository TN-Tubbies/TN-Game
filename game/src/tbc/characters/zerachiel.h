#ifndef ZERACHIEL_H
#define ZERACHIEL_H

#include "../components/battle_character.h"
#include "../status/duel_with_Zerachiel.h"
#include "../status/heal_blocked.h"

class ZerachielUnit : public BattleCharacter
{
public:
    ZerachielUnit(bool isFriendly);
};

BattleMoveActive GetZerachielBaseMove(void);
BattleMoveActive GetZerachielMove1(void);
BattleMoveActive GetZerachielMove2(void);
BattleMoveActive GetZerachielMove3(void);
BattleMoveActive GetZerachielUltimate(void);
BattleMovePassive GetZerachielPassive1(void);
BattleMovePassive GetZerachielPassive2(void);

#endif