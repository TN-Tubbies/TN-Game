#include "sdl_compare_surfaces.hpp"

int SDL_Surfaces_comparable(SDL_Surface *s1, SDL_Surface *s2)
{
    return (s1->format->format == s2->format->format && s1->w == s2->w && s1->h == s2->h);
}

int SDL_Surfaces_equal(SDL_Surface *s1, SDL_Surface *s2)
{
    if (!SDL_Surfaces_comparable(s1, s2))
    {
        return 0;
    }
    // the # of bytes we want to check is bytes_per_row * rows
    int len = s1->pitch * s1->h;
    return memcmp(s1->pixels, s2->pixels, len);
}

bool AreSurfacesEqual(SDL_Surface *s1, SDL_Surface *s2)
{
    return !(SDL_Surfaces_equal(s1, s2) == 0);
}