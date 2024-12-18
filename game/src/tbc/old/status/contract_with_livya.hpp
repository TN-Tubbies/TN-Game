#ifndef CONTRACT_WITH_LIVYA_HPP
#define CONTRACT_WITH_LIVYA_HPP

#include "../components/battle_status.hpp"
#include "../components/battle_character.hpp"

class Status_ContractWithLivya : public BattleStatus
{
public:
    Status_ContractWithLivya(BattleCharacter *linkedLivya, bool AreTargetAndLauncherSameSide);

private:
    bool IsHelpful; // Indicates whether the launcher and target are on the same side
};

#endif