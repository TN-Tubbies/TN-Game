#include "world.hpp"

// ------------------------------------------------------------------------------------------------

World::World(std::string file_name, Player *_player)
{
    // Extract the data ---------------------------------------------------------------------------

    std::ifstream json_file_unparsed(file_name.c_str());
    if (!json_file_unparsed.is_open())
    {
        std::cerr << "Error opening input file." << std::endl;
        exit(-1);
    }
    nlohmann::json json_file = nlohmann::json::parse(json_file_unparsed);
    json_file_unparsed.close();

    std::string world_name = json_file["world_name"];
    std::string first_map_name = json_file["first_map_name"];
    std::vector<std::string> map_names = json_file["map_names"];

    // Use the data -------------------------------------------------------------------------------

    this->player = _player;
    this->worldName = world_name;
    this->worldFirstMap = first_map_name;

    std::vector<Map *> _worldMaps;
    for (std::string map_name : map_names)
    {
        Map *map = new Map(map_name);
        _worldMaps.push_back(map);

        if (map_name == first_map_name)
        {
            this->player->SetCurrentMap(map);
        }
    }
    this->maps = _worldMaps;
}

/*
 * Destructor of the World class.
 *
 * Note: This won't destroy the linked Player.
 */
World::~World()
{
    for (Map *map : this->maps)
    {
        if (map != NULL)
        {
            delete map;
        }
    }
}

// ------------------------------------------------------------------------------------------------

void World::HandleKeyUp(SDL_Event event)
{
    // FIXME: Add controls
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
        break;
    case SDLK_RIGHT:
        break;
    case SDLK_UP:
        break;
    case SDLK_DOWN:
        break;
    default:
        break;
    }
}

void World::HandleMouseClickUp(SDL_Event event)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (event.button.button == SDL_BUTTON_RIGHT)
    {
        if (DEBUG_MODE)
        {
            std::clog << "Mouse right-button clicked up: " << mouse_x << ", " << mouse_y << std::endl;
        }
        // FIXME: Adding interactivity if right click
    }
}

void World::HandleMouseClickDown(SDL_Event event)
{
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (event.button.button == SDL_BUTTON_LEFT)
    {
        if (DEBUG_MODE)
        {
            std::clog << "Mouse left-button clicked down: " << mouse_x << ", " << mouse_y << std::endl;
        }

        this->player->MoveTo(mouse_x, mouse_y);
    }
}