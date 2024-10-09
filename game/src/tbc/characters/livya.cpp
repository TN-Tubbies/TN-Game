#include "livya.hpp"

void LivyaBaseMoveEffect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int Damage = 0;

    for (unsigned int i = 0; i < TargetID.size(); i++)
    {
        Field[TargetID[i]]->TakeDamage(Self, Damage, BattleElement_Lightening);
    }
}
BattleMoveActive *GetLivyaBaseMove(void)
{
    return new BattleMoveActive(
        "Léger différent",
        "Restaure M% de la BS. Inflige N% de dégâts à tous les ennemis.",
        BattleElement_Lightening,
        MoveTargetCategory_AllEnemies,
        LivyaBaseMoveEffect,
        -15,
        true,
        false);
}

// ------------------------------------------------------------------------------------------------

void LivyaMove1Effect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int HPConsumedPercentage = 0;
    int healingAmount = 0;

    Self->TakeDamage(Self, HPConsumedPercentage);
    Field[TargetID[0]]->TakeDamage(Self, -(HPConsumedPercentage * healingAmount));
}
BattleMoveActive *GetLivyaMove1(void)
{
    return new BattleMoveActive(
        "Je te maintiendrai en vie",
        "Consomme M% de la BS. Consomme N% de ses PV maximums pour soigner la cible à hauteur de O fois les PV consommés.",
        BattleElement_Lightening,
        MoveTargetCategory_OneAlly,
        LivyaMove1Effect,
        20,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void LivyaMove2Effect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    // FIXME: Edit the status duration in its file (default 1)

    int HPHealPercentage = 0;

    Field[TargetID[0]]->TakeDamage(Self, -HPHealPercentage);
    Field[TargetID[0]]->AddStatus(new Status_ContractWithLivya(Self, Field[TargetID[0]]->IsFriendly() == Self->IsFriendly()));
}
BattleMoveActive *GetLivyaMove2(void)
{
    return new BattleMoveActive(
        "Nous avions un accord",
        "Consomme M% de la BS. Cible un ennemi. Lui restaure N% de ses PV maximums, mais durant les O prochains tours, tous les PV censés être récupérés par la cible sont récupérés par Livya.",
        BattleElement_Lightening,
        MoveTargetCategory_OneEnemy,
        LivyaMove2Effect,
        20,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void LivyaUltimateEffect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    // FIXME: Edit the status duration in its file (default 1)

    int AtkIncreaseNotch = 0;
    int SpeedIncreaseNotch = 0;

    Field[TargetID[0]]->ChangeStat(CharacterStat_Atk, AtkIncreaseNotch);
    Field[TargetID[0]]->ChangeStat(CharacterStat_Speed, SpeedIncreaseNotch);
    Field[TargetID[0]]->AddStatus(new Status_ContractWithLivya(Self, Field[TargetID[0]]->IsFriendly() == Self->IsFriendly()));
}
BattleMoveActive *GetLivyaUltimate(void)
{
    return new BattleMoveActive(
        "Ne me déçois pas",
        "Cible un allié. Augmente son attaque de M% de l'attaque d'origine de la cible, sa vitesse de N% de la vitesse d'origine de la cible pendant P tours, et lui octroie jusqu'à la fin du combat les effets de son passif.",
        BattleElement_Lightening,
        MoveTargetCategory_OneAlly,
        LivyaUltimateEffect,
        0,
        false,
        true);
}

// ------------------------------------------------------------------------------------------------

void LivyaPassive1Effect(std::vector<BattleCharacter *> Field)
{
    int HPStealPercentage = 0;
    int ShieldStealChancePercentage = 0;
    int UltimateStealChancePercentage = 0;
    int UltimateChargeStealPercentage = 0;

    // Preparing for random value generation
    std::random_device rd;
    std::uniform_int_distribution<> distribution(0, 100);

    int LivyaID = -1;
    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i]->GetName() == "Livya")
        {
            LivyaID = i;
            break;
        }
    }

    Field[LivyaID]->TakeDamage(Field[LivyaID], -(Field[LivyaID]->GetLastDamageDealt() * HPStealPercentage));

    // TODO: Shield system before implementing stealing shield
    std::mt19937 gen1(rd());
    int shieldRandomValue = distribution(gen1);
    if (shieldRandomValue <= ShieldStealChancePercentage)
    {
    }

    std::mt19937 gen2(rd());
    int ultimateRandomValue = distribution(gen2);
    if (ultimateRandomValue <= UltimateStealChancePercentage)
    {
        Field[LivyaID]->AddToUltimateBar(UltimateChargeStealPercentage);
        Field[LivyaID]->GetLastTarget()->AddToUltimateBar(-UltimateChargeStealPercentage);
    }
}
BattleMovePassive *GetLivyaPassive1(void)
{
    return new BattleMovePassive(
        "Tu as quelque chose qui m'intéresse",
        "Les attaques de Livya volent M% des PV de la cible, ont N% de chances de voler une charge de bouclier et P% de chances de voler Q% de charge de compétence ultime.",
        MoveTargetCategory_OneEnemy,
        LivyaPassive1Effect,
        PassiveTriggerCategory_OnDamageDealtToEnemy);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

LivyaUnit::LivyaUnit(bool isFriendly)
{
    int MaxHP = 100;
    int HP = MaxHP;
    int Atk = 5;
    int Speed = 5;
    int Def = 5;

    this->name = "Livya";
    this->Type = CharacterType_Support;
    this->Element = BattleElement_Lightening;
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
    this->BaseMove = GetLivyaBaseMove();
    this->Move1 = GetLivyaMove1();
    this->Move2 = GetLivyaMove2();
    this->Move3 = GetNullActiveMove();
    this->Ultimate = GetLivyaUltimate();
    this->Passive1 = GetLivyaPassive1();
    this->Passive2 = GetNullPassiveMove();

    std::vector<BattleStatus *> affectedStatus;
    this->AffectedStatus = affectedStatus;

    this->SkillBar = 0;
    this->UltimateBar = 0;

    this->battle_sprite = new BattleSprite("game/assets/images/characters/zerachiel/battle_sprite.png", 0, 0);

    GeneralHudInit("game/assets/images/ui/faded_bg_lightning_enemy.png");

    // Personalized HUD elements //

    // UI & Buttons //
    std::vector<BattleButton *> buttons = std::vector<BattleButton *>();
    buttons.push_back(
        new BattleButton("game/assets/images/characters/zerachiel/basic.png",
                         "game/assets/images/ui/lightning_button_bg.png",
                         WIDTH - 10, HEIGHT - 10, SDLK_a,
                         GetLivyaBaseMove()));
    buttons.push_back(new BattleButton(
        "game/assets/images/characters/zerachiel/skill1.png",
        "game/assets/images/ui/lightning_button_bg.png",
        WIDTH - 35 - buttons[0]->GetWidth(), HEIGHT - 10, SDLK_e,
        GetLivyaMove1()));
    buttons.push_back(new BattleButton(
        "game/assets/images/characters/zerachiel/skill2.png",
        "game/assets/images/ui/lightning_button_bg.png", WIDTH - 10,
        HEIGHT - 33 - buttons[0]->GetHeight(), SDLK_f,
        GetLivyaMove2()));
    buttons.push_back(
        new UltimateButton("game/assets/images/characters/zerachiel/ult.png",
                           "game/assets/images/ui/lightning_button_bg.png",
                           WIDTH - 35 - buttons[0]->GetWidth(),
                           HEIGHT - 33 - buttons[0]->GetHeight(), SDLK_r,
                           GetLivyaUltimate()));
    this->BattleButtons = buttons;
}
