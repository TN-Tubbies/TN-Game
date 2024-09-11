#ifndef ZERACHIEL_H
#define ZERACHIEL_H

#include "../components/battle_character.h"

class ZerachielUnit : public BattleCharacter
{
public:
    ZerachielUnit(void);
};

BattleMoveActive GetZerachielBaseMove(void);
BattleMoveActive GetZerachielMove1(void);
BattleMoveActive GetZerachielMove2(void);
BattleMoveActive GetZerachielMove3(void);
BattleMoveActive GetZerachielUltimate(void);
BattleMovePassive GetZerachielPassive1(void);
BattleMovePassive GetZerachielPassive2(void);

#endif