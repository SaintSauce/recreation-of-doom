#define GL_SILENCE_DEPRECATION
#include <math.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define res			1			// screen resolution multiples
#define SW			160*res		// screen width
#define SH			120*res		// screen height
#define CENTER_X 	(SW/2)		// half of screen width
#define CENTER_Y	(SH/2)		// half of screen height
// ----------------------------------------------------------------------
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
void movePlayer()		// can remove
{
	// move up, down, left, right
	if (K.a == 1 && K.m == 0) { printf("left\n"); }
	if (K.d == 1 && K.m == 0) { printf("right\n"); }
	if (K.w == 1 && K.m == 0) { printf("up\n"); }
	if (K.s == 1 && K.m == 0) { printf("down\n"); }

	// strafe left
	if (K.sl == 1) { printf("strafe left\n"); }
	if (K.sr == 1) { printf("strafe right\n"); }

	// move up, down, look up, look down
	if (K.a == 1 && K.m == 1) { printf("look up\n"); }
	if (K.d == 1 && K.m == 1) { printf("look down\n"); }
	if (K.w == 1 && K.m == 1) { printf("move up\n"); }
	if (K.s == 1 && K.m == 1) { printf("move down\n"); }
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

void draw3D()
{
	
}

void display()
{

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

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(640, 480, "Doom Game", NULL, NULL);
	if (!window) {
		glfwTerminate();	// fail
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

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window)) {
		// Render here
        glClear(GL_COLOR_BUFFER_BIT);
	
		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();
	return 0;
}
