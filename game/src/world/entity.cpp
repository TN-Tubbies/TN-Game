#include "entity.hpp"

// ------------------------------------------------------------------------------------------------

Entity::Entity()
{
    this->name = "";
    this->x = 0;
    this->y = 0;
    this->angle = 0.0;
    this->IsWalking = false;
    this->Speed = 0;
    this->Sprites = nullptr;
    this->SpriteWidth = 0;
    this->SpriteHeight = 0;
    this->SpriteRect = nullptr;
    this->CurrentSpriteIndex = 0;
    this->direction = SpriteDirection_Down;
}
Entity::Entity(std::string _name, int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType)
{
    this->name = _name;
    this->x = x;
    this->y = y;
    this->angle = 0.0;
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
}

// ------------------------------------------------------------------------------------------------

void Entity::Render()
{
    SDL_Rect src = this->SpriteRect[this->direction][this->CurrentSpriteIndex];

    SDL_Rect dst;
    dst.x = this->x;
    dst.y = this->y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(Get_Renderer(), this->Sprites, &src, &dst);
}
void Entity::UpdateSprite()
{
}

// ------------------------------------------------------------------------------------------------

int Entity::GetXTile() const
{
    return this->x / TILE_SIZE;
}
int Entity::GetYTile() const
{
    return this->y / TILE_SIZE;
}

// ------------------------------------------------------------------------------------------------

void Entity::TeleportTo(int x, int y)
{
    this->x = x;
    this->y = y;
    this->angle = 0.0;
}

void Entity::MoveTo(int x, int y)
{
    if (DEBUG_MODE)
    {
        std::clog << "Entity \"" << this->name << "\" move to " << x << " " << y << std::endl;
    }

    // FIXME: Implement the selection of the path
    std::array<int, 2> TargettedTile = {0, 0};
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
    }
    else if (MoveVector[0] == 0 && MoveVector[1] == 0)
    {
        this->IsWalking = false;
    }
    this->UpdateSprite();
}

// ------------------------------------------------------------------------------------------------