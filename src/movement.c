#include "gamestate.h"

// Move the player based on key inputs
void movePlayer() {
    if (K.a == 1 && K.m == 0) { printf("left\n"); }
    if (K.d == 1 && K.m == 0) { printf("right\n"); }
    if (K.w == 1 && K.m == 0) { printf("up\n"); }
    if (K.s == 1 && K.m == 0) { printf("down\n"); }
    if (K.sl == 1) { printf("strafe left\n"); }
    if (K.sr == 1) { printf("strafe right\n"); }
    if (K.a == 1 && K.m == 1) { printf("look up\n"); }
    if (K.d == 1 && K.m == 1) { printf("look down\n"); }
    if (K.w == 1 && K.m == 1) { printf("move up\n"); }
    if (K.s == 1 && K.m == 1) { printf("move down\n"); }
}