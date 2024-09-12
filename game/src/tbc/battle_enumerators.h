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
    BattleElement_Lightning
};
enum CharacterType
{
    CharacterType_DPS,
};
enum CharacterStat
{
    CharacterStat_Atk,
    CharacterStat_Def,
    CharacterStat_Speed
};

#endif