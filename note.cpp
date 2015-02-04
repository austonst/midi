/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Note Implementation File-----
  Auston Sterling
  austonst@gmail.com
  
  Contains the implementations for the Note class and other related classes.
*/

#include "note.hpp"

namespace midi
{

  //Default constructor sets the internal note to 0, the lowest MIDI note
  Note::Note() : number_(0) {}

  //Takes in a note in format [Note][Octave] (C4, D#2, Bb6)
  Note::Note(const std::string& notation)
  {
    //Extract components and verify size and input
    int8_t note, mod, octave;
    int8_t unused = -2;
  
    note = notation[0];
    if (notation.size() == 2)
      {
        octave = notation[1] - '0';
        mod = unused;
      }
    else if (notation.size() == 3)
      {
        //Two cases, _10 or _[#b]_
        if (notation[1] == '1')
          {
            if (notation[2] != '0')
              {
                number_ = 0;
                return;
              }
            else octave = 10;
            mod = unused;
          }
        else if (notation[1] == '#' || notation[1] == 'b')
          {
            mod = notation[1];
            octave = notation[2] - '0';
          }
      }
    else if (notation.size() == 4)
      {
        if (notation[2] != '1' || notation[3] != '0')
          {
            number_ = 0;
            return;
          }
        mod = notation[1];
        octave = 10;
      }
    else
      {
        number_ = 0;
        return;
      }
  
    //Convert lower case note to upper case
    if (note > 'Z' || note < 'A') note -= 'a'-'A';

    //Lowest note is C, not A
    if (note < 'C') note += 'H'-'A';

    //Make room for the various sharps and flats
    int8_t newnote = note;
    if (note > 'C') newnote++;
    if (note > 'D') newnote++;
    if (note > 'F') newnote++;
    if (note > 'G') newnote++;
    if (note > 'H') newnote++;
    note = newnote;

    //Find any modification from sharp or flat
    if (mod != unused)
      {
        switch (mod)
          {
          case 'b': if (note != 0) note--;
            break;
          case '#': if (note != 127) note++;
            break;
          default: break;
          }
      }

    //Verify that the octave is a reasonable number
    if (octave < 0 || octave > 10)
      {
        number_ = 0;
        return;
      }

    //Finally, convert to midi number
    number_ = (note - 'C') + (12 * octave);
  }

  //Takes in a note as a string
  Note::Note(const char* notation)
  {
    std::string str(notation);
    *this = Note(str);
  }

  //Takes in a note as a midi number
  Note::Note(int8_t innumber) : number_(innumber) {}

  //Takes in a note as a midi number
  Note::Note(int innumber) : number_(innumber) {}

  //Returns the data in format [Note][Octave]
  std::string Note::val() const
  {
    //Return the proper string
    if (number_/12 < 10)
      {
        return MIDI_NOTE[number_%12] + char(((number_/12)) + '0');
      }
    else
      {
        return MIDI_NOTE[number_%12] + "10";
      }
  }

  //Typecast to string
  Note::operator std::string() const
  {
    return val();
  }

  //Returns the note as a midi number
  int8_t Note::midiVal() const
  {
    return number_;
  }

  //Typecast to int8_t
  Note::operator int8_t() const
  {
    return midiVal();
  }

  //Note operators
  bool operator==(const Note& n1, const Note& n2)
  {
    return n1.midiVal() == n2.midiVal();
  }

  bool operator!=(const Note& n1, const Note& n2)
  {
    return n1.midiVal() != n2.midiVal();
  }

  bool operator==(const Note& n1, const int& n2)
  {
    return n1.midiVal() == n2;
  }

  bool operator!=(const Note& n1, const int& n2)
  {
    return n1.midiVal() != n2;
  }

  bool operator==(const int& n1, const Note& n2)
  {
    return n1 == n2.midiVal();
  }

  bool operator!=(const int& n1, const Note& n2)
  {
    return n1 != n2.midiVal();
  }

  //Default constructor does nothing!
  Chord::Chord() {};

  //Standard constructor allows for up to five initial notes
  Chord::Chord(const Note n1, const Note n2, const Note n3,
               const Note n4, const Note n5)
  {
    //Just add all five
    add(n1, n2, n3, n4, n5);
  }

  //Adds the given notes. Returns true only if all were added properly
  bool Chord::add(const Note n1, const Note n2, const Note n3,
                  const Note n4, const Note n5)
  {
    bool ret = true;

    //Always try to insert n1
    if (!(note_.insert(n1).second)) ret = false;

    //Only insert the others if they aren't -1
    if (n2 != -1) if (!(note_.insert(n2).second)) ret = false;
    if (n3 != -1) if (!(note_.insert(n3).second)) ret = false;
    if (n4 != -1) if (!(note_.insert(n4).second)) ret = false;
    if (n5 != -1) if (!(note_.insert(n5).second)) ret = false;

    return ret;
  }

  //Removes the given notes
  bool Chord::remove(const Note n1, const Note n2, const Note n3,
                     const Note n4, const Note n5)
  {
    bool ret = true;
  
    //Always try to remove n1
    if (note_.erase(n1) == 0) ret = false;

    //Only erase the others if they aren't -1
    if (n2 != -1) if (note_.erase(n2) == 0) ret = false;
    if (n3 != -1) if (note_.erase(n3) == 0) ret = false;
    if (n4 != -1) if (note_.erase(n4) == 0) ret = false;
    if (n5 != -1) if (note_.erase(n5) == 0) ret = false;

    return ret;
  }

  //Returns true only if the given note is contained in the chord
  bool Chord::contains(const Note innote) const
  {
    return note_.find(innote) != note_.end();
  }

  //Returns the set for viewing
  const std::set<Note>& Chord::notes() const
  {
    return note_;
  }

} //Namespace
