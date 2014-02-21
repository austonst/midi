/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----MIDI Class Implementation-----
  Auston Sterling
  austonst@gmail.com

  Contains the header for the MIDI class, representing a MIDI file.
*/

#include "midi.h"

namespace midi
{

  //MIDI Class Functions
  //Writes the data to a file
  void MIDI::write(std::string filename) const
  {
    //Open the file
    std::ofstream fout(filename.c_str(), std::ios_base::out |
                       std::ios_base::trunc |
                       std::ios_base::binary);

    //Verify that it opened
    if (!fout) return;

    //Write data
    fout.write((const char*)(&(data()[0])), size());

    //Close file stream
    fout.close();
  }

  //Time division setter
  void MIDI::setTimeDivision(const TimeDivision & td)
  {
    td_ = td;
  }

  //MIDI_Type0 Class Functions
  //Constructor
  MIDI_Type0::MIDI_Type0(const Track & tr, const TimeDivision & td)
  {
    track_ = tr.clone();
    td_ = td;
  }

  //Destructor
  MIDI_Type0::~MIDI_Type0()
  {
    clear();
  }

  //Size
  size_t MIDI_Type0::size() const
  {
    return 14 + track_->size();
  }

  //Data
  std::vector<uint8_t> MIDI_Type0::data() const
  {
    //Create the output vector
    std::vector<uint8_t> out;
  
    //MIDI header
    out.reserve(14);
    out.push_back(0x4D);
    out.push_back(0x54);
    out.push_back(0x68);
    out.push_back(0x64);
    out.push_back(0);
    out.push_back(0);
    out.push_back(0);
    out.push_back(6);

    out.push_back(0);
    out.push_back(0);

    out.push_back(0);
    out.push_back(1);

    std::vector<uint8_t> td = td_.data();
    out.insert(out.end(), td.begin(), td.end());

    //Track data
    std::vector<uint8_t> tdata = track_->data();
    out.insert(out.end(), tdata.begin(), tdata.end());

    //Return the output
    return out;
  }

  //Track setter
  void MIDI_Type0::setTrack(const Track & tr)
  {
    clear();
    track_ = tr.clone();
  }

  //Clears the track
  void MIDI_Type0::clear()
  {
    if (track_ != NULL) delete track_;
    track_ = NULL;
  }

  //MIDI_Type1 Functions
  //Constructor
  MIDI_Type1::MIDI_Type1(const std::vector<Track*> & tr, const TimeDivision & td)
  {
    track_ = tr;
    td_ = td;
  }

  MIDI_Type1::MIDI_Type1(const TimeDivision & td)
  {
    td_ = td;
  }

  //Destructor
  MIDI_Type1::~MIDI_Type1()
  {
    clear();
  }

  //Size accessor
  size_t MIDI_Type1::size() const
  {
    //Start with header
    size_t out  = 14;

    //Add each track
    for (size_t i = 0; i < track_.size(); i++)
      {
        out += track_[i]->size();
      }

    return out;
  }

  //Data
  std::vector<uint8_t> MIDI_Type1::data() const
  {
    //Create the output vector
    std::vector<uint8_t> out;
  
    //MIDI header
    out.reserve(14);
    out.push_back(0x4D);
    out.push_back(0x54);
    out.push_back(0x68);
    out.push_back(0x64);
    out.push_back(0);
    out.push_back(0);
    out.push_back(0);
    out.push_back(6);

    out.push_back(0);
    out.push_back(1);

    out.push_back(track_.size() >> 8);
    out.push_back(track_.size() & 0xFF);

    std::vector<uint8_t> td = td_.data();
    out.insert(out.end(), td.begin(), td.end());

    //Track data
    std::vector<uint8_t> tdata;
    for (size_t i = 0; i < track_.size(); i++)
      {
        tdata = track_[i]->data();
        out.insert(out.end(), tdata.begin(), tdata.end());
      }

    //Return the output
    return out;
  }

  //Adds a track to the MIDI
  void MIDI_Type1::addTrack(const Track & tr)
  {
    track_.push_back(tr.clone());
  }

  //Clears all tracks from the MIDI
  void MIDI_Type1::clear()
  {
    for (size_t i = 0; i < track_.size(); i++)
      {
        delete track_[i];
      }
    track_.resize(0);
  }

  //MIDI_Type2 Functions
  //Constructor
  MIDI_Type2::MIDI_Type2(const std::vector<Track*> & tr, const TimeDivision & td)
  {
    track_ = tr;
    td_ = td;
  }

  MIDI_Type2::MIDI_Type2(const TimeDivision & td)
  {
    td_ = td;
  }

  //Destructor
  MIDI_Type2::~MIDI_Type2()
  {
    clear();
  }

  //Size accessor
  size_t MIDI_Type2::size() const
  {
    //Start with header
    size_t out  = 14;

    //Add each track
    for (size_t i = 0; i < track_.size(); i++)
      {
        out += track_[i]->size();
      }

    return out;
  }

  //Data
  std::vector<uint8_t> MIDI_Type2::data() const
  {
    //Create the output vector
    std::vector<uint8_t> out;
  
    //MIDI header
    out.reserve(14);
    out.push_back(0x4D);
    out.push_back(0x54);
    out.push_back(0x68);
    out.push_back(0x64);
    out.push_back(0);
    out.push_back(0);
    out.push_back(0);
    out.push_back(6);

    out.push_back(0);
    out.push_back(2);

    out.push_back(track_.size() >> 8);
    out.push_back(track_.size() & 0xFF);

    std::vector<uint8_t> td = td_.data();
    out.insert(out.end(), td.begin(), td.end());

    //Track data
    std::vector<uint8_t> tdata;
    for (size_t i = 0; i < track_.size(); i++)
      {
        tdata = track_[i]->data();
        out.insert(out.end(), tdata.begin(), tdata.end());
      }

    //Return the output
    return out;
  }

  //Adds a track to the MIDI
  void MIDI_Type2::addTrack(const Track & tr)
  {
    track_.push_back(tr.clone());
  }

  //Clears all tracks from the MIDI
  void MIDI_Type2::clear()
  {
    for (size_t i = 0; i < track_.size(); i++)
      {
        delete track_[i];
      }
    track_.resize(0);
  }

  //Loads a midi file into the proper structure, returning a pointer to it.
  //Returns NULL if the loading failed
  //THIS MUST BE MANUALLY FREED BY THE USER WITH freeLoadedMIDI
  /*MIDI* load(std::string filename)
  {
    //Open the file if possible
    std::ifstream fin(filename.c_str(), std::ios::in|std::ios::binary);
    if (!fin) return NULL;

    //Read the header
    uint8_t header[14];
    fin.seekg(0, ios::beg);
    fin.read(header, 14);

    //Check the type, time division, and number of tracks
    uint8_t type = header[9];
    uint16_t numTracks = uint16_t(header[10])<<8 | header[11];
    TimeDivision td(uint16_t(header[12])<<8 | header[13]);

    //Read in each track;
    std::vector<Track*> tracks;
    tracks.resize(numTracks);
    for (uint16_t i = 0; i < numTracks; i++)
      {
        //Read the track header
        uint8_t t_head[8];
        file.read(t_head, 8);

        //Find the track size
        uint32_t trackSize = 0;
        for (int j = 0; j < 4; j++)
          {
            trackSize << 8;
            trackSize |= t_head[4+j];
          }

        //Read in the track
        std::vector<uint8_t> tr;
        tr.resize(trackSize);
        fin.read(&(tr[0]), trackSize);

        //Put together the delta time
      }
    
    //Close the file
    fin.close();
    } //IT AINT DONE YET FINISH IT UP*/

  inline void freeLoadedMIDI(MIDI* mid) {delete mid;}

} //Namespace
