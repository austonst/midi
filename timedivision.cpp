/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----TimeDivision Class Implementation-----
  Auston Sterling
  austonst@gmail.com

  Contains the implementation for the TimeDivision class, for use in MIDI files.
*/

#include "timedivision.hpp"

namespace midi
{

  //Default constructor
  TimeDivision::TimeDivision()
  {
    data_.resize(2);
  }

  //Pulses Per Quarter Note constructor
  TimeDivision::TimeDivision(std::uint16_t ppqn)
  {
    data_.resize(2);
    set(ppqn);
  }

  //Frames Per Second and Ticks Per Frame constructor
  TimeDivision::TimeDivision(std::uint8_t fps, std::uint8_t tpf)
  {
    data_.resize(2);
    set(fps, tpf);
  }

  //Access the actual data
  std::vector<std::uint8_t> TimeDivision::data() const
  {
    return data_;
  }

  //Set based on Pulses Per Quarter Note
  void TimeDivision::set(std::uint16_t ppqn)
  {
    data_[0] = (ppqn & 0x7FFF) >> 8;
    data_[1] = ppqn & 0xFF;
  }

  //Set based on Frames Per Second and Ticks Per Frame
  void TimeDivision::set(std::uint8_t fps, std::uint8_t tpf)
  {
    data_[0] = -1 * char(fps);
    data_[1] = tpf;
  }

} //Namespace
