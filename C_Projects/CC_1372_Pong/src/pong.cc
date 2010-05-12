// Animate of the "Pong" Game
// Fall 2008, Georgia Tech
// Patrick Jackson

#include "gdisplay.h"
#include "cs1372.h"
#include <math.h>
#include <stdlib.h>

#define INDEX(x,y,w)	((y)*(w)+(x))
#define DISPLAY_HEIGHT	512
#define DISPLAY_WIDTH	512
#define PADDLE_HEIGHT	10
#define PADDLE_WIDTH	100
#define PADDLE_SPEED	40
#define PADDLE_TOP		DISPLAY_HEIGHT-PADDLE_HEIGHT
//#define DEBUG

int wball, hball;
int dx, dy;
int update;
GColor pc;
GColor bg;

bool checkPos(int x0, int y0, GDisplay ball, GDisplay show, GColor* ballPix,
		GColor* showPix);
void clearBall(int x0, int y0, GDisplay show, GColor* showPix);
void placeBall(int x0, int y0, GDisplay ball, GDisplay show, GColor* ballPix,
		GColor* showPix);
void Paddle(int Px, GDisplay show, GColor* showPix, bool set);
int movePaddle(int Px, GDisplay show, GColor* showPix);

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "Usage" << std::endl;
		return 1;
	}
	if (argc > 2)
		update = atoi(argv[2]);
	else
		update = 50;

	GDisplay ball = LoadImage(argv[1]);
	Hide(ball);
	wball = Width(ball);
	hball = Height(ball);
	GColor* ballPix = GetImageData(ball);

	if (DISPLAY_WIDTH < PADDLE_WIDTH) {
		std::cout << "Paddle too big" << std::endl;
		return 2;
	}
	if (DISPLAY_WIDTH < wball) {
		std::cout << "Ball too big" << std::endl;
		return 2;
	}
	if (DISPLAY_HEIGHT < PADDLE_HEIGHT + hball) {
		std::cout << "Height of paddle and ball too big" << std::endl;
		return 2;
	}

	bg = RGBColor(255,255,255);

	GDisplay show = BlankDisplay(DISPLAY_WIDTH, DISPLAY_HEIGHT);
	SetUpdateRate(show, update);
	GColor* showPix = GetImageData(show);

	int x0 = UniformRandom(200, 350);//Initial position
	int y0 = UniformRandom(0, 200);
	dx = UniformRandom(3, 7);//Initial speed/direction of travel
	dy = UniformRandom(3, 7);
	if (UniformRandom(1, 2) == 1)//Allow negative values initially
		dx *= -1;
	if (UniformRandom(1, 2) == 1)
		dy *= -1;
#ifdef DEBUG
	dx=0;
	dy=0;
#endif

	pc = RGBColor(0, 0, 0);
	int Px = (DISPLAY_WIDTH >> 1) - (PADDLE_WIDTH >> 1); //Px is the leftmost x-pos of paddle
	Paddle(Px, show, showPix, true);

	sleep(2); //Give user time to focus on the window
	while (true) {
		if (KeyPressed(show))
			Px = movePaddle(Px, show, showPix);
		int xsmall = x0;
		int ysmall = y0;
		for (int i = 0; i < abs(dx); i++) {
			x0 += abs(dx) / dx;
			if (!checkPos(x0, y0, ball, show, ballPix, showPix)) {
				dx *= -1;
				x0 += 2 * abs(dx) / dx;
			}
		}
		for (int i = 0; i < abs(dy); i++) {
			y0 += abs(dy) / dy;
			if (!checkPos(x0, y0, ball, show, ballPix, showPix)) {
				dy *= -1;
				y0 += 2 * abs(dy) / dy;
			}
		}
		placeBall(x0, y0, ball, show, ballPix, showPix);
		if (x0 < xsmall)
			xsmall = x0;
		if (y0 < ysmall)
			ysmall = y0;
		int updatewidth = abs(dx) + wball;
		if (xsmall + updatewidth > DISPLAY_WIDTH)
			updatewidth = DISPLAY_WIDTH - xsmall;
		int updateheight = abs(dy) + hball;
		if (ysmall + updateheight > PADDLE_TOP)
			updateheight = PADDLE_TOP - ysmall;
		Update(show, xsmall, ysmall, updatewidth, updateheight);
		clearBall(x0, y0, show, showPix);
	}
	WaitForClose();
	return 0;
}

//Place ball into current position
void placeBall(int x0, int y0, GDisplay ball, GDisplay show, GColor* ballPix,
		GColor* showPix) {
	for (int x = 0; x < wball; ++x) {
		for (int y = 0; y < hball; ++y) {
			GColor c = ballPix[INDEX(x,y,wball)];
			if (c.blue == bg.blue && c.red == bg.red && c.green == bg.green)
				continue;
			if ((x0 + x < DISPLAY_WIDTH) && (x0 + x > 0) && (y0 + y
					< PADDLE_TOP) && (y0 + y > 0)) {
				showPix[INDEX(x0+x,y0+y,DISPLAY_WIDTH)] = c;
			}
		}
	}
}

//Remove Ball completely from image
void clearBall(int x0, int y0, GDisplay show, GColor* showPix) {
	for (int x = 0; x < wball; ++x) {
		for (int y = 0; y < hball; ++y) {
			if ((x0 + x < DISPLAY_WIDTH) && (x0 + x > 0) && (y0 + y
					< PADDLE_TOP) && (y0 + y > 0)) {
				showPix[INDEX(x0+x,y0+y,DISPLAY_WIDTH)] = bg;
			}
		}
	}
}

//Did the ball hit anything?
bool checkPos(int x0, int y0, GDisplay ball, GDisplay show, GColor* ballPix,
		GColor* showPix) {
	for (int x = 0; x < wball; ++x) {
		for (int y = 0; y < hball; ++y) {
			GColor c = ballPix[INDEX(x,y,wball)];
			if (c.blue == bg.blue && c.red == bg.red && c.green == bg.green)
				continue;
			else if (y0 + y <= 0)
				return false;
			else if (x0 + x >= DISPLAY_WIDTH || x0 + x <= 0)
				return false;
			else if (y0 + y >= PADDLE_TOP) {//Hit paddle or death
				GColor d = showPix[INDEX(x0+x,y0+y,DISPLAY_WIDTH)];
				static int score = 0;
				if (d.blue == pc.blue && d.red == pc.red
						&& d.green == pc.green) {//Hit paddle
					score += abs(dx) + abs(dy);//Adds to score based on speed of ball
					dx += abs(dx) / dx;//Speed up
					dy += abs(dy) / dy;//Changes direction of ball slightly
					//update += 1;//This is unnecessary
					std::cout << "Score: " << score << std::endl;
					return false;
				}
				std::cout << "Final Score: " << score << std::endl;
				exit(0);//
			}
		}
	}
	return true;
}

//Draws or removes entire paddle from show
//Set=true to draw, false to remove
void Paddle(int Px, GDisplay show, GColor* showPix, bool set) {
	for (int x = Px; x < Px + PADDLE_WIDTH; ++x) {
		for (int y = PADDLE_TOP; y < DISPLAY_HEIGHT; ++y) {
			if (set) { //Draw paddle
				if (x > DISPLAY_WIDTH)
					showPix[INDEX(x-DISPLAY_WIDTH,y,DISPLAY_WIDTH)] = pc;
				else
					showPix[INDEX(x,y,DISPLAY_WIDTH)] = pc;
			}
			if (!set) {//Remove paddle
				if (x > DISPLAY_WIDTH)
					showPix[INDEX(x-DISPLAY_WIDTH,y,DISPLAY_WIDTH)] = bg;
				else
					showPix[INDEX(x,y,DISPLAY_WIDTH)] = bg;
			}
		}
	}
	if (Px > DISPLAY_WIDTH - PADDLE_WIDTH) {
		UpdateNoWait(show, Px, PADDLE_TOP, DISPLAY_WIDTH - Px, PADDLE_HEIGHT);
		UpdateNoWait(show, 0, PADDLE_TOP, PADDLE_WIDTH + Px - DISPLAY_WIDTH,
				PADDLE_HEIGHT);
	}
	UpdateNoWait(show, Px, PADDLE_TOP, PADDLE_WIDTH, PADDLE_HEIGHT);
}

//Move paddle based on keystroke
int movePaddle(int Px, GDisplay show, GColor* showPix) {
	Paddle(Px, show, showPix, false);
	Key_t val = GetKey(show);
	if (val == Key_Left)
		Px -= PADDLE_SPEED;
	if (val == Key_Right)
		Px += PADDLE_SPEED;
	if (val >= Key_0 && val <= Key_9)
		Px = (int) ((val - Key_0) * ((double) (DISPLAY_WIDTH - PADDLE_WIDTH))
				/ 9);
	if (Px < 0) //Keep 0 < Px < DISPLAY_WIDTH
		Px += DISPLAY_WIDTH;
	else if (Px > DISPLAY_WIDTH)
		Px -= DISPLAY_WIDTH;
	Paddle(Px, show, showPix, true);
	return Px;
}
