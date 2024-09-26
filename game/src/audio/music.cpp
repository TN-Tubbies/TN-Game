#include "music.hpp"

// ------------------------------------------------------------------------------------------------

Music::Music(std::string file_name)
{
    this->Name = file_name;
    this->SDL_Music = Mix_LoadMUS(file_name.c_str());
}
Music::~Music()
{
    Mix_FreeMusic(SDL_Music);
}

// ------------------------------------------------------------------------------------------------

void Music::Play(int times)
{
    Mix_PlayMusic(SDL_Music, times);
}

// ------------------------------------------------------------------------------------------------