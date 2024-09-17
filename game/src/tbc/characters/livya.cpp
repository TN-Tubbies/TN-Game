#include "livya.h"

void LivyaBaseMoveEffect(BattleCharacter* Self, std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
}
BattleMoveActive GetLivyaBaseMove(void)
{
    return BattleMoveActive(
        "Entre vous et moi",
        "Restaure 15\% de la BS.\nInflige M\% de dégâts à la cible, et la fait entrer en duel avec Livya. Si un autre adversaire est déjà en duel avec Livya, ce précédent duel est annulé.",
        BattleElement_Physical,
        MoveTargetCategory_OneEnemy,
        LivyaBaseMoveEffect,
        -15,
        true,
        false);
}

// ------------------------------------------------------------------------------------------------

void LivyaMove1Effect(BattleCharacter* Self, std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
}
BattleMoveActive GetLivyaMove1(void)
{
    return BattleMoveActive(
        "Lames de Duel",
        "Consomme 20\% de la BS.\nAugmente de N\% la vitesse de Livya. Si la cible a plus de P\% de ses PV max au début du duel contre Livya, elle ne pourra plus récupérer de PV jusqu'à la fin du duel, au bout de Q tours.",
        BattleElement_Light,
        MoveTargetCategory_Self,
        LivyaMove1Effect,
        20,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void LivyaMove2Effect(BattleCharacter* Self, std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
    int atkBuffNotch = 1;

    if (Field[TargetID[0]].GetChangeStat(CharacterStat_Atk) < 0)
    {
        Field[TargetID[0]].ChangeStat(CharacterStat_Atk, 0);
    }
    if (Field[TargetID[0]].GetChangeStat(CharacterStat_Def) < 0)
    {
        Field[TargetID[0]].ChangeStat(CharacterStat_Def, 0);
    }
    if (Field[TargetID[0]].GetChangeStat(CharacterStat_Speed) < 0)
    {
        Field[TargetID[0]].ChangeStat(CharacterStat_Speed, 0);
    }
    Field[TargetID[0]].ChangeStat(CharacterStat_Atk, atkBuffNotch);
}
BattleMoveActive GetLivyaMove2(void)
{
    return BattleMoveActive(
        "Infaillible",
        "Consomme 20\% de la BS.\nNettoie ses lunettes en plein combat, retirant la majorité des malus qui l'incombent et augmentant de M\% son attaque.",
        BattleElement_Light,
        MoveTargetCategory_Self,
        LivyaMove2Effect,
        20,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void LivyaUltimateEffect(BattleCharacter* Self, std::vector<int> TargetID, std::vector<BattleCharacter> Field)
{
    int M = 1;
    int X = 5;

    for (unsigned int i = 0; i < TargetID.size(); i++)
    {
        int remaining = 0;
        for (int j = 0; j < X; j++)
        {
            BattleCharacter target = Field[TargetID[i]];
            target.TakeDamage(M, BattleElement_Light);
            if (target.GetHP() <= 0)
            {
                remaining = X - j;
                break;
            }
        }

        if (remaining != 0)
        {
            int count = 0;
            for (int j = 0; j < Field.size(); j++)
            {
                if (!Field.at(j).IsFriendly())
                {
                    count++;
                }
            }

            int residual_damage = (int)M / count;
            for (int j = 0; j < remaining; j++)
            {
                for (int k = 0; k < Field.size(); k++)
                {
                    if (!Field.at(k).IsFriendly())
                    {
                        Field.at(k).TakeDamage(residual_damage, BattleElement_Light);
                    }
                }
            }
        }
    }
}
BattleMoveActive GetLivyaUltimate(void)
{
    return BattleMoveActive(
        "Question d'habitude, voyons !",
        "Inflige M\% de dégâts à un ennemi X fois. Si la cible est vaincue avant que tous les coups soient portés, les dégâts restants sont distribués à tous les ennemis.",
        BattleElement_Light,
        MoveTargetCategory_OneEnemy,
        LivyaUltimateEffect,
        0,
        false,
        true);
}

// ------------------------------------------------------------------------------------------------

void LivyaPassive1Effect(std::vector<BattleCharacter> Field)
{
    float HPLossPercentage = 0.1f;
    float UltimateChargeGained = 0.3f;
    float AttackIncreaseNotch = 0.1f;

    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i].CheckIfAffected("DuelWithLivya"))
        {
            if (Field[i].GetLastDamageReceived() >= HPLossPercentage * Field[i].GetMaxHP())
            {
                (*(Field[i].GetStatus("DuelWithLivya").GetLinkedCharacter())).ChangeStat(CharacterStat_Atk, AttackIncreaseNotch);
                (*(Field[i].GetStatus("DuelWithLivya").GetLinkedCharacter())).AddToUltimateBar((int)100 * UltimateChargeGained);
            }
        }
    }
}
BattleMovePassive GetLivyaPassive1(void)
{
    return BattleMovePassive(
        "L'amour du travail bien fait",
        "À chaque fois qu'un ennemi en duel avec Livya perd M\% de ses PV maximums, Livya récupère N\% de charge d'ultime et augmente de P\% son attaque.",
        MoveTargetCategory_OneEnemy,
        LivyaPassive1Effect,
        PassiveTriggerCategory_OnDamageDealtToEnemy);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

LivyaUnit::LivyaUnit(bool isFriendly)
{
    std::string livyaName = "Livya";
    CharacterType livyaType = CharacterType_DPS;
    BattleElement livyaElement = BattleElement_Light;
    this->isFriendly = isFriendly;

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
    this->BaseAtk = Atk;
    this->BaseSpeed = Speed;
    this->BaseDef = Def;
    this->CurrentAtk = Atk;
    this->AtkChange = 0;
    this->CurrentSpeed = Speed;
    this->SpeedChange = 0;
    this->CurrentDef = Def;
    this->DefChange = 0;
    this->LastDamageReceived = 0;
    this->BaseMove = GetLivyaBaseMove();
    this->Move1 = GetLivyaMove1();
    this->Move2 = GetLivyaMove2();
    this->Move3 = GetNullActiveMove();
    this->Ultimate = GetLivyaUltimate();
    this->Passive1 = GetLivyaPassive1();
    this->Passive2 = GetNullPassiveMove();

    std::vector<BattleStatus> affectedStatus;
    this->AffectedStatus = affectedStatus;

    this->SkillBar = 0;
    this->UltimateBar = 0;
}
