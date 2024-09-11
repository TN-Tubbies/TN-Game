#include "battle_system.h"

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
    NewBattle->CurrentCharacter = NULL;
    NewBattle->isBattleOver = false;
    NewBattle->currentState = BattleState_Starting;
    NewBattle->currentTurnState = BattleTurnState_Starting;

    std::vector<BattleCharacter> merged(playableCharacters.size() + enemyCharacters.size());
    merge(playableCharacters.begin(), playableCharacters.end(), enemyCharacters.begin(), enemyCharacters.end(), merged.begin());
    NewBattle->currentCharacterOrder = merged;
    NewBattle->battlefield = merged;
    return NewBattle;
}

void DestroyBattle(Battle_System *Battle)
{
    free(Battle);
}

// ------------------------------------------------------------------------------------------------
// SYSTEM -----------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

void RunBattleAction(Battle_System *CurrentBattle)
{
    switch (CurrentBattle->currentState)
    {
    case BattleState_Starting:
        CurrentBattle->currentCharacterOrder = SortCharactersWRTStat(CurrentBattle->currentCharacterOrder);
        break;
    // case BattleState_Turn:
    //     RunTurn(CurrentBattle);
    //     break;
    case BattleState_End:
        // EndBattle(CurrentBattle);
        break;
    }
}

void HandleTurnSystem(Battle_System *CurrentBattle)
{
    switch (CurrentBattle->currentTurnState)
    {
    case BattleTurnState_Starting:
        // StartTurn(CurrentBattle);
        break;
        // case BattleTurnState_Turn:
        //     RunTurn(CurrentBattle);
        //     break;
        // case BattleTurnState_Ending:
        //     EndTurn(CurrentBattle);
        //     break;
    }
}
