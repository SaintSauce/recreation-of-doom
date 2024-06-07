#include <SDL2/SDL.h>
#include "config.h"
#include "gamestate.h"
#include "loadmap.h"
#include "utils.h"

// Draw a pixel at x/y with color c
void pixel(SDL_Renderer* renderer, int x, int y, int c) {
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

// Clear background to background color
void clearBackground() {
    int x, y;
    for (y = 0;y < WIN_HEIGHT;y++)
    {
        for (x = 0;x < WIN_WIDTH;x++) { pixel(renderer, x, y, 8); } //clear background color
    }
}

void clipBehindPlayer(int* x1, int* y1, int* z1, int x2, int y2, int z2) {  // clip line
    float da = *y1;                                                     // distance plane -> point a
    float db = y2;                                                      // distance plane -> point b
    float d = da - db; if (d == 0) { d = 1; }                           // prevent division by zero
    float s = da / (da - db);                                           // intersection factor (between 0 and 1)
    *x1 = *x1 + s * (x2 - (*x1));
    *y1 = *y1 + s * (y2 - (*y1)); if (*y1 == 0) { *y1 = 1; }              // prevent divide by zero 
    *z1 = *z1 + s * (z2 - (*z1));
}

void drawWall(SDL_Renderer* renderer, int x1, int x2, int b1, int b2, int t1, int t2, int c, int s) {
    int x, y;

    // Hold difference in distance
    int dyb = b2 - b1;                                  // y distance of bottom line
    int dyt = t2 - t1;                                  // y distance of top    line
    int dx = x2 - x1; if (dx == 0) { dx = 1; }          // x distance
    int xs = x1;                                        // hold initial x1 starting position 

    // CLIP X
    if (x1 < 1) { x1 = 1; } // clip left
    if (x2 < 1) { x2 = 1; } // clip left
    if (x1 > WIN_WIDTH - 1) { x1 = WIN_WIDTH - 1; } // clip right
    if (x2 > WIN_WIDTH - 1) { x2 = WIN_WIDTH - 1; } // clip right

    // draw x verticle lines
    for (x = x1;x < x2; x++)
    {
        // The Y start and end point
        int y1 = dyb * (x - xs + 0.5) / dx + b1; // y bottom point
        int y2 = dyt * (x - xs + 0.5) / dx + t1; // y bottom point
        // Clip Y
        if (y1 < 1) { y1 = 1; } // clip y 
        if (y2 < 1) { y2 = 1; } // clip y 
        if (y1 > WIN_HEIGHT - 1) { y1 = WIN_HEIGHT - 1; } // clip y 
        if (y2 > WIN_HEIGHT - 1) { y2 = WIN_HEIGHT - 1; } // clip y 
        // surface
        if (S[s].surface == 1) { S[s].surf[x] = y1; continue; } // save bottom points
        if (S[s].surface == 2) { S[s].surf[x] = y2; continue; } // save top    points
        if (S[s].surface == -1) { for (y = S[s].surf[x];y < y1;y++) { pixel(renderer, x, y, S[s].c1); }; } // bottom
        if (S[s].surface == -2) { for (y = y2;y < S[s].surf[x];y++) { pixel(renderer, x, y, S[s].c2); }; } // top
        for (y = y1;y < y2;y++) { pixel(renderer, x, y, c); } // normal wall
    }
}

void draw3D(SDL_Renderer* renderer) {
    int s, w, loop, wx[4], wy[4], wz[4];
    float CS = M.cos[P.a], SN = M.sin[P.a];

    // order sectors by distance
    for (s = 0;s < numSect - 1;s++)
    {
        for (w = 0;w < numSect - s - 1;w++)
        {
            if (S[w].d < S[w + 1].d)
            {
                sectors st = S[w]; S[w] = S[w + 1]; S[w + 1] = st;
            }
        }
    }

    //draw sectors
    for (s = 0; s < numSect; s++)
    {
        S[s].d = 0; //clear distance
        if (P.z < S[s].z1) { S[s].surface = 1; }  //bottom surface
        else if (P.z > S[s].z2) { S[s].surface = 2; }  //top    surface
        else { S[s].surface = 0; }  //no     surfaces
        for (loop = 0; loop < 2; loop++)
        {
            for (w = S[s].ws;w < S[s].we;w++)
            {
                //offset bottom 2 points by player
                int x1 = W[w].x1 - P.x, y1 = W[w].y1 - P.y;
                int x2 = W[w].x2 - P.x, y2 = W[w].y2 - P.y;

                //swap for surface
                if (loop == 0) { int swp = x1; x1 = x2; x2 = swp; swp = y1; y1 = y2; y2 = swp; }

                //world X position 
                wx[0] = x1 * CS - y1 * SN;
                wx[1] = x2 * CS - y2 * SN;
                wx[2] = wx[0];                          //top line has the same x
                wx[3] = wx[1];

                //world Y position (depth)
                wy[0] = y1 * CS + x1 * SN;
                wy[1] = y2 * CS + x2 * SN;
                wy[2] = wy[0];                          //top line has the same y 
                wy[3] = wy[1];
                S[s].d += dist(0, 0, (wx[0] + wx[1]) / 2, (wy[0] + wy[1]) / 2);  //store this wall distance

                //world z height
                wz[0] = S[s].z1 - P.z + ((P.l * wy[0]) / 32.0);
                wz[1] = S[s].z1 - P.z + ((P.l * wy[1]) / 32.0);
                wz[2] = wz[0] + S[s].z2;                       //top line has new z 
                wz[3] = wz[1] + S[s].z2;

                //dont draw if behind player
                if (wy[0] < 1 && wy[1] < 1) { continue; }      //wall behind player, dont draw

                //point 1 behind player, clip
                if (wy[0] < 1)
                {
                    clipBehindPlayer(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]); //bottom line
                    clipBehindPlayer(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]); //top line
                }

                //point 2 behind player, clip
                if (wy[1] < 1)
                {
                    clipBehindPlayer(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]); //bottom line
                    clipBehindPlayer(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]); //top line
                }

                //screen x, screen y position
                wx[0] = wx[0] * 200 / wy[0] + HALF_WIN_WIDTH; wy[0] = wz[0] * 200 / wy[0] + HALF_WIN_HEIGHT;
                wx[1] = wx[1] * 200 / wy[1] + HALF_WIN_WIDTH; wy[1] = wz[1] * 200 / wy[1] + HALF_WIN_HEIGHT;
                wx[2] = wx[2] * 200 / wy[2] + HALF_WIN_WIDTH; wy[2] = wz[2] * 200 / wy[2] + HALF_WIN_HEIGHT;
                wx[3] = wx[3] * 200 / wy[3] + HALF_WIN_WIDTH; wy[3] = wz[3] * 200 / wy[3] + HALF_WIN_HEIGHT;

                //draw points
                drawWall(renderer, wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], W[w].c, s);
            }
            S[s].d /= (S[s].we - S[s].ws); //find average sector distance
            S[s].surface *= -1;          //flip to negative to draw surface
        }
    }
}