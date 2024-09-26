#ifndef LIVYA_HPP
#define LIVYA_HPP

#include "../components/battle_character.hpp"

class LivyaUnit : public BattleCharacter
{
public:
    LivyaUnit(bool isFriendly);
};

BattleMoveActive GetLivyaBaseMove(void);
BattleMoveActive GetLivyaMove1(void);
BattleMoveActive GetLivyaMove2(void);
BattleMoveActive GetLivyaMove3(void);
BattleMoveActive GetLivyaUltimate(void);
BattleMovePassive GetLivyaPassive1(void);
BattleMovePassive GetLivyaPassive2(void);

#endif