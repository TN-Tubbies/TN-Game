#include "renderer.h"

static SDL_Renderer *renderer = NULL;

void Init_Renderer(void){
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in init: %s", SDL_GetError());
        exit(-1);
    }
    atexit(SDL_Quit);

    // Creation fenetre et attribution moteur rendu //
    SDL_Window *window;
    window = SDL_CreateWindow("SDLWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_INPUT_FOCUS);
    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in window init : %s", SDL_GetError());
        exit(-1);
    }
    SDL_Renderer *_renderer;
    _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in renderer init : %s", SDL_GetError());
        exit(-1);
    }
    SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);

    renderer = _renderer;
}
SDL_Renderer *Get_Renderer(void){ return renderer; }
void Destroy_Renderer(void){ SDL_DestroyRenderer(renderer); }