#ifndef GAMESTATE_H
#define GAMESTATE_H

#define M_PI 3.14159265358979323846

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
    int x, y, z;             // player position. Z is up
    int a;                 // player angle of rotation left right
    int l;                 // variable to look up and down
} Player;

typedef struct {
    float cos[360];        // Save sin cos in values 0 - 360 degrees 
    float sin[360];
} trig;


// Game state variables
extern Time T;
extern Key K;
extern Player P;
extern trig M;
extern int tick;
extern SDL_bool done;
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// Function prototypes
void initGame();
void updateGame();
void renderGame(SDL_Renderer* renderer);

#endif