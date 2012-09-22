// Implementation of variable length string class
// ECE4893/8893 Fall 2012
// George F. Riley

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "String.h"

using namespace std;

String::String()
  : st(0)
{ // Default to empty string
}


String::String(const char* st0)
{
  st = (char*)malloc(strlen(st0) + 1);
  strcpy(st, st0);
}

// Copy constructor
String::String(const String& st0)
  : st(0)
{
  if (st0.c_str() != 0)
    { // Not Null string on rhs
      st = (char*)malloc(strlen(st0.c_str()) + 1);
      strcpy(st, st0.c_str());
    }
}

// Destructor
String::~String()
{
  free(st);
}

// Assignment operator
String& String::operator=(const String& rhs)
{
  // Insure not self assignment
  if (&rhs != this)
    {
      // Free original string
      free(st);
      st = (char*)malloc(strlen(rhs.c_str()) + 1);
      strcpy(st, rhs.c_str());
    }
  return *this;
}

// Underlying string accessor
char* String::c_str() const
{
  return st;
}

// Implement the printing function
ostream& operator<<(ostream& os, const String& st)
{
  os << st.c_str();
  return os;
}
