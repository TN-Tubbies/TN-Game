#include "player.hpp"

Player::Player(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType)
    : Entity("Player", x, y, speed, sprite_path, SheetType)
{
    this->CurrentMap = nullptr;

    SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];
    this->DisplayedX = std::floor(WIDTH / 2 - src.w / 2);
    this->DisplayedY = std::floor(HEIGHT / 2 - src.h / 2);
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
    // TODO: Implement the collision detection

    std::array<int, 2> TargettedTile = this->CurrentMap->GetTile(mouse_x, mouse_y);
    std::array<float, 2> MoveVector = {(float)(TargettedTile[0] - this->x), (float)(TargettedTile[1] - this->y)};

    if (DEBUG_MODE)
    {
        std::clog << "Player previously at (" << this->x << ", " << this->y << ")" << std::endl;
        std::clog << "Targetted Tile (" << TargettedTile[0] << ", " << TargettedTile[1] << ")" << std::endl;
        std::clog << "MoveVector (" << MoveVector[0] << ", " << MoveVector[1] << ")" << std::endl;
    }

    if (MoveVector[0] != 0 || MoveVector[1] != 0)
    {
        this->angle = std::atan((float)(MoveVector[1] / MoveVector[0]));

        // Calculating notches
        int x_notch = 0;
        if (std::abs(MoveVector[0] * TILE_SIZE) >= this->Speed)
        {
            x_notch = std::floor(this->Speed * copysign(1.0, MoveVector[0]));
            std::clog << "x_notch corresponds to speed" << std::endl;
        }
        else
        {
            x_notch = std::floor(MoveVector[0] * TILE_SIZE);
            std::clog << "x_notch corresponds to MoveVector" << std::endl;
        }
        int y_notch = 0;
        if (std::abs(MoveVector[1] * TILE_SIZE) >= this->Speed)
        {
            y_notch = std::floor(this->Speed * copysign(1.0, MoveVector[1]));
            std::clog << "y_notch corresponds to speed" << std::endl;
        }
        else
        {
            y_notch = std::floor(MoveVector[1] * TILE_SIZE);
            std::clog << "y_notch corresponds to MoveVector" << std::endl;
        }

        // Different prompts depending on the placement of the map
        if (this->CurrentMap->IsAtEdge())
        {
            std::clog << "Map edge detected. Player will move." << std::endl;

            this->DisplayedX += x_notch;
            this->DisplayedY += y_notch;

            SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];
            this->x = (int)std::floor(this->DisplayedX / TILE_SIZE);
            this->y = (int)std::floor((this->DisplayedY + (src.h - TILE_SIZE)) / TILE_SIZE);
        }
        else
        {
            std::clog << "Map edge  not detected." << std::endl;

            this->x = this->CurrentMap->GetTLTileXIndex() + (int)(std::floor(WIDTH / 2) * TILE_SIZE);
            this->y = this->CurrentMap->GetTLTileYIndex() + (int)(std::floor(HEIGHT / 2) * TILE_SIZE);

            SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];
            this->DisplayedX = std::floor(WIDTH / 2 - src.w / 2);
            this->DisplayedY = std::floor(HEIGHT / 2 - src.h / 2);
            this->CurrentMap->MoveMap(x_notch, y_notch);
        }

        // To prevent overlapping
        SDL_Delay(FRAMERATE);

        if (DEBUG_MODE)
        {
            std::clog << "Mouse clicked at (" << TargettedTile[0] << "," << TargettedTile[1] << ")" << std::endl;
            std::clog << "Player moved to (" << this->x << ", " << this->y << ")" << std::endl;
            std::clog << "Angle: " << this->angle << ", X Notch: " << x_notch << ", Y Notch: " << y_notch << std::endl;
            std::clog << std::endl;
        }
    }

    this->UpdateSprite();
}

// ------------------------------------------------------------------------------------------------

void Player::Render()
{
    SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];

    SDL_Rect dst;
    dst.x = this->DisplayedX;
    dst.y = this->DisplayedY;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(Get_Renderer(), this->Sprites, &src, &dst);
}