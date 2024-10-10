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
    void SetCurrentMap(Map *map) { this->CurrentMap = map; }

    void MoveTo(int delta_x, int delta_y);
};

#endif