#include "battle_move.h"

// ------------------------------------------------------------------------------------------------
// CLASS ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

BattleMovePassive::BattleMovePassive(std::string name, std::string description, enum MoveTargetCategory moveTarget, std::function<void(std::vector<int> TargetID, std::vector<BattleCharacter> Field)> effect, int turnDelay)
{
    this->name = name;
    this->description = description;
    this->moveTarget = moveTarget;
    this->effect = effect;
    this->turnDelay = turnDelay;
}

BattleMoveActive::BattleMoveActive(std::string name, std::string description, enum BattleElement element, enum MoveTargetCategory moveTarget, std::function<void(std::vector<int> TargetID, std::vector<BattleCharacter> Field)> damageCalculator,
                                   std::function<void(std::vector<int> TargetID, std::vector<BattleCharacter> Field)> sideEffect, int cost, bool isBM, bool isU)
{
    this->name = name;
    this->description = description;
    this->element = element;
    this->moveTarget = moveTarget;
    this->damageCalculator = damageCalculator;
    this->sideEffect = sideEffect;
    this->cost = cost;
    this->isBaseMove = isBM;
    this->isUltimate = isU;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

std::function<void(std::vector<int> TargetID, std::vector<BattleCharacter> Field)> GetNullMoveFunction(void)
{
    // TODO: Tkt ça arrive fort
}
BattleMoveActive GetNullActiveMove(void)
{
    return BattleMoveActive("", "", BattleElement_Null, MoveTargetCategory_None, GetNullMoveFunction(), GetNullMoveFunction(), 0, false, false);
}
BattleMovePassive GetNullPassiveMove(void)
{
    return BattleMovePassive("", "", MoveTargetCategory_None, GetNullMoveFunction(), 0);
}