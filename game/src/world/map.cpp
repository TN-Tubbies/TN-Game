#include "map.h"

// Generate headers -------------------------------------------------------------------------------

std::vector<std::string> GenerateHeaders() {
    std::vector<std::string> headers;

    headers.push_back("map name");
    headers.push_back("height");
    headers.push_back("width");
    headers.push_back("link amount");
    headers.push_back("links");

    return headers;
}

// Map Methods ------------------------------------------------------------------------------------

// Constr and destr
/*
 * Constructor of the Map class.
 *
 * Note: the height and width are in tiles.
 * Note: The img_folder_path is the path to the folder containing the textures. It should not end with a '/'.
 */
Map::Map(std::string data_file_path, std::string img_folder_path){
    this->ID = LastMapID;
    LastMapID++;

    // Extract the data ---------------------------------------------------------------------------

    std::ifstream f(data_file_path.c_str());
    nlohmann::json json_file = nlohmann::json::parse(f);



    json_file["/baz/1"_json_pointer];

    // Use the data ------------------------------------------------------------------------------- 

    if ((Height*TILE_SIZE < HEIGHT) || (Width*TILE_SIZE < WIDTH)){
        std::cout << "WARNING: the map \"" << MapName.c_str() << "\" is smaller than the screen."<< std::endl;
    }

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
    std::vector<std::vector<Tile>> map_tiles(Height, std::vector<Tile>(Width));
    for (int i = 0; i < Height; ++i) {
        for (int j = 0; j < Width; ++j) {
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

    // Cleaning up surfaces
    SDL_FreeSurface(floor_surface);
    SDL_FreeSurface(wall_surface);
    SDL_FreeSurface(EmptyTile);
}
Map::Map(std::string name, int height, int width, std::string img_folder_path){
    this->ID = LastMapID;
    LastMapID++;

    this->MapName = name;
    this->Height = height;
    this->Width = width;
    this->XPos = 0;
    this->YPos = 0;
    this->LinkedMapsID = std::vector<int>();

    if ((height*TILE_SIZE < HEIGHT) || (width*TILE_SIZE < WIDTH)){
        std::cout << "WARNING: the map \"" << name.c_str() << "\" is smaller than the screen."<< std::endl;
    }

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
int Map::GetID() const { return ID; }
int Map::GetHeight() const { return Height; }
int Map::GetWidth() const { return Width; }
int Map::GetXPos() { return XPos; }
int Map::GetYPos() { return YPos; }
std::string Map::GetMapName() const { return MapName; }
std::vector<std::vector<Tile>> Map::GetMapTiles(){ return MapTiles; }
std::vector<int> Map::GetLinkedMapsID(){ return LinkedMapsID; }

// Render
void Map::Render(void){
    SDL_Renderer* renderer = Get_Renderer();

    int widthInPixels = Width * TILE_SIZE;
    int heightInPixels = Height * TILE_SIZE;
    SDL_Rect dest = {.x = XPos,.y = YPos,.w = widthInPixels,.h = heightInPixels};

    // Render sky over wall over floor
    SDL_RenderCopy(renderer, FloorTexture, NULL, &dest);
    SDL_RenderCopy(renderer, WallTexture, NULL, &dest);
    SDL_RenderCopy(renderer, SkyTexture, NULL, &dest);
}