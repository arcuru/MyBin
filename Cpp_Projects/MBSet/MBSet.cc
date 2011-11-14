/** @file MBSet.cc
 *  Calculate and display the Mandelbrot set
 *  ECE4893/8893 final project, Fall 2011
 *  Patrick Jackson
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include <GL/glut.h>
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "complex.h"

using namespace std;

#define DEBUG //!< Un comment to print debug statements
#ifdef DEBUG
#include <sys/time.h>
#include <iomanip>
#endif

// Defaults
unsigned int init_width = 512;
unsigned int init_height = 512;
double init_XMin = -2.0;
double init_YMin = -1.2;
double init_XMax = 1.0;
double init_YMax = 1.8;
int      maxIt = 2000;     //!< Max iterations for the set computations

//GLfloat palette[5][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {0.5, 0.5, 0.5}, {1.0, 1.0, 1.0}}; 
GLfloat* default_palette;

//! Structure to hold all information necessary for a single viewport
struct MBWindow {
	double XMin;           //!< Minimum X value of the window
	double XMax;           //!< Maximum X value of the window
	double YMin;           //!< Minimum Y value of the window
	double YMax;           //!< Maximum Y value of the window
	unsigned int width;    //!< Width of the window in pixels
	unsigned int height;   //!< Height of the window in pixels
	unsigned int maxIters; //!< Maximum iterations for the computations
	unsigned short* Iters;   //!< Holds the iterations
	GLfloat* palette;      //!< Color palette for this window
};

MBWindow window;  //!< Struct holding the properties of the current window

/** Iterate Point
 *  returns the number of iterations below max_iter that it took to reach
 *  the threshold
 *
 *  @param a Real component of original point
 *  @param b Imaginary component of original point
 *  @param max_iter Maximum number of iterations to run
 *  @return The number of iterations left until reaching the max
 */
unsigned int iterate_point(double a, double b, unsigned int max_iter)
{
/* Using the Complex class
	Complex c(a, b);
	Complex z(0, 0);

	do {
		z = z*z;
		z = z + c;
		if (z.Mag2() > 16.0)
			break;
	} while (--max_iter);
	return max_iter;
*/
	double za, zb, za2, zb2;
	za = zb = za2 = zb2 = 0.0;

	do {
		// Run a single step of the algorithm and check
		zb = (za + za) * zb + b;
		za = za2 - zb2 + a;
		za2 = za * za;
		zb2 = zb * zb;
		if ( (za2 + zb2) >= 4.0 )
			break;
	} while ( --max_iter );

	return max_iter;
}

void mandelbrot_compute(MBWindow* w)
{
	// Skip if already calculated this window
	if (NULL != w->Iters)
		return;
#ifdef DEBUG
	cout << "Calculating..." << endl;
	struct timeval t;
	gettimeofday(&t, 0);
#endif
	w->Iters = (unsigned short*) malloc(sizeof(unsigned short) * w->width * w->height);
	double real, imag;
	for (int r = 0; r < w->height; r++) {
		imag = (((double) r) / ((double) w->height - 1)) * (w->YMax - w->YMin) + w->YMin;
		for (int c = 0; c < w->width; c++) {
			real = (((double) c) / ((double) w->width - 1)) * (w->XMax - w->XMin) + w->XMin;
			w->Iters[w->width * r + c] = iterate_point(real, imag, maxIt);
		}
	}
#ifdef DEBUG
	cout << "Finished calculating" << endl;
	struct timeval t2;
	gettimeofday(&t2, 0);
	unsigned int time = (t2.tv_sec - t.tv_sec) * 1000000 + (t2.tv_usec - t.tv_usec);
	cout << "Calculation time: " << setw(6) << ((float)time) / 1000000 << endl;
#endif
}

/** Display
 *  re-draw the image to the screen. Clear old screen, draw MBset,
 *  swap buffers.
 */
void display(void)
{
#ifdef DEBUG
	static int pass;
	cout << "Displaying pass " << ++pass << endl;
#endif

	// Clear all the colors
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Clear the matrix
	glLoadIdentity();

	// Set the viewing transformation
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Center the origin on the screen
	glTranslatef( ((double)window.width) / 2.0, ((double)window.height) / 2.0, 0);
	
	// Scale image to fill the whole screen
	double scaleX = ((double)window.width) / (window.XMax - window.XMin);
	double scaleY = ((double)window.height) / (window.YMax - window.YMin);
	double min_Scale = (scaleX < scaleY) ? scaleX : scaleY;
	glScalef(min_Scale, min_Scale, 0.0);

	// Size of one pixel
	double dx = 1.0 / ((double) window.width) * (window.XMax - window.XMin);
	double dy = 1.0 / ((double) window.height) * (window.YMax - window.YMin);
	double midx = ((double)(window.XMin + window.XMax)) / 2.0;
	double midy = ((double)(window.YMin + window.YMax)) / 2.0;
	midx *= -1;
	midy *= -1;
	glTranslatef(midx, midy, 0);

	// Calculate mandelbrot window
	mandelbrot_compute(&window);

	// Iterate over calculated image and display points
	glBegin( GL_POINTS );
	double real, imag;
	unsigned int iters;
	for (int r = 0; r < window.height; r++) {
		imag = (((double) r) / ((double) window.height - 1)) * (window.YMax - window.YMin) + window.YMin;
		for (int c = 0; c < window.width; c++) {
			real = (((double) c) / ((double) window.width - 1)) * (window.XMax - window.XMin) + window.XMin;
			int tmp = 3 * window.Iters[window.width * r + c];
			if (tmp < 0 || tmp > 3*maxIt)
				cout << tmp << endl;
			glColor3fv(&window.palette[3 * window.Iters[window.width * r + c]]);
			glVertex2f(real, imag);
		}
	}
	glEnd();

	// Double buffering
	glutSwapBuffers();
}

/** Initialize
 *  performs opengl initialization functions.
 */
void init()
{
	// Set bg color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);

	// Initialize default palette
	default_palette = (GLfloat*) malloc(sizeof(GLfloat) * (maxIt+1) * 3);
	for (int i = 0; i < maxIt*3; i++)
		default_palette[i] = ((GLfloat)rand()) / RAND_MAX;
	// Mark Black and white
	for (int i = 0; i < 3; i++) {
		default_palette[i] = 0.0;
		default_palette[3*maxIt-i+2] = 1.0;
		default_palette[3*maxIt-i-1] = 1.0;
		default_palette[3*maxIt-(2*i)-1] = 1.0;
		default_palette[3*maxIt-(3*i)-1] = 1.0;
	}

	// Initialize current window defaults
	window.XMin = init_XMin;
	window.YMin = init_YMin;
	window.XMax = init_XMax;
	window.YMax = init_YMax;
	window.maxIters = maxIt;
	window.width = init_width;
	window.height = init_height;
	window.Iters = NULL;
	window.palette = default_palette;
}

/** Reshape
 *  when the window is resized, redraw the image
 *
 *  @param w Width of new window
 *  @param h Height of new window
 */
void reshape(int w, int h)
{
#ifdef DEBUG
	cout << "Reshape: (" << w << ", " << h << ")" << endl;
#endif
	window.width = w;
	window.height = h;
	if (NULL != window.Iters)
		free(window.Iters);
	window.Iters = NULL;
	// Resize viewport and ortho projection
	glViewport(0,0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, (GLdouble)0.0, h, (GLdouble)-w, (GLdouble)w);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{ // Your mouse click processing here
  // state == 0 means pressed, state != 0 means released
  // Note that the x and y coordinates passed in are in
  // PIXELS, with y = 0 at the top.
#ifdef DEBUG
	cout << "Mouse: " << button << " - " << state << " - (" << x << ", " << y << ")" << endl;
#endif
	static int firstx = 0;
	static int firsty = 0;
	static bool firstvalid = false;
	if (0 == state) {
		firstvalid = true;
		firstx = x;
		firsty = y;
	}
	if (state && firstvalid) {
		MBWindow w;
		w.YMin = (((double)window.height - y) / ((double) window.height)) * (window.YMax - window.YMin) + window.YMin;
		w.YMax = (((double)window.height - firsty) / ((double) window.height)) * (window.YMax - window.YMin) + window.YMin;
		w.XMin = (((double)firstx) / ((double) window.width)) * (window.XMax - window.XMin) + window.XMin;
		w.XMax = (((double)x) / ((double) window.width)) * (window.XMax - window.XMin) + window.XMin;
		w.width = window.width;
		w.height = window.height;
		w.maxIters = window.maxIters;
		w.Iters = NULL;
		w.palette = default_palette;
		if (NULL != window.Iters)
			free(window.Iters);
		window = w;
		glutPostRedisplay();
	}
}

void motion(int x, int y)
{ // Your mouse motion here, x and y coordinates are as above
#ifdef DEBUG
	cout << "Motion: (" << x << ", " << y << ")" << endl;
#endif
}

void keyboard(unsigned char c, int x, int y)
{ // Your keyboard processing here
#ifdef DEBUG
	cout << "Keyboard: (" << x << ", " << y << ") " << c << endl;
#endif
}

int main(int argc, char** argv)
{
	// Initialize OpenGL, but only on the "master" thread or process.
	// See the assignment writeup to determine which is "master" 
	// and which is slave.

	// Initialize glut to default window size and display mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(init_width, init_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("MBSet");

	// Run initialization for opengl
	init();

	// Set callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);

	// Start main loop
	glutMainLoop();

	return 0;
}

