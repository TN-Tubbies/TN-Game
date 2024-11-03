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

    SDL_Texture *SpeakerTexture;
    SDL_Texture *BoxTexture;
    SDL_Texture *TextTexture;
    int x_box, y_box;
    int box_width, box_height;
    int x_speaker, y_speaker, speaker_size;
    int x_text, y_text, text_width;

public:
    Dialog();
};

#endif