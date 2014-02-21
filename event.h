/*
  -----Event Class Header-----
  Auston Sterling
  austonst@gmail.com

  Contains the header for the Event class, referring to MIDI events on a track.
*/

#ifndef _event_h_
#define _event_h_

#include "varlength.h"
#include "instruments.h"

#include <vector>
#include <stdint.h>

namespace midi
{

  class Event
  {
  public:
    virtual ~Event() {};
    virtual Event* clone() const = 0;
    virtual std::vector<uint8_t> data() const = 0;
    virtual size_t size() const = 0;
    uint32_t dt() const;
    void setdt(uint32_t indt);
    virtual uint16_t getNote() const = 0;
  
  protected:
    //Common structure
    VarLength deltaTime_;
    uint8_t type_;
    uint8_t usesNote_;
  };


  //*****CHANNEL EVENTS*****

  class ChannelEvent : public Event
  {
  public:
    virtual ~ChannelEvent() {};
    
    //All channel events write themselves the same way
    std::vector<uint8_t> data() const;
    size_t size() const;
    uint16_t getNote() const;
  
  protected:
    //MIDI Channel Event format
    uint8_t channel_;
    uint8_t param1_;
    uint8_t param2_;
  };

  //Note Off event
  class NoteOffEvent : public ChannelEvent
  {
  public:
    NoteOffEvent(uint32_t deltaTime, uint8_t channel, uint8_t note, uint8_t velocity);
    Event* clone() const {return new NoteOffEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Note On event
  class NoteOnEvent : public ChannelEvent
  {
  public:
    NoteOnEvent(uint32_t deltaTime, uint8_t channel, uint8_t note, uint8_t velocity);
    Event* clone() const {return new NoteOnEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Note Aftertouch event
  class NoteAftertouchEvent : public ChannelEvent
  {
  public:
    NoteAftertouchEvent(uint32_t deltaTime, uint8_t channel, uint8_t note, uint8_t amount);
    Event* clone() const {return new NoteAftertouchEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Controller event
  class ControllerEvent : public ChannelEvent
  {
  public:
    ControllerEvent(uint32_t deltaTime, uint8_t channel, uint8_t type, uint8_t value);
    Event* clone() const {return new ControllerEvent(deltaTime_, channel_, param1_, param2_);}
  };

  //Program Change event
  class ProgramChangeEvent : public ChannelEvent
  {
  public:
    ProgramChangeEvent(uint32_t deltaTime, uint8_t channel, Instrument number);
    Event* clone() const {return new ProgramChangeEvent(deltaTime_, channel_, param1_);}
  };

  //Channel Aftertouch event
  class ChannelAftertouchEvent : public ChannelEvent
  {
  public:
    ChannelAftertouchEvent(uint32_t deltaTime, uint8_t channel, uint8_t amount);
    Event* clone() const {return new ChannelAftertouchEvent(deltaTime_, channel_, param1_);}
  };

  //Pitch Bend event
  class PitchBendEvent : public ChannelEvent
  {
  public:
    PitchBendEvent(uint32_t deltaTime, uint8_t channel, uint16_t value);
    Event* clone() const {return new PitchBendEvent(deltaTime_, channel_, (param2_<<7)|param1_);}
  };

  //*****META EVENTS*****

  class MetaEvent : public Event
  {
  public:
    virtual ~MetaEvent() {};
  
    //Size is not the same for all meta events, but required for proper writing
    size_t size() const;
    virtual std::vector<uint8_t> data() const;
    uint16_t getNote() const;
  
  protected:
    //MIDI Meta Event format
    VarLength length_;
    std::vector<uint8_t> data_;
  };

  //Sequence Number event
  class SequenceNumberEvent : public MetaEvent
  {
  public:
    SequenceNumberEvent(uint16_t number);
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
    LyricsEvent(uint32_t deltaTime, std::string text);
    Event* clone() const {return new LyricsEvent(deltaTime_, std::string(data_.begin(), data_.end()));}
  };

  //Marker event
  class MarkerEvent : public MetaEvent
  {
  public:
    MarkerEvent(uint32_t deltaTime, std::string text);
    Event* clone() const {return new MarkerEvent(deltaTime_, std::string(data_.begin(), data_.end()));}
  };

  //Cue Point event
  class CuePointEvent : public MetaEvent
  {
  public:
    CuePointEvent(uint32_t deltaTime, std::string text);
    Event* clone() const {return new CuePointEvent(deltaTime_, std::string(data_.begin(), data_.end()));}
  };

  //MIDI Channel Prefix event
  class MIDIChannelPrefixEvent : public MetaEvent
  {
  public:
    MIDIChannelPrefixEvent(uint32_t deltaTime, uint8_t channel);
    Event* clone() const {return new MIDIChannelPrefixEvent(deltaTime_, data_[0]);}
  };

  //End Of Track event
  class EndOfTrackEvent : public MetaEvent
  {
  public:
    EndOfTrackEvent(uint32_t deltaTime);
    Event* clone() const {return new EndOfTrackEvent(deltaTime_);}
  };

  //Set Tempo event
  class SetTempoEvent : public MetaEvent
  {
  public:
    SetTempoEvent(uint32_t deltaTime, uint32_t mspq);
    Event* clone() const {return new SetTempoEvent(deltaTime_, (data_[0]<<16)|(data_[1]<<8)|data_[2]);}
  };

  //SMPTE Offset event
  class SMPTEOffsetEvent : public MetaEvent
  {
  public:
    SMPTEOffsetEvent(uint32_t deltaTime, uint8_t hour, uint8_t minute, uint8_t second, uint8_t frame, uint8_t sub_frame);
    Event* clone() const {return new SMPTEOffsetEvent(deltaTime_, data_[0], data_[1], data_[2], data_[3], data_[4]);}
  };

  //Time Signature Event
  class TimeSignatureEvent : public MetaEvent
  {
  public:
    TimeSignatureEvent(uint32_t deltaTime, uint8_t numerator, uint8_t denominator, uint8_t metronome, uint8_t num32s);
    Event* clone() const {return new TimeSignatureEvent(deltaTime_, data_[0], data_[1], data_[2], data_[3]);}
  };

  //Key Signature Event
  class KeySignatureEvent : public MetaEvent
  {
  public:
    KeySignatureEvent(uint32_t deltaTime, char key, bool scale);
    Event* clone() const {return new KeySignatureEvent(deltaTime_, data_[0], data_[1]);}
  };

  //Sequencer Specific Event
  class SequencerSpecificEvent : public MetaEvent
  {
  public:
    SequencerSpecificEvent(uint32_t deltaTime, std::vector<uint8_t> input);
    Event* clone() const {return new SequencerSpecificEvent(deltaTime_, data_);}
  };

  //*****SysEx Events*****
  class SysExEvent : public Event
  {
  public:
    virtual ~SysExEvent() {};
  
    //We don't know the length of these normally
    size_t size() const;
    std::vector<uint8_t> data() const;
    uint16_t getNote() const;

  protected:
    VarLength length_;
    std::vector<uint8_t> data_;
  };

  //Normal SysEx Event
  class NormalSysExEvent : public SysExEvent
  {
  public:
    NormalSysExEvent(uint32_t deltaTime, std::vector<uint8_t> data, bool startDivide = false);
    Event* clone() const {return new NormalSysExEvent(deltaTime_, data_, true);}
  };

  //Divided SysEx Event
  class DividedSysExEvent : public SysExEvent
  {
  public:
    DividedSysExEvent(uint32_t deltaTime, std::vector<uint8_t> data, bool endDivide = false);
    Event* clone() const {return new DividedSysExEvent(deltaTime_, data_, false);}
  };

  //Authorization SysEx Event
  class AuthorizationSysExEvent : public SysExEvent
  {
  public:
    AuthorizationSysExEvent(uint32_t deltaTime, std::vector<uint8_t> data);
    Event* clone() const {return new AuthorizationSysExEvent(deltaTime_, data_);}
  };

} //Namespace

#endif
