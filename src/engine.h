#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include "config.h"
#include "gamestate.h"
#include "loadmap.h"
#include "utils.h"

void clearBackground(SDL_Renderer* renderer);
void pixel(SDL_Renderer* renderer, int x, int y, int c);
void draw3D(SDL_Renderer* renderer);

void clipBehindPlayer(int* x1, int* y1, int* z1, int x2, int y2, int z2);

#endif