// Interface to Qt graphical display.
// George F. Riley, Georgia Tech, Spring 2004
// ECE3090

#ifndef __QDISPLAY_H__
#define __QDISPLAY_H__

#include <qapplication.h>
#include <qmainwindow.h>

class QTimer;
class QImage;

class QApp : public QApplication 
{
  //Q_OBJECT
public :
  QApp(int argc, char** argv);
public:
  void  Run();                // Process events until all windows closed
  //public slots:
  //void mainClosed();
};
  
class QDisplay : public QMainWindow 
{
Q_OBJECT
public:
  QDisplay(QApplication&);    // Requires a QApplication object
  virtual ~QDisplay();        // Destructor
  bool  Load(const char*);    // Load image from a file
  bool  Save(const char*);    // Save image to a file
  void  BlankImage(int, int, int); // Create a blank grayscale image, w h d
  int   Depth();              // Get image depth
  int   Width();              // Get image width
  int   Height();             // Get image height
  unsigned char* ImageData(); // Get image data
  void  Show(bool s = true);  // Set window visibility
  void  Update();             // Update the entire screen image
  // Update a rectangular area
  void  Update(int x,int y, int w = 1, int h = 1, bool noPaint = false);
  bool  IsClosed();           // True if main window is closed 
  void  UpdateRate(int);      // Set update rate (frames/sec) 0 = infinite
  // Inherited from QMainWindow
  void paintEvent(QPaintEvent*);
  void mousePressEvent(QMouseEvent*);
  // Slots
public slots:
  void timerDone();
private:
  bool           ready;        // If ready to display
  bool           closed;       // If main window closed
  QTimer*        qTimer;       // Ready timer, to enforce 25fps update rate
  QImage*        image;        // Current image
  QApplication&  app;          // Application object
  int            updateRate;   // Update rate (frames per sec)
  QRgb*          colorTable;   // Grayscale color table
  unsigned char* white;        // All white for creating blank images
  int            whitew;       // Width of white buffer
  int            whiteh;       // Height of white buffer
  int            whited;       // Depth of white buffer
  static int     windowCount;  // Number of open windows
};

#endif
