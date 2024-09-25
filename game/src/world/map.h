#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "../lib/json.hpp"

#include "../defs.h"
#include "../static/renderer.h"
#include "../utility/sdl_compare_surfaces.h"
#include "../audio/audio.h"
#include "tile.h"

static int LastMapID = 0;

class Map {
private:
    int ID;

    std::string MapName;
    int Height, Width;
    int XPos, YPos;
    std::vector<std::vector<Tile>> MapTiles;

    SDL_Texture* FloorTexture;
    int FloorTextureWidth, FloorTextureHeight;
    SDL_Texture* WallTexture;
    int WallTextureWidth, WallTextureHeight;
    SDL_Texture* SkyTexture;
    int SkyTextureWidth, SkyTextureHeight;

    // Each std::vector<int> in LinkedMaps represents a link:
    //              [Map_ID, source_x, source_y, destination_x, destination_y]
    std::vector<std::vector<int>> LinkedMaps;

    Music *MapTheme;

public:
    Map(std::string normalize_map_name);
    Map(std::string data_file_path, std::string img_folder_path);
    ~Map();

    int GetID() const;
    int GetHeight() const;
    int GetWidth() const;
    std::string GetMapName() const;
    int GetXPos();
    int GetYPos();
    std::vector<std::vector<Tile>> GetMapTiles();
    std::vector<std::vector<int>> GetLinkedMaps();

    void Render(void);
    void PlayTheme(void);
};

#endif