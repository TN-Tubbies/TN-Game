#include "battle_character.h"

// ------------------------------------------------------------------------------------------------

BattleCharacter::BattleCharacter(
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
    BattleMove Passive2)
{
    this->name = name;
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

    std::vector<BattleStatus> affectedStatus;
    this->AffectedStatus = affectedStatus;
}

BattleCharacter::~BattleCharacter()
{
}

// ------------------------------------------------------------------------------------------------

std::string BattleCharacter::GetName()
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
int BattleCharacter::GetStat(enum CharacterStat stat)
{
    switch (stat)
    {
    case CharacterStat::CharacterStat_Atk:
        return Atk;
    case CharacterStat::CharacterStat_Def:
        return Def;
    case CharacterStat::CharacterStat_Speed:
        return Speed;
    default:
        return 0;
    }
}

// ------------------------------------------------------------------------------------------------

float BattleCharacter::GetElementReactionCoefficient(enum BattleElement IncomingElement)
{
    float low = 0.5f;
    float high = 1.5f;
    float classic = 1.0f;
    if (Element == BattleElement_Light && IncomingElement == BattleElement_Light)
    {
        return low;
    }
    else if (Element == BattleElement_Light && IncomingElement == BattleElement_Dark)
    {
        return high;
    }
    else if (Element == BattleElement_Dark && IncomingElement == BattleElement_Light)
    {
        return high;
    }
    else if (Element == BattleElement_Dark && IncomingElement == BattleElement_Dark)
    {
        return low;
    }
    else if (Element == BattleElement_Water && IncomingElement == BattleElement_Water)
    {
        return low;
    }
    else if (Element == BattleElement_Fire && IncomingElement == BattleElement_Water)
    {
        return high;
    }
    else if (Element == BattleElement_Fire && IncomingElement == BattleElement_Fire)
    {
        return low;
    }
    else if (Element == BattleElement_Grass && IncomingElement == BattleElement_Fire)
    {
        return high;
    }
    else if (Element == BattleElement_Grass && IncomingElement == BattleElement_Grass)
    {
        return low;
    }
    else if (Element == BattleElement_Wind && IncomingElement == BattleElement_Grass)
    {
        return high;
    }
    else if (Element == BattleElement_Wind && IncomingElement == BattleElement_Wind)
    {
        return low;
    }
    else if (Element == BattleElement_Earth && IncomingElement == BattleElement_Wind)
    {
        return high;
    }
    else if (Element == BattleElement_Earth && IncomingElement == BattleElement_Earth)
    {
        return low;
    }
    else if (Element == BattleElement_Lightening && IncomingElement == BattleElement_Earth)
    {
        return high;
    }
    else if (Element == BattleElement_Lightening && IncomingElement == BattleElement_Lightening)
    {
        return low;
    }
    else if (Element == BattleElement_Water && IncomingElement == BattleElement_Lightening)
    {
        return low;
    }
    else
    {
        return classic;
    }
}

void BattleCharacter::TakeDamage(int damage, enum BattleElement IncomingElement)
{
    int readDamage = (int)damage * GetElementReactionCoefficient(IncomingElement);
    if (HP - readDamage < 0)
    {
        HP = 0;
    }
    else
    {
        HP -= readDamage;
    }
}

void BattleCharacter::ChangeStat(enum CharacterStat stat, int notch)
{
    if (notch < 0)
    {
        float coef;
        switch (notch)
        {
        case -1:
            coef = 2 / 3;
            break;
        case -2:
            coef = 1 / 2;
            break;
        case -3:
            coef = 2 / 5;
            break;
        case -4:
            coef = 1 / 3;
            break;
        case -5:
            coef = 2 / 7;
            break;
        default:
            coef = 1;
            break;
        }
        switch (stat)
        {
        case CharacterStat_Atk:
            Atk = (int)Atk * (coef);
            break;
        case CharacterStat_Def:
            Def = (int)Def * (coef);
            break;
        case CharacterStat_Speed:
            Speed = (int)Speed * (coef);
            break;
        default:
            break;
        }
    }
    else if (notch > 0)
    {

        switch (stat)
        {
        case CharacterStat_Atk:
            Atk = (int)Atk * (1 + 0.5 * notch);
            break;
        case CharacterStat_Def:
            Def = (int)Def * (1 + 0.5 * notch);
            break;
        case CharacterStat_Speed:
            Speed = (int)Speed * (1 + 0.5 * notch);
            break;
        default:
            break;
        }
    }
}

bool BattleCharacter::CheckIfAffected(BattleStatus status)
{
    return std::find(AffectedStatus.begin(), AffectedStatus.end(), status) != AffectedStatus.end();
}
void BattleCharacter::RemoveInactiveStatus()
{
    for (int i = 0; i < AffectedStatus.size(); i++)
    {
        if (!AffectedStatus[i].IsActive())
        {
            AffectedStatus.erase(AffectedStatus.begin() + i);
            i--;
        }
    }
}

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