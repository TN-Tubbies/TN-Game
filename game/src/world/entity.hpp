#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../lib/json.hpp"

#include "../static/renderer.hpp"
#include "../defs.hpp"

// ------------------------------------------------------------------------------------------------

class Entity
{
protected:
    std::string name;
    // X and Y coordinates are in tiles
    // speed is in pixels
    int x, y;
    bool IsWalking;
    int Speed;
    enum SpriteDirection direction;

    SDL_Texture *Sprites;
    int CurrentSpriteIndex;
    int SpriteWidth, SpriteHeight;
    SDL_Rect **SpriteRect;

public:
    Entity();
    Entity(std::string file_name);
    Entity(std::string _name, int x, int y, int speed, std::string sprite_path, enum SpriteSheetTypes SheetType);
    ~Entity();

    std::string GetName() const { return name; }
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetXTile() const;
    int GetYTile() const;

    void Render();
    void UpdateSprite();

    void TeleportTo(int x, int y);
    void MoveTo(int x, int y);
};

#endif