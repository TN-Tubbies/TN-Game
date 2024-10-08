#include "zerachiel.hpp"

void ZerachielBaseMoveEffect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int Damage = 0;
    int DefenseDropNotch = -1;

    Field[TargetID[0]]->TakeDamage(Self, Damage, BattleElement_Light);

    if (Field[TargetID[0]]->CheckIfAffected("DuelWithZerachiel"))
    {
        Field[TargetID[0]]->ChangeStat(CharacterStat_Def, DefenseDropNotch);
    }
}
BattleMoveActive *GetZerachielBaseMove(void)
{
    return new BattleMoveActive(
        "Je t'ai dans mon viseur",
        "Restaure M % de la BS.Inflige N % de dégâts à la cible. Si celle-ci est en duel avec Zerachiel, sa défense est diminuée de O %.",
        BattleElement_Light,
        MoveTargetCategory_OneEnemy,
        ZerachielBaseMoveEffect,
        -15,
        true,
        false);
}

// ------------------------------------------------------------------------------------------------

void ZerachielMove1Effect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int N = 1;
    float P = 0.5f;
    int Q = 3;

    Field[TargetID[0]]->ChangeStat(CharacterStat_Speed, N);
    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i]->CheckIfAffected("DuelWithZerachiel") && Field[i]->GetHP() / Field[i]->GetMaxHP() > P)
        {
            Status_Heal_Blocked *status = new Status_Heal_Blocked(Q);
            Field[i]->AddStatus(status);
        }
    }
}
BattleMoveActive *GetZerachielMove1(void)
{
    return new BattleMoveActive(
        "Lames de Duel",
        "Consomme 20% de la BS.\nAugmente de N% la vitesse de Zerachiel. Si la cible a plus de P% de ses PV max au début du duel contre Zerachiel, elle ne pourra plus récupérer de PV jusqu'à la fin du duel, au bout de Q tours.",
        BattleElement_Light,
        MoveTargetCategory_Self,
        ZerachielMove1Effect,
        20,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void ZerachielMove2Effect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int atkBuffNotch = 1;

    if (Field[TargetID[0]]->GetChangeStat(CharacterStat_Atk) < 0)
    {
        Field[TargetID[0]]->ChangeStat(CharacterStat_Atk, 0);
    }
    if (Field[TargetID[0]]->GetChangeStat(CharacterStat_Def) < 0)
    {
        Field[TargetID[0]]->ChangeStat(CharacterStat_Def, 0);
    }
    if (Field[TargetID[0]]->GetChangeStat(CharacterStat_Speed) < 0)
    {
        Field[TargetID[0]]->ChangeStat(CharacterStat_Speed, 0);
    }
    Field[TargetID[0]]->ChangeStat(CharacterStat_Atk, atkBuffNotch);
}
BattleMoveActive *GetZerachielMove2(void)
{
    return new BattleMoveActive(
        "Infaillible",
        "Consomme 20% de la BS.\nNettoie ses lunettes en plein combat, retirant la majorité des malus qui l'incombent et augmentant de M% son attaque.",
        BattleElement_Light,
        MoveTargetCategory_Self,
        ZerachielMove2Effect,
        20,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void ZerachielUltimateEffect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int M = 1;
    int X = 5;

    for (unsigned int i = 0; i < TargetID.size(); i++)
    {
        int remaining = 0;
        for (int j = 0; j < X; j++)
        {
            BattleCharacter *target = Field[TargetID[i]];
            target->TakeDamage(Self, M, BattleElement_Light);
            if (target->GetHP() <= 0)
            {
                remaining = X - j;
                break;
            }
        }

        if (remaining != 0)
        {
            int count = 0;
            for (unsigned int j = 0; j < Field.size(); j++)
            {
                if (!Field.at(j)->IsFriendly())
                {
                    count++;
                }
            }

            int residual_damage = (int)M / count;
            for (int j = 0; j < remaining; j++)
            {
                for (unsigned int k = 0; k < Field.size(); k++)
                {
                    if (!Field.at(k)->IsFriendly())
                    {
                        Field.at(k)->TakeDamage(Self, residual_damage, BattleElement_Light);
                    }
                }
            }
        }
    }
}
BattleMoveActive *GetZerachielUltimate(void)
{
    return new BattleMoveActive(
        "Question d'habitude, voyons !",
        "Inflige M% de dégâts à un ennemi X fois. Si la cible est vaincue avant que tous les coups soient portés, les dégâts restants sont distribués à tous les ennemis.",
        BattleElement_Light,
        MoveTargetCategory_OneEnemy,
        ZerachielUltimateEffect,
        0,
        false,
        true);
}

// ------------------------------------------------------------------------------------------------

void ZerachielPassive1Effect(std::vector<BattleCharacter *> Field)
{
    int ZerachielID = -1;
    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i]->GetName() == "Zerachiel")
        {
            ZerachielID = i;
            break;
        }
    }

    std::vector<int> enemyIDs;
    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i]->IsFriendly() != Field[ZerachielID]->IsFriendly() && Field[i]->GetHP() > 0)
        {
            enemyIDs.push_back(i);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(enemyIDs.begin(), enemyIDs.end(), g);
    Field[enemyIDs[0]]->AddStatus(new Status_DuelWithZerachiel(Field[ZerachielID]));
}
BattleMovePassive *GetZerachielPassive1(void)
{
    return new BattleMovePassive(
        "C'est entre vous et moi",
        "Au début du combat, Zerachiel cible un ennemi aléatoire : ce dernier rentre en duel avec lui. Le duel ne peut se terminer que par la chute de l'un des participants, ou à la fin du combat. À la mort de l'adversaire, aucun autre ennemi ne rentre en duel.",
        MoveTargetCategory_OneEnemy,
        ZerachielPassive1Effect,
        PassiveTriggerCategory_OnBattleStart);
}

// ------------------------------------------------------------------------------------------------

void ZerachielPassive2Effect(std::vector<BattleCharacter *> Field)
{
    float HPLossPercentage = 0.1f;
    float UltimateChargeGained = 0.3f;
    float AttackIncreaseNotch = 0.1f;

    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i]->CheckIfAffected("DuelWithZerachiel"))
        {
            if (Field[i]->GetLastDamageReceived() >= HPLossPercentage * Field[i]->GetMaxHP())
            {
                Field[i]->GetStatus("DuelWithZerachiel")->GetLinkedCharacter()->ChangeStat(CharacterStat_Atk, AttackIncreaseNotch);
                Field[i]->GetStatus("DuelWithZerachiel")->GetLinkedCharacter()->AddToUltimateBar((int)100 * UltimateChargeGained);
            }
        }
    }
}
BattleMovePassive *GetZerachielPassive2(void)
{
    return new BattleMovePassive(
        "L'amour du travail bien fait",
        "À chaque fois qu'un ennemi en duel avec Zerachiel perd M% de ses PV maximums, Zerachiel récupère N% de charge d'ultime et augmente de P% son attaque.",
        MoveTargetCategory_OneEnemy,
        ZerachielPassive2Effect,
        PassiveTriggerCategory_OnDamageDealtToEnemy);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

ZerachielUnit::ZerachielUnit(bool isFriendly)
{
    int MaxHP = 100;
    int HP = MaxHP;
    int Atk = 5;
    int Speed = 5;
    int Def = 5;

    this->name = "Zerachiel";
    this->Type = CharacterType_DPS;
    this->Element = BattleElement_Light;
    this->isFriendly = isFriendly;
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
    this->BaseMove = GetZerachielBaseMove();
    this->Move1 = GetZerachielMove1();
    this->Move2 = GetZerachielMove2();
    this->Move3 = GetNullActiveMove();
    this->Ultimate = GetZerachielUltimate();
    this->Passive1 = GetZerachielPassive1();
    this->Passive2 = GetZerachielPassive2();

    std::vector<BattleStatus *> affectedStatus;
    this->AffectedStatus = affectedStatus;

    this->SkillBar = 0;
    this->UltimateBar = 0;

    GeneralHudInit("game/assets/images/ui/faded_bg.png");

    // Personalized HUD elements //

    // UI & Buttons //
    std::vector<BattleButton *> buttons = std::vector<BattleButton *>();
    buttons.push_back(
        new BattleButton("game/assets/images/characters/zerachiel/basic.png",
                         "game/assets/images/ui/light_button_bg.png",
                         WIDTH - 10, HEIGHT - 10, SDLK_a));
    buttons.push_back(new BattleButton(
        "game/assets/images/characters/zerachiel/skill1.png",
        "game/assets/images/ui/light_button_bg.png",
        WIDTH - 35 - buttons[0]->GetWidth(), HEIGHT - 10, SDLK_e));
    buttons.push_back(new BattleButton(
        "game/assets/images/characters/zerachiel/skill2.png",
        "game/assets/images/ui/light_button_bg.png", WIDTH - 10,
        HEIGHT - 33 - buttons[0]->GetHeight(), SDLK_f));
    buttons.push_back(
        new UltimateButton("game/assets/images/characters/zerachiel/ult.png",
                           "game/assets/images/ui/light_button_bg.png",
                           WIDTH - 35 - buttons[0]->GetWidth(),
                           HEIGHT - 33 - buttons[0]->GetHeight(), SDLK_r));
    this->BattleButtons = buttons;
}
