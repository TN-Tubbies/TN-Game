#include "player.hpp"

Player::Player(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType)
    : Entity(x, y, speed, sprite_path, SheetType)
{
    this->CurrentMap = nullptr;
}

// ------------------------------------------------------------------------------------------------

void Player::MoveTo(int mouse_x, int mouse_y)
{
    std::array<int, 2> TargettedTile = this->CurrentMap->GetTile(mouse_x, mouse_y);
    std::array<int, 2> MoveVector = {TargettedTile[0] - this->GetX(), TargettedTile[1] - this->GetY()};

    if (MoveVector[0] != 0 || MoveVector[1] != 0)
    {
        this->angle = std::tan((float)MoveVector[1] / MoveVector[0]);
        this->IsWalking = true;

        // Normalize the direction vector
        float vector_length = (float)sqrt(MoveVector[0] ^ 2 + MoveVector[1] ^ 2);
        MoveVector[0] /= vector_length;
        MoveVector[1] /= vector_length;

        this->x += (int)MoveVector[0] * this->Speed;
        this->y += (int)MoveVector[1] * this->Speed;

        this->CurrentMap->MoveMap(this->x, this->y);
    }
    else if (MoveVector[0] == 0 && MoveVector[1] == 0)
    {
        this->IsWalking = false;
    }
    this->UpdateSprite();
}

// ------------------------------------------------------------------------------------------------