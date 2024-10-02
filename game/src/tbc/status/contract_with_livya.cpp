#include "contract_with_livya.hpp"

Status_ContractWithLivya::Status_ContractWithLivya(BattleCharacter *linkedLivya, bool AreTargetAndLauncherSameSide)
{
    statusName = "ContractWithLivya";
    linkedCharacter = linkedLivya;
    removeAfterBattle = true;
    isActive = true;
    trigger = PassiveTriggerCategory_None;
    IsHelpful = AreTargetAndLauncherSameSide;

    if (AreTargetAndLauncherSameSide) // Launcher and target are on the same side
    {
        hasTimer = false;
        timerDuration = -1;
    }
    else // Launcher and target are not on the same side
    {
        hasTimer = true;
        timerDuration = 1;
    }
}