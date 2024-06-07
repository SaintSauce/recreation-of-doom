#include <SDL2/SDL.h>
#include "config.h"
#include "gamestate.h"

// Clear background to background color
void clearBackground(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);             // Set specific color
    SDL_RenderClear(renderer);                                  // Draw each pixel of the screen to bg-color
}

// Draw a pixel at x/y with color c
void pixel(SDL_Renderer *renderer, int x, int y, int c) {
    int rgb[3];
    switch (c) {
        case 0: rgb[0] = 255; rgb[1] = 255; rgb[2] = 0; break;  // Yellow
        case 1: rgb[0] = 160; rgb[1] = 160; rgb[2] = 0; break;  // Yellow darker
        case 2: rgb[0] = 0; rgb[1] = 255; rgb[2] = 0; break;    // Green
        case 3: rgb[0] = 0; rgb[1] = 160; rgb[2] = 0; break;    // Green darker
        case 4: rgb[0] = 0; rgb[1] = 255; rgb[2] = 255; break;  // Cyan
        case 5: rgb[0] = 0; rgb[1] = 160; rgb[2] = 160; break;  // Cyan darker
        case 6: rgb[0] = 160; rgb[1] = 100; rgb[2] = 0; break;  // Brown
        case 7: rgb[0] = 110; rgb[1] = 50; rgb[2] = 0; break;   // Brown darker
        case 8: rgb[0] = 0; rgb[1] = 60; rgb[2] = 130; break;   // Background
    }

    SDL_SetRenderDrawColor(renderer, rgb[0], rgb[1], rgb[2], 255);
    SDL_RenderDrawPoint(renderer, x, y);
}

// Draw 3D scene (placeholder function)
void draw3D(SDL_Renderer *renderer) {
    int c = 0;
    for (int y = 0; y < HALF_WIN_HEIGHT; y++) {
        for (int x = 0; x < HALF_WIN_WIDTH; x++) {
            pixel(renderer, x, y, c);
            c += 1;
            if (c > 8) { c = 0; }
        }
    }

    tick += 1;
    if (tick > 20) { tick = 0; }
    pixel(renderer, HALF_WIN_WIDTH, HALF_WIN_HEIGHT + tick, 0);
}