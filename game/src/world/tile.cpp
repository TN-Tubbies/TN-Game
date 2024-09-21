#include "tile.h"

Tile::Tile(void){
    this->isWall = true;
    this->AnimationPath = "*None*";
}
Tile::Tile(bool is_wall){
    this->isWall = is_wall;
    this->AnimationPath = "*None*";
}
Tile::Tile(bool is_wall, std::string animation_path){
    this->isWall = is_wall;
    this->AnimationPath = animation_path;
}
bool Tile::IsWall() { return isWall; }
std::string Tile::GetAnimationPath() { return AnimationPath; }

// ------------------------------------------------------------------------------------------------

WarpingTile::WarpingTile(int destination_map_id,
    int destination_x, int destination_y) : Tile(false){
    this->DestinationMapID = destination_map_id;
    this->DestinationX = destination_x;
    this->DestinationY = destination_y;
}
int WarpingTile::GetDestinationMapID() { return DestinationMapID; }
int WarpingTile::GetDestinationX() { return DestinationX; }
int WarpingTile::GetDestinationY() { return DestinationY; }