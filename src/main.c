/*
	-> 10 : 45
*/

#define GL_SILENCE_DEPRECATION

#include <math.h>
#include <stdio.h>
#include <GL/freeglut.h>

#define RESOLUTION				2								// Resolution scale factor
#define SCREEN_WIDTH			(160 * RESOLUTION)				// Screen width
#define SCREEN_HEIGHT			(120 * RESOLUTION)				// Screen height
#define HALF_SCREEN_WIDTH		(SCREEN_WIDTH/2)				// Half of screen width
#define HALF_SCREEN_HEIGHT		(SCREEN_HEIGHT/2)				// Half of screen height
#define PIXEL_SCALE				(4/RESOLUTION)					// OpenGL pixel scale
#define WINDOW_WIDTH			(SCREEN_WIDTH * PIXEL_SCALE)	// OpenGL Window Width
#define WINDOW_HEIGHT			(SCREEN_HEIGHT * PIXEL_SCALE)	// OpenGL Window Height

#define numSect					4								// number of sectors
#define numWall					16								// number of walls

#define FOV_VAL 				300								// need to convert later

// ----------------------------------------------------------------------------------------

typedef struct {
	int prev, curr;			// only draw constant framerate
} time_t; time_t T;

typedef struct {
	int w, a, s, d;			// move up, down, left, right
	int sl, sr;				// strafe left, right
	int m;					// move up, down, look up, down
} keys_t; keys_t K;

typedef struct {
	float cos[360];			// lookup values for sin & cos
	float sin[360];			// access index by degree (0 - 360)
} math_t; math_t M;

typedef struct {
	int x, y, z;			// player position (camera posX, posY, posZ)
	int a;					// angle of rotation (left - right)
	int l;					// look up / down
} player_t; player_t P;

typedef struct {
	int x1, y1;				// bottom line point 1
	int x2, y2;				// bottom line point 2
	int c;					// wall color
} walls; walls W[30];

typedef struct {
	int ws, we;				// wall number start and end
	int z1, z2;				// height of bottom and top
	int d;					// add y distances to sort drawing order
	int c1, c2;				// top and bottom color
	int surf[SCREEN_WIDTH];	// to hold points for surface
	int surface;			// is there a surface to draw
} sectors; sectors S[30];

typedef struct {
	int fov_scale;
	// Will add more stuff
} RenderSettings; RenderSettings settings;

// ----------------------------------------------------------------------------------------

void drawPixel(int x, int y, int c) {

	int rgb[3];
	
	switch (c) {
        case 0: rgb[0] = 255; rgb[1] = 255; rgb[2] =   0; break;  // yellow
        case 1: rgb[0] = 160; rgb[1] = 160; rgb[2] =   0; break;  // dark yellow
        case 2: rgb[0] =   0; rgb[1] = 255; rgb[2] =   0; break;  // green
        case 3: rgb[0] =   0; rgb[1] = 160; rgb[2] =   0; break;  // dark green
        case 4: rgb[0] =   0; rgb[1] = 255; rgb[2] = 255; break;  // cyan
        case 5: rgb[0] =   0; rgb[1] = 160; rgb[2] = 160; break;  // dark cyan
        case 6: rgb[0] = 160; rgb[1] = 100; rgb[2] =   0; break;  // brown
        case 7: rgb[0] = 110; rgb[1] =  50; rgb[2] =   0; break;  // dark brown
        case 8: rgb[0] =   0; rgb[1] =  60; rgb[2] = 130; break;  // background
    }

    glColor3ub(rgb[0], rgb[1], rgb[2]);							  // set the color
	glBegin(GL_POINTS);
	glVertex2i(x * PIXEL_SCALE + 2, y * PIXEL_SCALE + 2);
	glEnd();
}

void movePlayer() {
	// Move up, down, left, right
	if (K.a && !K.m) { P.a -= 4; if (P.a < 0) { P.a += 360; } }
	if (K.d && !K.m) { P.a += 4; if (P.a > 359) { P.a -= 360; } }

	int dx = M.sin[P.a] * 10.0;							// player x direction
	int dy = M.cos[P.a] * 10.0;							// player y direction

	if (K.w && !K.m) { P.x += dx; P.y += dy; }			// move forward (in current direction)
	if (K.s && !K.m) { P.x -= dx; P.y -= dy; }			// move backwards (in current direction)

	// Strafe left, right
	if (K.sl) { P.x += dy; P.y -= dx; }					// strafe left
	if (K.sr) { P.x -= dy; P.y += dx; }					// strafe right

	// Move up, down, look up, look down
	if (K.a && K.m) { P.l -= 1; }						// look up
	if (K.d && K.m) { P.l += 1; }						// look down
	if (K.w && K.m) { P.z -= 4; }						// fly down
	if (K.s && K.m) { P.z += 4; }						// fly up
}

void clearBackground() {
	int x, y;
	for (y = 0; y < SCREEN_HEIGHT; y++) {
		for (x = 0; x < SCREEN_WIDTH; x++) {
			drawPixel(x, y, 8);						// clear screen to background color
		}
	}
}

void clipBehindPlayer(int *x1, int *y1, int *z1, int x2, int y2, int z2) {	// clip line
	float da = *y1;															// distance plane -> point a
	float db = y2;															// distance plane -> point b
	float d = da - db; if (d == 0) { d = 1; }
	float s = da / (da - db);												// intersection factor (0 - 1)
	*x1 = *x1 + s * (x2 - (*x1));
	*y1 = *y1 + s * (y2 - (*y1)); if (*y1 == 0) { *y1 = 1; }				// prevent divide by zero
	*z1 = *z1 + s * (z2 - (*z1));
}

void drawWall(int x1, int x2, int bot_1, int bot_2, int top_1, int top_2, int c, int s) {
	// Hold the difference in distance
	int dy_bottom = bot_2 - bot_1;								// y distance of bottom line
	int dy_top = top_2 - top_1;									// y distance of top line
	int dx = x2 - x1; 											// x distance
	
	if (dx == 0) { 												// avoid division by zero
		dx = 1; 
	}
	
	int xs = x1;												// hold initial x1 starting position

	// clip X (+ a delimeter pixel)
	if (x1 < 1) { x1 = 1; } 									// clip left
	if (x2 < 1) { x2 = 1; }										// clip left
	if (x1 > SCREEN_WIDTH - 1) { x1 = SCREEN_WIDTH - 1; }		// clip right
	if (x2 > SCREEN_WIDTH - 1) { x2 = SCREEN_WIDTH - 1; }		// clip right

	// Draw vertical lines
	int x, y;
	for (x = x1; x < x2; x++) {

		// The y start and end point
		int y1 = dy_bottom * (x - xs + 0.5) / dx + bot_1;		// y bottom point
		int y2 = dy_top * (x - xs + 0.5) / dx + top_1;			// y bottom point

		// clip Y
		if (y1 < 1) { y1 = 1; }									// clip y
		if (y2 < 1) { y2 = 1; }									// clip y
		if (y1 > SCREEN_HEIGHT - 1) { y1 = SCREEN_HEIGHT - 1; }	// clip y
		if (y2 > SCREEN_HEIGHT - 1) { y2 = SCREEN_HEIGHT - 1; }	// clip y

		if (S[s].surface == 1) { S[s].surf[x] = y1; continue; } // save bottom points
		if (S[s].surface == 2) { S[s].surf[x] = y2; continue; } // save top points
		if (S[s].surface == -1) { for (y = S[s].surf[x]; y < y1; y++) { drawPixel(x, y, S[s].c1); }; } // bottom
		if (S[s].surface == -2) { for (y = y2; y < S[s].surf[x]; y++) { drawPixel(x, y, S[s].c2); }; } // top

		for (y = y1; y < y2; y++) {
			drawPixel(x, y, c);			// normal wall (front-facing wlal)
		}
	}
}

// Euclidean distance formula
int dist(int x1, int y1, int x2, int y2) {
	int distance = sqrt( (x2 - x2) * (x2 - x1) + (y2 - y1) * (y2 - y1) );
	return distance;
}

void draw3D() {

	int s, w;

	// Wall values (x, y, z)
	int wx[4], wy[4], wz[4];

	// Player angle
	float cosine = M.cos[P.a];
	float sine = M.sin[P.a];

	// Order sectors by distance
	// Implements bubble sort
	for (s = 0; s < numSect - 1; s++) {
		for (w = 0; w < numSect - s - 1; w++) {
			if (S[w].d < S[w + 1].d) {
				sectors st = S[w];
				S[w] = S[w + 1];
				S[w + 1] = st;
			}
		}
	}

	// Draw sectors
	for (s = 0; s < numSect; s++) {
		
		S[s].d = 0;										// clear distances

		if (P.z < S[s].z1) { S[s].surface = 1; }		// bottom surface (Player is below surface value)
		else if (P.z > S[s].z2) { S[s].surface = 2; }	// top surface (Player is above surface value)
		else { S[s].surface = 0; }						// no surfaces (Player is in the middle)

		for (int sides = 0; sides < 2; sides++) {		// draw each wall twice (back & front facing)

			for (w = S[s].ws; w < S[s].we; w++) {

				// Offset bottom 2 points by player
				int x1 = W[w].x1 - P.x, y1 = W[w].y1 - P.y;
				int x2 = W[w].x2 - P.x, y2 = W[w].y2 - P.y;

				// Swap for surface
				if (sides == 0) { int swp = x1; x1 = x2; x2 = swp; swp = y1; y1 = y2; y2 = swp; }
				
				/*
					2D vector (x, y) matrix rotation

					R(theta) = [
						[cos theta, - sin theta]
						[sin theta,   cos theta]
					]

					i.e. turn the (x, y) coordinates of the walls to the Player's angle

					then (x, y)^T R = 2D vector of rotated coordinates
				*/

				// World X position
				wx[0] = x1 * cosine - y1 * sine;
				wx[1] = x2 * cosine - y2 * sine;
				wx[2] = wx[0];								// top line has same x
				wx[3] = wx[1];

				// World Y position (depth)
				wy[0] = y1 * cosine + x1 * sine;
				wy[1] = y2 * cosine + x2 * sine;
				wy[2] = wy[0];								// top line has same y
				wy[3] = wy[1];

				// Store this wall distance
				S[s].d += dist(0, 0, (wx[0] + wx[1])/2, (wy[0] + wy[1])/2);

				// World Z height
				wz[0] = S[s].z1 - P.z + ((P.l * wy[0]) / 32.0);
				wz[1] = S[s].z1 - P.z + ((P.l * wy[1]) / 32.0);
				wz[2] = wz[0] + S[s].z2;					// 40 units higher than bottom line
				wz[3] = wz[1] + S[s].z2;

				if (wy[0] < 1 && wy[1] < 1) { continue; }	// don't draw if wall behind player

				// point 1 behind player, clip
				if (wy[0] < 1) {
					clipBehindPlayer(&wx[0], &wy[0], &wz[0], wx[1], wy[1], wz[1]);		// bottom line
					clipBehindPlayer(&wx[2], &wy[2], &wz[2], wx[3], wy[3], wz[3]);		// top line
				}

				// point 2 behind player, clip
				if (wy[1] < 1) {
					clipBehindPlayer(&wx[1], &wy[1], &wz[1], wx[0], wy[0], wz[0]);		// bottom line
					clipBehindPlayer(&wx[3], &wy[3], &wz[3], wx[2], wy[2], wz[2]);		// top line
				}

				// Screen x, screen y position
				wx[0] = wx[0] * settings.fov_scale / wy[0] + HALF_SCREEN_WIDTH; wy[0] = wz[0] * settings.fov_scale / wy[0] + HALF_SCREEN_HEIGHT;
				wx[1] = wx[1] * settings.fov_scale / wy[1] + HALF_SCREEN_WIDTH; wy[1] = wz[1] * settings.fov_scale / wy[1] + HALF_SCREEN_HEIGHT;
				wx[2] = wx[2] * settings.fov_scale / wy[2] + HALF_SCREEN_WIDTH; wy[2] = wz[2] * settings.fov_scale / wy[2] + HALF_SCREEN_HEIGHT;
				wx[3] = wx[3] * settings.fov_scale / wy[3] + HALF_SCREEN_WIDTH; wy[3] = wz[3] * settings.fov_scale / wy[3] + HALF_SCREEN_HEIGHT;

				// Draw points
				drawWall(wx[0], wx[1], wy[0], wy[1], wy[2], wy[3], W[w].c, s);
			}

			S[s].d /= (S[s].we - S[s].ws);		// find average sector distance
			S[s].surface *= -1;					// flip to negaative to draw surface

		}
	}
}

void display() {
	
	/*
		only draw new frame if delta > 1000 ms / fps (frame/s)
	*/
	
	if (T.curr - T.prev >= 20) {									// Only draw 50 frames per second

		clearBackground();
		movePlayer();
		draw3D();

		T.prev = T.curr;

		/*
			Double buffering
			
			- front buffer : currently displayed on the screen
			- back buffer : next frame being drawn

			while the front buffer is displayed, the application
			draws the next frame in the back buffer, once drawing
			is complete, swap the front and back buffers (displays it)

			-> prevents flickering and tearing in animations in render
		*/

		glutSwapBuffers();

		glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);			// Prevent window rescaling
	}

	T.curr = glutGet(GLUT_ELAPSED_TIME);         				// 1000 ms per second
	glutPostRedisplay();

}

void KeysDown(unsigned char key, int x, int y) { 
    switch (key) {
        case 'w': K.w = 1; break;
        case 's': K.s = 1; break;
        case 'a': K.a = 1; break;
        case 'd': K.d = 1; break;
        case 'm': K.m = 1; break;
        case ',': K.sr = 1; break;
        case '.': K.sl = 1; break;
    }
}

void KeysUp(unsigned char key, int x, int y) { 
    switch (key) {
        case 'w': K.w = 0; break;
        case 's': K.s = 0; break;
        case 'a': K.a = 0; break;
        case 'd': K.d = 0; break;
        case 'm': K.m = 0; break;
        case ',': K.sr = 0; break;
        case '.': K.sl = 0; break;
    }
}

int loadSectors[] = {
	// wall start, wall end, z1 height, z2 height, bottom color, top color
	0, 	 4, 0, 40, 2, 3,		// sector 1
	4, 	 8, 0, 40, 4, 5,		// sector 2
	8, 	12, 0, 40, 6, 7,		// sector 3
	12, 16, 0, 40, 0, 1,		// sector 4
};

int loadWalls[] = {
	// x1, y1, x2, y2, color
	0, 0, 32, 0, 0,
	32, 0, 32, 32, 1,
	32, 32, 0, 32, 0,
	0, 32, 0, 0, 1,

	64, 0, 96, 0, 2,
	96, 0, 96, 32, 3,
	96, 32, 64, 32, 2,
	64, 32, 64, 0, 3,

	64, 64, 96, 64, 4,
	96, 64, 96, 96, 5,
	96, 96, 64, 96, 4,
	64, 96, 64, 64, 5,

	0, 64, 32, 64, 6,
	32, 64, 32, 96, 7,
	32, 96, 0, 96, 6,
	0, 96, 0, 64, 7,
};

void init() {

	int deg;

	// Calculate each sin/cos value for each 0 - 360 degrees
	for (deg = 0; deg < 360; deg++) {
		M.cos[deg] = cos(deg / 180.0 * M_PI);
		M.sin[deg] = sin(deg / 180.0 * M_PI);
	}

	// Renderer settings
	settings.fov_scale = FOV_VAL;

	// Initialize player variables
	P.x = 70;
	P.y = -110;
	P.z = 20;
	P.a = 0;
	P.l = 0;

	// Load sectors
	int s, w, v1 = 0, v2 = 0;
	for (s = 0; s < numSect; s++) {
		S[s].ws = loadSectors[v1 + 0];							// wall start number
		S[s].we = loadSectors[v1 + 1];							// wall end number
		S[s].z1 = loadSectors[v1 + 2];							// sector bottom height
		S[s].z2 = loadSectors[v1 + 3] - loadSectors[v1 + 2];	// sector top height
		S[s].c1 = loadSectors[v1 + 4];							// sector top color
		S[s].c2 = loadSectors[v1 + 5];							// sector bottom color
		v1 += 6;												// jump to next sector

		for (w = S[s].ws; w < S[s].we; w++) {
			W[w].x1 = loadWalls[v2 + 0];						// bottom x1
			W[w].y1 = loadWalls[v2 + 1];						// bottom y1
			W[w].x2 = loadWalls[v2 + 2];						// top x2
			W[w].y2 = loadWalls[v2 + 3];						// top y2
			W[w].c  = loadWalls[v2 + 4];						// wall color
			v2 += 5;											// jump to next wall
		}
	}
}

int main (int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(""); 
	glPointSize(PIXEL_SCALE);                       			// Set pixel size
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);				// Origin at bottom left
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(KeysDown);
	glutKeyboardUpFunc(KeysUp);
	glutMainLoop();
	return 0;
}