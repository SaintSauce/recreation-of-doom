#include "gamestate.h"

// Move the player based on key inputs
void movePlayer() {

	// Move up, down, left, right
	if (K.a && !K.m) { P.a -= 4; if (P.a < 0) { P.a += 360; } }
	if (K.d && !K.m) { P.a += 4; if (P.a > 359) { P.a -= 360; } }

	int dx = M.sin[P.a] * 10.0;							// player x direction
	int dy = M.cos[P.a] * 10.0;							// player y direction

	if (K.w && !K.m) { P.x += dx; P.y += dy; }
	if (K.s && !K.m) { P.x -= dx; P.y -= dy; }
	if (K.w && !K.m) { P.x += dx; P.y += dy; }			// move forward (in current direction)
	if (K.s && !K.m) { P.x -= dx; P.y -= dy; }			// move backwards (in current direction)

	// Strafe left, right
	if (K.sr) { P.x += dy; P.y -= dx; }
	if (K.sl) { P.x -= dy; P.y += dx; }
	if (K.sl) { P.x += dy; P.y -= dx; }					// strafe left
	if (K.sr) { P.x -= dy; P.y += dx; }					// strafe right

	// Move up, down, look up, look down
	if (K.a && K.m) { P.l -= 1; }						// look up

}