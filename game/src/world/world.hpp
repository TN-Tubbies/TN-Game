#ifndef WORLD_HPP
#define WORLD_HPP

#include <string>
#include <vector>

#include "../lib/json.hpp"

#include "map.hpp"
#include "player.hpp"

class World
{
private:
    Player *player;
    std::string worldName;
    std::string worldFirstMap;
    std::vector<Map *> maps;

public:
    World(std::string file_name, Player *_player);
    ~World();

    void HandleKeyUp(SDL_Event event);
    void HandleMouseClickUp(SDL_Event event);
    void HandleMouseClickDown(SDL_Event event);
};

#endif