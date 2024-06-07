#ifndef LOADMAP_H
#define LOADMAP_H

#include "config.h"

typedef struct {
    int x1, y1;             //bottom line point 1
    int x2, y2;             //bottom line point 2
    int c;                 //wall color
} walls;

typedef struct {
    int ws, we;             //wall number start and end
    int z1, z2;             //height of bottom and top 
    int d;                 //add y distances to sort drawing order
    int c1, c2;             //bottom and top color
    int surf[WIN_WIDTH];          //to hold points for surfaces
    int surface;           //is there a surfaces to draw
} sectors;

extern walls W[30];
extern sectors S[30];

extern int loadSectors[];
extern int loadWalls[];

#define numSect  4                          //number of sectors
#define numWall 16                          //number of walls

#endif