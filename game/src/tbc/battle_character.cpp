#include "battle_character.h"

// ------------------------------------------------------------------------------------------------

BattleCharacter::BattleCharacter(
    const char *name,
    int lengthOfName,
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
    BattleMove Passive2)
{
    char *nameCpy = new char[lengthOfName];
    strcpy(nameCpy, name);
    this->name = nameCpy;

    this->Type = Type;
    this->Element = Element;
    this->HP = HP;
    this->MaxHP = MaxHP;
    this->Atk = Atk;
    this->Speed = Speed;
    this->Def = Def;
    this->BaseMove = BaseMove;
    this->Move1 = Move1;
    this->Move2 = Move2;
    this->Move3 = Move3;
    this->Ultimate = Ultimate;
    this->Passive1 = Passive1;
    this->Passive2 = Passive2;
}

BattleCharacter::~BattleCharacter()
{
    delete[] name;
}

// ------------------------------------------------------------------------------------------------

char *BattleCharacter::GetName()
{
    return name;
}
enum CharacterType BattleCharacter::GetType()
{
    return Type;
}
enum BattleElement BattleCharacter::GetElement()
{
    return Element;
}
int BattleCharacter::GetHP()
{
    return HP;
}
int BattleCharacter::GetMaxHP()
{
    return MaxHP;
}
int BattleCharacter::GetAtk()
{
    return Atk;
}
int BattleCharacter::GetSpeed()
{
    return Speed;
}
int BattleCharacter::GetDef()
{
    return Def;
}

// ------------------------------------------------------------------------------------------------

int TakeDamage();