#include "battle_character.hpp"

// ------------------------------------------------------------------------------------------------

BattleCharacter::BattleCharacter()
{
    this->currentBattleButton = NULL;
    this->isTarget = none;
}

BattleCharacter::~BattleCharacter()
{
    // Delete all statuses
    for (unsigned int i = 0; i < AffectedStatus.size(); i++)
    {
        delete AffectedStatus[i];
    }

    // Delete moves
    delete BaseMove;
    delete Move1;
    delete Move2;
    delete Move3;
    delete Ultimate;
    delete Passive1;
    delete Passive2;

    // Delete hud-related textures
    if (HudBG != NULL)
    {
        SDL_DestroyTexture(HudBG);
    }
    if (DisplayedName != NULL)
    {
        SDL_DestroyTexture(DisplayedName);
    }
    for (unsigned int i = 0; i < BattleButtons.size(); i++)
    {
        delete BattleButtons[i];
    }
}

// ------------------------------------------------------------------------------------------------

bool BattleCharacter::operator==(BattleCharacter &other) const
{
    return (name == other.name && Type == other.Type && Element == other.Element && isFriendly == other.isFriendly && HP == other.HP && MaxHP == other.MaxHP && BaseAtk == other.BaseAtk && BaseSpeed == other.BaseSpeed && BaseDef == other.BaseDef && (*BaseMove).getName() == (*other.BaseMove).getName() && (*Move1).getName() == (*other.Move1).getName() && (*Move2).getName() == (*other.Move2).getName() && (*Move3).getName() == (*other.Move3).getName() && (*Ultimate).getName() == (*other.Ultimate).getName() && (*Passive1).getName() == (*other.Passive1).getName() && (*Passive2).getName() == (*other.Passive2).getName());
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

void BattleCharacter::AddToHP(int quantity)
{
    if (HP + quantity > MaxHP)
    {
        HP = MaxHP;
    }
    else if (HP + quantity < 0)
    {
        HP = 0;
    }
    else
    {
        HP += quantity;
    }
    std::string hp_string = std::to_string(HP);
    SDL_Surface *hp_surf;
    if (HP < MaxHP / 4)
    {
        SDL_Color color = {255, 0, 0, 255};
        hp_surf = TTF_RenderUTF8_Blended(Get_Roboto(10), hp_string.c_str(), color);
    }
    else
    {
        SDL_Color color = {255, 255, 255, 255};
        hp_surf = TTF_RenderUTF8_Blended(Get_Roboto(10), hp_string.c_str(), color);
    }
    this->DisplayedHPHeight = hp_surf->h;
    this->DisplayedHPWidth = hp_surf->w;
    this->DisplayedHP = SDL_CreateTextureFromSurface(Get_Renderer(), hp_surf);
    SDL_FreeSurface(hp_surf);
}

void BattleCharacter::TakeDamage(BattleCharacter *launcher, int damage)
{
    launcher->SetLastDamageDealt(damage);
    launcher->SetLastTarget(this);
    AddToHP(-damage);
}
void BattleCharacter::TakeDamage(BattleCharacter *launcher, int damage, enum BattleElement IncomingElement)
{
    // FIXME: Implement atk and defense influences
    int readDamage = (int)damage * GetElementReactionCoefficient(IncomingElement);
    launcher->SetLastDamageDealt(damage);
    launcher->SetLastTarget(this);
    AddToHP(-readDamage);
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

void BattleCharacter::AddStatus(BattleStatus *status) { AffectedStatus.push_back(status); }
BattleStatus *BattleCharacter::GetStatus(std::string statusName)
{
    for (unsigned int i = 0; i < AffectedStatus.size(); i++)
    {
        if (AffectedStatus[i]->GetName() == statusName)
        {
            return AffectedStatus[i];
        }
    }
    return new BattleStatus(); // Return empty status if not found
}
bool BattleCharacter::CheckIfAffected(std::string statusName)
{
    bool res = false;

    for (unsigned int i = 0; i < AffectedStatus.size(); i++)
    {
        if (AffectedStatus[i]->GetName() == statusName)
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
        if (!AffectedStatus[i]->IsActive())
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
        if (AffectedStatus[i]->GetName() == statusName)
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

void BattleCharacter::GeneralHudInit(std::string bg_path)
{
    // HUD //
    this->HudWidth = 256;
    this->HudHeight = 128;

    SDL_Texture *bg = IMG_LoadTexture(Get_Renderer(), bg_path.c_str());
    if (bg == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in ui_init, bg load: %s", SDL_GetError());
        exit(-1);
    }
    this->HudBG = bg;

    SDL_Surface *name_surf;
    SDL_Color color;
    if (isFriendly)
    {
        color = {255, 255, 255, 255};
        name_surf = TTF_RenderUTF8_Solid(Get_Jersey(32), this->name.c_str(), color);
    }
    else
    {
        color = {255, 0, 0, 255};
        name_surf = TTF_RenderUTF8_Solid(Get_Jersey(32), this->name.c_str(), color);
    }
    if (name_surf == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in BattleCharacter::GeneralHudInit for %s, name_surf: %s", this->name.c_str(), SDL_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in BattleCharacter::GeneralHudInit for %s, name_surf: %s", this->name.c_str(), SDL_GetError());
        exit(-1);
    }
    this->DisplayedNameHeight = name_surf->h;
    this->DisplayedNameWidth = name_surf->w;
    this->DisplayedName = SDL_CreateTextureFromSurface(Get_Renderer(), name_surf);
    if (this->DisplayedName == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in BattleCharacter::GeneralHudInit, DisplayedName: %s", SDL_GetError());
        exit(-1);
    }
    SDL_FreeSurface(name_surf);

    std::string hp_string = std::to_string(HP);
    color = {255, 255, 255, 255};
    SDL_Surface *hp_surf = TTF_RenderUTF8_Blended(Get_Roboto(14), hp_string.c_str(), color);
    if (hp_surf == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in BattleCharacter::GeneralHudInit, hp_surf: %s", SDL_GetError());
        exit(-1);
    }
    this->DisplayedHPHeight = hp_surf->h;
    this->DisplayedHPWidth = hp_surf->w;
    this->DisplayedHP = SDL_CreateTextureFromSurface(Get_Renderer(), hp_surf);
    if (this->DisplayedHP == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in BattleCharacter::GeneralHudInit, DisplayedHP: %s", SDL_GetError());
        exit(-1);
    }
    SDL_FreeSurface(hp_surf);

    std::string max_hp_string = " / " + std::to_string(MaxHP);
    color = {255, 255, 255, 255};
    SDL_Surface *max_hp_surf = TTF_RenderUTF8_Blended(Get_Roboto(14), max_hp_string.c_str(), color);
    if (max_hp_surf == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in BattleCharacter::GeneralHudInit, max_hp_surf: %s", SDL_GetError());
        exit(-1);
    }
    this->DisplayedMaxHPHeight = max_hp_surf->h;
    this->DisplayedMaxHPWidth = max_hp_surf->w;
    this->DisplayedMaxHP = SDL_CreateTextureFromSurface(Get_Renderer(), max_hp_surf);
    if (this->DisplayedMaxHP == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in BattleCharacter::GeneralHudInit, DisplayedMaxHP: %s", SDL_GetError());
        exit(-1);
    }
    SDL_FreeSurface(max_hp_surf);
}

void BattleCharacter::RenderHud(int x, int y)
{
    int y_offset = 5;
    int bar_thickness = 12;
    int x_offset = 64;

    // BG //
    SDL_Rect bg_rect = {x, y, HudWidth, HudHeight};
    SDL_RenderCopy(Get_Renderer(), HudBG, NULL, &bg_rect);

    // Name //
    int center_name_x = x + HudWidth / 2 - DisplayedNameWidth / 2;
    SDL_Rect name_rect = {center_name_x, y + y_offset, DisplayedNameWidth, DisplayedNameHeight};
    SDL_RenderCopy(Get_Renderer(), DisplayedName, NULL, &name_rect);
    y_offset += DisplayedNameHeight + 10;

    // HP //
    rectangleColor(Get_Renderer(), x + x_offset + 5, y + y_offset, x + HudWidth - x_offset - 5, y + y_offset + bar_thickness, 0xFFFFFFFF);
    if (this->HP <= this->MaxHP / 4)
    {
        boxColor(Get_Renderer(), x + x_offset + 7, y + y_offset + 2, x + 7 + (HudWidth - x_offset - 15) * this->HP / this->MaxHP, y + y_offset + bar_thickness - 3, 0xFF0000FF);
    }
    else
    {
        boxColor(Get_Renderer(), x + x_offset + 7, y + y_offset + 2, x + 7 + (HudWidth - x_offset - 15) * this->HP / this->MaxHP, y + y_offset + bar_thickness - 3, 0xFFFFFFFF);
    }
    y_offset += bar_thickness + 1;

    int center_hp_x = x + HudWidth / 2 - (DisplayedHPWidth + DisplayedMaxHPWidth) / 2;
    SDL_Rect hp_rect = {center_hp_x, y + y_offset, DisplayedHPWidth, DisplayedHPHeight};
    SDL_RenderCopy(Get_Renderer(), DisplayedHP, NULL, &hp_rect);

    int center_max_hp_x = center_hp_x + DisplayedHPWidth;
    SDL_Rect max_hp_rect = {center_max_hp_x, y + y_offset, DisplayedMaxHPWidth, DisplayedMaxHPHeight};
    SDL_RenderCopy(Get_Renderer(), DisplayedMaxHP, NULL, &max_hp_rect);

    y_offset += DisplayedHPHeight + 5;

    // Skill Bar //
    if (isFriendly)
    {
        rectangleColor(Get_Renderer(), x + x_offset - 30, y + HudHeight - 5, x + x_offset - 30 + bar_thickness, y + 10 + DisplayedNameHeight, 0xFFFFFFFF);
        int max_bar_height = y + 10 + DisplayedNameHeight + 2;
        int min_bar_height = y + HudHeight - 8;
        int bar_height = min_bar_height - (min_bar_height - max_bar_height) * SkillBar / 100;
        if (SkillBar > 0)
        {
            boxColor(Get_Renderer(), x + x_offset - 28, min_bar_height, x + x_offset - 28 + bar_thickness - 5, bar_height, 0xFFFFFFFF);
        }
        if (currentBattleButton)
        {
            if (currentBattleButton->GetMove()->getCost() > 0)
            {
                int cost_height = bar_height + (min_bar_height - max_bar_height) * currentBattleButton->GetMove()->getCost() / 100;
                boxRGBA(Get_Renderer(), x + x_offset - 28, bar_height, x + x_offset - 28 + bar_thickness - 5, cost_height, 255, 0, 0, 100);
            }
            if (currentBattleButton->GetMove()->getCost() < 0)
            {
                int cost_height = bar_height + (min_bar_height - max_bar_height) * currentBattleButton->GetMove()->getCost() / 100;
                boxRGBA(Get_Renderer(), x + x_offset - 28, bar_height, x + x_offset - 28 + bar_thickness - 5, cost_height, 0, 255, 0, 100);
            }
        }
    }
}

void BattleCharacter::RenderButtons()
{
    for (BattleButton *battleButton : BattleButtons)
    {
        if (currentBattleButton == battleButton)
        {
            battleButton->RenderHover();
        }
        if (dynamic_cast<UltimateButton *>(battleButton))
        {
            UltimateButton *ultimateButton = dynamic_cast<UltimateButton *>(battleButton);
            ultimateButton->Render(UltimateBar, buttonIsUsable(ultimateButton));
        }
        else
        {
            battleButton->Render(buttonIsUsable(battleButton));
        }
    }
}

void BattleCharacter::RenderSprite()
{
    battle_sprite->Render(isTarget);
}

bool BattleCharacter::buttonIsUsable(BattleButton *button)
{
    if (button->GetMove()->getCost() > 0)
    {
        if (SkillBar >= button->GetMove()->getCost())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (button->GetMove()->IsUltimate() && UltimateBar == 100)
    {
        return true;
    }
    else if (button->GetMove()->getCost() <= 0 && !button->GetMove()->IsUltimate())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void BattleCharacter::HandleKeyUp(SDL_Event event, DisplayState *displayState)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
        *displayState = DISPLAY_STATE_MENU;
        break;
    default:
        if (currentBattleButton)
        {
            if (currentBattleButton)
            {
                if (currentBattleButton->GetKey() == event.key.keysym.sym)
                {
                    std::cout << "Button Pressed: " << currentBattleButton->GetMove()->getName().c_str() << std::endl;
                }
                else
                {
                    for (unsigned int i = 0; i < BattleButtons.size(); i++)
                    {
                        if (BattleButtons[i]->GetKey() == event.key.keysym.sym)
                        {
                            if (buttonIsUsable(BattleButtons[i]))
                            {
                                currentBattleButton = BattleButtons[i];
                            }
                        }
                    }
                }
            }
            else
            {
                for (unsigned int i = 0; i < BattleButtons.size(); i++)
                {
                    for (unsigned int i = 0; i < BattleButtons.size(); i++)
                    {
                        if (BattleButtons[i]->GetKey() == event.key.keysym.sym)
                        {
                            currentBattleButton = BattleButtons[i];
                        }
                    }
                    for (unsigned int i = 0; i < BattleButtons.size(); i++)
                    {
                        if (BattleButtons[i]->GetKey() == event.key.keysym.sym)
                        {
                            currentBattleButton = BattleButtons[i];
                        }
                    }
                }
                break;
            }
        }
    }
}

bool isMouseHovering(int mouse_x, int mouse_y, BattleButton *button)
{
    return (mouse_x >= button->GetX() && mouse_x <= button->GetX() + button->GetWidth() && mouse_y >= button->GetY() && mouse_y <= button->GetY() + button->GetHeight());
}

void BattleCharacter::HandleMouseHover(SDL_Event event)
{
    int x = event.motion.x;
    int y = event.motion.y;
    for (unsigned int i = 0; i < BattleButtons.size(); i++)
        for (unsigned int i = 0; i < BattleButtons.size(); i++)
        {
            if (isMouseHovering(x, y, BattleButtons[i]))
            {
                if (buttonIsUsable(BattleButtons[i]))
                {
                    currentBattleButton = BattleButtons[i];
                }
            }
        }
}

void BattleCharacter::HandleMouseClick(SDL_Event event)
{
    int x = event.button.x;
    int y = event.button.y;
    for (unsigned int i = 0; i < BattleButtons.size(); i++)
        for (unsigned int i = 0; i < BattleButtons.size(); i++)
        {
            if (isMouseHovering(x, y, BattleButtons[i]))
                if (isMouseHovering(x, y, BattleButtons[i]))
                {
                    if (buttonIsUsable(BattleButtons[i]))
                    {
                        std::cout << "Button Pressed: " << BattleButtons[i]->GetMove()->getName().c_str() << std::endl;
                    }
                }
        }
}
