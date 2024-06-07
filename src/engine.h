#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include "config.h"
#include "gamestate.h"

void clearBackground(SDL_Renderer *renderer);
void pixel(SDL_Renderer *renderer, int x, int y, int c);
void draw3D(SDL_Renderer *renderer);

#endif