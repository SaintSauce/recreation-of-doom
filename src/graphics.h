#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

void initGraphics(SDL_Window **window, SDL_Renderer **renderer);
void renderRect(SDL_Renderer *renderer, int x, int y, int width, int height);
void presentRenderer(SDL_Renderer *renderer);
void cleanupGraphics(SDL_Window *window, SDL_Renderer *renderer);

#endif