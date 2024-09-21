#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <string>

#include "../defs.h"
#include "../static/renderer.h"

class Tile{
private:
    bool IsWall;
    std::string AnimationPath;
public:
    Tile(bool is_wall);
    Tile(bool is_wall, std::string animation_path);
};

class Map {
private:
    std::string MapName;
    int Height, Width;
    std::vector<std::vector<Tile>> MapTiles;

    SDL_Texture* FloorTexture;
    int FloorTextureWidth, FloorTextureHeight;
    SDL_Texture* WallTexture;
    int WallTextureWidth, WallTextureHeight;
    SDL_Texture* SkyTexture;
    int SkyTextureWidth, SkyTextureHeight;

public:
    Map(std::string name, int height, int width, std::string base_img_path);
};

#endif