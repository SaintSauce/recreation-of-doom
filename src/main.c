#define GL_SILENCE_DEPRECATION

#include <math.h>
#include <stdio.h>
#include <GL/freeglut.h>

#define res				1						// 
#define SW				160 * res				// screen width
#define SH				120 * res				// screen height
#define SW2				(SW/2)					// half of screen width
#define SH2				(SH/2)					// half of screen height
#define pixelScale		4/res					// OpenGL pixel scale
#define GLSW			(SW * pixelScale)		// OpenGL Window Width
#define GLSH			(SH * pixelScale)		// OpenGL Window Height
// ----------------------------------------------------------------------
typedef struct 
{
	int fr1, fr2;			// to create constant frame rate
} time; time T;

typedef struct 
{
	int w, a, s, d;			// move up, down, left, right
	int sl, sr;				// strafe left, right
	int m;					// move up, down, look up, down
} keys; keys K;
// ----------------------------------------------------------------------
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

    glColor3ub(rgb[0], rgb[1], rgb[2]);		// set the color
	glBegin(GL_POINTS);
	glVertex2f(x * pixelScale + 2, y * pixelScale + 2);
	glEnd();
}

void movePlayer()
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

void clearBackground()
{
	int x, y;
	for (y = 0; y < SH; y++) 
	{
		for (x = 0; x < SW; x++) 
		{
			pixel(x, y, 8);				// clear screen to background color
		}
	}
}

int tick;

void draw3D()
{
	int x, y, c = 0;
	for (y = 0; y < SH2; y++)
	{
		for (x = 0; x < SW2; x++)
		{
			pixel(x, y, c);
			c += 1;
			if (c > 8) 
			{ 
				c = 0; 					// reset color to background
			}
		}
	}

	// framerate
	tick += 1;
	if (tick > 20)
	{
		tick = 0;
	}
	pixel(SW2, SH2 + tick, 0);
}

void display()
{
	int x, y;
	if (T.fr1 - T.fr2 >= 50)				// only draw 50 frames per second
	{
		clearBackground();
		movePlayer();
		draw3D();

		T.fr2 = T.fr1;
		glutSwapBuffers();
		glutReshapeWindow(GLSW, GLSH);		// prevent window rescaling
	}

	T.fr1 = glutGet(GLUT_ELAPSED_TIME);          //1000 ms per second
	glutPostRedisplay();
}

void KeysDown(unsigned char key, int x, int y)   
{ 
    if (key == 'w') { K.w = 1; } 
    if (key == 's') { K.s = 1; } 
    if (key == 'a') { K.a = 1; } 
    if (key == 'd') { K.d = 1; } 
    if (key == 'm') { K.m = 1; } 
    if (key == ',') { K.sr = 1; } 
    if (key == '.') { K.sl = 1; } 
    glutPostRedisplay();
}

void KeysUp(unsigned char key, int x, int y)
{ 
    if (key == 'w') { K.w = 0; }
    if (key == 's') { K.s = 0; }
    if (key == 'a') { K.a = 0; }
    if (key == 'd') { K.d = 0; }
    if (key == 'm') { K.m = 0; }
    if (key == ',') { K.sr = 0; } 
    if (key == '.') { K.sl = 0; }
    glutPostRedisplay();
}

void init()
{   
	   
}

int main (int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(GLSW/2,GLSH/2);
	glutInitWindowSize(GLSW,GLSH);
	glutCreateWindow(""); 
	glPointSize(pixelScale);                        //pixel size
	gluOrtho2D(0,GLSW,0,GLSH);                      //origin bottom left
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(KeysDown);
	glutKeyboardUpFunc(KeysUp);
	glutMainLoop();
	return 0;
}