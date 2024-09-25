#include "battle_system.h"

// ------------------------------------------------------------------------------------------------
// UTILITY FUNCTION -------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

bool compare_vectors_from_id(std::vector<BattleCharacter> v1, std::vector<BattleCharacter> v2, unsigned int id){
    if (v1.size()!= v2.size()){ return false; }     // Vectors have different sizes
    else if (v1.size() <= id){ return false; }      // Index is out of range
    else{
        bool res = true;
        for (unsigned int i = id; i < v1.size(); i++){
            if (v1[i] != v2[i]){ res = false; break; }
        }
        return res;
    }
}

// ------------------------------------------------------------------------------------------------
// CONST & DESTR ----------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

Battle_System *StartBattle(std::vector<BattleCharacter> playableCharacters, std::vector<BattleCharacter> enemyCharacters, int MaxTurnCount)
{
    Battle_System *NewBattle = (Battle_System *)malloc(sizeof(Battle_System));
    NewBattle->playableCharacters = playableCharacters;
    NewBattle->enemyCharacters = enemyCharacters;
    NewBattle->currentTurn = 0;
    NewBattle->maxTurnCount = MaxTurnCount;
    NewBattle->currentCharacterIndex = 100;     // This can't be less than the maximum amount of characters
    NewBattle->isBattleOver = false;
    NewBattle->currentState = BattleState_Starting;

    std::vector<BattleCharacter> merged;
    for (unsigned int i = 0; i < playableCharacters.size();i++){merged.push_back(playableCharacters[i]);}
    for (unsigned int i = 0; i < enemyCharacters.size();i++){merged.push_back(enemyCharacters[i]);}

    NewBattle->currentCharacterOrder = merged;
    NewBattle->battlefield = merged;

    if (DEBUG_MODE){ std::clog << "BattleDebug: a battle has been successfully launched." << std::endl; }

    return NewBattle;
}

void DestroyBattle(Battle_System *Battle)
{
    // TODO: Adding logs to the log file?

    free(Battle);
}

// ------------------------------------------------------------------------------------------------
// SYSTEM -----------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void RunTurn(Battle_System *CurrentBattle)
{
    BattleCharacter currentCharacter = CurrentBattle->currentCharacterOrder[CurrentBattle->currentCharacterIndex];
    if (DEBUG_MODE) { std::clog << "BattleDebug: " << currentCharacter.GetName() << " is taking a turn." << std::endl; }

    if (currentCharacter.IsFriendly()){
        // User turn code here

        // Player choose action code
    } else {
        // Enemy turn code here
        // TODO: Implement enemy AI turn logic
    }
}

void RunBattleManager(Battle_System *CurrentBattle){
    if (DEBUG_MODE){ std::clog << "BattleDebug: battle manager started." << std::endl; }

    switch (CurrentBattle->currentState){
        case BattleState_Starting:
            CurrentBattle->currentState = BattleState_TurnStart;
            break;
        case BattleState_TurnStart:
            CurrentBattle->currentTurn++;
            if (CurrentBattle->currentTurn >= CurrentBattle->maxTurnCount){
                if (DEBUG_MODE){ std::clog << "BattleDebug: battle ended after " << CurrentBattle->currentTurn << " turns (maximum exceeded)." << std::endl; }
                CurrentBattle->isBattleOver = true;
                CurrentBattle->currentState = BattleState_TurnEnd;
                break;
            } else {
                CurrentBattle->currentCharacterOrder = SortCharactersWRTStat(CurrentBattle->currentCharacterOrder);
                CurrentBattle->currentCharacterIndex = 0;
                CurrentBattle->currentState = BattleState_InATurn;
                break;
            }
        case BattleState_InATurn:
            CurrentBattle->currentCharacterIndex++;
            if (CurrentBattle->currentCharacterIndex >= CurrentBattle->currentCharacterOrder.size()){
                CurrentBattle->currentState = BattleState_TurnEnd;
                break;
            } else {
                RunTurn(CurrentBattle);
                break;
            }
        case BattleState_TurnEnd:
            if (CurrentBattle->isBattleOver){
                CurrentBattle->currentState = BattleState_Ending;
                break;
            } else {
                CurrentBattle->currentState = BattleState_TurnStart;
                break;
            }
        case BattleState_Ending:
            // EndBattle(CurrentBattle);
            break;
    }
}
