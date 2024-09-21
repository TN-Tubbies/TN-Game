#include "map.h"

// Tile Methods -----------------------------------------------------------------------------------

Tile::Tile(bool is_wall){
    this->IsWall = is_wall;

    // Default animation path is "*None*"
    this->AnimationPath = "*None*";
}
Tile::Tile(bool is_wall, std::string animation_path){
    this->IsWall = is_wall;
    this->AnimationPath = animation_path;
}

// Map Methods ------------------------------------------------------------------------------------

Map::Map(std::string name, int height, int width, std::string img_path){
    this->MapName = name;
    this->Height = height;
    this->Width = width;

    // Load floor texture
    SDL_Surface* floor_surface = IMG_Load(("floor_" + img_path).c_str());
    if (!floor_surface) {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    FloorTexture = SDL_CreateTextureFromSurface(Get_Renderer(), floor_surface);
    SDL_FreeSurface(floor_surface);
    if (!FloorTexture) {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(FloorTexture, NULL, NULL, &FloorTextureWidth, &FloorTextureHeight);

    // Load wall texture
    SDL_Surface* wall_surface = IMG_Load(("wall_" + img_path).c_str());
    if (!wall_surface) {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    WallTexture = SDL_CreateTextureFromSurface(Get_Renderer(), wall_surface);
    SDL_FreeSurface(wall_surface);
    if (!WallTexture) {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(WallTexture, NULL, NULL, &WallTextureWidth, &WallTextureHeight);

    // Load sky texture
    SDL_Surface* sky_surface = IMG_Load(("sky_" + img_path).c_str());
    if (!sky_surface) {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    SkyTexture = SDL_CreateTextureFromSurface(Get_Renderer(), sky_surface);
    SDL_FreeSurface(sky_surface);
    if (!SkyTexture) {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(SkyTexture, NULL, NULL, &SkyTextureWidth, &SkyTextureHeight);

    // Setup map tiles
    std::vector<std::vector<Tile>> map_tiles(Height, std::vector<Tile>(Width));
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
            map_tiles[i][j] = Tile(false);   // FIXME: Add tile data based on map data
        }
    }
    this->MapTiles = map_tiles;
}