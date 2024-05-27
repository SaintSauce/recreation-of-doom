#define GL_SILENCE_DEPRECATION
#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define res			6			// screen resolution multiples
#define SW			160*res		// screen width
#define SH			120*res		// screen height
#define SW2 		(SW/2)		// half of screen width
#define SH2			(SH/2)		// half of screen height
// ----------------------------------------------------------------------
typedef struct
{
	int fr1, fr2;		// create constant framerate
} time; time T;

typedef struct 
{	
	int w, s, d, a;		// move up, down, left, right
	int sl, sr;			// strafe left, right
	int m;				// move up, down, look up, down
} keys; keys K;

typedef struct
{
	float cos[360];
	float sin[360];
} math; math M;

typedef struct
{
	int x, y, z;		// player position
	int a;				// angle of rotation left, right
	int l;				// look up and down
} player; player P;
// ----------------------------------------------------------------------
// draw a pixel at (x, y) with color rgb
void pixel(int x, int y, int c)
{
	int rgb[3];
	if (c == 0) { rgb[0] = 255; rgb[1] = 255; rgb[2] =   0; } 	// yellow
	if (c == 1) { rgb[0] = 160; rgb[1] = 160; rgb[2] =   0; } 	// dark yellow
	if (c == 2) { rgb[0] = 	 0; rgb[1] = 255; rgb[2] =   0; } 	// green
	if (c == 3) { rgb[0] =   0; rgb[1] = 160; rgb[2] =   0; } 	// dark green
	if (c == 4) { rgb[0] =   0; rgb[1] = 255; rgb[2] = 255; } 	// cyan
	if (c == 5) { rgb[0] =   0; rgb[1] = 160; rgb[2] = 160; } 	// dark cyan
	if (c == 6) { rgb[0] = 160; rgb[1] = 100; rgb[2] =   0; } 	// brown
	if (c == 7) { rgb[0] = 110; rgb[1] =  50; rgb[2] =   0; } 	// dark brown
	if (c == 8) { rgb[0] =   0; rgb[1] =  60; rgb[2] = 130; } 	// background

	// Set the color
    glColor3ub(rgb[0], rgb[1], rgb[2]);

    // Calculate the normalized device coordinates (-1 to 1) for the pixel
    float ndcX = ((float)x / (float)SW2) - 1.0f;
    float ndcY = 1.0f - ((float)y / (float)SH2);

    // Set up an orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);

    // Set up the modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw a small rectangle (quad) at the pixel's position
    glBegin(GL_QUADS);
    glVertex2f(ndcX, ndcY);
    glVertex2f(ndcX + (2.0f / SW), ndcY);
    glVertex2f(ndcX + (2.0f / SW), ndcY - (2.0f / SH));
    glVertex2f(ndcX, ndcY - (2.0f / SH));
    glEnd();
}

void movePlayer()
{
	// move up, down, left, right
	if (K.a == 1 && K.m == 0) { P.a -= 4; if (P.a < 0) { P.a += 360; } }
	if (K.d == 1 && K.m == 0) { P.a += 4; if (P.a >359) { P.a -= 360; } }
	if (K.w == 1 && K.m == 0) { printf("up\n"); }
	if (K.s == 1 && K.m == 0) { printf("down\n"); }

	int dx = M.sin[P.a] * 10.0;
	int dy = M.cos[P.a] * 10.0;

	// strafe left
	if (K.sl == 1) { P.x -= dy; P.y += dx; }
	if (K.sr == 1) { P.x += dy; P.y -= dx; }

	// move up, down, look up, look down
	if (K.a == 1 && K.m == 1) { printf("look up\n"); }
	if (K.d == 1 && K.m == 1) { printf("look down\n"); }
	if (K.w == 1 && K.m == 1) { printf("move up\n"); }
	if (K.s == 1 && K.m == 1) { printf("move down\n"); }
}

void clearBackground()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (action == GLFW_PRESS || action == GLFW_RELEASE) {
		int state = (action == GLFW_PRESS) ? 1 : 0;

		switch(key) {
			case GLFW_KEY_W: K.w = state; break;
            case GLFW_KEY_S: K.s = state; break;
            case GLFW_KEY_A: K.a = state; break;
            case GLFW_KEY_D: K.d = state; break;
            case GLFW_KEY_LEFT_SHIFT: K.sl = state; break;
            case GLFW_KEY_RIGHT_SHIFT: K.sr = state; break;
            case GLFW_KEY_M: K.m = state; break;
		}
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int tick;

void draw3D()
{
	int x, y, c = 0;
	for (y = 0; y < SH2; y++) {
		for (x = 0; x < SW2; x++) {
			pixel(x,y,c); 
   			c+=1; if( c > 8 ){ c = 0;}
		}
	}
	//frame rate
 	tick += 1; if (tick > 20){ tick = 0;} pixel(SW2, SH2 + tick, 0); 
}

void display(GLFWwindow* window)
{
	int x, y;
	if (T.fr1 - T.fr2 >= 50) {		//only draw 20 frames/second
		movePlayer();
		draw3D();
		T.fr2 = T.fr1;
		glfwSwapBuffers(window); // Swap front and back buffers
	}

	T.fr1 = (int) glfwGetTime();
	glfwPollEvents(); // Poll for and process events

	// Delay to control the frame rate
    // Adjust the value (in seconds) to control the frame rate
    glfwSwapInterval(1);
}


void init()
{
	int x;

	// store sin/cos in degrees
	for (x = 0; x < 360; x++) {
		M.cos[x] = cos(x / 180.0 * M_PI);
		M.sin[x] = sin(x / 180.0 * M_PI);
	}

	// init player
	P.x = 70; P.y = -110; P.z = 20; P.a = 0; P.l = 0;
}

int main(void) 
{
	// Initialize the library
	if (!glfwInit()) {
		return -1;
	}

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);		// prevent window rescaling

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(SW, SH, "Doom Game", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

	// Register the key callback
    glfwSetKeyCallback(window, keyCallback);

	// Initialize your structures and variables
    init();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		// Render here
        // glClear(GL_COLOR_BUFFER_BIT);
	
		// Call the display function
		display(window);
	}

	// Terminate GLFW
	glfwTerminate();
	return 0;
}
