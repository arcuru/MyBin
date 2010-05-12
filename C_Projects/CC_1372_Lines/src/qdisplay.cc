// Interface to Qt graphics library
// George F. Riley, Georgia Tech, Spring 2004
// ECE3090, Spring 2004

#include <iostream>
#include <fstream>

#include "moc_qdisplay.h"
#include <qtimer.h>
#include <qimage.h>

#define nil 0

using namespace std;

int QDisplay::windowCount = 0;

// QApp methods
QApp::QApp(int argc, char** argv) 
    : QApplication(argc, argv)
{
  // Connect application "lastwindowclosed" signal
  //connect(this, SIGNAL(lastWindowClosed()), SLOT(mainClosed()));
  connect(this, SIGNAL(lastWindowClosed()), SLOT(quit()));
}

void QApp::Run()
{
  exec();
}

//void QApp::mainClosed()
//{
//  quit();
//}

// Constructors
QDisplay::QDisplay(QApplication& a)
    : ready(true), closed(false), qTimer(nil), image(nil), app(a),
    updateRate(0), colorTable(nil), white(nil), whitew(0), whiteh(0)
{
  // Create and connect the timer
  qTimer = new QTimer();
  connect(qTimer, SIGNAL(timeout()), SLOT(timerDone()));  

}

QDisplay::~QDisplay()
{ // Destructor
  if (qTimer) qTimer->stop();
  delete qTimer;
  delete image;
  delete colorTable;
  delete white;
}

// Member functions
bool QDisplay::Load(const char* fn)
{ // Load an image from a file
  image = new QImage();
  if (!image->load(fn))
    { // load failed
      delete image;
      image = nil;
      return false;
    }
  resize(image->width(), image->height()); // Size the main window to image
  Update();
  if (windowCount++==0)
    {
      //app.setMainWidget(this);
    }
  return true;
}

bool QDisplay::Save(const  char* fn)
{
  if (!image) return false; // no image to save
  return image->save(fn, "PNG");
#ifdef TRY_PNM
  if (Depth() == 8)
    return image->save(fn, "PNM");
  else
    return image->save(fn, "PNG");
#endif
#ifdef OLD_WAY
  ofstream fs(fn);
  if (!fs) return false;
  fs << "P5" << endl;
  fs << "# CREATOR George F. RILEY" << endl;
  fs << "# GENERATOR: QDisplay::Save" << endl;
  fs << image->width() << " " << image->height() << endl;
  fs << image->numColors() << endl;
  unsigned char* b = image->bits();
  for (int y = 0; y < image->height(); ++y)
    {
      for (int x = 0; x < image->width(); ++x)
        fs << b[y*image->width() + x];
    }
  fs << endl;
  fs.close();
  return true;
#endif
}

void QDisplay::BlankImage(int w, int h, int d)
{  // Create a blank (all white) image
  int colorCount;
  
  if (d == 8)
    {
      if (!colorTable)
        {
          colorTable = new QRgb[256];
          for (int i = 0; i < 256; ++i)
            {
              colorTable[i] = QColor(i, i, i).rgb();
            }
        }
      if (whitew != w || whiteh != h || whited != d)
        { // Existing white buffer wrong size
          delete [] white;
          white = new unsigned char[w * h];
          memset(white, 0xff, w * h);
          whitew = w;
          whiteh = h;
          whited = d;
        }
      colorCount = 256;
    }
  else
    {
      colorCount = 0; // 32 bit color
      if (whitew != w || whiteh != h || whited != d)
        { // Existing white buffer wrong size
          delete [] white;
          white = (unsigned char*)new QRgb[w * h];
          for (int i = 0; i < w * h; ++i)
            ((QRgb*)white)[i] = QColor(255,255,255).rgb();
        }
      
    }
  whitew = w;
  whiteh = h;
  whited = d;
  
  if (image)
    { // Delete any existing
      delete image;
      image = nil;
    }
  
  // Create an image, all white
  image = new QImage(white, w, h, d,
                     colorTable, colorCount, QImage::IgnoreEndian);
  resize(image->width(), image->height()); // Size the main window to image
  //Update(); // And draw on screen
  if (windowCount++==0)
    {
      //app.setMainWidget(this);
    }
}

  
int  QDisplay::Depth()
{ // Return image depth (bits per pixel), either 1, 8, or 32.
  // Note, the 32 bit images are actually 24 bits, with 8 bits of filler
  // for word alignment
  if (!image) return 0; // No image loaded
  int d = image->depth();
  if (d == 24) d = 32;
  return d;             // Bits per pixel
}

int  QDisplay::Width()
{ // Return image width (pixels)
  if (!image) return 0;
  return image->width();
}

int  QDisplay::Height()
{ // Return image height (pixels)
  if (!image) return 0;
  return image->height();
}
  
unsigned char* QDisplay::ImageData()
{ // Get a pointer to the image data
  if(!image) return nil; // No image loaded
  //cout << "Image data has " << image->numBytes() << " bytes " << endl;
  return image->bits();
}

void  QDisplay::Show(bool s)
{
  if (s) show();
  else   hide();
}

void  QDisplay::Update()
{
  if (closed) return; // No more updates after window closed
  while(!ready && !closed) app.processEvents(1); // Wait for 25fps elapsed 
  if (updateRate)
    { // Non-zero update rate specified
      ready = false;
      qTimer->start(1000/updateRate, TRUE);  // 40ms is 25 frames per secnod
    }
  // Update image here
  update();                                  // Force re-paint event later
  //repaint();                                  // Force re-paint event now
  while(app.hasPendingEvents()) app.processEvents();
}

void  QDisplay::Update(int x, int y, int w, int h, bool noPaint)
{
  if (closed) return; // No more updates after window closed
  if (!noPaint)
    {
      while(!ready && !closed) app.processEvents(1); // Wait for 25fps elapsed 
      if (updateRate)
        { // Non-zero update rate specified
          ready = false;
          qTimer->start(1000/updateRate, TRUE);  // Start timer for next update
        }
    }
  
  
  // Update the pixel
  if (image)
    {
      //repaint(x, y, 1, 1);
      update(x, y, w, h);
    }
  if (!noPaint)while(app.hasPendingEvents()) app.processEvents();
}

bool QDisplay::IsClosed()
{
  return closed;
}

void QDisplay::UpdateRate(int r)
{
  updateRate = r;
}

// Inherited from QMainWindow
void QDisplay::paintEvent(QPaintEvent* pe)
{
  if (image)
    {
      QRect r = pe->rect();
      bitBlt(this, r.x(), r.y(), image, r.x(), r.y(), r.width(), r.height());
    }
}

void QDisplay::mousePressEvent(QMouseEvent* e)
{
  cout << "Mouse pressed, x " << e->x()
       << " y " << e->y() << endl;
}

// Slots
void QDisplay::timerDone()
{
  ready = true; // Enough time elapsed for another frame update
}


