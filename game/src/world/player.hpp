#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cmath>

#include "../static/delta_time.hpp"

#include "entity.hpp"
#include "map.hpp"

class Player : public Entity
{
private:
    std::array<int, 2> move_notches;
    int DisplayedX;
    int DisplayedY;
    Map *CurrentMap;

public:
    Player(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType);
    ~Player();

    std::array<int, 2> GetMoveNotches() { return move_notches; }
    Map *GetCurrentMap() { return CurrentMap; }
    bool GetIsWalking() const { return IsWalking; }

    void SetMoveNotches(std::array<int, 2> move_notches) { this->move_notches = move_notches; }
    void SetCurrentMap(Map *map) { this->CurrentMap = map; }
    void SetIsWalking(bool is_walking) { this->IsWalking = is_walking; }

    void Move();

    void Render();
};

#endif