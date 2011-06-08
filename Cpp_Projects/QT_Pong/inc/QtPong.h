/* 
 * File:   QtPong.h
 * Author: patty
 *
 * Created on February 20, 2010, 3:05 AM
 */

#ifndef _QTPONG_H
#define	_QTPONG_H

#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QImage>

typedef struct {
    unsigned char blue; // The red component
    unsigned char green; // The blue component
    unsigned char red; // The green component
    unsigned char alpha; // The transparency
} ColorBit;

bool ColorBitCompare(ColorBit,ColorBit);

class QtPong : public QMainWindow {
    Q_OBJECT
public:
    QtPong(QApplication&);
    virtual ~QtPong();
    void run(); //Run game until complete
    void paintEvent(QPaintEvent*);
    void createBackground();
    void createScreen();
    void setSize(int w, int h);
    bool createBall();
    void initBall();
public slots:
private:
    QApplication& app; //Holds QApp to allow sending updates to main app
    QImage* bg; //Holds background image
    ColorBit* bgdata;
    QImage* screen; //Holds current screen image
    ColorBit* screendata;
    QImage* ball; //Holds the ball image
    ColorBit* balldata;
    const char* ballname; //Ball filename
    int sw; //Screen Width
    int sh; //Screen Height
    int bx,by; //Ball's x & y position
    int dx,dy; //Ball's speed in pixels
    int bw,bh; //Ball's width and height
};

#endif	/* _QTPONG_H */

