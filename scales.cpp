/*
  -----Scales Listing-----
  Auston Sterling
  austonst@gmail.com

  Contains constants and functions to be able to easily use or reference scales.
*/

#ifndef _scales_cpp_
#define _scales_cpp_

#include "scales.h"

namespace midi
{

  //Returns the note given as a number in the major scale based at the input key
  Note majorScale(Note key, char num)
  {
    num--;
    char minus = 2*(num/7)+((num%7>2)?1:0);
    return key + num*2 - minus;
  }

  //Returns the note given as a number in the natural minor scale based at the input key
  Note natMinorScale(Note key, char num)
  {
    num--;
    char minus = 2*(num/7)+((num%7>1)?1:0)+((num%7>4)?1:0);
    return key + num*2 - minus;
  }

  //Returns the note given as a number in the harmonic minor scale based at the key
  Note harMinorScale(Note key, char num)
  {
    num--;
    char minus = 2*(num/7)+((num%7>1)?1:0)+((num%7>4)?1:0)-((num%7>5)?1:0);
    return key + num*2 - minus;
  }
  
} //Namespace

#endif
