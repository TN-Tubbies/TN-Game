#include "zerachiel.h"

void ZerachielBaseMoveCalculator(std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
    for (int i = 0; i < TargetID.size(); i++)
    {
        BattleCharacter target = Field[TargetID[i]];
        target.TakeDamage(1);
    }
}
void ZerachielBaseMoveEffect(std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
    for (int i = 0; i < TargetID.size(); i++)
    {
        BattleCharacter target = Field[TargetID[i]];
        target.ChangeStat(CharacterStat_Def, -1);
    }
}
BattleMoveActive GetZerachielBaseMove(void)
{
    return BattleMoveActive(
        "Haché Menu",
        "Restaure 15\% de la BS.\nInflige M\% de dégâts à la cible. Si celle-ci est en duel avec Zerachiel, sa défense est diminuée de N\%.",
        BattleElement_Physical,
        MoveTargetCategory_OneEnemy,
        ZerachielBaseMoveCalculator,
        ZerachielBaseMoveEffect,
        -15,
        true,
        false);
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetZerachielMove1(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetZerachielMove2(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetZerachielMove3(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMoveActive GetZerachielUltimate(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMovePassive GetZerachielPassive1(void)
{
}

// ------------------------------------------------------------------------------------------------

BattleMovePassive GetZerachielPassive2(void)
{
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZerachielUnit::ZerachielUnit(void)
{
    std::string zerachielName = "Zerachiel";
    CharacterType zerachielType = CharacterType_DPS;
    BattleElement zerachielElement = BattleElement_Fire;

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
    this->BaseMove = GetZerachielBaseMove();
    this->Move1 = GetZerachielMove1();
    this->Move2 = GetZerachielMove2();
    this->Move3 = GetZerachielMove3();
    this->Ultimate = GetZerachielUltimate();
    this->Passive1 = GetZerachielPassive1();
    this->Passive2 = GetZerachielPassive2();
}
