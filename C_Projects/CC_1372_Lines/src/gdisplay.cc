// Sample Graphics API, Implementation, CS1372
// George F. Riley, Georgia Tech, CS1372, Fall 2008

#include <iostream>

#include "gdisplay.h"
#include "qdisplay.h"

using namespace std;

QApp* app;  // The qapplication object

// Initialize the GDisplay interface
void Initialize()
{
  int argc = 1;
  char* argv[] = {(char*)"testqd", 0};
  app = new QApp(argc, argv);
  cout << "Initialized" << endl;
}


// Create a blank display of w by h
GDisplay BlankDisplay(int w, int h)
{
  if (!app) Initialize();
  QDisplay* d = new QDisplay(*app);
  d->Show(true);
  d->BlankImage(w, h, 32);
  return d;
}

// Load an image from a file
GDisplay LoadImage(const char* fileName)
{
  if (!app) Initialize();
  QDisplay* d = new QDisplay(*app);
  d->Load(fileName);
  d->Show(true);
  return d;
}

// Get the width of the image
int Width(GDisplay g)
{
  return ((QDisplay*)g)->Width();
}

// Get the height of the image
int Height(GDisplay g)
{
  return ((QDisplay*)g)->Height();
}

// Update the entire display window
void Update(GDisplay g)
{ 
  ((QDisplay*)g)->Update();
}

// Update the a portion of the display window
void Update(GDisplay g, int x, int y, int w, int h)
{ 
  ((QDisplay*)g)->Update(x, y, w, h);
}

GColor* GetImageData(GDisplay g)
{
  return (GColor*)((QDisplay*)g)->ImageData();
}


// Wait for all windows to close
void WaitForClose()
{
  app->Run();
}

void SetUpdateRate(GDisplay g, int framesPerSecond)
{
  ((QDisplay*)g)->UpdateRate(framesPerSecond);
}

// Helper to create a GColor structure
GColor RGBColor(unsigned char red, unsigned char green, unsigned char blue)
{
  GColor c;
  c.red = red;
  c.green = green;
  c.blue = blue;
  c.alpha = 0;
  return c;
}
