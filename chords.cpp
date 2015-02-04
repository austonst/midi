/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Chords Listing-----
  Auston Sterling
  austonst@gmail.com

  Contains functions to be able to easily use or reference common chords.
*/

#ifndef _chords_cpp_
#define _chords_cpp_

#include "chords.hpp"

namespace midi
{
  
  //Returns the major triadic chord with the given root
  Chord majTriad(const Note root)
  {
    return Chord(root, root+4, root+7);
  }
  
  //Returns the minor triadic chord with the given root
  Chord minTriad(const Note root)
  {
    return Chord(root, root+3, root+7);
  }
  
  //Returns the diminished triadic chord with the given root
  Chord dimTriad(const Note root)
  {
    return Chord(root, root+3, root+6);
  }
  
  //Returns the augmented triadic chord with the given root
  Chord augTriad(const Note root)
  {
    return Chord(root, root+4, root+8);
  }

  //Returns the major seventh chord with the given root
  Chord majSeventh(const Note root)
  {
    return Chord(root, root+4, root+7, root+11);
  }

  //Returns the minor seventh chord with the given root
  Chord minSeventh(const Note root)
  {
    return Chord(root, root+3, root+7, root+10);
  }

  //Returns the dominant seventh chord with the given root
  Chord domSeventh(const Note root)
  {
    return Chord(root, root+4, root+7, root+10);
  }

  //Returns the diminished seventh chord with the given root
  Chord dimSeventh(const Note root)
  {
    return Chord(root, root+3, root+6, root+9);
  }

  //Returns the half-diminished seventh chord with the given root
  Chord halfDimSeventh(const Note root)
  {
    return Chord(root, root+3, root+6, root+10);
  }

  //Returns the minor major seventh chord with the given root
  Chord minMajSeventh(const Note root)
  {
    return Chord(root, root+3, root+7, root+11);
  }

  //Returns the augmented major seventh chord with the given root
  Chord augMajSeventh(const Note root)
  {
    return Chord(root, root+4, root+8, root+11);
  }
  
} //Namespace

#endif
