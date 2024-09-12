#ifndef BATTLE_CHARACTER_H
#define BATTLE_CHARACTER_H

#include "../battle_declarations.h"
#include "../battle_enumerators.h"
#include "battle_status.h"
#include "battle_move.h"

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

// Classes:
// Débloque des équipements particuliers

class BattleCharacter
{
protected:
    std::string name;
    enum CharacterType Type;
    enum BattleElement Element;

    int HP;
    int MaxHP;
    int Atk;
    int Speed;
    int Def;

    int AtkChange;
    int SpeedChange;
    int DefChange;

    std::vector<BattleStatus> AffectedStatus;

public:
    BattleMove BaseMove;
    BattleMove Move1;
    BattleMove Move2;
    BattleMove Move3;
    BattleMove Ultimate;
    BattleMove Passive1;
    BattleMove Passive2;

    // Construct
    BattleCharacter() {};
    BattleCharacter(
        std::string name,
        enum CharacterType Type,
        enum BattleElement Element,
        int HP,
        int MaxHP,
        int Atk,
        int Speed,
        int Def,
        BattleMove BaseMove,
        BattleMove Move1,
        BattleMove Move2,
        BattleMove Move3,
        BattleMove Ultimate,
        BattleMove Passive1,
        BattleMove Passive2);

    // Destruct
    ~BattleCharacter();

    // Getters
    std::string GetName();
    enum CharacterType GetType();
    enum BattleElement GetElement();
    int GetHP();
    int GetMaxHP();
    int GetAtk();
    int GetSpeed();
    int GetDef();
    int GetStat(enum CharacterStat stat);

    void TakeDamage(int damage, enum BattleElement IncomingElement);
    float GetElementReactionCoefficient(enum BattleElement IncomingElement);
    void ChangeStat(enum CharacterStat stat, int notch);

    bool CheckIfAffected(BattleStatus status);
    void RemoveInactiveStatus();
};

std::vector<BattleCharacter> SortCharactersWRTStat(std::vector<BattleCharacter> array);

#endif