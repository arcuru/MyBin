// CS1372 Assignment 9 - Bouncing Balls
// Fall 2008, Georgia Tech
// Patrick Jackson

#include "gdisplay.h"
#include "cs1372.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INDEX(x,y,w)	((y)*(w)+(x))
int wball,hball,w,h;

bool checkPos(int x0,int y0, GDisplay ball, GDisplay show, GColor* ballPix);
void clearBall(int x0, int y0, GDisplay ball, GDisplay show, GColor* showPix);
void placeBall(int x0, int y0, GDisplay ball, GDisplay show, GColor* ballPix, GColor* showPix);

int main(int argc, char** argv)
{
	if (argc < 2) return 0;
	GDisplay ball = LoadImage(argv[1]);
	GDisplay show = BlankDisplay(512,512);
	Hide(ball);
	SetUpdateRate(show,24);
	wball = Width(ball);
	hball = Height(ball);
	w = Width(show);
	h = Height(show);
	GColor* ballPix = GetImageData(ball);
	GColor* showPix = GetImageData(show);
	int x0 = UniformRandom(200,350);
	int y0 = UniformRandom(200,350);
	int dx = UniformRandom(5,15);
	int dy = UniformRandom(5,15);
	while (true)
	{
		int xsmall=x0;
		int ysmall=y0;
		for (int i=0; i<abs(dx); i++)
		{
			x0+=abs(dx)/dx;
			if (!checkPos(x0,y0,ball,show,ballPix))
			{
				dx*=-1;
				x0+=2*abs(dx)/dx;
			}
		}
		for (int i=0; i<abs(dy); i++)
		{
			y0+=abs(dy)/dy;
			if (!checkPos(x0,y0,ball,show,ballPix))
			{
				dy*=-1;
				y0+=2*abs(dy)/dy;
			}
		}
		placeBall(x0,y0,ball,show,ballPix,showPix);
		if (x0<xsmall) xsmall=x0;
		if (y0<ysmall) ysmall=y0;
		Update(show,xsmall,ysmall,abs(dx)+wball,abs(dy)+hball);
		clearBall(x0,y0,ball,show,showPix);
	}
	WaitForClose();
	return 0;
}

void placeBall(int x0, int y0, GDisplay ball, GDisplay show, GColor* ballPix, GColor* showPix)
{
	for (int x=0; x<wball; ++x)
	{
		for (int y=0; y<hball; ++y)
		{
			GColor c = ballPix[INDEX(x,y,wball)];
			if (x0+x < w && x0+x > 0 && y0+y < h && y0+y > 0)
			{
				showPix[INDEX(x0+x,y0+y,w)] = c;
			}
		}
	}
}

void clearBall(int x0, int y0, GDisplay ball, GDisplay show, GColor* showPix)
{
	for (int x=0; x<wball; ++x)
	{
		for (int y=0; y<hball; ++y)
		{
			if (x0+x < w && x0+x  >0 && y0+y < h && y0+y > 0)
				{
					showPix[INDEX(x0+x,y0+y,w)] = RGBColor(255,255,255);
				}
		}
	}
}

bool checkPos(int x0,int y0, GDisplay ball, GDisplay show, GColor* ballPix)
{
	for (int x=0; x<wball; ++x)
	{
		for (int y=0; y<hball; ++y)
		{
			GColor c = ballPix[INDEX(x,y,wball)];
			if (c.blue == 255 && c.red == 255 && c.green == 255) continue;
			if (y0+y >= h || y0+y <= 0)	return false;
			if (x0+x >= w || x0+x <= 0)	return false;
		}
	}
	return true;
}
