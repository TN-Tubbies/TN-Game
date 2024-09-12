#ifndef BATTLE_CHARACTER_H
#define BATTLE_CHARACTER_H

#include "../battle_declarations.h"
#include "../battle_enumerators.h"
#include "battle_move.h"

#include <stdio.h>
#include <string>
#include <vector>

// HP MaxHP Speed Atk Def + affinités de type

// Lumière <=> Ténèbres
// Quantique
// Eau => Feu => Bois => Vent => Terre => Foudre => Eau

// Classes:
// Débloque des équipements particuliers

// Movepool
// same movepool

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

    // SDL_Texture
    int width, length;

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

    void TakeDamage(int damage);
};

std::vector<BattleCharacter> SortCharactersWRTStat(std::vector<BattleCharacter> array);

#endif