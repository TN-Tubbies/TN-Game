#ifndef BATTLE_HUD_H
#define BATTLE_HUD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <iostream>

#include "../../static/renderer.h"
#include "../../static/jersey.h"

class BattleHUD {
private:
    SDL_Texture *bg;
    SDL_Texture *name_disp;
    int name_w;
    int name_h;
public:
    BattleHUD(){};
    BattleHUD(std::string bg_path, std::string char_name, bool isFriendly);
    void render(int x, int y);
    ~BattleHUD();
};

#endif // BATTLE_HUD_H