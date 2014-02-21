/*
  -----Variable Length Number Implementation-----
  Auston Sterling
  austonst@gmail.com

  MIDI's variable-length number format. Big-endian, where the most significant bit
  in each byte indicates whether or not there are more bytes to read. The maximum
  length is four bytes.
*/

#include "varlength.h"

namespace midi
{

  //Default constructor, all zeros
  VarLength::VarLength()
  {
    for (int i = 0; i < VARLENGTH_MAX_SIZE; i++)
      {
        data_[i] = 0;
      }
  }

  //Copy constructor
  VarLength::VarLength(const VarLength& vl)
  {
    for (int i = 0; i < VARLENGTH_MAX_SIZE; i++)
      {
        data_[i] = vl.data_[i];
      }
  }

  //Constructor from uint32_t
  //Since this class can hold 28 bits, this uses the lower 28 bits of the uint32_t
  VarLength::VarLength(uint32_t in)
  {
    //Copy over 7 bits at a time
    for (int i = VARLENGTH_MAX_SIZE-1; i >= 0; i--)
      {
        data_[i] = in & 0x7F;
        in >>= 7;
      }

    //Assign most significant bits appropriately
    //Last byte always has 0
    data_[VARLENGTH_MAX_SIZE-1] &= ~0x80;

    //For all other bytes
    bool begin = false;
    for (int i = 0; i < VARLENGTH_MAX_SIZE-1; i++)
      {
        //If it's zero and we're not inbetween (1 0 1)
        if (data_[i] == 0 && !begin)
          {
            //Set to 0
            data_[i] &= ~0x80;
          }
        else //Value or inbetween
          {
            data_[i] |= 0x80;
            begin = true;
          }
      }
  }

  //Typecast from VarLength to uint32_t
  VarLength::operator uint32_t() const
  {
    //Create output
    uint32_t ret = 0;

    //Add each component
    for (int i = VARLENGTH_MAX_SIZE-1; i >= 0; i--)
      {
        ret += (data_[i] & 0x7F) << 7*(VARLENGTH_MAX_SIZE - 1 - i);
      }

    //Return the answer
    return ret;
  }

  uint8_t VarLength::operator[](unsigned char index) const
  {
    //Align with actual data
    index += VARLENGTH_MAX_SIZE-size();
    return data_[index];
  }

  //Assignment operator
  VarLength& VarLength::operator=(const VarLength& vl)
  {
    for (int i = 0; i < VARLENGTH_MAX_SIZE; i++)
      {
        data_[i] = vl.data_[i];
      }

    return *this;
  }

  //Returns the size in bytes of this VarLength
  size_t VarLength::size() const
  {
    //Starting size is 1
    size_t ret = 1;

    //Check most significant bits to determine length
    for (int i = VARLENGTH_MAX_SIZE-2; i >= 0; i--)
      {
        if (data_[i] & 0x80) ret++;
      }

    return ret;
  }

} //Namespace
