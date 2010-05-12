// Simple Graphics API for CS1372
// George F. Riley, Georgia Tech, CS1372, Fall 2008

#ifndef __GDISPLAY_H__
#define __GDISPLAY_H__

// Define the type
typedef void* GDisplay;

// Define the GColor structure
typedef struct 
{
  unsigned char blue;   // The red component 
  unsigned char green;  // The blue component
  unsigned char red;    // The green component
  unsigned char alpha;  // The transparency
} GColor;

// Create a blank display of the specified width and height
GDisplay BlankDisplay(int w, int h);

// Load the specified image file and create a display window
GDisplay LoadImage(const char* fileName);

// Return the width of the image
int Width(GDisplay);

// Return the height of the image
int Height(GDisplay);

// Update the on-Screen image
void Update(GDisplay);

// Update a portion of the on-Screen image
void Update(GDisplay, int x, int y, int w, int h);

// Get the image data for the display
GColor* GetImageData(GDisplay);

// Wait for the windows to close
void WaitForClose();

// Set the update rate, in frames per second
void SetUpdateRate(GDisplay g, int framesPerSecond);

// Helper function to make a RGB color element
GColor RGBColor(unsigned char red, unsigned char green, unsigned char blue);

#endif
