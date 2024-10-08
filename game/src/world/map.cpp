#include "map.hpp"

// Map Methods ------------------------------------------------------------------------------------

// Constr and destr
/*
 * Constructor of the Map class.
 *
 * Note: The normalize name should be in lower case, with underscores (_) instead of spaces.
 * Note: The normalize name should be used as name of the JSON file and the folder containing the images.
 */
Map::Map(std::string normalize_map_name)
{
    std::string data_file_path = "game/data/maps/" + normalize_map_name + ".json";
    std::string img_folder_path = "game/assets/images/maps/" + normalize_map_name;

    this->ID = LastMapID;
    LastMapID++;

    // Extract the data ---------------------------------------------------------------------------

    std::ifstream json_file_unparsed(data_file_path.c_str());
    if (!json_file_unparsed.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        exit(-1);
    }
    nlohmann::json json_file = nlohmann::json::parse(json_file_unparsed);
    json_file_unparsed.close();

    std::string map_name = json_file["map_name"];
    int height = json_file["height"];
    int width = json_file["width"];
    std::string music_path = json_file["music_path"];

    // Processing links
    std::vector<nlohmann::json> links = json_file["links"];
    std::vector<std::vector<int>> processed_links;
    for (unsigned int i = 0; i < links.size(); i++)
    {
        std::vector<int> processed_link;
        processed_link.push_back(links[i]["Map_ID"]);
        processed_link.push_back(links[i]["source"]["x"]);
        processed_link.push_back(links[i]["source"]["y"]);
        processed_link.push_back(links[i]["destination"]["x"]);
        processed_link.push_back(links[i]["destination"]["y"]);
        processed_links.push_back(processed_link);
    }

    // Use the data -------------------------------------------------------------------------------

    this->MapName = map_name;
    this->Height = height;
    this->Width = width;
    this->XPos = 0;
    this->YPos = 0;
    this->LinkedMaps = processed_links;
    this->MapTheme = new Music(music_path);

    if ((Height * TILE_SIZE < HEIGHT) || (Width * TILE_SIZE < WIDTH))
    {
        std::cout << "WARNING: the map \"" << MapName.c_str() << "\" is smaller than the screen." << std::endl;
    }

    // Load textures ------------------------------------------------------------------------------

    // Load floor texture
    SDL_Surface *floor_surface = IMG_Load((img_folder_path + "/floor.png").c_str());
    if (!floor_surface)
    {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    FloorTexture = SDL_CreateTextureFromSurface(Get_Renderer(), floor_surface);
    if (!FloorTexture)
    {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(FloorTexture, NULL, NULL, &FloorTextureWidth, &FloorTextureHeight);

    // Load wall texture
    SDL_Surface *wall_surface = IMG_Load((img_folder_path + "/wall.png").c_str());
    if (!wall_surface)
    {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    WallTexture = SDL_CreateTextureFromSurface(Get_Renderer(), wall_surface);
    if (!WallTexture)
    {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(WallTexture, NULL, NULL, &WallTextureWidth, &WallTextureHeight);

    // Load sky texture
    SDL_Surface *sky_surface = IMG_Load((img_folder_path + "/sky").c_str());
    if (sky_surface)
    {
        SkyTexture = SDL_CreateTextureFromSurface(Get_Renderer(), sky_surface);
        if (!SkyTexture)
        {
            std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
            return;
        }
        SDL_QueryTexture(SkyTexture, NULL, NULL, &SkyTextureWidth, &SkyTextureHeight);
        SDL_FreeSurface(sky_surface);
    }
    else
    {
        SkyTexture = NULL;
        SkyTextureWidth = 0;
        SkyTextureHeight = 0;
    }

    // Setup tiles --------------------------------------------------------------------------------

    // Get empty tile
    SDL_Surface *EmptyTile = IMG_Load(PATH_TO_EMPTY_TILE);
    if (!EmptyTile)
    {
        std::cerr << "Error loading empty tile: " << IMG_GetError() << std::endl;
        return;
    }
    // Setup map tiles
    std::vector<std::vector<Tile>> map_tiles(Height, std::vector<Tile>(Width));
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            bool IsWall;
            SDL_Surface *CurrentTile = IMG_Load(PATH_TO_EMPTY_TILE);
            if (!CurrentTile)
            {
                std::cerr << "Error loading empty tile: " << IMG_GetError() << std::endl;
                return;
            }

            SDL_Rect src = {.x = i * TILE_SIZE, .y = j * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
            // project tile to current working tile
            if (SDL_BlitSurface(wall_surface, &src, CurrentTile, NULL))
            {
                std::cerr << "Error blitting wall map to current working tile: " << IMG_GetError() << std::endl;
                return;
            }

            if (AreSurfacesEqual(CurrentTile, EmptyTile))
            {
                IsWall = false;
            }
            else
            {
                IsWall = true;
            }

            SDL_FreeSurface(CurrentTile);

            map_tiles[i][j] = Tile(IsWall);
        }
    }
    this->MapTiles = map_tiles;

    // Cleaning up surfaces -----------------------------------------------------------------------

    SDL_FreeSurface(floor_surface);
    SDL_FreeSurface(wall_surface);
    SDL_FreeSurface(EmptyTile);
}
/*
 * Constructor of the Map class.
 *
 * Note: The data_file_path is the exact path to the JSON file containing the map data.
 * Note: The img_folder_path is the path to the folder containing the textures. It should not end with a '/'.
 */
Map::Map(std::string data_file_path, std::string img_folder_path)
{
    this->ID = LastMapID;
    LastMapID++;

    // Extract the data ---------------------------------------------------------------------------

    std::ifstream json_file_unparsed(data_file_path.c_str());
    if (!json_file_unparsed.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        exit(-1);
    }
    nlohmann::json json_file = nlohmann::json::parse(json_file_unparsed);
    json_file_unparsed.close();

    std::string map_name = json_file["map_name"];
    int height = json_file["height"];
    int width = json_file["width"];
    std::string music_path = json_file["music_path"];

    // Processing links
    std::vector<nlohmann::json> links = json_file["links"];
    std::vector<std::vector<int>> processed_links;
    for (unsigned int i = 0; i < links.size(); i++)
    {
        std::vector<int> processed_link;
        processed_link.push_back(links[i]["Map_ID"]);
        processed_link.push_back(links[i]["source"]["x"]);
        processed_link.push_back(links[i]["source"]["y"]);
        processed_link.push_back(links[i]["destination"]["x"]);
        processed_link.push_back(links[i]["destination"]["y"]);
        processed_links.push_back(processed_link);
    }

    // Use the data -------------------------------------------------------------------------------

    this->MapName = map_name;
    this->Height = height;
    this->Width = width;
    this->XPos = 0;
    this->YPos = 0;
    this->LinkedMaps = processed_links;
    this->MapTheme = new Music(music_path);

    if ((Height * TILE_SIZE < HEIGHT) || (Width * TILE_SIZE < WIDTH))
    {
        std::cout << "WARNING: the map \"" << MapName.c_str() << "\" is smaller than the screen." << std::endl;
    }

    // Load textures ------------------------------------------------------------------------------

    // Load floor texture
    SDL_Surface *floor_surface = IMG_Load((img_folder_path + "/floor.png").c_str());
    if (!floor_surface)
    {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    FloorTexture = SDL_CreateTextureFromSurface(Get_Renderer(), floor_surface);
    if (!FloorTexture)
    {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(FloorTexture, NULL, NULL, &FloorTextureWidth, &FloorTextureHeight);

    // Load wall texture
    SDL_Surface *wall_surface = IMG_Load((img_folder_path + "/wall.png").c_str());
    if (!wall_surface)
    {
        std::cerr << "Error loading map texture: " << IMG_GetError() << std::endl;
        return;
    }
    WallTexture = SDL_CreateTextureFromSurface(Get_Renderer(), wall_surface);
    if (!WallTexture)
    {
        std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_QueryTexture(WallTexture, NULL, NULL, &WallTextureWidth, &WallTextureHeight);

    // Load sky texture
    SDL_Surface *sky_surface = IMG_Load((img_folder_path + "/sky").c_str());
    if (sky_surface)
    {
        SkyTexture = SDL_CreateTextureFromSurface(Get_Renderer(), sky_surface);
        if (!SkyTexture)
        {
            std::cerr << "Error creating texture from map: " << SDL_GetError() << std::endl;
            return;
        }
        SDL_QueryTexture(SkyTexture, NULL, NULL, &SkyTextureWidth, &SkyTextureHeight);
        SDL_FreeSurface(sky_surface);
    }
    else
    {
        SkyTexture = NULL;
        SkyTextureWidth = 0;
        SkyTextureHeight = 0;
    }

    // Setup tiles --------------------------------------------------------------------------------

    // Get empty tile
    SDL_Surface *EmptyTile = IMG_Load(PATH_TO_EMPTY_TILE);
    if (!EmptyTile)
    {
        std::cerr << "Error loading empty tile: " << IMG_GetError() << std::endl;
        return;
    }
    // Setup map tiles
    std::vector<std::vector<Tile>> map_tiles(Height, std::vector<Tile>(Width));
    for (int i = 0; i < Height; ++i)
    {
        for (int j = 0; j < Width; ++j)
        {
            bool IsWall;
            SDL_Surface *CurrentTile = IMG_Load(PATH_TO_EMPTY_TILE);
            if (!CurrentTile)
            {
                std::cerr << "Error loading empty tile: " << IMG_GetError() << std::endl;
                return;
            }

            SDL_Rect src = {.x = i * TILE_SIZE, .y = j * TILE_SIZE, .w = TILE_SIZE, .h = TILE_SIZE};
            // project tile to current working tile
            if (SDL_BlitSurface(wall_surface, &src, CurrentTile, NULL))
            {
                std::cerr << "Error blitting wall map to current working tile: " << IMG_GetError() << std::endl;
                return;
            }

            if (AreSurfacesEqual(CurrentTile, EmptyTile))
            {
                IsWall = false;
            }
            else
            {
                IsWall = true;
            }

            SDL_FreeSurface(CurrentTile);

            map_tiles[i][j] = Tile(IsWall);
        }
    }
    this->MapTiles = map_tiles;

    // Cleaning up surfaces -----------------------------------------------------------------------

    SDL_FreeSurface(floor_surface);
    SDL_FreeSurface(wall_surface);
    SDL_FreeSurface(EmptyTile);
}
Map::~Map(void)
{
    delete MapTheme;

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
std::vector<std::vector<Tile>> Map::GetMapTiles() { return MapTiles; }
std::vector<std::vector<int>> Map::GetLinkedMaps() { return LinkedMaps; }

// Render
void Map::Render(void)
{
    SDL_Renderer *renderer = Get_Renderer();

    int widthInPixels = Width * TILE_SIZE;
    int heightInPixels = Height * TILE_SIZE;
    SDL_Rect dest = {.x = XPos, .y = YPos, .w = widthInPixels, .h = heightInPixels};

    // Render sky over wall over floor
    SDL_RenderCopy(renderer, FloorTexture, NULL, &dest);
    SDL_RenderCopy(renderer, WallTexture, NULL, &dest);
    SDL_RenderCopy(renderer, SkyTexture, NULL, &dest);
}

// Music player
void Map::PlayTheme(void)
{
    MapTheme->Play(1);
}