/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Scales Listing-----
  Auston Sterling
  austonst@gmail.com

  Contains constants and functions to be able to easily use or reference scales.
*/

#ifndef _scales_h_
#define _scales_h_

#include "note.h"

namespace midi
{
  
  Note majorScale(Note key, char num);
  
  Note natMinorScale(Note key, char num);

  Note harMinorScale(Note key, char num);
  
} //Namespace

#endif
