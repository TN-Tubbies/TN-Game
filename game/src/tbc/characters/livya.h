#ifndef LIVYA_H
#define LIVYA_H

#include "../components/battle_character.h"

class LivyaUnit : public BattleCharacter
{
public:
    LivyaUnit(void);
};

BattleMoveActive GetLivyaBaseMove(void);
BattleMoveActive GetLivyaMove1(void);
BattleMoveActive GetLivyaMove2(void);
BattleMoveActive GetLivyaMove3(void);
BattleMoveActive GetLivyaUltimate(void);
BattleMovePassive GetLivyaPassive1(void);
BattleMovePassive GetLivyaPassive2(void);

#endif