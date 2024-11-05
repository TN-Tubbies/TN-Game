#ifndef DIALOG_LINE_HPP
#define DIALOG_LINE_HPP

#include <string>
#include <vector>

#include <SDL2/SDL_ttf.h>

#include "../../defs.hpp"

class DialogLine
{
private:
    std::string FullText;
    TTF_Font *TextFont;
    std::vector<std::string> Rows;
    int currentRowIndex;

    std::string Speaker;

public:
    DialogLine(std::string fullText, std::string speaker, TTF_Font *textFont,
               int speaker_size, int text_width);

    void ResetRead();
    std::string Read();
};

#endif