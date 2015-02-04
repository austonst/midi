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

#ifndef _varlength_hpp_
#define _varlength_hpp_

#include <cstdint>
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
    VarLength(std::uint32_t in);
  
    //Operators and typecasts
    operator std::uint32_t() const;
    VarLength& operator=(const VarLength& vl);
    std::uint8_t operator[](unsigned char index) const;
    
    //Other useful functions
    std::size_t size() const;
  private:
    //The number itself
    std::uint8_t data_[VARLENGTH_MAX_SIZE];
  };

} //Namespace

#endif
