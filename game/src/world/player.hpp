#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cmath>

#include "entity.hpp"
#include "map.hpp"

class Player : public Entity
{
private:
    Map *CurrentMap;

public:
    Player(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType);
    ~Player();

    Map *GetCurrentMap() { return CurrentMap; }
    bool GetIsWalking() const { return IsWalking; }
    void SetCurrentMap(Map *map) { this->CurrentMap = map; }
    void SetIsWalking(bool is_walking) { this->IsWalking = is_walking; }

    void MoveTo(int mouse_x, int mouse_y);
};

#endif