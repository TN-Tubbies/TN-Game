#include "player.hpp"

Player::Player(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType)
{
    this->name = "Player";
    this->x = x;
    this->y = y;
    this->IsWalking = false;
    this->Speed = speed;
    this->direction = SpriteDirection_Down;

    // Selecting what are the sprite sizes --------------------------------------------------------

    int ***sprite_sizes = NULL;

    if (SheetType == SPRITE_SHEET_MAIN_CHARACTER)
    {
        int base_sprite_sizes[4][3][4] = {
            {{66, 0, 26, 44}, {386, 128, 26, 44}, {416, 126, 28, 44}},
            {{30, 0, 32, 44}, {254, 128, 30, 44}, {222, 126, 32, 46}},
            {{2, 0, 26, 44}, {4, 128, 26, 44}, {35, 126, 28, 44}},
            {{94, 0, 52, 44}, {576, 126, 30, 44}, {608, 128, 30, 44}}};

        sprite_sizes = (int ***)malloc(4 * sizeof(int **));
        for (int i = 0; i < 4; ++i)
        {
            sprite_sizes[i] = (int **)malloc(3 * sizeof(int *));
            for (int j = 0; j < 3; ++j)
            {
                sprite_sizes[i][j] = (int *)malloc(4 * sizeof(int));
                for (int k = 0; k < 4; ++k)
                {
                    sprite_sizes[i][j][k] = base_sprite_sizes[i][j][k];
                }
            }
        }
    }

    // Load texture ------------------------------------------------------------------------------

    SDL_Surface *surface = IMG_Load(sprite_path.c_str());
    if (!surface)
    {
        std::cerr << "Error loading sprite: " << IMG_GetError() << std::endl;
        return;
    }
    this->Sprites = SDL_CreateTextureFromSurface(Get_Renderer(), surface);
    if (!this->Sprites)
    {
        std::cerr << "Error creating texture from sprite: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(this->Sprites, NULL, NULL, &this->SpriteWidth, &this->SpriteHeight);
    SDL_FreeSurface(surface);

    SDL_Rect **srcs = (SDL_Rect **)malloc(4 * sizeof(SDL_Rect *));

    for (int i = 0; i < 4; i++)
    {
        srcs[i] = (SDL_Rect *)malloc(3 * sizeof(SDL_Rect));
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            srcs[i][j].x = sprite_sizes[i][j][0];
            srcs[i][j].y = sprite_sizes[i][j][1];
            srcs[i][j].w = sprite_sizes[i][j][2];
            srcs[i][j].h = sprite_sizes[i][j][3];
        }
    }
    this->SpriteRect = srcs;
    this->CurrentSpriteIndex = 0;

    // Freeing allocated memory
    if (SheetType == SPRITE_SHEET_MAIN_CHARACTER)
    {
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                free(sprite_sizes[i][j]);
            }
            free(sprite_sizes[i]);
        }
        free(sprite_sizes);
    }

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

        if (y_notch > 0)
        {
            this->DisplayedY = std::min(y_dest, (int)std::floor(HEIGHT / 2 - src.h / 2));
        }
        else if (y_notch < 0)
        {
            this->DisplayedY = std::max(y_dest, (int)std::floor(HEIGHT / 2 - src.h / 2));
        }
        else
        {
            this->DisplayedY = y_dest;
        }

        this->CurrentMap->MoveMap(0, y_notch * this->Speed);
    }
    else if (this->CurrentMap->IsAtEdge(orientation_y)) // Only y side
    {
        if (x_notch > 0)
        {
            this->DisplayedX = std::min(x_dest, (int)std::floor(WIDTH / 2 - src.h / 2));
        }
        else if (x_notch < 0)
        {
            this->DisplayedX = std::max(x_dest, (int)std::floor(WIDTH / 2 - src.h / 2));
        }
        else
        {
            this->DisplayedX = x_dest;
        }

        this->DisplayedY = y_dest;

        this->CurrentMap->MoveMap(x_notch * this->Speed, 0);
    }
    else // Neither side
    {
        if (x_notch > 0)
        {
            this->DisplayedX = std::min(x_dest, (int)std::floor(WIDTH / 2 - src.w / 2));
        }
        else if (x_notch < 0)
        {
            this->DisplayedX = std::max(x_dest, (int)std::floor(WIDTH / 2 - src.w / 2));
        }
        else
        {
            this->DisplayedX = x_dest;
        }

        if (y_notch > 0)
        {
            this->DisplayedY = std::min(y_dest, (int)std::floor(HEIGHT / 2 - src.h / 2));
        }
        else if (y_notch < 0)
        {
            this->DisplayedY = std::max(y_dest, (int)std::floor(HEIGHT / 2 - src.h / 2));
        }
        else
        {
            this->DisplayedY = y_dest;
        }

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