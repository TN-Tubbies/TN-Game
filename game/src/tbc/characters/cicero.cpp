#include "cicero.hpp"

void CiceroBaseMoveEffect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int HPConsumedPercentage = 0;

    Self->TakeDamage(Self, HPConsumedPercentage);

    std::vector<int> enemyIDs;
    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i]->IsFriendly() != Self->IsFriendly() && Field[i]->GetHP() > 0)
        {
            enemyIDs.push_back(i);
        }
    }

    // Preparing for random value generation
    std::random_device rd;
    std::uniform_int_distribution<> distribution(0, enemyIDs.size() - 1);
    std::mt19937 gen1(rd());
    int randomID = distribution(gen1);
    Field[TargetID[randomID]]->TakeDamage(Self, -HPConsumedPercentage);
}
BattleMoveActive *GetCiceroBaseMove(void)
{
    return new BattleMoveActive(
        "J'augmente la mise !",
        "Restaure M% de la BS. Consomme N% de ses PV, attaque un ennemi aléatoire de la valeur des PV perdus (ignore tout calcul).",
        BattleElement_Dark,
        MoveTargetCategory_AllEnemies,
        CiceroBaseMoveEffect,
        -50,
        true,
        false);
}

// ------------------------------------------------------------------------------------------------

void CiceroMove1Effect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int Damage = 0;
    int SpeedIncreaseNotch = 0;

    Field[TargetID[0]]->TakeDamage(Self, Damage, BattleElement_Dark);
    Self->ChangeStat(CharacterStat_Speed, SpeedIncreaseNotch);
}
BattleMoveActive *GetCiceroMove1(void)
{
    return new BattleMoveActive(
        "On fait 50/50 ?",
        "Consomme M% de la BS. Inflige N% de dégâts à un ennemi et augmente de O% sa vitesse.",
        BattleElement_Dark,
        MoveTargetCategory_OneEnemy,
        CiceroMove1Effect,
        15,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void CiceroMove2Effect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    int StatIncreaseNotch = 0;
    int DefenseDecreaseNotch = 0;

    Self->ChangeStat(CharacterStat_Atk, StatIncreaseNotch);
    Self->ChangeStat(CharacterStat_Speed, StatIncreaseNotch);
    Self->ChangeStat(CharacterStat_Def, DefenseDecreaseNotch);
}
BattleMoveActive *GetCiceroMove2(void)
{
    return new BattleMoveActive(
        "Un UTG professionnel",
        "Consomme M% de la BS. Augmente de N% son attaque et sa vitesse, mais réduit de O% sa défense.",
        BattleElement_Dark,
        MoveTargetCategory_Self,
        CiceroMove2Effect,
        15,
        false,
        false);
}

// ------------------------------------------------------------------------------------------------

void CiceroUltimateEffect(BattleCharacter *Self, std::vector<int> TargetID, std::vector<BattleCharacter *> Field)
{
    Self->AddStatus(new Status_CiceroAllIn());
}
BattleMoveActive *GetCiceroUltimate(void)
{
    return new BattleMoveActive(
        "Quand le dealer est All'In !",
        "Cicero est All'In : si la prochaine attaque qu'il reçoit réduit ses PV à 0, les PV du lanceur de l'attaque passent également à 0. L'attaque n'inflige que M dégâts au maximum.",
        BattleElement_Dark,
        MoveTargetCategory_Self,
        CiceroUltimateEffect,
        0,
        false,
        true);
}

// ------------------------------------------------------------------------------------------------

void CiceroPassive1Effect(std::vector<BattleCharacter *> Field)
{
    int ReanimationChancePercentage = 0;

    int CiceroID = -1;
    for (unsigned int i = 0; i < Field.size(); i++)
    {
        if (Field[i]->GetName() == "Cicero")
        {
            CiceroID = i;
            break;
        }
    }

    // Preparing for random value generation
    std::random_device rd;
    std::uniform_int_distribution<> distribution(1, 100);
    std::mt19937 gen1(rd());
    int randomInt = distribution(gen1);
    if (Field[CiceroID]->GetHP() <= 0 && randomInt <= ReanimationChancePercentage)
    {
        Field[CiceroID]->SetHP(1);
    }
}
BattleMovePassive *GetCiceroPassive1(void)
{
    return new BattleMovePassive(
        "\"Order from the house\"",
        "À chaque attaque qui aurait dû faire descendre les PV de Cicero à 0, il a M% de chances d'être réanimé à 1PV. Sa capacité ultime est tout de même déclenchée. L'effet ne peut être déclenché qu'une seule fois par combat.",
        MoveTargetCategory_Self,
        CiceroPassive1Effect,
        PassiveTriggerCategory_OnDamageReceived);
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

CiceroUnit::CiceroUnit(bool isFriendly)
{
    int MaxHP = 100;
    int HP = MaxHP;
    int Atk = 5;
    int Speed = 5;
    int Def = 5;

    this->name = "Cicero";
    this->Type = CharacterType_DPS;
    this->Element = BattleElement_Dark;
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
    this->BaseMove = GetCiceroBaseMove();
    this->Move1 = GetCiceroMove1();
    this->Move2 = GetNullActiveMove();
    this->Move3 = GetNullActiveMove();
    this->Ultimate = GetCiceroUltimate();
    this->Passive1 = GetCiceroPassive1();
    this->Passive2 = GetNullPassiveMove();

    std::vector<BattleStatus *> affectedStatus;
    this->AffectedStatus = affectedStatus;

    this->SkillBar = 0;
    this->UltimateBar = 0;

    GeneralHudInit();

    // Personalized HUD elements //
    SDL_Texture *bg = IMG_LoadTexture(Get_Renderer(), "game/assets/images/ui/faded_bg.png");
    if (bg == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in ui_init, bg load: %s", SDL_GetError());
        exit(-1);
    }
    this->HudBG = bg;

    // UI & Buttons //
    std::vector<BattleButton *> buttons = std::vector<BattleButton *>();
    buttons.push_back(new BattleButton("BasicAtk", WIDTH - 10, HEIGHT - 10, SDLK_a));
    buttons.push_back(new BattleButton("Skill 1", WIDTH - 35 - buttons[0]->GetWidth(), HEIGHT - 10, SDLK_e));
    buttons.push_back(new BattleButton("Skill 2", WIDTH - 10, HEIGHT - 33 - buttons[0]->GetHeight(), SDLK_f));
    this->BattleButtons = buttons;
}
