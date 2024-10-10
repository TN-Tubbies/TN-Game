#include "player.hpp"

Player::Player(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType)
    : Entity("Player", x, y, speed, sprite_path, SheetType)
{
    this->CurrentMap = nullptr;
}

Player::~Player()
{
    if (this->Sprites != nullptr)
    {
        SDL_DestroyTexture(this->Sprites);
        this->Sprites = nullptr;
    }

    if (this->SpriteRect != nullptr)
    {
        for (int i = 0; i < 4; i++)
        {
            free(this->SpriteRect[i]);
        }
        free(this->SpriteRect);
    }
}

// ------------------------------------------------------------------------------------------------

void Player::MoveTo(int mouse_x, int mouse_y)
{
    std::array<int, 2> TargettedTile = this->CurrentMap->GetTile(mouse_x, mouse_y);
    std::array<float, 2> MoveVector = {(float)TargettedTile[0] - this->x, (float)TargettedTile[1] - this->y};
    std::clog << "Player previously at (" << this->x << ", " << this->y << ")" << std::endl;

    if (MoveVector[0] != 0 || MoveVector[1] != 0)
    {
        this->angle = std::tan((float)MoveVector[1] / MoveVector[0]);
        this->IsWalking = true;

        // Normalize the direction vector
        float vector_length = (float)sqrt(pow(MoveVector[0], 2) + pow(MoveVector[1], 2));
        MoveVector[0] /= vector_length;
        MoveVector[1] /= vector_length;

        this->x += (int)MoveVector[0] * this->Speed;
        this->y += (int)MoveVector[1] * this->Speed;

        if (DEBUG_MODE)
        {
            std::clog << "Mouse clicked at " << mouse_x << "," << mouse_y << std::endl;
            std::clog << "TargettedTile: " << TargettedTile[0] << ", " << TargettedTile[1] << std::endl;
            std::clog << "Player moved to (" << this->x << ", " << this->y << ")" << std::endl;
            std::clog << "Angle: " << this->angle << ", X Notch: " << (int)MoveVector[0] * this->Speed << ", Y Notch: " << (int)MoveVector[0] * this->Speed << std::endl;
            std::clog << "Moved by " << MoveVector[0] * vector_length << ", " << MoveVector[1] * vector_length << std::endl;
        }

        // this->CurrentMap->MoveMap((int)std::abs(MoveVector[0]) * this->Speed, (int)std::abs(MoveVector[0]) * this->Speed);
    }
    else if (MoveVector[0] == 0 && MoveVector[1] == 0)
    {
        this->IsWalking = false;
    }
    this->UpdateSprite();
}

// ------------------------------------------------------------------------------------------------