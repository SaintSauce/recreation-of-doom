#include "config.h"
#include "engine.h"
#include "gamestate.h"
#include "graphics.h"
#include "input.h"
#include "movement.h"

#include <stdbool.h>

// Global variables
Time T;            // Game time
Key K;             // Keyboard press events
Player p;          // Player instance
int tick;          // Idk tbh.

SDL_bool done;
SDL_Window *window;
SDL_Renderer *renderer;

// Framerate
int framerate;
int framerateThreshold;
bool shouldDrawImage = false;

void initGame() {
    // Initialize game state variables
    done = SDL_FALSE;

    // Initialize graphics
    initGraphics(&window, &renderer); // Initializes SDL library, window, renderer

    // Initialize timing variables
    T.prev = T.curr = SDL_GetTicks(); // Initialize time variables

    // Framerate
    framerate = 60;
    framerateThreshold = 1000 / framerate;
    shouldDrawImage = T.curr - T.prev >= framerateThreshold;
}

void updateGame() {
    // Update game state
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
        }
        processEvents(&event);
    }

    // Calculate shouldDrawImage based on frame rate
    T.curr = SDL_GetTicks();
    int deltaTimeImage = T.curr - T.prev;
    if (deltaTimeImage >= framerateThreshold) {
        shouldDrawImage = true;
        T.prev = T.curr;
    } else {
        shouldDrawImage = false;
    }

    if (shouldDrawImage) {
        clearBackground(renderer);
        movePlayer();
        draw3D(renderer);
        SDL_RenderPresent(renderer);
    }
}

void renderGame(SDL_Renderer *renderer) {
    // Render game state
}