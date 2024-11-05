#include "dialog_line.hpp"

DialogLine::DialogLine(std::string fullText, std::string speaker, TTF_Font *textFont,
                       int speaker_size, int text_width)
{
    this->FullText = fullText;
    this->Speaker = speaker;
    this->TextFont = textFont;
    currentRowIndex = 0;

    int TextMaxWidth;
    if (speaker == "")
    {
        TextMaxWidth = speaker_size + DIALOG_BOX_BORDER + text_width;
    }
    else
    {
        TextMaxWidth = text_width;
    }

    std::vector<std::string> lines;
    unsigned int currentLetter = 0;
    std::string currentLine;
    while (currentLetter < fullText.size())
    {
        currentLine += fullText.at(currentLetter);
        // TODO: load text with font, and check if its size is less than the max
        currentLetter++;
    }
}

void DialogLine::ResetRead()
{
    currentRowIndex = 0;
}
std::string DialogLine::Read()
{
    std::string currentLine = Rows[currentRowIndex];
    currentRowIndex++;
    return currentLine;
}