#include "battle_move.hpp"

// ------------------------------------------------------------------------------------------------
// CLASS ------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

std::string BattleMove::getName() const { return name; }
std::string BattleMove::getDescription() const { return description; }
enum MoveTargetCategory BattleMove::getMoveTarget() const { return moveTarget; }

// ------------------------------------------------------------------------------------------------

BattleMovePassive::BattleMovePassive(std::string name, std::string description, enum MoveTargetCategory moveTarget, std::function<void(std::vector<BattleCharacter *> Field)> effect, enum PassiveTriggerCategory triggerCategory)
{
    this->name = name;
    this->description = description;
    this->moveTarget = moveTarget;
    this->effect = effect;
    this->triggerCategory = triggerCategory;
}

BattleMoveActive::BattleMoveActive(std::string name, std::string description, enum BattleElement element, enum MoveTargetCategory moveTarget,
                                   std::function<void(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)> RunEffect, int cost, bool isBM, bool isU)
{
    this->name = name;
    this->description = description;
    this->element = element;
    this->moveTarget = moveTarget;
    this->runFunction = RunEffect;
    this->cost = cost;
    this->isBaseMove = isBM;
    this->isUltimate = isU;
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
BattleMoveActive *GetNullActiveMove(void)
{
    std::function<void(BattleCharacter * Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)> NullMoveFunction = [](BattleCharacter *, std::vector<int>, std::vector<BattleCharacter *>) {};
    return new BattleMoveActive("", "", BattleElement_Null, MoveTargetCategory_None, NullMoveFunction, 0, false, false);
}
BattleMovePassive *GetNullPassiveMove(void)
{
    std::function<void(std::vector<BattleCharacter *> Field)> NullMoveFunction2 = [](std::vector<BattleCharacter *> Field) {};
    return new BattleMovePassive("", "", MoveTargetCategory_None, NullMoveFunction2, PassiveTriggerCategory_None);
}