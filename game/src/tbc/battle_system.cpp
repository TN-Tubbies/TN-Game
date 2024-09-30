#include "battle_system.hpp"

// ------------------------------------------------------------------------------------------------
// CONST & DESTR ----------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------

Battle_System *StartBattle(std::vector<BattleCharacter *> playableCharacters, std::vector<BattleCharacter *> enemyCharacters, int MaxTurnCount)
{
    Battle_System *NewBattle = (Battle_System *)malloc(sizeof(Battle_System));
    NewBattle->playableCharacters = playableCharacters;
    NewBattle->enemyCharacters = enemyCharacters;
    NewBattle->currentTurn = 0;
    NewBattle->maxTurnCount = MaxTurnCount;
    NewBattle->actionMadeAmount = 100; // This can't be less than the maximum amount of characters
    NewBattle->isBattleOver = false;
    NewBattle->currentState = BattleState_Starting;

    std::vector<BattleCharacter *> merged;
    for (unsigned int i = 0; i < playableCharacters.size(); i++)
    {
        merged.push_back(playableCharacters[i]);
    }
    for (unsigned int i = 0; i < enemyCharacters.size(); i++)
    {
        merged.push_back(enemyCharacters[i]);
    }
    NewBattle->battlefield = merged;
    NewBattle->currentPriorityList = CreatePriorityList(merged);

    if (DEBUG_MODE)
    {
        std::clog << "BattleDebug: a battle has been successfully launched." << std::endl;
    }

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
    CurrentBattle->currentPriorityList = SortPriorityList(CurrentBattle->currentPriorityList);

    // Getting the first "active" character from the priority list
    PriorityEntity *currentEntity = CurrentBattle->currentPriorityList->head;
    while (currentEntity != NULL && currentEntity->hasMadeAction)
    {
        currentEntity = currentEntity->next;
    }
    if (currentEntity == NULL)
    {
        std::cerr << "BattleError: no character can move, but still in a turn." << std::endl;
        return;
    }
    else
    {
        BattleCharacter *currentCharacter = currentEntity->character;

        if (DEBUG_MODE)
        {
            std::clog << "BattleDebug: " << currentCharacter->GetName() << " is taking a turn." << std::endl;
        }

        if (currentCharacter->IsFriendly())
        {
            // User turn code here
            // TODO: Player choose action code
        }
        else
        {
            // Enemy turn code here
            // TODO: Implement enemy AI turn logic
        }

        currentEntity->hasMadeAction = true;
    }
}

void RunBattleManager(Battle_System *CurrentBattle)
{
    if (DEBUG_MODE)
    {
        std::clog << "BattleDebug: battle manager started." << std::endl;
    }

    switch (CurrentBattle->currentState)
    {
    case BattleState_Starting:
        CurrentBattle->currentState = BattleState_TurnStart;
        break;
    case BattleState_TurnStart:
        CurrentBattle->currentTurn++;
        if (CurrentBattle->currentTurn >= CurrentBattle->maxTurnCount)
        {
            if (DEBUG_MODE)
            {
                std::clog << "BattleDebug: battle ended after " << CurrentBattle->currentTurn << " turns (maximum exceeded)." << std::endl;
            }
            CurrentBattle->isBattleOver = true;
            CurrentBattle->currentState = BattleState_TurnEnd;
            break;
        }
        else
        {
            CurrentBattle->currentPriorityList = SortPriorityList(CurrentBattle->currentPriorityList);
            CurrentBattle->actionMadeAmount = 0;
            CurrentBattle->currentState = BattleState_InATurn;
            break;
        }
    case BattleState_InATurn:
        CurrentBattle->actionMadeAmount++;
        if (CurrentBattle->actionMadeAmount >= CurrentBattle->currentPriorityList->size)
        {
            CurrentBattle->currentState = BattleState_TurnEnd;
            break;
        }
        else
        {
            RunTurn(CurrentBattle);
            break;
        }
    case BattleState_TurnEnd:
        if (CurrentBattle->isBattleOver)
        {
            CurrentBattle->currentState = BattleState_Ending;
            break;
        }
        else
        {
            CurrentBattle->currentState = BattleState_TurnStart;
            break;
        }
    case BattleState_Ending:
        // EndBattle(CurrentBattle);
        break;
    }
}
