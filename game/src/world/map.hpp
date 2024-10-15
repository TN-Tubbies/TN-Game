#ifndef MAP_HPP
#define MAP_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "../lib/json.hpp"

#include "../defs.hpp"
#include "../static/renderer.hpp"
#include "../utility/sdl_compare_surfaces.hpp"
#include "../audio/audio.hpp"
#include "tile.hpp"

class Map
{
private:
    // Height and width are in tiles
    std::string MapName;
    int Height, Width;
    std::array<unsigned int, 2> TL_TileID;
    std::array<unsigned int, 2> BR_TileID;
    std::vector<std::vector<Tile>> MapTiles;

    SDL_Texture *FloorTexture;
    int FloorTextureWidth, FloorTextureHeight;
    SDL_Texture *WallTexture;
    int WallTextureWidth, WallTextureHeight;
    SDL_Texture *SkyTexture;
    int SkyTextureWidth, SkyTextureHeight;

    // Each std::vector<std::any> in LinkedMaps represents a link:
    //              [MapName, source_x, source_y, destination_x, destination_y]
    std::vector<std::vector<std::any>> LinkedMaps;

    Music *MapTheme;

public:
    Map(std::string normalize_map_name);
    Map(std::string data_file_path, std::string img_folder_path);
    ~Map();

    int GetHeight() const { return Height; }
    int GetWidth() const { return Width; }
    int GetTLTileXIndex() { return TL_TileID[0]; }
    int GetTLTileYIndex() { return TL_TileID[1]; }
    int GetBRTileXIndex() { return BR_TileID[0]; }
    int GetBRTileYIndex() { return BR_TileID[1]; }
    std::string GetMapName() const { return MapName; }
    std::vector<std::vector<Tile>> GetMapTiles() { return MapTiles; }
    std::vector<std::vector<std::any>> GetLinkedMaps() { return LinkedMaps; }

    bool IsAtEdge(std::string orientation);
    bool IsAtEdge();

    std::array<int, 2> GetTile(int mouse_x, int mouse_y);
    void MoveMap(int delta_x, int delta_y);
    void Render(void);
    void PlayTheme(void);
};

#endif