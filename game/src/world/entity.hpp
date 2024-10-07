#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../static/renderer.hpp"
#include "../defs.hpp"

// ------------------------------------------------------------------------------------------------

class Entity
{
protected:
    // X and Y coordinates are in tiles
    int x, y;
    float angle;
    bool IsWalking;
    int Speed;

    SDL_Texture *Sprites;
    int CurrentSpriteIndex;
    int SpriteWidth, SpriteHeight;
    SDL_Rect **SpriteRect;

public:
    Entity();
    Entity(int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType);

    int GetX() const { return x; }
    int GetY() const { return y; }
    float GetAngle() const { return angle; }

    void UpdateSprite();
    void TeleportTo(int x, int y);
    void MoveTo(int x, int y);
};

#endif