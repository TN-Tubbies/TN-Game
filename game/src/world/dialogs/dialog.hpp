#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../lib/json.hpp"

#include "../../static/ttf.hpp"
#include "dialog_line.hpp"
#include "../world_enums.hpp"

class Dialog
{
private:
    std::vector<DialogLine> lines;

    SDL_Texture *SpeakerTexture;
    SDL_Texture *BoxTexture;
    SDL_Texture *TextTexture;
    int x_box, y_box;
    int box_width, box_height;
    int x_speaker, y_speaker, speaker_size;
    int x_text, y_text, text_width;

public:
    Dialog(std::string file_name);
    ~Dialog();
};

#endif