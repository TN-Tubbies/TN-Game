#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>

#include <SDL2/SDL_mixer.h>

class Music
{
private:
    std::string Name;
    Mix_Music *SDL_Music;

public:
    Music() {};
    Music(std::string file_name);
    ~Music();

    void Play(int times);
};

#endif