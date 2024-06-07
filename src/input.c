#include "input.h"
#include "gamestate.h"

#include <stdio.h>
#include <SDL2/SDL.h>

// Process key press events
void processEvents(SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
        switch (event->key.keysym.sym) {
            case SDLK_w: K.w = 1; break;
            case SDLK_s: K.s = 1; break;
            case SDLK_a: K.a = 1; break;
            case SDLK_d: K.d = 1; break;
            case SDLK_m: K.m = 1; break;
            case SDLK_COMMA: K.sr = 1; break;
            case SDLK_PERIOD: K.sl = 1; break;
        }
    }
    if (event->type == SDL_KEYUP) {
        switch (event->key.keysym.sym) {
            case SDLK_w: K.w = 0; break;
            case SDLK_s: K.s = 0; break;
            case SDLK_a: K.a = 0; break;
            case SDLK_d: K.d = 0; break;
            case SDLK_m: K.m = 0; break;
            case SDLK_COMMA: K.sr = 0; break;
            case SDLK_PERIOD: K.sl = 0; break;
        }
    }
}