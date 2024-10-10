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
    // TODO: Implement the collision detection with this line:
    // std::array<int, 2> TargettedTile = this->CurrentMap->GetTile(mouse_x, mouse_y);

    std::array<float, 2> MoveVector = {(float)mouse_x - this->x, (float)mouse_y - this->y};
    std::clog << "Player previously at (" << this->x << ", " << this->y << ")" << std::endl;

    if (MoveVector[0] != 0 || MoveVector[1] != 0)
    {
        if (std::abs(MoveVector[0]) >= this->Speed || std::abs(MoveVector[1]) >= this->Speed)
        {
            this->angle = std::atan((float)MoveVector[1] / MoveVector[0]);

            // Normalize the direction vector
            float vector_length = (float)sqrt(pow(MoveVector[0], 2) + pow(MoveVector[1], 2));
            MoveVector[0] /= vector_length;
            MoveVector[1] /= vector_length;

            this->x += std::floor(MoveVector[0] * this->Speed);
            this->y += std::floor(MoveVector[1] * this->Speed);

            if (DEBUG_MODE)
            {
                std::clog << "Mouse clicked at " << mouse_x << "," << mouse_y << std::endl;
                // std::clog << "TargettedTile: " << TargettedTile[0] << ", " << TargettedTile[1] << std::endl;
                std::clog << "Player moved to (" << this->x << ", " << this->y << ")" << std::endl;
                std::clog << "Angle: " << this->angle << ", X Notch: " << std::floor(MoveVector[0] * this->Speed) << ", Y Notch: " << std::floor(MoveVector[0] * this->Speed) << std::endl;

                float new_vector_length = (float)sqrt(pow(MoveVector[0], 2) + pow(MoveVector[1], 2));
                std::clog << "MoveVector " << MoveVector[0] * vector_length << ", " << MoveVector[1] * vector_length << " with length:" << new_vector_length << std::endl;
            }
            // this->CurrentMap->MoveMap((int)std::abs(MoveVector[0]) * this->Speed, (int)std::abs(MoveVector[0]) * this->Speed);
        }
    }
    this->UpdateSprite();
}

// ------------------------------------------------------------------------------------------------