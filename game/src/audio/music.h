#ifndef MUSIC_H
#define MUSIC_H

#include <string>

#include <SDL2/SDL_mixer.h>

class Music {
private:    
    std::string Name;
    Mix_Music *SDL_Music;
public:
    Music(std::string file_name);
    ~Music();

    void Play(int times);
};

#endif