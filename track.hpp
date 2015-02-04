/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Track Class Header-----
  Auston Sterling
  austonst@gmail.com

  Contains the header for the Track class, representing a MIDI track.
*/

#ifndef _track_hpp_
#define _track_hpp_

#include "event.hpp"
#include "note.hpp"

#include <vector>
#include <queue>

namespace midi
{

  //Helper struct to track when a note is pressed and how long it is held
  struct NoteTime
  {
    Note note;
    uint32_t begin;
    uint32_t duration;
    Instrument instrument;
  };

  class NoteTimeComparer
  {
  public:
    bool operator()(const NoteTime & nt1, const NoteTime & nt2)
    {
      return nt1.begin > nt2.begin;
    }
  };

  //Forward declaration of NoteTrack
  class NoteTrack;


  //Parent class to the more specific types of tracks
  class Track
  {
  public:
    //Common functions
    virtual ~Track() {};
    virtual void clear() = 0;
    virtual size_t size() const = 0;
    virtual Track* clone() const = 0;
  
    //Retrieve the contents of the track as a vector of uint8_t's
    virtual std::vector<uint8_t> data() const = 0;
  
  private:
  };

  //A track the way MIDI percieves it: as a series of events
  class EventTrack : public Track
  {
  public:
    //Standard stuff
    ~EventTrack();
  
    //Operations on the events
    void clear();
    size_t size() const;
    void add(const Event & ev);
  
    //Implementation of Track::data
    std::vector<uint8_t> data() const;

    //Convert to NoteTrack
    NoteTrack toNotes() const;
    operator NoteTrack() const;

    //Clone function
    Track* clone() const;
  
  private:
    std::vector<Event*> event_;
  };

  //A track the way human beans see it: as a series of notes
  class NoteTrack : public Track
  {
  public:
    //Operations on the notes
    void clear();
    size_t size() const;
    void add(Note note, uint32_t time, uint32_t duration, Instrument instrument = 0);
    void add(NoteTime nt);
    void add(Chord chord, uint32_t time, uint32_t duration, Instrument instrument = 0);
    void addAfterLastPress(Note note, uint32_t deltaTime, uint32_t duration, Instrument instrument = 0);
    void addAfterLastPress(Chord chord, uint32_t deltaTime, uint32_t duration, Instrument instrument = 0);

    //Implementation of Track::data
    std::vector<uint8_t> data() const;

    //Accessor for read-only examination or debugging
    const std::vector<NoteTime> & note() const {return note_;}

    //Convert to EventTrack
    EventTrack toEvents() const;
    operator EventTrack() const;

    //Clone function
    Track* clone() const;
  
  private:
    std::vector<NoteTime> note_;
  };

} //Namespace

#endif
