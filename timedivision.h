/*
  -----TimeDivision Class Header-----
  Auston Sterling
  austonst@gmail.com

  Contains the header for the TimeDivision class, for use in MIDI files.
*/

#ifndef _timedivision_h_
#define _timedivision_h_

#include <vector>
#include <stdint.h>

namespace midi
{

  class TimeDivision
  {
  public:
    TimeDivision();
    TimeDivision(uint16_t ppqn);
    TimeDivision(uint8_t fps, uint8_t tpf);
    std::vector<uint8_t> data() const;
    void set(uint16_t ppqn);
    void set(uint8_t fps, uint8_t tpf);

  private:
    std::vector<uint8_t> data_;
  };

} //Namespace

#endif
