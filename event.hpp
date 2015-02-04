/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Event Class Header-----
  Auston Sterling
  austonst@gmail.com

  Contains the header for the Event class, referring to MIDI events on a track.
*/

#ifndef _event_hpp_
#define _event_hpp_

#include "varlength.hpp"
#include "instruments.hpp"

#include <vector>
#include <cstdint>

namespace midi
{

  class Event
  {
  public:
    virtual ~Event() {};
    virtual Event* clone() const = 0;
    virtual std::vector<std::uint8_t> data() const = 0;
    virtual std::size_t size() const = 0;
    std::uint32_t dt() const;
    void setdt(std::uint32_t indt);
    virtual std::uint16_t getNote() const = 0;
  
  protected:
    //Common structure
    VarLength deltaTime_;
    std::uint8_t type_;
    std::uint8_t usesNote_;
  };


  //*****CHANNEL EVENTS*****

  class ChannelEvent : public Event
  {
  public:
    virtual ~ChannelEvent() {};
    
    //All channel events write themselves the same way
    std::vector<std::uint8_t> data() const;
    std::size_t size() const;
    std::uint16_t getNote() const;
  
  protected:
    //MIDI Channel Event format
    std::uint8_t channel_;
    std::uint8_t param1_;
    std::uint8_t param2_;
  };

  //Note Off event
  class NoteOffEvent : public ChannelEvent
  {
  public:
    NoteOffEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t note, std::uint8_t velocity);
    Event* clone() const {return new NoteOffEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Note On event
  class NoteOnEvent : public ChannelEvent
  {
  public:
    NoteOnEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t note, std::uint8_t velocity);
    Event* clone() const {return new NoteOnEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Note Aftertouch event
  class NoteAftertouchEvent : public ChannelEvent
  {
  public:
    NoteAftertouchEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t note, std::uint8_t amount);
    Event* clone() const {return new NoteAftertouchEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Controller event
  class ControllerEvent : public ChannelEvent
  {
  public:
    ControllerEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t type, std::uint8_t value);
    Event* clone() const {return new ControllerEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Program Change event
  class ProgramChangeEvent : public ChannelEvent
  {
  public:
    ProgramChangeEvent(std::uint32_t deltaTime, std::uint8_t channel, Instrument number);
    Event* clone() const {return new ProgramChangeEvent(deltaTime_, channel_, param1_);}
  };

  //Channel Aftertouch event
  class ChannelAftertouchEvent : public ChannelEvent
  {
  public:
    ChannelAftertouchEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t amount);
    Event* clone() const {return new ChannelAftertouchEvent(deltaTime_, channel_, param1_);}
  };

  //Pitch Bend event
  class PitchBendEvent : public ChannelEvent
  {
  public:
    PitchBendEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint16_t value);
    Event* clone() const {return new PitchBendEvent(deltaTime_, channel_, (param2_<<7)|param1_);}
  };

  //*****META EVENTS*****

  class MetaEvent : public Event
  {
  public:
    virtual ~MetaEvent() {};
  
    //Size is not the same for all meta events, but required for proper writing
    std::size_t size() const;
    virtual std::vector<std::uint8_t> data() const;
    std::uint16_t getNote() const;
  
  protected:
    //MIDI Meta Event format
    VarLength length_;
    std::vector<std::uint8_t> data_;
  };

  //Sequence Number event
  class SequenceNumberEvent : public MetaEvent
  {
  public:
    SequenceNumberEvent(std::uint16_t number);
    Event* clone() const {return new SequenceNumberEvent((data_[0]<<8)|data_[1]);}
  };

  //Text event
  class TextEvent : public MetaEvent
  {
  public:
    TextEvent(std::string text);
    Event* clone() const {return new TextEvent(std::string(data_.begin(), data_.end()));}
  };

  //Copyright Notice event
  class CopyrightNoticeEvent : public MetaEvent
  {
  public:
    CopyrightNoticeEvent(std::string text);
    Event* clone() const {return new CopyrightNoticeEvent(std::string(data_.begin(), data_.end()));}
  };

  //Sequence/Track Name event
  class SequenceTrackNameEvent : public MetaEvent
  {
  public:
    SequenceTrackNameEvent(std::string text);
    Event* clone() const {return new SequenceTrackNameEvent(std::string(data_.begin(), data_.end()));}
  };

  //Instrument Name event
  class InstrumentNameEvent : public MetaEvent
  {
  public:
    InstrumentNameEvent(std::string text);
    Event* clone() const {return new InstrumentNameEvent(std::string(data_.begin(), data_.end()));}
  };

  //Lyrics event
  class LyricsEvent : public MetaEvent
  {
  public:
    LyricsEvent(std::uint32_t deltaTime, std::string text);
    Event* clone() const {return new LyricsEvent(deltaTime_, std::string(data_.begin(), data_.end()));}
  };

  //Marker event
  class MarkerEvent : public MetaEvent
  {
  public:
    MarkerEvent(std::uint32_t deltaTime, std::string text);
    Event* clone() const {return new MarkerEvent(deltaTime_, std::string(data_.begin(), data_.end()));}
  };

  //Cue Point event
  class CuePointEvent : public MetaEvent
  {
  public:
    CuePointEvent(std::uint32_t deltaTime, std::string text);
    Event* clone() const {return new CuePointEvent(deltaTime_, std::string(data_.begin(), data_.end()));}
  };

  //MIDI Channel Prefix event
  class MIDIChannelPrefixEvent : public MetaEvent
  {
  public:
    MIDIChannelPrefixEvent(std::uint32_t deltaTime, std::uint8_t channel);
    Event* clone() const {return new MIDIChannelPrefixEvent(deltaTime_, data_[0]);}
  };

  //End Of Track event
  class EndOfTrackEvent : public MetaEvent
  {
  public:
    EndOfTrackEvent(std::uint32_t deltaTime);
    Event* clone() const {return new EndOfTrackEvent(deltaTime_);}
  };

  //Set Tempo event
  class SetTempoEvent : public MetaEvent
  {
  public:
    SetTempoEvent(std::uint32_t deltaTime, std::uint32_t mspq);
    Event* clone() const {return new SetTempoEvent(deltaTime_, (data_[0]<<16)|(data_[1]<<8)|data_[2]);}
  };

  //SMPTE Offset event
  class SMPTEOffsetEvent : public MetaEvent
  {
  public:
    SMPTEOffsetEvent(std::uint32_t deltaTime, std::uint8_t hour, std::uint8_t minute, std::uint8_t second, std::uint8_t frame, std::uint8_t sub_frame);
    Event* clone() const {return new SMPTEOffsetEvent(deltaTime_, data_[0], data_[1], data_[2], data_[3], data_[4]);}
  };

  //Time Signature Event
  class TimeSignatureEvent : public MetaEvent
  {
  public:
    TimeSignatureEvent(std::uint32_t deltaTime, std::uint8_t numerator, std::uint8_t denominator, std::uint8_t metronome, std::uint8_t num32s);
    Event* clone() const {return new TimeSignatureEvent(deltaTime_, data_[0], data_[1], data_[2], data_[3]);}
  };

  //Key Signature Event
  class KeySignatureEvent : public MetaEvent
  {
  public:
    KeySignatureEvent(std::uint32_t deltaTime, char key, bool scale);
    Event* clone() const {return new KeySignatureEvent(deltaTime_, data_[0], data_[1]);}
  };

  //Sequencer Specific Event
  class SequencerSpecificEvent : public MetaEvent
  {
  public:
    SequencerSpecificEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> input);
    Event* clone() const {return new SequencerSpecificEvent(deltaTime_, data_);}
  };

  //*****SysEx Events*****
  class SysExEvent : public Event
  {
  public:
    virtual ~SysExEvent() {};
  
    //We don't know the length of these normally
    std::size_t size() const;
    std::vector<std::uint8_t> data() const;
    std::uint16_t getNote() const;

  protected:
    VarLength length_;
    std::vector<std::uint8_t> data_;
  };

  //Normal SysEx Event
  class NormalSysExEvent : public SysExEvent
  {
  public:
    NormalSysExEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> data, bool startDivide = false);
    Event* clone() const {return new NormalSysExEvent(deltaTime_, data_, true);}
  };

  //Divided SysEx Event
  class DividedSysExEvent : public SysExEvent
  {
  public:
    DividedSysExEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> data, bool endDivide = false);
    Event* clone() const {return new DividedSysExEvent(deltaTime_, data_, false);}
  };

  //Authorization SysEx Event
  class AuthorizationSysExEvent : public SysExEvent
  {
  public:
    AuthorizationSysExEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> data);
    Event* clone() const {return new AuthorizationSysExEvent(deltaTime_, data_);}
  };

} //Namespace

#endif
