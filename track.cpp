/*
  -----Track Class Implementation-----
  Auston Sterling
  austonst@gmail.com

  Contains the implementation for the Track class, representing a MIDI track.
*/

#include "track.h"

#include <map>

namespace midi
{

  //Destructor
  EventTrack::~EventTrack()
  {
    clear();
  }

  //Clears the vector, freeing all Events
  void EventTrack::clear()
  {
    for (size_t i = 0; i < event_.size(); i++)
      {
        delete event_[i];
      }
    event_.resize(0);
  }

  //Returns the size of the entire track
  size_t EventTrack::size() const
  {
    //Header
    size_t ret = 8;

    //Events
    for (size_t i = 0; i < event_.size(); i++)
      {
        ret += event_[i]->size();
      }

    return ret;
  }

  //Adds an event to the end of the track
  void EventTrack::add(const Event & ev)
  {
    Event* addition = ev.clone();
    event_.push_back(addition);
  }

  //Combines all of the event data along with the header
  std::vector<uint8_t> EventTrack::data() const
  {
    //Construct header
    std::vector<uint8_t> out;
    out.push_back('M');
    out.push_back('T');
    out.push_back('r');
    out.push_back('k');
    size_t trackSize = size()-8;
    out.push_back(trackSize >> 24);
    out.push_back((trackSize >> 16)&0xFF);
    out.push_back((trackSize >> 8)&0xFF);
    out.push_back(trackSize&0xFF);

    //Add on every event's data
    for (size_t i = 0; i < event_.size(); i++)
      {
        //Get the event's data
        std::vector<uint8_t> eventData = event_[i]->data();

        //Add it all
        out.insert(out.end(), eventData.begin(), eventData.end());
      }

    return out;
  }

  //Conversion from an EventTrack to a NoteTrack
  NoteTrack EventTrack::toNotes() const
  {
    //The only events we care about are Note On and Note Off events,
    //which will return their note from getNote. Note On returns the actual
    //note, Note Off returns the note + 128. Any other event returns 256.
    NoteTrack track;
    uint32_t totalTime = 0;
    for (size_t i = 0; i < event_.size(); i++)
      {
        totalTime += event_[i]->dt();
        uint16_t val = event_[i]->getNote();
      
        if (val < 128)
          {
            //Find the associated Note Off event
            uint32_t duration = 0;
            size_t j;
            for (j = i+1; j < event_.size(); j++)
              {
                duration += event_[j]->dt();
                if (event_[j]->getNote() == val+128) break;
              }

            if (j == event_.size()) continue;
          
            NoteTime nt;
            nt.note = val;
            nt.begin = totalTime;
            nt.duration = duration;
            nt.instrument = 0; //FOR NOW...
            track.add(nt);
          }
      }

    return track;
  }

  //Typecast from an EventTrack to a NoteTrack
  EventTrack::operator NoteTrack() const
  {
    return toNotes();
  }

  //Clone function
  Track* EventTrack::clone() const
  {
    EventTrack* et = new EventTrack;
  
    for (size_t i = 0; i < event_.size(); i++)
      {
        et->add(*event_[i]);
      }

    return et;
  }

  //Clears the NoteTrack
  void NoteTrack::clear()
  {
    note_.clear();
  }

  //Returns the size of the data when converted to an EventTrack
  size_t NoteTrack::size() const
  {
    return data().size();
  }

  //Adds a note in a few different ways
  void NoteTrack::add(Note note, uint32_t time, uint32_t duration, uint8_t instrument)
  {
    NoteTime nt;
    nt.note = note;
    nt.begin = time;
    nt.duration = duration;
    nt.instrument = instrument;
    note_.push_back(nt);
  }

  void NoteTrack::add(NoteTime nt)
  {
    note_.push_back(nt);
  }

  void NoteTrack::add(Chord chord, uint32_t time, uint32_t duration, uint8_t instrument)
  {
    //Add each of the notes
    for (std::set<Note>::const_iterator i = chord.notes().begin(); i != chord.notes().end(); i++)
      {
        NoteTime nt;
        nt.note = *i;
        nt.begin = time;
        nt.duration = duration;
        nt.instrument = instrument;
        note_.push_back(nt);
      }
  }

  //Adds this note deltaTime after the last note begins
  void NoteTrack::addAfterLastPress(Note note, uint32_t deltaTime, uint32_t duration, uint8_t instrument)
  {
    uint32_t time = 0;
    for (size_t i = 0; i < note_.size(); i++)
      {
        if (note_[i].begin > time) time = note_[i].begin;
      }

    time += deltaTime;

    add(note, time, duration, instrument);
  }

  //TODO: Verify that this plays all notes at once
  void NoteTrack::addAfterLastPress(Chord chord, uint32_t deltaTime, uint32_t duration, uint8_t instrument)
  {
    //Add each of the notes
    for (std::set<Note>::const_iterator i = chord.notes().begin(); i != chord.notes().end(); i++)
      {
        addAfterLastPress(*i, deltaTime, duration, instrument);
      }
  }

  //Conversion to EventTrack
  EventTrack NoteTrack::toEvents() const
  {
    //Create the event track
    EventTrack track;

    //Add a few starting events
    track.add(TimeSignatureEvent(0, 4, 4, 24, 8));

    //Find all of the instruments used in this track
    std::map<uint8_t, uint8_t> instrumentChannel;
    uint8_t channel = 0;
    for (size_t i = 0; i < note_.size(); i++)
      {
        if (instrumentChannel.find(note_[i].instrument) == instrumentChannel.end())
          {
            instrumentChannel[note_[i].instrument] = channel;
            channel++;
            if (channel > 15) channel = 15;
          }
      }

    for (std::map<uint8_t, uint8_t>::iterator i = instrumentChannel.begin();
         i != instrumentChannel.end(); i++)
      {
        track.add(ProgramChangeEvent(0, i->second, i->first));
      }

    //Create a priority queue
    std::priority_queue<NoteTime, std::vector<NoteTime>, NoteTimeComparer> queue;

    //For each note
    for (size_t i = 0; i < note_.size(); i++)
      {
        //Add both the Note On and Note Off events
        queue.push(note_[i]);
        NoteTime off;
        off.note = note_[i].note;
        off.begin = note_[i].begin + note_[i].duration;
        off.duration = 0;
        off.instrument = note_[i].instrument;
        queue.push(off);
      }

    //Fill up the EventTrack
    uint32_t prevTime = 0;
    while (!queue.empty())
      {
        //Get the next NoteTime
        NoteTime nt = queue.top();
        queue.pop();

        //Find the deltaTime
        uint32_t deltaTime;
        deltaTime = nt.begin - prevTime;
        prevTime = nt.begin;

        //Check if it's a Note On or Note Off event
        if (nt.duration != 0) //Note On
          {
            //Create the event and add it
            track.add(NoteOnEvent(deltaTime, instrumentChannel[nt.instrument], nt.note.midiVal(), 127));
          }
        else //Note off
          {
            track.add(NoteOffEvent(deltaTime, instrumentChannel[nt.instrument], nt.note.midiVal(), 127));
          }
      }

    //Add an End Of Track event
    track.add(EndOfTrackEvent(0));

    return track;
  }

  //Typecast to EventTrack
  NoteTrack::operator EventTrack() const
  {
    return toEvents();
  }

  //Data, which only really makes sense as an EventTrack
  std::vector<uint8_t> NoteTrack::data() const
  {
    return toEvents().data();
  }

  //Clone function
  Track* NoteTrack::clone() const
  {
    NoteTrack* et = new NoteTrack;
  
    for (size_t i = 0; i < note_.size(); i++)
      {
        et->add(note_[i]);
      }

    return et;
  }

} //Namespace
