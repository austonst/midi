/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----MIDI Class Header-----
  Auston Sterling
  austonst@gmail.com

  Contains the header for the MIDI class, representing a MIDI file.
*/

#ifndef _midi_hpp_
#define _midi_hpp_

#include "track.hpp"
#include "timedivision.hpp"

#include <vector>
#include <fstream>
#include <string>

namespace midi
{

  class MIDI
  {
  public:
    virtual ~MIDI() {};
    virtual size_t size() const = 0;
    void write(std::string filename) const;
    virtual std::vector<uint8_t> data() const = 0;
    void setTimeDivision(const TimeDivision & td);
    virtual void clear() = 0;
  protected:
    TimeDivision td_;
  };

  class MIDI_Type0 : public MIDI
  {
  public:
    MIDI_Type0(const Track & tr, const TimeDivision & td);
    ~MIDI_Type0();
    size_t size() const;
    std::vector<uint8_t> data() const;
    void setTrack(const Track & tr);
    void clear();
  private:
    Track* track_;
  };

  class MIDI_Type1 : public MIDI
  {
  public:
    MIDI_Type1(const std::vector<Track*> & tr, const TimeDivision & td);
    MIDI_Type1(const TimeDivision & td);
    ~MIDI_Type1();
    size_t size() const;
    std::vector<uint8_t> data() const;
    void addTrack(const Track & tr);
    void clear();
  private:
    std::vector<Track*> track_;
  };

  class MIDI_Type2 : public MIDI
  {
  public:
    MIDI_Type2(const std::vector<Track*> & tr, const TimeDivision & td);
    MIDI_Type2(const TimeDivision & td);
    ~MIDI_Type2();
    size_t size() const;
    std::vector<uint8_t> data() const;
    void addTrack(const Track & tr);
    void clear();
  private:
    std::vector<Track*> track_;
  };

  //MIDI* load(std::string filename); //IT'S NOT DONE YET. LOTS TO DO.
  void freeLoadedMIDI(MIDI* mid);

} //Namespace

#endif
