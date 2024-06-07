#include "graphics.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include "config.h"

void initGraphics(SDL_Window **window, SDL_Renderer **renderer) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Create a window
    *window = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    if (!(*window)) {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        exit(1);
    }

    // Create a renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!(*renderer)) {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        exit(1);
    }
}

void renderRect(SDL_Renderer *renderer, int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void presentRenderer(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
}

void cleanupGraphics(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}