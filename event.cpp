/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Event Class Implementation-----
  Auston Sterling
  austonst@gmail.com

  Contains the implementation for the Event class, referring to MIDI events on a track.
*/

#include "event.hpp"

namespace midi
{

  //Event functions
  //All events must have a delta time
  std::uint32_t Event::dt() const
  {
    return deltaTime_;
  }

  void Event::setdt(std::uint32_t indt)
  {
    deltaTime_ = indt;
  }

  //Channel event functions
  std::vector<std::uint8_t> ChannelEvent::data() const
  {
    //Create the output vector
    std::vector<std::uint8_t> out;

    //Start adding things to it
    //Delta Time
    for (std::size_t i = 0; i < deltaTime_.size(); i++)
      {
        out.push_back(deltaTime_[i]);
      }
    //Type and MIDI channel
    out.push_back((type_ << 4) | (channel_ & 0x0F));
    //Parameter 1
    out.push_back(param1_);
    //Parameter 2
    if (param2_ != 0) out.push_back(param2_);

    //Return the completed data
    return out;
  }

  std::size_t ChannelEvent::size() const
  {
    if (param2_ != 0) return deltaTime_.size() + 3;
    return deltaTime_.size() + 2;
  }

  std::uint16_t ChannelEvent::getNote() const
  {
    if (usesNote_ == 1)
      {
        return param1_;
      }
    else if (usesNote_ == 2)
      {
        return param1_+128;
      }
    return 256;
  }

  //Note Off event
  NoteOffEvent::NoteOffEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t note, std::uint8_t velocity)
  {
    deltaTime_ = deltaTime;
    type_ = 0x08;
    channel_ = channel;
    param1_ = note;
    param2_ = velocity;
    usesNote_ = 2;
  }

  //Note On event
  NoteOnEvent::NoteOnEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t note, std::uint8_t velocity)
  {
    deltaTime_ = deltaTime;
    type_ = 0x09;
    channel_ = channel;
    param1_ = note;
    param2_ = velocity;
    usesNote_ = 1;
  }

  //Note Aftertouch event
  NoteAftertouchEvent::NoteAftertouchEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t note, std::uint8_t amount)
  {
    deltaTime_ = deltaTime;
    type_ = 0x0A;
    channel_ = channel;
    param1_ = note;
    param2_ = amount;
    usesNote_ = 0;
  }

  //Controller event
  ControllerEvent::ControllerEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t type, std::uint8_t value)
  {
    deltaTime_ = deltaTime;
    type_ = 0x0B;
    channel_ = channel;
    param1_ = type;
    param2_ = value;
    usesNote_ = 0;
  }

  //Program Change event
  ProgramChangeEvent::ProgramChangeEvent(std::uint32_t deltaTime, std::uint8_t channel, Instrument number)
  {
    deltaTime_ = deltaTime;
    type_ = 0x0C;
    channel_ = channel;
    param1_ = number;
    param2_ = 0;
    usesNote_ = 0;
  }

  //Channel Aftertouch event
  ChannelAftertouchEvent::ChannelAftertouchEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint8_t amount)
  {
    deltaTime_ = deltaTime;
    type_ = 0x0D;
    channel_ = channel;
    param1_ = amount;
    param2_ = 0;
    usesNote_ = 0;
  }

  //Pitch Bend event
  PitchBendEvent::PitchBendEvent(std::uint32_t deltaTime, std::uint8_t channel, std::uint16_t value)
  {
    deltaTime_ = deltaTime;
    type_ = 0x0E;
    channel_ = channel;
    param1_ = value >> 8;
    param2_ = value & 0x00FF;
    usesNote_ = 0;
  }

  //MetaEvent functions
  std::vector<std::uint8_t> MetaEvent::data() const
  {
    //Create the output vector
    std::vector<std::uint8_t> out;

    //Fill it up
    for (std::size_t i = 0; i < deltaTime_.size(); i++)
      {
        out.push_back(deltaTime_[i]);
      }
    out.push_back(0xFF);
    out.push_back(type_);
    for (std::size_t i = 0; i < length_.size(); i++)
      {
        out.push_back(length_[i]);
      }
    out.insert(out.end(), data_.begin(), data_.end());

    //Return
    return out;
  }

  std::size_t MetaEvent::size() const
  {
    return deltaTime_.size() + 2 + length_.size() + data_.size();
  }

  std::uint16_t MetaEvent::getNote() const
  {
    return 256;
  }

  //Sequence Number event
  SequenceNumberEvent::SequenceNumberEvent(std::uint16_t number)
  {
    deltaTime_ = 0;
    type_ = 0x00;
    length_ = 2;
    data_.push_back(number >> 8);
    data_.push_back(number & 0x00FF);
    usesNote_ = 0;
  }

  //Text event
  TextEvent::TextEvent(std::string text)
  {
    deltaTime_ = 0;
    type_ = 0x01;
    length_ = text.size();
    for (std::size_t i = 0; i < text.size(); i++)
      {
        data_.push_back(text[i]);
      }
    usesNote_ = 0;
  }     

  //Copyright Notice event
  CopyrightNoticeEvent::CopyrightNoticeEvent(std::string text)
  {
    deltaTime_ = 0;
    type_ = 0x02;
    length_ = text.size();
    for (std::size_t i = 0; i < text.size(); i++)
      {
        data_.push_back(text[i]);
      }
    usesNote_ = 0;
  }

  //Sequence/Track Name event
  SequenceTrackNameEvent::SequenceTrackNameEvent(std::string text)
  {
    deltaTime_ = 0;
    type_ = 0x03;
    length_ = text.size();
    for (std::size_t i = 0; i < text.size(); i++)
      {
        data_.push_back(text[i]);
      }
    usesNote_ = 0;
  }

  //Instrument Name event
  InstrumentNameEvent::InstrumentNameEvent(std::string text)
  {
    deltaTime_ = 0;
    type_ = 0x04;
    length_ = text.size();
    for (std::size_t i = 0; i < text.size(); i++)
      {
        data_.push_back(text[i]);
      }
    usesNote_ = 0;
  }

  //Lyrics event
  LyricsEvent::LyricsEvent(std::uint32_t deltaTime, std::string text)
  {
    deltaTime_ = deltaTime;
    type_ = 0x05;
    length_ = text.size();
    for (std::size_t i = 0; i < text.size(); i++)
      {
        data_.push_back(text[i]);
      }
    usesNote_ = 0;
  }

  //Marker event
  MarkerEvent::MarkerEvent(std::uint32_t deltaTime, std::string text)
  {
    deltaTime_ = deltaTime;
    type_ = 0x06;
    length_ = text.size();
    for (std::size_t i = 0; i < text.size(); i++)
      {
        data_.push_back(text[i]);
      }
    usesNote_ = 0;
  }

  //Cue Point event
  CuePointEvent::CuePointEvent(std::uint32_t deltaTime, std::string text)
  {
    deltaTime_ = deltaTime;
    type_ = 0x07;
    length_ = text.size();
    for (std::size_t i = 0; i < text.size(); i++)
      {
        data_.push_back(text[i]);
      }
    usesNote_ = 0;
  }

  //MIDI Channel Prefix event
  MIDIChannelPrefixEvent::MIDIChannelPrefixEvent(std::uint32_t deltaTime, std::uint8_t channel)
  {
    deltaTime_ = deltaTime;
    type_ = 0x20;
    length_ = 1;
    data_.push_back(channel);
    usesNote_ = 0;
  }

  //End Of Track event
  EndOfTrackEvent::EndOfTrackEvent(std::uint32_t deltaTime)
  {
    deltaTime_ = deltaTime;
    type_ = 0x2F;
    length_ = 0;
    usesNote_ = 0;
  }

  //Set Tempo event
  SetTempoEvent::SetTempoEvent(std::uint32_t deltaTime, std::uint32_t mspq)
  {
    deltaTime_ = deltaTime;
    type_ = 0x51;
    length_ = 3;
    data_.push_back((mspq & 0xFF0000) >> 16);
    data_.push_back((mspq & 0xFF00) >> 8);
    data_.push_back(mspq & 0xFF);
    usesNote_ = 0;
  }

  //SMPTE Offset event
  SMPTEOffsetEvent::SMPTEOffsetEvent(std::uint32_t deltaTime, std::uint8_t hour, std::uint8_t minute, std::uint8_t second, std::uint8_t frame, std::uint8_t sub_frame)
  {
    deltaTime_ = deltaTime;
    type_ = 0x54;
    length_ = 5;
    data_.push_back(hour);
    data_.push_back(minute);
    data_.push_back(second);
    data_.push_back(frame);
    data_.push_back(sub_frame);
    usesNote_ = 0;
  }

  //Time Signature event
  TimeSignatureEvent::TimeSignatureEvent(std::uint32_t deltaTime, std::uint8_t numerator, std::uint8_t denominator, std::uint8_t metronome, std::uint8_t num32s)
  {
    deltaTime_ = deltaTime;
    type_ = 0x58;
    length_ = 4;
    data_.push_back(numerator);
    data_.push_back(denominator);
    data_.push_back(metronome);
    data_.push_back(num32s);
    usesNote_ = 0;
  }

  //Key Signature event
  KeySignatureEvent::KeySignatureEvent(std::uint32_t deltaTime, char key, bool scale)
  {
    deltaTime_ = deltaTime;
    type_ = 0x59;
    length_ = 2;
    data_.push_back(key);
    if (scale) data_.push_back(0x01);
    else data_.push_back(0x00);
    usesNote_ = 0;
  }

  //Sequencer Specific Event
  SequencerSpecificEvent::SequencerSpecificEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> input)
  {
    deltaTime_ = deltaTime;
    type_ = 0x7F;
    length_ = input.size();
    data_.insert(data_.end(), input.begin(), input.end());
    usesNote_ = 0;
  }

  //SysExEvent functions
  std::vector<std::uint8_t> SysExEvent::data() const
  {
    //Create the output vector
    std::vector<std::uint8_t> out;

    //Fill it up
    for (std::size_t i = 0; i < deltaTime_.size(); i++)
      {
        out.push_back(deltaTime_[i]);
      }
    out.push_back(type_);
    for (std::size_t i = 0; i < length_.size(); i++)
      {
        out.push_back(length_[i]);
      }
    out.insert(out.end(), data_.begin(), data_.end());

    //Return
    return out;
  }

  std::size_t SysExEvent::size() const
  {
    return deltaTime_.size() + 1 + length_.size() + data_.size();
  }

  std::uint16_t SysExEvent::getNote() const
  {
    return 256;
  }

  //Normal SysEx event
  NormalSysExEvent::NormalSysExEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> data, bool startDivide)
  {
    deltaTime_ = deltaTime;
    type_ = 0xF0;
    length_ = data.size() + (startDivide?0:1);
    data_.insert(data_.end(), data.begin(), data.end());
    if (!startDivide) data_.push_back(0xF7);
    usesNote_ = 0;
  }

  //Divided SysEx event
  DividedSysExEvent::DividedSysExEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> data, bool endDivide)
  {
    deltaTime_ = deltaTime;
    type_ = 0xF7;
    length_ = data.size() + (endDivide?1:0);
    data_.insert(data_.end(), data.begin(), data.end());
    if (endDivide) data_.push_back(0xF7);
    usesNote_ = 0;
  }

  //Authorization SysEx event
  AuthorizationSysExEvent::AuthorizationSysExEvent(std::uint32_t deltaTime, std::vector<std::uint8_t> data)
  {
    deltaTime_ = deltaTime;
    type_ = 0xF7;
    length_ = data.size();
    data_.insert(data_.end(), data.begin(), data.end());
    usesNote_ = 0;
  }

} //Namespace
