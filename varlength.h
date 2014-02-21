/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Variable Length Number Header-----
  Auston Sterling
  austonst@gmail.com

  MIDI's variable-length number format. Big-endian, where the most significant bit
  in each byte indicates whether or not there are more bytes to read. The maximum
  length is four bytes.
*/

#ifndef _varlength_h_
#define _varlength_h_

#include <stdint.h>
#include <string>

namespace midi
{

  const int VARLENGTH_MAX_SIZE = 4;

  class VarLength
  {
  public:
    //Constructors
    VarLength();
    VarLength(const VarLength& vl);
    VarLength(uint32_t in);
  
    //Operators and typecasts
    operator uint32_t() const;
    VarLength& operator=(const VarLength& vl);
    uint8_t operator[](unsigned char index) const;
    
    //Other useful functions
    size_t size() const;
  private:
    //The number itself
    uint8_t data_[VARLENGTH_MAX_SIZE];
  };

} //Namespace

#endif
