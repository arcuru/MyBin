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

#define NTHREADS 16 

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
int maxIt = 2000;     //!< Max iterations for the set computations

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
pthread_mutex_t win_mutex; //!< Mutex for accessing the current window
pthread_barrier_t calc_barrier; //!< Barrier for synchronization between the rank0 threads

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
   this is approximately 4 times slower than unrolling the calculations
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
	double r, i, rr, ii;
	r = i = rr = ii = 0.0;

	do {
		// Run a single step of the algorithm and check
		i = 2 * r * i + b;
		r = rr - ii + a;
		rr = r * r;
		ii = i * i;
		if ( (rr + ii) >= 4.0 )
			break;
	} while ( --max_iter );

	return max_iter;
}

struct compute_thread_struct_t {
	int total_tasks;  //!< Informs thread of the total number of tasks in the system
	int thread_rank;  //!< Informs thread of its rank
	MBWindow* w;      //!< Pointer to the window to update
};

/** Compute Thread
 *  runs the computation for a subset of the mandelbrot image
 */
void* compute_thread(void *info)
{
	compute_thread_struct_t* i = (compute_thread_struct_t*) info;
	int numtasks, rank;
	numtasks = i->total_tasks;
	rank = i->thread_rank;
	MBWindow* w = i->w;

	// Figure out number of rows and starting row for calculations
	int height = w->height / numtasks;
	if (0 != (w->height % numtasks))
		height++;
	int start = height * rank;
	if (rank == numtasks-1) { // Scale last task down to not overshoot end
		height = w->height - start;
	}

#ifdef DEBUG
	cout << "Rank " << rank << " started." << start << endl;
#endif

	// Allocate space
	unsigned short* iters = (unsigned short*) malloc(sizeof(unsigned short) * w->width * height);
	size_t index = 0;

	// Run through the calculations
	double imag, real;
	for (unsigned int r = start; r < start+height; r++) {
		imag = (((double) r) / ((double) w->height - 1)) * (w->YMax - w->YMin) + w->YMin;
		for (unsigned int c = 0; c < w->width; c++) {
			real = (((double) c) / ((double) w->width - 1)) * (w->XMax - w->XMin) + w->XMin;
			//iters[index++] = iterate_point(real, imag, maxIt);
			//w->Iters[start+index++] = iterate_point(real, imag, maxIt);
			w->Iters[w->width * r + c] = iterate_point(real, imag, maxIt);
		}
	}
#ifdef DEBUG
	cout << "Rank " << rank << " with " << start << endl;
#endif

	//memcpy(&w->Iters[start], iters, sizeof(unsigned short) * w->width * height);

	free( iters );

	pthread_exit( NULL );
}

/** Thread Communicator
 *  handles communication with the MPI slaves to calculate the current window
 */
/* void* thread_com_slave(void* unused)
{
	// Get vital information about mpi settings
	int numtasks;
	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
	numtasks--;

	while ( 1 ) {
		// Wait for window to be set
		pthread_barrier_wait(&calc_barrier);

		// Get a pointer to the current window
		MBWindow* w = &window_list[window];

		// Allocate space in current window
		w->Iters = (unsigned short*) malloc(sizeof(unsigned short) * w->width * w->height);
		
		// Determine size of calculations for each MPI process
		int height = w->height / numtasks;
		if (0 != (w->height % numtasks))
			height++;
		int bufsize = height * w->width;
		int bufsize2 = bufsize;

		// Retrieve computed values and save
		MPI_Request requestRecv[numtasks];
		int q = 0;
		int rc;
		for (int i = 0; i < numtasks; i++) {
			rc = MPI_Irecv(&w->Iters[i*bufsize], sizeof(unsigned short) * bufsize2, MPI_BYTE, i+1,
					0, MPI_COMM_WORLD, &requestRecv[q++]);
			if (rc != MPI_SUCCESS) {
				cout << "Error receiving iters from " << i << endl;
				MPI_Finalize();
				exit(1);
			}
			if (i == numtasks - 2) {
				// Change bufsize if necessary
				bufsize2 = (w->height - (height * (numtasks-1))) * w->width;
			}
		}
		// Wait for all data to be received
		MPI_Status status[numtasks];
		MPI_Waitall(numtasks, requestRecv, status);

		// Indicate finished to main task
		pthread_barrier_wait(&calc_barrier);
	}
	return NULL;
}
*/

/** Mandelbrot Compute Threads
 *  Computes the window area with threads
 *
 *  @args w MBWindow pointer that needs to be computed
 */
void mandelbrot_compute_threads(MBWindow* w)
{
	// Skip if already calculated this window
	if (NULL != w->Iters)
		return;
	w->Iters = (unsigned short*) malloc(sizeof(unsigned short) * w->width * w->height);
#ifdef DEBUG
	cout << "Calculating..." << endl;
	struct timeval t;
	gettimeofday(&t, 0);
#endif
	// Fill a list with all the arguments to the threads
	compute_thread_struct_t* info = (compute_thread_struct_t*) malloc(sizeof(compute_thread_struct_t) * NTHREADS);
	for (int i = 0; i < NTHREADS; i++) {
		info[i].total_tasks = NTHREADS;
		info[i].thread_rank = i;
		info[i].w = w;
	}
	// Create the threads
	pthread_t* p = (pthread_t*) malloc(sizeof(pthread_t) * NTHREADS);
	for (int i = 0; i < NTHREADS; i++) {
		pthread_create(&p[i], 0, compute_thread, (void*)&info[i]); 
	}
	// Wait until threads finish
	for (int i = 0; i < NTHREADS; i++) {
		pthread_join(p[i], NULL);
	}
	// Free memory
	free( info );
	free( p );
#ifdef DEBUG
	cout << "Finished calculating" << endl;
	struct timeval t2;
	gettimeofday(&t2, 0);
	unsigned int time = (t2.tv_sec - t.tv_sec) * 1000000 + (t2.tv_usec - t.tv_usec);
	cout << "Calculation time: " << setw(6) << ((float)time) / 1000000 << endl;
#endif

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
	for (unsigned int r = 0; r < w->height; r++) {
		imag = (((double) r) / ((double) w->height - 1)) * (w->YMax - w->YMin) + w->YMin;
		for (unsigned int c = 0; c < w->width; c++) {
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

	// Get a pointer to the current window
	MBWindow* w = &window_list[window];

	// Clear all the colors
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Clear the matrix
	glLoadIdentity();

	// Set the viewing transformation
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	// Correct for 1 pixel discrepency
	glTranslatef(1, 0, 0);

	if (NULL == w->Iters) {
		// Compute the window
		mandelbrot_compute_threads(w);
	}

	// Iterate over calculated image and display points
	glBegin( GL_POINTS );
	for (unsigned int r = 0; r < w->height; r++) {
		for (unsigned int c = 0; c < w->width; c++) {
			glColor3fv(&w->palette[3 * w->Iters[w->width * r + c]]);
			glVertex2d(c, r);
		}
	}
	if (click) {
		glColor3f(1.0, 0.0, 0.0);
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
	pthread_mutex_lock(&win_mutex);
	memcpy(&window_list[window+1], &window_list[window], sizeof(MBWindow));
	window++;
	MBWindow* win = &window_list[window];
	win->width = w;
	win->height = h;
	win->Iters = NULL;

	// Scale Min and Max points for correct aspect ratio
	// shouldn't change anything unless window is not a square
	double pix_scale = ((double)win->height) / win->width;
	double point_scale = (win->YMax - win->YMin) / (win->XMax - win->XMin);
	if (pix_scale != point_scale) {
		double dy = win->YMax - win->YMin;
		double dx = win->XMax - win->XMin;
		double x_pix_size = dx / ((double)win->width);
		double y_pix_size = dy / ((double)win->height);
		if (x_pix_size < y_pix_size) {
			// Modify X vals
			double mid = (win->XMax + win->XMin) / 2.0;
			win->XMin = mid - (y_pix_size * win->width / 2.0);
			win->XMax = mid + (y_pix_size * win->width / 2.0);
		}
		else if (x_pix_size > y_pix_size) {
			// Modify Y vals
			double mid = (win->YMax + win->YMin) / 2.0;
			win->YMin = mid - (x_pix_size * win->height / 2.0);
			win->YMax = mid + (x_pix_size * win->height / 2.0);
		}
	}

	pthread_mutex_unlock(&win_mutex);
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
	static bool firstvalid = false;
	if (0 == state) {
		firstvalid = true;
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

		pthread_mutex_lock(&win_mutex);
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
		pthread_mutex_unlock(&win_mutex);
		glutPostRedisplay();
	}
}

void motion(int x, int y)
{
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
{ 
#ifdef DEBUG
	cout << "Keyboard: (" << x << ", " << y << ") " << c << endl;
#endif
	// Switch on keyboard command
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

	// Init mutex
	pthread_mutex_init(&win_mutex, NULL);
	//pthread_barrier_init(&calc_barrier, NULL, 2);


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

