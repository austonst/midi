/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Chords Listing-----
  Auston Sterling
  austonst@gmail.com

  Contains functions to be able to easily use or reference common chords.
*/

#ifndef _chords_h_
#define _chords_h_

#include "note.h"

namespace midi
{

  Chord majTriad(const Note root);
  Chord minTriad(const Note root);
  Chord dimTriad(const Note root);
  Chord augTriad(const Note root);

  Chord majSeventh(const Note root);
  Chord minSeventh(const Note root);
  Chord domSeventh(const Note root);
  Chord dimSeventh(const Note root);
  Chord halfDimSeventh(const Note root);
  Chord minMajSeventh(const Note root);
  Chord augMajSeventh(const Note root);
  
} //Namespace

#endif
