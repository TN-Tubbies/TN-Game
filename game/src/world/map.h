#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <string>

#include "../defs.h"
#include "../static/renderer.h"
#include "../utility/sdl_compare_surfaces.h"
#include "tile.h"

class Map {
private:
    int ID;
    std::string MapName;
    int Height, Width;
    std::vector<std::vector<Tile>> MapTiles;

    SDL_Texture* FloorTexture;
    int FloorTextureWidth, FloorTextureHeight;
    SDL_Texture* WallTexture;
    int WallTextureWidth, WallTextureHeight;
    SDL_Texture* SkyTexture;
    int SkyTextureWidth, SkyTextureHeight;

    std::vector<int> LinkedMapsID;

public:
    Map(std::string name, int height, int width, std::string img_folder_path);
    ~Map();

    int GetID() const;
    int GetHeight() const;
    int GetWidth() const;
    std::string GetMapName() const;
    std::vector<std::vector<Tile>> GetMapTiles();
    std::vector<int> GetLinkedMapsID();

    void Render(void);
};

#endif