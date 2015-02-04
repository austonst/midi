/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Note Header File-----
  Auston Sterling
  austonst@gmail.com
  
  Contains the headers for the Note class and other related classes.
*/

#ifndef _note_hpp_
#define _note_hpp_

#include <string>
#include <set>
#include <cstdint>

namespace midi
{

  const std::string MIDI_NOTE[12] =
    {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

  class Note
  {
  public:
    //Constructors
    Note();
    Note(const std::string& notation);
    Note(std::int8_t innumber);
    Note(const char* notation);
    Note(int innumber);

    //Get the data in different formats
    std::string val() const;
    operator std::string() const;
    std::int8_t midiVal() const;
    operator std::int8_t() const;
  
  private:
    std::int8_t number_;
  };

  //Note operators
  bool operator==(const Note& n1, const Note& n2);
  bool operator!=(const Note& n1, const Note& n2);
  bool operator==(const Note& n1, const int& n2);
  bool operator!=(const Note& n1, const int& n2);
  bool operator==(const int& n1, const Note& n2);
  bool operator!=(const int& n1, const Note& n2);

  class Chord
  {
  public:
    //Constructors
    Chord();
    Chord(const Note n1, const Note n2 = -1, const Note n3 = -1,
          const Note n4 = -1, const Note n5 = -1);

    //Note operations
    bool add(const Note n1, const Note n2 = -1, const Note n3 = -1,
             const Note n4 = -1, const Note n5 = -1);
    bool remove(const Note n1, const Note n2 = -1, const Note n3 = -1,
                const Note n4 = -1, const Note n5 = -1);
    bool contains(const Note innote) const;

    //Accessor, just for viewing
    const std::set<Note>& notes() const;
  
  private:
    std::set<Note> note_;
  };

} //Namespace

#endif
