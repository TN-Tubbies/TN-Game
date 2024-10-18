#include "player.hpp"

Player::Player(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType)
    : Entity("Player", x, y, speed, sprite_path, SheetType)
{
    this->CurrentMap = nullptr;

    SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];
    this->DisplayedX = std::floor(WIDTH / 2 - src.w / 2);
    this->DisplayedY = std::floor(HEIGHT / 2 - src.h / 2);

    this->move_notches = {0, 0};
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

void Player::Move()
{
    // TODO: Collision detection

    // ------------------------------------------

    int x_notch = this->move_notches[0];
    int y_notch = this->move_notches[1];
    // In pixels
    SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];
    int x_dest = this->DisplayedX + x_notch * this->Speed;
    int y_dest = this->DisplayedY + y_notch * this->Speed;

    // Get the destination tile
    int x_dest_tile = (int)std::floor(x_dest / TILE_SIZE);
    int y_dest_tile = (int)std::floor(y_dest / TILE_SIZE);

    if (x_dest_tile < 0 || x_dest + src.w >= this->CurrentMap->GetWidth() * TILE_SIZE)
    {
        if (DEBUG_MODE)
        {
            std::clog << "Player: Destination tile out of map bounds (x)." << std::endl;
        }
    }
    else if (y_dest_tile < 0 || y_dest + src.h >= this->CurrentMap->GetHeight() * TILE_SIZE)
    {
        if (DEBUG_MODE)
        {
            std::clog << "Player: Destination tile out of map bounds (y)." << std::endl;
        }
    }
    else
    {
        if (DEBUG_MODE)
        {
            std::clog << "Player: Moving to tile (" << x_dest_tile << ", " << y_dest_tile << ")." << std::endl;
        }

        this->x += x_notch;
        this->y += y_notch;

        this->UpdateDisplayedPosition();
    }

    // ------------------------------------------

    this->UpdateSprite();
}

// ------------------------------------------------------------------------------------------------

void Player::UpdateDisplayedPosition()
{
    SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];
    int x_notch = this->move_notches[0];
    int y_notch = this->move_notches[1];
    std::string orientation_x = "";
    std::string orientation_y = "";
    if (x_notch < 0)
    {
        orientation_x = "x-";
    }
    else if (x_notch > 0)
    {
        orientation_x = "x+";
    }
    if (y_notch < 0)
    {
        orientation_y = "y-";
    }
    else if (y_notch > 0)
    {
        orientation_y = "y+";
    }

    // ------------------------------------------

    int x_dest = this->DisplayedX + x_notch * this->Speed;
    int y_dest = this->DisplayedY + y_notch * this->Speed;

    // ------------------------------------------

    if (this->CurrentMap->IsAtEdge(orientation_x) && this->CurrentMap->IsAtEdge(orientation_y)) // Both sides
    {
        this->DisplayedX = x_dest;
        this->DisplayedY = y_dest;
    }
    else if (this->CurrentMap->IsAtEdge(orientation_x)) // Only x side
    {
        this->DisplayedX = x_dest;
        this->DisplayedY = std::min(y_dest, (int)std::floor(HEIGHT / 2 - src.h / 2));
        this->CurrentMap->MoveMap(0, y_notch * this->Speed);
    }
    else if (this->CurrentMap->IsAtEdge(orientation_y)) // Only y side
    {
        this->DisplayedX = std::min(x_dest, (int)std::floor(WIDTH / 2 - src.w / 2));
        this->DisplayedY = y_dest;
        this->CurrentMap->MoveMap(x_notch * this->Speed, 0);
    }
    else // Neither side
    {
        this->DisplayedX = std::min(x_dest, (int)std::floor(WIDTH / 2 - src.w / 2));
        this->DisplayedY = std::min(y_dest, (int)std::floor(HEIGHT / 2 - src.h / 2));
        this->CurrentMap->MoveMap(x_notch * this->Speed, y_notch * this->Speed);
    }
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