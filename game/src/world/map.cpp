#include "map.h"

// Map Methods ------------------------------------------------------------------------------------

// Constr and destr
Map::Map(std::string name, int height, int width, std::string img_folder_path){
    this->MapName = name;
    this->Height = height;
    this->Width = width;

    // Load floor texture
    SDL_Surface* floor_surface = IMG_Load((img_folder_path + "/floor.png").c_str());
    if (!floor_surface) {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    FloorTexture = SDL_CreateTextureFromSurface(Get_Renderer(), floor_surface);
    if (!FloorTexture) {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(FloorTexture, NULL, NULL, &FloorTextureWidth, &FloorTextureHeight);

    // Load wall texture
    SDL_Surface* wall_surface = IMG_Load((img_folder_path + "/wall.png").c_str());
    if (!wall_surface) {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    WallTexture = SDL_CreateTextureFromSurface(Get_Renderer(), wall_surface);
    if (!WallTexture) {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(WallTexture, NULL, NULL, &WallTextureWidth, &WallTextureHeight);

    // Load sky texture
    SDL_Surface* sky_surface = IMG_Load((img_folder_path + "/sky").c_str());
    if (sky_surface) {
        SkyTexture = SDL_CreateTextureFromSurface(Get_Renderer(), sky_surface);
        if (!SkyTexture) {
            std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
            return;
        }
        SDL_QueryTexture(SkyTexture, NULL, NULL, &SkyTextureWidth, &SkyTextureHeight);
        SDL_FreeSurface(sky_surface);
    } else {
        SkyTexture = NULL;
        SkyTextureWidth = 0;
        SkyTextureHeight = 0;
    }


    // Get empty tile
    SDL_Surface* EmptyTile = IMG_Load(PATH_TO_EMPTY_TILE);
    if (!EmptyTile) {
        std::cerr << "Error loading empty tile: " << IMG_GetError() << std::endl;
        return;
    }
    // Setup map tiles
    int NbTilesHeight = height/TILE_SIZE;
    int NbTilesWidth = width/TILE_SIZE;
    std::vector<std::vector<Tile>> map_tiles(NbTilesHeight, std::vector<Tile>(NbTilesWidth));
    for (int i = 0; i < NbTilesHeight; ++i) {
        for (int j = 0; j < NbTilesWidth; ++j) {
            bool IsWall;
            SDL_Surface* CurrentTile = IMG_Load(PATH_TO_EMPTY_TILE);
            if (!CurrentTile) {
                std::cerr << "Error loading empty tile: " << IMG_GetError() << std::endl;
                return;
            }

            SDL_Rect src = {.x = i*TILE_SIZE, .y = j*TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
            // project tile to current working tile
            if (SDL_BlitSurface(wall_surface, &src, CurrentTile, NULL)) {
                std::cerr << "Error blitting wall map to current working tile: " << IMG_GetError() << std::endl;
                return;
            }

            if (AreSurfacesEqual(CurrentTile, EmptyTile)) {
                IsWall = false;
            } else {
                IsWall = true;
            }

            SDL_FreeSurface(CurrentTile);

            map_tiles[i][j] = Tile(IsWall);
        }
    }
    this->MapTiles = map_tiles;
    this->LinkedMapsID = std::vector<int>();

    // Cleaning up surfaces
    SDL_FreeSurface(floor_surface);
    SDL_FreeSurface(wall_surface);
    SDL_FreeSurface(EmptyTile);
}
Map::~Map(void){
    SDL_DestroyTexture(FloorTexture);
    SDL_DestroyTexture(WallTexture);
    SDL_DestroyTexture(SkyTexture);
}

// Getters
int Map::GetID() const { return ID;}
int Map::GetHeight() const { return Height;  }
int Map::GetWidth() const { return Width;  }
std::string Map::GetMapName() const { return MapName; }
std::vector<std::vector<Tile>> Map::GetMapTiles(){ return MapTiles; }
std::vector<int> Map::GetLinkedMapsID(){ return LinkedMapsID; }

// Render
void Map::Render(void){    // TODO: Implement rendering logic
    // Render sky over wall over floor
}