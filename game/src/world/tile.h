#ifndef TILE_H
#define TILE_H

#include <string>

class Tile{
private:
    bool isWall;
    std::string AnimationPath;
public:
    Tile(bool is_wall);
    Tile(bool is_wall, std::string animation_path);

    bool IsWall();
    std::string GetAnimationPath();
};

class WarpingTile : public Tile {
private:
    int DestinationMapID;
    int DestinationX, DestinationY;
public:
    WarpingTile(int destination_map_id, int destination_x, int destination_y);

    int GetDestinationMapID();
    int* GetDestinationCoordinates();
};

#endif