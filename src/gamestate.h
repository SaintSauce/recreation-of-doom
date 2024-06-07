#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>

typedef struct {
    int prev, curr;
} Time;

typedef struct {
    int w, a, s, d;
    int sl, sr;
    int m;
} Key;

typedef struct {
    int x, y, z;
    int health;

    // Other player attributes
} Player;

// Game state variables
extern Time T;
extern Key K;
extern Player p;
extern int tick;
extern SDL_bool done;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

// Function prototypes
void initGame();
void updateGame();
void renderGame(SDL_Renderer *renderer);

#endif