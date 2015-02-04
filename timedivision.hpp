/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----TimeDivision Class Header-----
  Auston Sterling
  austonst@gmail.com

  Contains the header for the TimeDivision class, for use in MIDI files.
*/

#ifndef _timedivision_hpp_
#define _timedivision_hpp_

#include <vector>
#include <cstdint>

namespace midi
{

  class TimeDivision
  {
  public:
    TimeDivision();
    TimeDivision(std::uint16_t ppqn);
    TimeDivision(std::uint8_t fps, std::uint8_t tpf);
    std::vector<std::uint8_t> data() const;
    void set(std::uint16_t ppqn);
    void set(std::uint8_t fps, std::uint8_t tpf);

  private:
    std::vector<std::uint8_t> data_;
  };

} //Namespace

#endif
