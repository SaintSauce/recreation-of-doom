#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "config.h"
#include "gamestate.h"
#include "graphics.h"
#include "engine.h"
#include "movement.h"
#include "input.h"

int main(int argc, char* argv[]) {
    // Initialize game state
    initGame();

    // Game loop
    SDL_Event event;
    while (!done) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            processEvents(&event);
        }

        // Update game state
        updateGame();                       // information-wise
        renderGame(renderer);               // image-wise
        clearBackground(renderer);
    }

    // Clean up
    cleanupGraphics(window, renderer);

    return 0;
}