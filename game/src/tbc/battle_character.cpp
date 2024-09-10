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

// ------------------------------------------------------------------------------------------------
// BATTLE CHARACTER RELATED FUNCTIONS -------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

std::vector<BattleCharacter> SortCharactersWRTStat(std::vector<BattleCharacter> array)
{
    int length = array.size();
    std::vector<std::vector<int>> unsorted(length);

    for (int i = 0; i < length; i++)
    {
        std::vector<int> token(2);
        token.push_back(i);
        token.push_back(array[i].GetSpeed());
        unsorted.push_back(token);
    }

    std::vector<std::vector<int>> sorted(length);
    while (unsorted.size() > 0)
    {
        int max = 0;
        int maxIndex = -1;
        for (int i = 0; i < unsorted.size(); i++)
        {
            if (unsorted[i][1] > max)
            {
                max = unsorted[i][1];
                maxIndex = i;
            }
        }
        sorted.push_back(unsorted[maxIndex]);
        unsorted.erase(unsorted.begin() + maxIndex);
    }

    std::vector<BattleCharacter> res(length);
    for (int i = 0; i < sorted.size(); i++)
    {
        res.push_back(array[sorted[i][0]]);
    }

    return res;
}