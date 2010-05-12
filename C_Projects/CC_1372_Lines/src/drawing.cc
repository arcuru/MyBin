// CS1372 Line Drawing Assignment
// Patrick Jackson

#include "cs1372.h"
#include "gdisplay.h"
#include <math.h>

#define INDEX(x,y,w)	((y)*(w)+(x))

int Interp(int x0, int x1, int x2, int y0, int y1) {
	double distance = (double) (x2 - x1) / (x2 - x0); // (x2-x0)/(x1-x0)
	return y0 + (int) distance * (y1 - y0);
}

void SetPixel(int x, int y, GDisplay d, GColor c) {
	GColor* image = GetImageData(d);
	image[INDEX(x,y,Width(d))] = c;
}

void MidPointLine(int x0, int y0, int x1, int y1, GDisplay d1, GColor c1) { //I'll be trying to type this in, it needs to be checked
//Edited to do whole circle
	int origX0 = x0;
	int origY0 = y0;
	x1 = (x1 - x0);
	y1 = (y1 - y0);
	x0 = 0;
	y0 = 0;
	int xMult = 1;
	if (x1 < 0) {
		x1 = -x1;
		xMult = -1;
	}
	int yMult = 1;
	if (y1 < 0) {
		y1 = -y1;
		yMult = -1;
	}
	bool Swapped = false;
	if (y1 > x1) {
		int tmp = x1;
		x1 = y1;
		y1 = tmp;
		Swapped = true;
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int d = 2 * dy - dx;
	int incrE = 2 * dy;
	int incrNE = 2 * (dy - dx);
	int x = x0;
	int y = y0;
	SetPixel(x, y, d1, c1); //difference here
	while (x < x1) {
		if (d <= 0)
			d += incrE;
		else {
			d += incrNE;
			y++;
		}
		x++;
		if (Swapped) {
			SetPixel(origY0 + y * xMult, origX0 + x * yMult, d1, c1);
		} else
			SetPixel(origX0 + x * xMult, origY0 + y * yMult, d1, c1);
	}
}

void MidpointCircle(int radius, GDisplay d1, GColor c1) {
	int x = 0;
	int y = radius;
	double d = 5.0 / 4.0 - radius;
	SetPixel(x, y, d1, c1);
	while (y > x) {
		if (d < 0) {
			d += 2.0 * x + 3.0; // Select East
		} else {
			d += 2.0 * (x - y) + 5.0; // Select SE
			y--;
		}
		x++;
		SetPixel(x, y, d1, c1);
	}
}

int main() {
	GDisplay d = BlankDisplay(512, 512);
	SetUpdateRate(d, 20);
	int w = Width(d);
	int h = Height(d);

	int x0 = w / 2;
	int y0 = h / 2;
	double theta = 0;
	int nSpokes = 60;
	int r = 250;
	double deltaTheta = M_PI * 2 / nSpokes;

	GColor c = RGBColor(0, 0, 0);
	//MidpointCircle(r, d, c);
	for (int i = 0; i < nSpokes; ++i) {
		int x1 = x0 + r * cos(theta);
		int y1 = y0 + r * sin(theta);
		std::cout << "x0 " << x0 << "y 0" << y0 << " x1 " << x1;
		std::cout << " y1 " << y1 << std::endl;
		GColor c = RGBColor(0, 0, 0);

		//Something wrong here
		if (i < 10)
			c = RGBColor(255, Interp(0, 10, i, 0, 255), 0);
		else if (i < 20)
			c = RGBColor(Interp(10, 20, i, 255, 0), 255, 0);
		else if (i < 30)
			c = RGBColor(0, 255, Interp(20, 30, i, 0, 255));
		else if (i < 40)
			c = RGBColor(0, Interp(30, 40, i, 255, 0), 255);
		else if (i < 50)
			c = RGBColor(Interp(40, 50, i, 0, 255), 0, 255);
		else if (i < 60)
			c = RGBColor(255, 0, Interp(50, 60, i, 255, 0));

		MidPointLine(x0, y0, x1, y1, d, c);
		theta += deltaTheta;
	}
	WaitForClose();
	Update(d); //Move this to end instead in real program
}
