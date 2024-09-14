#ifndef BATTLE_ENUMERATORS_H
#define BATTLE_ENUMERATORS_H

// Battle-related enumerators
enum BattleState
{
    BattleState_Starting,
    BattleState_End
};
enum BattleTurnState
{
    BattleTurnState_Starting,
};

// Move-related enumerators
enum MoveTargetCategory
{
    MoveTargetCategory_None,
    MoveTargetCategory_Self,
    MoveTargetCategory_OneEnemy,
};
enum PassiveTriggerCategory
{
    PassiveTriggerCategory_None,
    PassiveTriggerCategory_OnMoveStart,
    PassiveTriggerCategory_OnMoveEnd,
    PassiveTriggerCategory_OnTurnStart,
    PassiveTriggerCategory_OnTurnEnd,
    PassiveTriggerCategory_OnDamageDealt,
    PassiveTriggerCategory_OnDamageReceived,
    PassiveTriggerCategory_OnHeal,
    PassiveTriggerCategory_OnStatusApplied,
    PassiveTriggerCategory_OnStatusRemoved,
    PassiveTriggerCategory_OnEachMoveStart,
    PassiveTriggerCategory_OnEachMoveEnd,
    PassiveTriggerCategory_OnEachTurnStart,
    PassiveTriggerCategory_OnEachTurnEnd,
    PassiveTriggerCategory_OnDamageDealtToEnemy,
    PassiveTriggerCategory_OnDamageReceivedFromEnemy
};

// Character-related enumerators
enum BattleElement
{
    BattleElement_Null,
    BattleElement_Physical,
    BattleElement_Light,
    BattleElement_Dark,
    BattleElement_Quantum,
    BattleElement_Water,
    BattleElement_Fire,
    BattleElement_Grass,
    BattleElement_Wind,
    BattleElement_Earth,
    BattleElement_Lightening
};
enum CharacterType
{
    CharacterType_Null,
    CharacterType_Tank,
    CharacterType_Healer,
    CharacterType_Support,
    CharacterType_DPS
};
enum CharacterStat
{
    CharacterStat_Atk,
    CharacterStat_Def,
    CharacterStat_Speed
};

#endif