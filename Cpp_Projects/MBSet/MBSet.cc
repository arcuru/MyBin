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
bool click = false;
int click_XMin;
int click_XMax;
int click_YMin;
int click_YMax;
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

MBWindow window_list[100]; //!< List containing all the drawn windows
size_t window = 0;  //!< Index of current working window

/** Iterate Point
 *  returns the number of iterations below max_iter that it took to reach
 *  the threshold
 *
 *  @param a Real component of original point
 *  @param b Imaginary component of original point
 *  @param max_iter Maximum number of iterations to run
 *  @return The number of iterations left until reaching the max
 */
unsigned short iterate_point(double a, double b, unsigned int max_iter)
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

/* All of this is unnecessary, just draw at each individual pixel
	// Center the origin on the screen
	glTranslated( ((double)window.width) / 2.0, ((double)window.height) / 2.0, 0);
	
	// Scale image to fill the whole screen
	double scaleX = ((double)window.width) / (window.XMax - window.XMin);
	double scaleY = ((double)window.height) / (window.YMax - window.YMin);
	double min_Scale = (scaleX < scaleY) ? scaleX : scaleY;
	min_Scale *= ((double)511) / 512;
	glScaled(min_Scale, min_Scale, 0.0);

	// Size of one pixel
	double dx = 1.0 / ((double) window.width) * (window.XMax - window.XMin);
	double dy = 1.0 / ((double) window.height) * (window.YMax - window.YMin);
	double midx = ((double)(window.XMin + window.XMax)) / 2.0;
	double midy = ((double)(window.YMin + window.YMax)) / 2.0;
	midx *= -1;
	midy *= -1;
	glTranslated(midx, midy, 0);
*/
	// Get a pointer to the current window
	MBWindow* w = &window_list[window];

	// Scale Min and Max points for correct aspect ratio
	double pix_scale = ((double)w->height) / w->width;
	double point_scale = (w->YMax - w->YMin) / (w->XMax - w->XMin);
	if (pix_scale != point_scale) {
		double dy = w->YMax - w->YMin;
		double dx = w->XMax - w->XMin;
		double x_pix_size = dx / ((double)w->width);
		double y_pix_size = dy / ((double)w->height);
		if (x_pix_size < y_pix_size) {
			// Modify X vals
			double mid = (w->XMax + w->XMin) / 2.0;
			w->XMin = mid - (y_pix_size * w->width / 2.0);
			w->XMax = mid + (y_pix_size * w->width / 2.0);
		}
		else if (x_pix_size > y_pix_size) {
			// Modify Y vals
			double mid = (w->YMax + w->YMin) / 2.0;
			w->YMin = mid - (x_pix_size * w->height / 2.0);
			w->YMax = mid + (x_pix_size * w->height / 2.0);
			cout << w->YMin << endl;
			cout << w->YMax << endl;
		}
	}

	// Calculate mandelbrot window
	mandelbrot_compute(w);

	// Correct for 1 pixel discrepency
	glTranslatef(1, 0, 0);

	// Iterate over calculated image and display points
	glBegin( GL_POINTS );
	for (int r = 0; r < w->height; r++) {
		for (int c = 0; c < w->width; c++) {
			glColor3fv(&w->palette[3 * w->Iters[w->width * r + c]]);
			glVertex2d(c, r);
		}
	}
	if (click) {
		glColor3f(1.0, 0.0, 0.0);
		cout << "Coords" << endl;
		cout << click_XMin << ", " << click_XMax << endl;
		cout << click_YMin << ", " << click_YMax << endl;
		for (int i = click_XMin; i != click_XMax; i += (click_XMax - click_XMin) / abs(click_XMax - click_XMin)) {
			glVertex2d(i, w->height - click_YMin);
			glVertex2d(i, w->height - click_YMax);
		}
		for (int i = click_YMin; i != click_YMax; i += (click_YMax - click_YMin) / abs(click_YMax - click_YMin)) {
			glVertex2d(click_XMin, w->height - i);
			glVertex2d(click_XMax, w->height - i);
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
#ifdef DEBUG
	// Draw red bg to check for missed pixels
	glClearColor(1.0, 0.0, 0.0, 1.0);
#else
	glClearColor(1.0, 1.0, 1.0, 1.0);
#endif
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
	MBWindow* w = &window_list[window];
	w->XMin = init_XMin;
	w->YMin = init_YMin;
	w->XMax = init_XMax;
	w->YMax = init_YMax;
	w->maxIters = maxIt;
	w->width = init_width;
	w->height = init_height;
	w->Iters = NULL;
	w->palette = default_palette;
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
	// Get pointer to current window object
	MBWindow* win = &window_list[window];
	win->width = w;
	win->height = h;
	if (NULL != win->Iters)
		free(win->Iters);
	win->Iters = NULL;
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
		click_XMin = x;
		click_YMin = y;
		click_XMax = x;
		click_YMax = y;
		click = true;
	}
	if (state && firstvalid) {
		click = false;

		// Calculate pixel coordinates
		int min = (abs(x - click_XMin) < abs(y - click_YMin)) ? x-click_XMin : y-click_YMin;
		if (0 == min)
			return;
		min = abs(min);
		click_XMax = click_XMin + (min * ((x - click_XMin) / abs(x-click_XMin)));
		click_YMax = click_YMin + (min * ((y - click_YMin) / abs(y-click_YMin)));

		MBWindow* w = &window_list[window+1];
		MBWindow* wtmp = &window_list[window];
		w->YMin = (((double)wtmp->height - click_YMax) / ((double) wtmp->height)) * (wtmp->YMax - wtmp->YMin) + wtmp->YMin;
		w->YMax = (((double)wtmp->height - click_YMin) / ((double) wtmp->height)) * (wtmp->YMax - wtmp->YMin) + wtmp->YMin;
		w->XMin = (((double)click_XMin) / ((double) wtmp->width)) * (wtmp->XMax - wtmp->XMin) + wtmp->XMin;
		w->XMax = (((double)click_XMax) / ((double) wtmp->width)) * (wtmp->XMax - wtmp->XMin) + wtmp->XMin;
		
		// Ensure that we have the min and max set up as lower left and upper right corners
		if (w->YMax < w->YMin) {
			// Swap
			double tmp = w->YMax;
			w->YMax = w->YMin;
			w->YMin = tmp;
		}
		if (w->XMax < w->XMin) {
			// Swap
			double tmp = w->XMax;
			w->XMax = w->XMin;
			w->XMin = tmp;
		}

		// Inherit attributes from old window
		w->width = wtmp->width;
		w->height = wtmp->height;
		w->maxIters = wtmp->maxIters;
		w->Iters = NULL;
		w->palette = wtmp->palette;
		window++;
		glutPostRedisplay();
	}
}

void motion(int x, int y)
{ // Your mouse motion here, x and y coordinates are as above
#ifdef DEBUG
	cout << "Motion: (" << x << ", " << y << ")" << endl;
#endif
	int min = (abs(x - click_XMin) < abs(y - click_YMin)) ? x-click_XMin : y-click_YMin;
	if (0 == min)
		return;
	min = abs(min);
	click_XMax = click_XMin + (min * ((x - click_XMin) / abs(x-click_XMin)));
	click_YMax = click_YMin + (min * ((y - click_YMin) / abs(y-click_YMin)));
	glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y)
{ // Your keyboard processing here
#ifdef DEBUG
	cout << "Keyboard: (" << x << ", " << y << ") " << c << endl;
#endif
	
	switch ( c ) {
		case 'b':	
			if (window > 0) // Restrict to positive values
				window--;
			glutPostRedisplay();
			break;

		default:	
			break;
	}
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

