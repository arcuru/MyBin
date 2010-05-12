/* 
 * File:   QtPong.cc
 * Author: patty
 * 
 * Created on February 20, 2010, 3:05 AM
 */

#include "QtPong.h"
#include <stdio.h>

class QImage;
class QMainWindow;

#define IND(x,y,w)	((y)*(w)+(x))

ColorBit ballbg = {255, 255, 255, 0};

bool ColorBitCompare(ColorBit a, ColorBit b) {
    if ((a.blue != b.blue) || (a.green != b.green) || (a.red != b.red) || (a.alpha != b.alpha))
        return false;
    return true;
}

QtPong::QtPong(QApplication& input) : app(input), bg(0), screen(0), ball(0), ballname("Sphere64.png"), sw(512), sh(512) {
}

QtPong::~QtPong() {
}

void QtPong::run() {
    if (!bg)
        createBackground();
    if (!ball)
        if (!createBall())
            printf("Ballwrong");
    initBall();
    //createScreen();
    resize(sw, sh);
    
    show();

    app.processEvents();
}

void QtPong::setSize(int w, int h) { // Create a blank (all white) image
    sw = w;
    sh = h;
    createBackground();
    resize(sw, sh);
}

bool QtPong::createBall() {
    ball = new QImage();
    if (!ball->load(ballname)) { // load failed
        delete ball;
        ball = 0;
        return false;
    }
    balldata = (ColorBit*) ball->bits();
    bw = ball->width();
    bh = ball->height();
    return true;
}

void QtPong::createBackground() {
    bg = new QImage(sw, sh, QImage::Format_RGB32);
    bgdata = (ColorBit*) bg->bits();
    for (int i = 0; i < sw * sh; ++i) {
        bgdata[i].blue = 255;
        bgdata[i].green = 255;
        bgdata[i].red = 255;
        bgdata[i].alpha=0;
    }
    printf("Created Background");
}

void QtPong::createScreen() {
    screen = new QImage(sw, sh, QImage::Format_RGB32);
    screendata = (ColorBit*) screen->bits();
    for (int i = 0; i < sw * sh; ++i) {
        screendata[i] = bgdata[i];
    }
    int dex, dex2;
    for (int n = by; n < by + bh; ++n)
        for (int i = bx; i < bx + bw; ++i) {
            dex = IND(i, n, sw);
            dex2 = IND(i - bx, n - by, bw);
            if (!ColorBitCompare(balldata[dex2], ballbg) && !ColorBitCompare(balldata[dex2], screendata[dex]))
                screendata[dex] = balldata[dex2];
        }
}

void QtPong::initBall() {

    bx = by = 50;
    dx = dy = 1;
}

void QtPong::paintEvent(QPaintEvent* pe) {//Will draw image onto window during app.processEvents()
    QPainter p(this);
    p.drawImage(QPoint(0, 0), *bg);
}