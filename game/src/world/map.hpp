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
#include "entity.hpp"
#include "tile.hpp"

class Map
{
private:
    // Height and width are in tiles, TL Coords are in pixels
    std::string MapName;
    int Height, Width;
    std::array<int, 2> TopLeftCoordinates;
    std::vector<std::vector<Tile>> MapTiles;

    SDL_Texture *FloorTexture;
    int FloorTextureWidth, FloorTextureHeight;
    SDL_Texture *WallTexture;
    int WallTextureWidth, WallTextureHeight;
    SDL_Texture *SkyTexture;
    int SkyTextureWidth, SkyTextureHeight;

    // Each std::vector<std::any> in LinkedMaps represents a link:
    //       [MapName (std::string), source_x (int), source_y (int), destination_x (int), destination_y (int)]
    std::vector<std::vector<std::any>> LinkedMaps;

    std::vector<Entity *> NPCs;

    Music *MapTheme;

public:
    Map(std::string normalize_map_name);
    ~Map();

    int GetHeight() const { return Height; }
    int GetWidth() const { return Width; }
    std::array<int, 2> GetTopLeftCoordinates() { return TopLeftCoordinates; }
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