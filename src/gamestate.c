#include "config.h"
#include "engine.h"
#include "gamestate.h"
#include "graphics.h"
#include "input.h"
#include "movement.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

// Global variables
Time T;                         // Game time
Key K;                          // Keyboard press events
Player P;                       // Player instance
int tick;                       // Idk tbh.
trig M;

SDL_bool done;
SDL_Window* window;
SDL_Renderer* renderer;

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
    framerate = 20;
    framerateThreshold = 1000 / framerate;

    // store sin/cos in degrees
    for (int deg = 0; deg < 360; deg++) {
        M.cos[deg] = cos(deg / 180.0 * M_PI);
        M.sin[deg] = sin(deg / 180.0 * M_PI);
    }

    // Initialize player
    P.x = 70; P.y = -110; P.z = 20; P.a = 0; P.l = 0;

    // Load Sectors
    int s, w, v1 = 0, v2 = 0;
    for (s = 0;s < numSect;s++)
    {
        S[s].ws = loadSectors[v1 + 0];                   //wall start number
        S[s].we = loadSectors[v1 + 1];                   //wall end   number
        S[s].z1 = loadSectors[v1 + 2];                   //sector bottom height
        S[s].z2 = loadSectors[v1 + 3] - loadSectors[v1 + 2]; //sector top    height
        S[s].c1 = loadSectors[v1 + 4];                   //sector top    color
        S[s].c2 = loadSectors[v1 + 5];                   //sector bottom color
        v1 += 6;
        for (w = S[s].ws;w < S[s].we;w++)
        {
            W[w].x1 = loadWalls[v2 + 0]; //bottom x1
            W[w].y1 = loadWalls[v2 + 1]; //bottom y1
            W[w].x2 = loadWalls[v2 + 2]; //top    x2
            W[w].y2 = loadWalls[v2 + 3]; //top    y2
            W[w].c = loadWalls[v2 + 4]; //wall color
            v2 += 5;
        }
    }
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
    if (T.curr - T.prev >= framerateThreshold) {
        shouldDrawImage = true;
        T.prev = T.curr;
    }
    else {
        shouldDrawImage = false;
    }
}

void renderGame(SDL_Renderer* renderer) {
    // Render game state
    if (shouldDrawImage) {
        draw3D(renderer);
        movePlayer();
        SDL_RenderPresent(renderer);
    }
}