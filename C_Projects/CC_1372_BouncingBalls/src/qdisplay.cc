// Interface to Qt graphics library
// George F. Riley, Georgia Tech, Spring 2004
// ECE3090, Spring 2004

#include <iostream>
#include <fstream>


#ifdef QT4
#include "moc_qdisplay4.h"
#include <QTimer>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#else
#include "moc_qdisplay.h"
#include <qtimer.h>
#include <qimage.h>
#endif

#define nil 0

using namespace std;

// Define the GColor structure if on MAC
#ifdef MAC_OSX
typedef struct 
{
  unsigned char alpha;  // The transparency
  unsigned char red;    // The green component
  unsigned char green;  // The blue component
  unsigned char blue;   // The red component 
} GColorMac;
#endif


int QDisplay::windowCount = 0;

// QApp methods
QApp::QApp(int argc, char** argv) 
    : QApplication(argc, argv)
{
  // Connect application "lastwindowclosed" signal
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
  : ready(true), closed(false), paused(false),
    qTimer(nil), image(nil), app(a),
    updateRate(0), colorTable(nil), white(nil), whitew(0), whiteh(0),
    keyPressed(false), key(Qt::Key_unknown)
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

// QT4 uses a slightly different way to create images
#ifdef QT4
void QDisplay::BlankImage(int w, int h, int d)
{  // Create a blank (all white) image
  int colorCount;
  QImage::Format fmt = QImage::Format_Indexed8;
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
      fmt = QImage::Format_RGB32;
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
  image = new QImage(w, h, fmt);
  //cout << "Created new image width " << image->width()
  //     << " height " << image->height() << endl;
  if (d == 8)
    { // Set all 1-byte pixels to white
      uchar* d8 = image->bits();
      for (int i = 0; i < w * h; ++i) d8[i] = 0xff; // Set pixel to white
    }
  else
    { // Set all QRgb pixels to white
      QRgb* d32 = (QRgb*)image->bits();
      for (int i = 0; i < w * h; ++i)
        {
          d32[i] = qRgb(255,255,255); // Set pixel to white
        }
    }
  Update();
  resize(image->width(), image->height()); // Size the main window to image
}

#else

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
  Update();
}
#endif
  
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
  while(paused) app.processEvents();  // Wait while paused
  while(!ready && !closed) app.processEvents(); // Wait for 25fps elapsed 
  if (updateRate)
    { // Non-zero update rate specified
      ready = false;
#ifdef QT4
      qTimer->setSingleShot(true);
      qTimer->start(1000/updateRate);  // 40ms is 25 frames per secnod
#else
      qTimer->start(1000/updateRate, TRUE);  // 40ms is 25 frames per secnod
#endif
    }
  // Update image here
  update();                                  // Force re-paint event later
  //repaint();                                  // Force re-paint event now
  while(app.hasPendingEvents()) app.processEvents();
}

void  QDisplay::Update(int x, int y, int w, int h, bool noPaint)
{
  while(paused) app.processEvents();  // Wait while paused
  if (closed) return; // No more updates after window closed
  if (!noPaint)
    {
      while(!ready && !closed) app.processEvents(); // Wait for 25fps elapsed 
      if (updateRate)
        { // Non-zero update rate specified
          ready = false;
#ifdef QT4
          qTimer->setSingleShot(true);
          qTimer->start(1000/updateRate);  // 40ms is 25 frames per secnod
#else
          qTimer->start(1000/updateRate, TRUE);  // Start timer for next update
#endif
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

bool QDisplay::KeyPressed()
{
  return keyPressed;
}

Qt::Key QDisplay::GetKey()
{
  keyPressed = false;
  Qt::Key k = key;
  key = Qt::Key_unknown;
  return k;
}

void QDisplay::Pause()
{
  paused = true;
}

// Inherited from QMainWindow
void QDisplay::paintEvent(QPaintEvent* pe)
{
  if (image)
    {
#ifdef QT4
      QPainter p(this);
      p.drawImage(QPoint(0,0), *image);
#else
      QRect r = pe->rect();
      bitBlt(this, r.x(), r.y(), image, r.x(), r.y(), r.width(), r.height());
#endif
    }
}

// Define the GColorMac structure
#ifdef MAC_OSX
typedef struct 
{
  unsigned char alpha;  // The transparency
  unsigned char red;    // The green component
  unsigned char green;  // The blue component
  unsigned char blue;   // The red component 
} GColorMacMac;
#endif


void QDisplay::mousePressEvent(QMouseEvent* e)
{
  //cout << "Mouse pressed, x " << e->x()
  //     << " y " << e->y() << endl;
#ifdef QT4
  Qt::MouseButton b = e->button();
  if (b == Qt::RightButton)
#else
  ButtonState b = e->button();
  if (b == RightButton)
#endif
    {
#ifdef MAC_OSX
      GColorMac* image = (GColorMac*)ImageData();
      for (int i = 0; i < Width() * Height(); ++i)
        {
          GColorMac c = image[i];
          GColorMac c1;
          c1.blue = c.alpha;
          c1.green = c.red;
          c1.red = c.green;
          c1.alpha = c.blue;
          image[i] = c1;
        }
#endif
      Save("Saved.png");
#ifdef MAC_OSX
      // Now put it back
      for (int i = 0; i < Width() * Height(); ++i)
        {
          GColorMac c = image[i];
          GColorMac c1;
          c1.blue = c.alpha;
          c1.green = c.red;
          c1.red = c.green;
          c1.alpha = c.blue;
          image[i] = c1;
        }
#endif
    }
  //paused = !paused; // No pausing for student's projects
}

void QDisplay::keyPressEvent(QKeyEvent* k)
{
  k->accept(); // Accept the keystroke
  key = Qt::Key(k->key());
  keyPressed = true;
  //cout << "Key is " << key << endl;
}

  
// Slots
void QDisplay::timerDone()
{
  ready = true; // Enough time elapsed for another frame update
}


