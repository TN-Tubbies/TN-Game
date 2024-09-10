#ifndef BATTLE_MOVE_H
#define BATTLE_MOVE_H

#include "battle_declarations.h"
#include "battle_enumerators.h"

#include <functional>

class BattleMove
{
protected:
    char *name;
    enum BattleElement Element;
    enum MoveTargetCategory MoveTarget;
};

class BattleMovePassive : public BattleMove
{
public:
    std::function<void()> Effect;

private:
    int TurnDelay;
};

class BattleMoveActive : public BattleMove
{
public:
    std::function<void()> DamageCalculator;
    std::function<void()> SideEffect;

    // TODO: Les getters arrivent fort

private:
    int Cost;
    bool IsBaseMove;
    bool IsUltimate;
};

#endif