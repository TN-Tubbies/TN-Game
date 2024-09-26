#ifndef BATTLE_MOVE_HPP
#define BATTLE_MOVE_HPP

#include "../battle_declarations.hpp"
#include "../battle_enumerators.hpp"

#include <string>
#include <vector>
#include <functional>

class BattleMove
{
public:
    BattleMove() {};

    std::string getName() const;
    std::string getDescription() const;
    enum MoveTargetCategory getMoveTarget() const;

protected:
    std::string name;
    std::string description;
    enum MoveTargetCategory moveTarget;
};

class BattleMovePassive : public BattleMove
{
public:
    std::function<void(std::vector<BattleCharacter> Field)> effect;

    BattleMovePassive(std::string name, std::string description, enum MoveTargetCategory moveTarget, std::function<void(std::vector<BattleCharacter> Field)> effect, enum PassiveTriggerCategory triggerCategory);

private:
    enum PassiveTriggerCategory triggerCategory;
};

class BattleMoveActive : public BattleMove
{
public:
    std::function<void(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter> Field)> runFunction;

    BattleMoveActive(std::string name, std::string description, enum BattleElement element, enum MoveTargetCategory moveTarget,
                     std::function<void(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter> Field)> sideEffect, int cost, bool isBM, bool isU);

    // TODO: Les getters arrivent fort

private:
    enum BattleElement element;
    int cost;
    bool isBaseMove;
    bool isUltimate;
};

BattleMoveActive GetNullActiveMove(void);
BattleMovePassive GetNullPassiveMove(void);

#endif