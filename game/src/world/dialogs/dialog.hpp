#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../world_enums.hpp"

class Dialog
{
private:
    std::string FullText;
    std::vector<std::string> Lines;
    int currentLineIndex;
    enum DialogShowType ShowType;

    SDL_Texture *Box;
    int BoxWidth, BoxHeight;
    // TODO: add textable part data
public:
    Dialog(std::string file_name, enum DialogBoxType boxType, enum DialogShowType showType);
};

#endif