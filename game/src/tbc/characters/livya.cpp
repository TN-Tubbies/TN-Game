#include "livya.h"

void LivyaBaseMoveCalculator(std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
}
void LivyaBaseMoveEffect(std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
}
BattleMoveActive GetLivyaBaseMove(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetLivyaMove1(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetLivyaMove2(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetLivyaMove3(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetLivyaUltimate(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMovePassive GetLivyaPassive1(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMovePassive GetLivyaPassive2(void)
{
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

LivyaUnit::LivyaUnit(void)
{
    std::string livyaName = "Livya";
    CharacterType livyaType = CharacterType_Support;
    BattleElement livyaElement = BattleElement_Lightening;

    int MaxHP = 100;
    int HP = MaxHP;
    int Atk = 5;
    int Speed = 5;
    int Def = 5;

    this->name = name;
    this->Type = Type;
    this->Element = Element;
    this->HP = HP;
    this->MaxHP = MaxHP;
    this->Atk = Atk;
    this->Speed = Speed;
    this->Def = Def;
    this->BaseMove = GetLivyaBaseMove();
    this->Move1 = GetLivyaMove1();
    this->Move2 = GetLivyaMove2();
    this->Move3 = GetLivyaMove3();
    this->Ultimate = GetLivyaUltimate();
    this->Passive1 = GetLivyaPassive1();
    this->Passive2 = GetLivyaPassive2();
}
