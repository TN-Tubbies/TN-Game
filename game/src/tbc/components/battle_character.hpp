#ifndef BATTLE_CHARACTER_HPP
#define BATTLE_CHARACTER_HPP

#include "../battle_declarations.hpp"
#include "../battle_enumerators.hpp"
#include "../../static/renderer.hpp"
#include "../../static/ttf.hpp"
#include "battle_status.hpp"
#include "battle_move.hpp"

#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Classes:
// Débloque des équipements particuliers

class BattleCharacter
{
protected:
    std::string name;
    enum CharacterType Type;
    enum BattleElement Element;

    int HP;
    int MaxHP;
    int BaseAtk;
    int BaseSpeed;
    int BaseDef;

    int CurrentAtk;
    int AtkChange;
    int CurrentSpeed;
    int SpeedChange;
    int CurrentDef;
    int DefChange;
    int LastDamageReceived;

    bool isFriendly;

    std::vector<BattleStatus *> AffectedStatus;

    int SkillBar;
    int UltimateBar;

    SDL_Texture *HudBG;
    SDL_Texture *DisplayedName;
    int DisplayedNameWidth;
    int DisplayedNameHeight;

public:
    BattleMove *BaseMove;
    BattleMove *Move1;
    BattleMove *Move2;
    BattleMove *Move3;
    BattleMove *Ultimate;
    BattleMove *Passive1;
    BattleMove *Passive2;

    // Construct
    BattleCharacter() {};

    // Destruct
    ~BattleCharacter();

    // Operators
    bool operator==(BattleCharacter &other) const;
    bool operator!=(BattleCharacter &other) const;

    // Getters
    std::string GetName();
    enum CharacterType GetType();
    enum BattleElement GetElement();
    int GetHP();
    int GetMaxHP();
    int GetBaseAtk();
    int GetBaseSpeed();
    int GetBaseDef();
    int GetBaseStat(enum CharacterStat stat);
    int GetCurrentStat(enum CharacterStat stat);
    bool IsFriendly();
    int GetLastDamageReceived();

    void TakeDamage(int damage, enum BattleElement IncomingElement);
    float GetElementReactionCoefficient(enum BattleElement IncomingElement);

    int GetChangeStat(enum CharacterStat stat);
    void ChangeStat(enum CharacterStat stat, int notch);

    void AddStatus(BattleStatus *status);
    BattleStatus *GetStatus(std::string statusName);
    bool CheckIfAffected(std::string statusName);
    void RemoveInactiveStatus();
    void RemoveStatus(std::string statusName);

    void AddToSkillBar(int adding);
    void AddToUltimateBar(int adding);

    void DrawHud(int x, int y);
};

#endif