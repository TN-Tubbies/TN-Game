#include "battle_character.hpp"
#include <SDL2/SDL2_gfxPrimitives.h>

// ------------------------------------------------------------------------------------------------

BattleCharacter::BattleCharacter(
    std::string name,
    enum CharacterType Type,
    enum BattleElement Element,
    bool isFriendly,
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
    this->isFriendly = isFriendly;
    this->HP = HP;
    this->MaxHP = MaxHP;
    this->BaseAtk = Atk;
    this->BaseSpeed = Speed;
    this->BaseDef = Def;
    this->BaseMove = BaseMove;
    this->Move1 = Move1;
    this->Move2 = Move2;
    this->Move3 = Move3;
    this->Ultimate = Ultimate;
    this->Passive1 = Passive1;
    this->Passive2 = Passive2;

    this->CurrentAtk = Atk;
    this->AtkChange = 0;
    this->CurrentSpeed = Speed;
    this->SpeedChange = 0;
    this->CurrentDef = Def;
    this->DefChange = 0;
    this->LastDamageReceived = 0;

    std::vector<BattleStatus> affectedStatus;
    this->AffectedStatus = affectedStatus;

    this->SkillBar = 0;
    this->UltimateBar = 0;
}

BattleCharacter::~BattleCharacter()
{
    if (HudBG != NULL)
    {
        SDL_DestroyTexture(HudBG);
    }
    if (DisplayedName != NULL)
    {
        SDL_DestroyTexture(DisplayedName);
    }
}

// ------------------------------------------------------------------------------------------------

bool BattleCharacter::operator==(BattleCharacter &other) const
{
    return (name == other.name && Type == other.Type && Element == other.Element && isFriendly == other.isFriendly && HP == other.HP && MaxHP == other.MaxHP && BaseAtk == other.BaseAtk && BaseSpeed == other.BaseSpeed && BaseDef == other.BaseDef && BaseMove.getName() == other.BaseMove.getName() && Move1.getName() == other.Move1.getName() && Move2.getName() == other.Move2.getName() && Move3.getName() == other.Move3.getName() && Ultimate.getName() == other.Ultimate.getName() && Passive1.getName() == other.Passive1.getName() && Passive2.getName() == other.Passive2.getName());
}
bool BattleCharacter::operator!=(BattleCharacter &other) const
{
    return !(*this == other);
}

// ------------------------------------------------------------------------------------------------

std::string BattleCharacter::GetName() { return name; }
enum CharacterType BattleCharacter::GetType() { return Type; }
enum BattleElement BattleCharacter::GetElement() { return Element; }
int BattleCharacter::GetHP() { return HP; }
int BattleCharacter::GetMaxHP() { return MaxHP; }
int BattleCharacter::GetBaseAtk() { return BaseAtk; }
int BattleCharacter::GetBaseSpeed() { return BaseSpeed; }
int BattleCharacter::GetBaseDef() { return BaseDef; }
int BattleCharacter::GetBaseStat(enum CharacterStat stat)
{
    switch (stat)
    {
    case CharacterStat::CharacterStat_Atk:
        return BaseAtk;
    case CharacterStat::CharacterStat_Def:
        return BaseDef;
    case CharacterStat::CharacterStat_Speed:
        return BaseSpeed;
    default:
        return 0;
    }
}
int BattleCharacter::GetCurrentStat(enum CharacterStat stat)
{
    switch (stat)
    {
    case CharacterStat::CharacterStat_Atk:
        return CurrentAtk;
    case CharacterStat::CharacterStat_Def:
        return CurrentDef;
    case CharacterStat::CharacterStat_Speed:
        return CurrentSpeed;
    default:
        return 0;
    }
}
bool BattleCharacter::IsFriendly() { return isFriendly; }
int BattleCharacter::GetLastDamageReceived() { return LastDamageReceived; }

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
            CurrentAtk = (int)BaseAtk * (coef);
            break;
        case CharacterStat_Def:
            CurrentDef = (int)BaseDef * (coef);
            break;
        case CharacterStat_Speed:
            CurrentSpeed = (int)BaseSpeed * (coef);
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
            CurrentAtk = (int)BaseAtk * (1 + 0.5 * notch);
            break;
        case CharacterStat_Def:
            CurrentDef = (int)BaseDef * (1 + 0.5 * notch);
            break;
        case CharacterStat_Speed:
            CurrentSpeed = (int)BaseSpeed * (1 + 0.5 * notch);
            break;
        default:
            break;
        }
    }
}
int BattleCharacter::GetChangeStat(enum CharacterStat stat)
{
    switch (stat)
    {
    case CharacterStat_Atk:
        return AtkChange;
    case CharacterStat_Def:
        return DefChange;
    case CharacterStat_Speed:
        return SpeedChange;
    default:
        return 0;
    }
}

void BattleCharacter::AddStatus(BattleStatus status) { AffectedStatus.push_back(status); }
BattleStatus BattleCharacter::GetStatus(std::string statusName)
{
    for (unsigned int i = 0; i < AffectedStatus.size(); i++)
    {
        if (AffectedStatus[i].GetName() == statusName)
        {
            return AffectedStatus[i];
        }
    }
    return BattleStatus(); // Return empty status if not found
}
bool BattleCharacter::CheckIfAffected(std::string statusName)
{
    bool res = false;

    for (unsigned int i = 0; i < AffectedStatus.size(); i++)
    {
        if (AffectedStatus[i].GetName() == statusName)
        {
            res = true;
            break;
        }
    }

    return res;
}
void BattleCharacter::RemoveInactiveStatus()
{
    for (unsigned int i = 0; i < AffectedStatus.size(); i++)
    {
        if (!AffectedStatus[i].IsActive())
        {
            AffectedStatus.erase(AffectedStatus.begin() + i);
            i--;
        }
    }
}
void BattleCharacter::RemoveStatus(std::string statusName)
{
    for (unsigned int i = 0; i < AffectedStatus.size(); i++)
    {
        if (AffectedStatus[i].GetName() == statusName)
        {
            AffectedStatus.erase(AffectedStatus.begin() + i);
            break;
        }
    }
}

void BattleCharacter::AddToSkillBar(int adding) { SkillBar += adding; }
void BattleCharacter::AddToUltimateBar(int adding) { UltimateBar += adding; }

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
        token.push_back(array[i].GetBaseSpeed());
        unsorted.push_back(token);
    }

    std::vector<std::vector<int>> sorted(length);
    while (unsorted.size() > 0)
    {
        int max = 0;
        int maxIndex = -1;
        for (unsigned int i = 0; i < unsorted.size(); i++)
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
    for (unsigned int i = 0; i < sorted.size(); i++)
    {
        res.push_back(array[sorted[i][0]]);
    }

    return res;
}

// ------------------------------------------------------------------------------------------------
// HUD RELATED FUNCTIONS --------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void BattleCharacter::DrawHud(int x, int y)
{
    int y_offset = 5;
    int HudWidth = 128;
    int HudHeight = 128;
    int bar_height = 10;

    SDL_Rect bg_rect = {x, y, HudWidth, HudHeight};
    SDL_RenderCopy(Get_Renderer(), HudBG, NULL, &bg_rect);

    //Name
    int center_name_x = x + HudWidth / 2 - DisplayedNameWidth / 2;
    SDL_Rect name_rect = {center_name_x, y + y_offset, DisplayedNameWidth, DisplayedNameHeight};
    SDL_RenderCopy(Get_Renderer(), DisplayedName, NULL, &name_rect);
    y_offset += DisplayedNameHeight + 10;

    // HP //
    rectangleColor(Get_Renderer(), x + 5, y + y_offset, x + HudWidth - 5, y + y_offset + bar_height, 0xFFFFFFFF);
    if (this->HP <= this->MaxHP / 4)
    {
        boxColor(Get_Renderer(), x + 6, y + y_offset + 1, x + 6 + (HudWidth - 13) * this->HP/ this->MaxHP, y + y_offset + bar_height - 2, 0xFF0000FF);
    }
    else
    {
        boxColor(Get_Renderer(), x + 6, y + y_offset + 1, x + 6 + (HudWidth - 13) * this->HP / this->MaxHP, y + y_offset + bar_height - 2, 0xFFFFFFFF);
    }
    y_offset += bar_height + 1;

    int center_hp_x = x + HudWidth / 2 - (DisplayedHPWidth + DisplayedMaxHPWidth) / 2;
    SDL_Rect hp_rect = {center_hp_x, y + y_offset, DisplayedHPWidth, DisplayedHPHeight};
    SDL_RenderCopy(Get_Renderer(), DisplayedHP, NULL, &hp_rect);
    int center_max_hp_x = center_hp_x + DisplayedHPWidth;
    SDL_Rect max_hp_rect = {center_max_hp_x, y + y_offset, DisplayedMaxHPWidth, DisplayedMaxHPHeight};
    SDL_RenderCopy(Get_Renderer(), DisplayedMaxHP, NULL, &max_hp_rect);
    y_offset += DisplayedHPHeight + 5;
}