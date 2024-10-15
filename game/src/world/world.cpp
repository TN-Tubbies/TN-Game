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

void World::HandleKeyDown(SDL_Event event)
{
    int x_notch = 0;
    int y_notch = 0;
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_q:
        if (DEBUG_MODE)
        {
            std::clog << "Key press: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        }
        x_notch = -1;
        break;
    case SDLK_RIGHT:
    case SDLK_d:
        if (DEBUG_MODE)
        {
            std::clog << "Key press: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        }
        x_notch = 1;
        break;
    case SDLK_UP:
    case SDLK_z:
        if (DEBUG_MODE)
        {
            std::clog << "Key press: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        }
        y_notch = -1;
        break;
    case SDLK_DOWN:
    case SDLK_s:
        if (DEBUG_MODE)
        {
            std::clog << "Key press: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        }
        y_notch = 1;
        break;
    default:
        if (DEBUG_MODE)
        {
            std::clog << "Unhandled key press: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
        }
        break;
    }

    this->player->SetMoveNotches({x_notch, y_notch});
    this->player->SetIsWalking(x_notch != 0 || y_notch != 0);
}

void World::HandleKeyUp(SDL_Event event)
{
    int x_notch = this->player->GetMoveNotches()[0];
    int y_notch = this->player->GetMoveNotches()[1];
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
    case SDLK_q:
    case SDLK_RIGHT:
    case SDLK_d:
        x_notch = 0;
        break;
    case SDLK_UP:
    case SDLK_z:
    case SDLK_DOWN:
    case SDLK_s:
        y_notch = 0;
        break;
    default:
        break;
    }

    this->player->SetMoveNotches({x_notch, y_notch});
    this->player->SetIsWalking(x_notch != 0 || y_notch != 0);
}