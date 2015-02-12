/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----MIDI Library Test-----
  Auston Sterling
  austonst@gmail.com

  Unit tests for various aspects of the MIDI library.
*/

#include "midi.hpp"
#include "instruments.hpp"
#include "scales.hpp"
#include "chords.hpp"

#include <iostream>
#include <string>

using namespace midi;

void displayAndReset(bool & pass, int & fail, std::string id)
{
  if (pass)
    {
      std::cout << "[" << id << "]: PASS" << std::endl;
    }
  else
    {
      std::cout << "[" << id << "]: **FAIL**" << std::endl;
      fail++;
    }

  pass = true;
}

int main()
{
  //Initial header and setup
  std::cout << "-----MIDI Library Unit Tests-----" << std::endl;
  bool pass = true;
  int fail = 0;
  
  //-----VARLENGTH TESTS-----//
  std::cout << std::endl << "--VARLENGTH TESTS--" << std::endl;

  //VL01: Construction and general data 1
  VarLength vl1(0);
  if (vl1.size() != 1) pass = false;
  if (vl1[0] != 0) pass = false;
  
  displayAndReset(pass, fail, "VL01");

  //VL02: Construction and general data 2
  VarLength vl2(0xC8);
  if (vl2.size() != 2) pass = false;
  if (vl2[0] != 0x81 || vl2[1] != 0x48) pass = false;

  displayAndReset(pass, fail, "VL02");

  //VL03: Construction and general data 3
  VarLength vl3(0x100000);
  if (vl3.size() != 3) pass = false;
  if (vl3[0] != 0xC0 || vl3[1] != 0x80 || vl3[2] != 0) pass = false;

  displayAndReset(pass, fail, "VL03");
  
  //VL04: Copy constructor
  VarLength vl4(vl3);
  for (int i = 0; i < VARLENGTH_MAX_SIZE; i++)
    {
      if (vl3[i] != vl4[i]) pass = false;
    }

  displayAndReset(pass, fail, "VL04");
  
  //VL05: uint32_t typecast
  VarLength vl5(12345);
  if (std::uint32_t(vl5) != 12345) pass = false;

  displayAndReset(pass, fail, "VL05");

  //VL06: Assignment operator
  VarLength vl6 = vl5;
  for (std::size_t i = 0; i < vl6.size(); i++)
    {
      if (vl6[i] != vl5[i]) pass = false;
    }

  displayAndReset(pass, fail, "VL06");

  //-----NOTE AND CHORD TESTS-----//
  std::cout << std::endl << "--NOTE AND CHORD TESTS--" << std::endl;

  //NC01: Midi value construction and access 1
  Note no1;
  if (no1.midiVal() != 0) pass = false;
  displayAndReset(pass, fail, "NC01");

  //NC02: Midi value construction and access 2
  Note no2(100);
  if (no2.midiVal() != 100) pass = false;
  displayAndReset(pass, fail, "NC02");

  //NC03: Notation construction and access 1
  Note no3("C4");
  if (no3.midiVal() != 48) pass = false;
  if (no3.val() != "C4") pass = false;
  displayAndReset(pass, fail, "NC03");

  //NC04: Notation construction and access 2
  Note no4("Bb5");
  if (no4.midiVal() != 70) pass = false;
  if (no4.val() != "A#5" && no4.val() != "Bb5") pass = false;
  displayAndReset(pass, fail, "NC04");

  //NC05: Octave 10 edge case
  Note no5("F#10");
  if (no5.midiVal() != 126) pass = false;
  if (no5.val() != "F#10" && no5.val() != "Gb10") pass = false;
  displayAndReset(pass, fail, "NC05");

  //NC06: String typecast
  Note no6(no4);
  if (std::string(no6) != "A#5" && std::string(no6) != "Bb5") pass = false;
  displayAndReset(pass, fail, "NC06");

  //NC07: int8_t and int typecast
  Note no7 = no6;
  if (std::int8_t(no7) != 70) pass = false;
  if (int(no7) != 70) pass = false;
  if (no7 != 70) pass = false;
  displayAndReset(pass, fail, "NC07");

  //NC08: Octave 0 edge case
  Note no8("C0");
  if (no8.midiVal() != 0) pass = false;
  if (no8.val() != "C0") pass = false;
  displayAndReset(pass, fail, "NC08");

  //NC09: Lowercase and A edge case
  Note no9("a8");
  if (no9.midiVal() != 105) pass = false;
  if (no9.val() != "A8") pass = false;
  displayAndReset(pass, fail, "NC09");

  //NC10: Default constructor
  Chord ch1;
  if (ch1.remove(Note(20), 0)) pass = false;
  if (ch1.contains(Note(10))) pass = false;
  if (ch1.notes().size() != 0) pass = false;
  displayAndReset(pass, fail, "NC10");

  //NC11: Standard constructor and contains
  Chord ch2(Note("G10"), Note("F#0"), Note(1));
  if (!ch2.contains(Note("G10"))) pass = false;
  if (!ch2.contains(Note("F#0"))) pass = false;
  if (!ch2.contains(Note(1))) pass = false;
  if (ch2.contains(Note(2))) pass = false;
  if (ch2.contains(Note("F0"))) pass = false;
  displayAndReset(pass, fail, "NC11");

  //NC12: Add and remove
  Chord ch3;
  if (!ch3.add(Note(5), Note(6), Note(7))) pass = false;
  if (ch3.add(Note(4), Note(5))) pass = false;
  if (!ch3.contains(4)) pass = false;
  if (!ch3.remove(5)) pass = false;
  if (ch3.remove(5)) pass = false;
  if (ch3.contains(5)) pass = false;
  displayAndReset(pass, fail, "NC12");

  //-----TIMEDIVISION TESTS-----//
  std::cout << std::endl << "--TIMEDIVISION TESTS--" << std::endl;

  //TD01: Default construction
  TimeDivision td1;
  if (td1.data().size() != 2) pass = false;
  if (td1.data()[0] != 0) pass = false;
  if (td1.data()[1] != 0) pass = false;
  displayAndReset(pass, fail, "TD01");

  //TD02: PPQN construction and storage
  td1 = TimeDivision(1548);
  if (td1.data().size() != 2) pass = false;
  if (td1.data()[0] != 0x06 || td1.data()[1] != 0x0C) pass = false;
  displayAndReset(pass, fail, "TD02");

  //TD03: FPS and TPF construction and storage
  TimeDivision td2(64, 168);
  if (td2.data().size() != 2) pass = false;
  if (td2.data()[0] != 192 || td2.data()[1] != 168) pass = false;
  displayAndReset(pass, fail, "TD03");

  //-----EVENT TESTS-----//
  std::cout << std::endl << "--EVENT TESTS--" << std::endl;

  //EV01: NoteOffEvent construction test
  NoteOffEvent ev1(0, 1, 1, 1);
  if (ev1.size() != 4) pass = false;
  if (ev1.data()[0] != 0) pass = false;
  if (ev1.data()[1] != 0x81) pass = false;
  if (ev1.data()[2] != 1) pass = false;
  if (ev1.data()[3] != 1) pass = false;
  displayAndReset(pass, fail, "EV01");

  //EV02: NoteOnEvent construction test
  NoteOnEvent ev2(0, 2, 2, 2);
  if (ev2.size() != 4) pass = false;
  if (ev2.data()[0] != 0) pass = false;
  if (ev2.data()[1] != 0x92) pass = false;
  if (ev2.data()[2] != 2) pass = false;
  if (ev2.data()[3] != 2) pass = false;
  displayAndReset(pass, fail, "EV02");

  //EV03: PitchBendEvent construction test
  PitchBendEvent ev3(512, 3, 1548);
  if (ev3.size() != 5) pass = false;
  if (ev3.data()[0] != 0x84) pass = false;
  if (ev3.data()[1] != 0) pass = false;
  if (ev3.data()[2] != 0xE3) pass = false;
  if (ev3.data()[3] != 0x06) pass = false;
  if (ev3.data()[4] != 0x0C) pass = false;
  displayAndReset(pass, fail, "EV03");

  //EV04: SequenceNumberEvent construction test
  SequenceNumberEvent ev4(1548);
  if (ev4.size() != 6) pass = false;
  if (ev4.data()[0] != 0) pass = false;
  if (ev4.data()[1] != 0xFF) pass = false;
  if (ev4.data()[2] != 0) pass = false;
  if (ev4.data()[3] != 2) pass = false;
  if (ev4.data()[4] != 0x06) pass = false;
  if (ev4.data()[5] != 0x0C) pass = false;
  displayAndReset(pass, fail, "EV04");

  //EV05: MarkerEvent construction test
  MarkerEvent ev5(512, "abc");
  if (ev5.size() != 8) pass = false;
  if (ev5.data()[0] != 0x84) pass = false;
  if (ev5.data()[1] != 0) pass = false;
  if (ev5.data()[2] != 0xFF) pass = false;
  if (ev5.data()[3] != 6) pass = false;
  if (ev5.data()[4] != 3) pass = false;
  if (ev5.data()[5] != 'a') pass = false;
  if (ev5.data()[6] != 'b') pass = false;
  if (ev5.data()[7] != 'c') pass = false;
  displayAndReset(pass, fail, "EV05");

  //EV06: SetTempoEvent construction test
  SetTempoEvent ev6(0, 1548);
  if (ev6.size() != 7) pass = false;
  if (ev6.data()[0] != 0) pass = false;
  if (ev6.data()[1] != 0xFF) pass = false;
  if (ev6.data()[2] != 0x51) pass = false;
  if (ev6.data()[3] != 3) pass = false;
  if (ev6.data()[4] != 0) pass = false;
  if (ev6.data()[5] != 0x06) pass = false;
  if (ev6.data()[6] != 0x0C) pass = false;
  displayAndReset(pass, fail, "EV06");

  //EV07: KeySignatureEvent construction test
  KeySignatureEvent ev7(0, -2, true);
  if (std::int8_t(ev7.data()[4]) != -2) pass = false;
  if (ev7.data()[5] != 1) pass = false;
  displayAndReset(pass, fail, "EV07");

  //EV08: SysExEvent construction test
  std::vector<std::uint8_t> testdata;
  testdata.push_back(1);
  NormalSysExEvent ev8(0, testdata, true);
  if (ev8.size() != 4) pass = false;
  if (ev8.data()[0] != 0) pass = false;
  if (ev8.data()[1] != 0xF0) pass = false;
  if (ev8.data()[2] != 1) pass = false;
  if (ev8.data()[3] != 1) pass = false;
  DividedSysExEvent ev8a(0, testdata, true);
  if (ev8a.size() != 5) pass = false;
  if (ev8a.data()[0] != 0) pass = false;
  if (ev8a.data()[1] != 0xF7) pass = false;
  if (ev8a.data()[2] != 2) pass = false;
  if (ev8a.data()[3] != 1) pass = false;
  if (ev8a.data()[4] != 0xF7) pass = false;
  displayAndReset(pass, fail, "EV08");

  //EV09: getNote test
  if (ev8.getNote() != 256) pass = false;
  if (ev3.getNote() != 256) pass = false;
  if (ev2.getNote() != 2) pass = false;
  if (ev1.getNote() != 129) pass = false;
  displayAndReset(pass, fail, "EV09");

  //EV10: Clone test
  Event* ev10 = ev8.clone();
  if (ev10->size() != 4) pass = false;
  if (ev10->data()[0] != 0) pass = false;
  if (ev10->data()[1] != 0xF0) pass = false;
  if (ev10->data()[2] != 1) pass = false;
  if (ev10->data()[3] != 1) pass = false;
  delete ev10;
  ev10 = ev5.clone();
  if (ev10->size() != 8) pass = false;
  if (ev10->data()[0] != 0x84) pass = false;
  if (ev10->data()[1] != 0) pass = false;
  if (ev10->data()[2] != 0xFF) pass = false;
  if (ev10->data()[3] != 6) pass = false;
  if (ev10->data()[4] != 3) pass = false;
  if (ev10->data()[5] != 'a') pass = false;
  if (ev10->data()[6] != 'b') pass = false;
  if (ev10->data()[7] != 'c') pass = false;
  delete ev10;
  displayAndReset(pass, fail, "EV10");

  //EV11: dt getter and setter test
  if (ev5.dt() != 512) pass = false;
  ev8.setdt(123456);
  if (ev8.dt() != 123456) pass = false;
  displayAndReset(pass, fail, "EV11");

  //-----TRACK TESTS-----//
  std::cout << std::endl << "--TRACK TESTS--" << std::endl;

  //TR01: EventTrack constructon, event addition, and data storage
  EventTrack et1;
  et1.add(ev1);
  if (et1.size() != 12) pass = false;
  if (et1.data()[0] != 'M') pass = false;
  if (et1.data()[1] != 'T') pass = false;
  if (et1.data()[2] != 'r') pass = false;
  if (et1.data()[3] != 'k') pass = false;
  if (et1.data()[4] != 0) pass = false;
  if (et1.data()[5] != 0) pass = false;
  if (et1.data()[6] != 0) pass = false;
  if (et1.data()[7] != 4) pass = false;
  if (et1.data()[8] != ev1.data()[0]) pass = false;
  if (et1.data()[9] != ev1.data()[1]) pass = false;
  if (et1.data()[10] != ev1.data()[2]) pass = false;
  if (et1.data()[11] != ev1.data()[3]) pass = false;
  displayAndReset(pass, fail, "TR01");

  //TR02: Clear test
  et1.clear();
  if (et1.size() != 8) pass = false;
  if (et1.data()[7] != 0) pass = false;
  displayAndReset(pass, fail, "TR02");

  //TR03: NoteTrack construction, addition
  NoteTrack nt1;
  NoteTime testNoteTime;
  testNoteTime.note = 20;
  testNoteTime.begin = 0;
  testNoteTime.duration = 1;
  nt1.add(10, 2, 1);
  nt1.add(testNoteTime);
  nt1.addAfterLastPress(11, 1, 1);
  if (nt1.note()[0].note != 10) pass = false;
  if (nt1.note()[0].begin != 2) pass = false;
  if (nt1.note()[0].duration != 1) pass = false;
  if (nt1.note()[1].note != 20) pass = false;
  if (nt1.note()[1].begin != 0) pass = false;
  if (nt1.note()[1].duration != 1) pass = false;
  if (nt1.note()[2].note != 11) pass = false;
  if (nt1.note()[2].begin != 3) pass = false;
  if (nt1.note()[2].duration != 1) pass = false;
  displayAndReset(pass, fail, "TR03");

  //TR04: NoteTrack clear test
  nt1.clear();
  if (nt1.note().size() != 0) pass = false;
  displayAndReset(pass, fail, "TR04");

  //TR05: NoteTrack -> EventTrack conversion
  NoteTrack nt2;
  nt2.add(10, 2, 3);
  std::vector<std::uint8_t> nt2data1 = nt2.data();
  std::vector<std::uint8_t> nt2data2 = nt2.toEvents().data();
  std::vector<std::uint8_t> nt2data3 = EventTrack(nt2).data();
  if (nt2data1.size() != nt2data2.size() ||
      nt2data2.size() != nt2data3.size() ||
      nt2data1.size() != nt2.size()) pass = false;
  if (nt2data1.size() != 31) pass = false;
  for (std::size_t i = 0; i < nt2data1.size(); i++)
    {
      if (nt2data1[i] != nt2data2[i] || nt2data2[i] != nt2data3[i]) pass = false;
    }
  if (nt2data1[7] != 23) pass = false;
  if (nt2data1[8] != 0) pass = false;
  if (nt2data1[9] != 0xFF) pass = false;
  if (nt2data1[10] != 88) pass = false;
  if (nt2data1[11] != 4) pass = false;
  if (nt2data1[12] != 4) pass = false;
  if (nt2data1[13] != 4) pass = false;
  if (nt2data1[14] != 24) pass = false;
  if (nt2data1[15] != 8) pass = false;
  if (nt2data1[16] != 0) pass = false;
  if (nt2data1[17] != 0xC0) pass = false;
  if (nt2data1[18] != 0) pass = false;
  if (nt2data1[19] != 2) pass = false;
  if (nt2data1[20] != 144) pass = false;
  if (nt2data1[21] != 10) pass = false;
  if (nt2data1[22] != 127) pass = false;
  if (nt2data1[23] != 3) pass = false;
  if (nt2data1[24] != 128) pass = false;
  if (nt2data1[25] != 10) pass = false;
  if (nt2data1[26] != 127) pass = false;
  if (nt2data1[27] != 0) pass = false;
  if (nt2data1[28] != 0xFF) pass = false;
  if (nt2data1[29] != 0x2F) pass = false;
  if (nt2data1[30] != 0) pass = false;
  displayAndReset(pass, fail, "TR05");

  //TR06: EventTrack -> NoteTrack conversion
  EventTrack et2 = nt2;
  et2.add(TextEvent("abc"));
  et2.add(NoteOnEvent(1, 0, 20, 127));
  et2.add(NoteOffEvent(1, 0, 20, 127));
  NoteTrack nt3 = et2;
  if (nt3.note().size() != 2) pass = false;
  if (nt3.note()[0].note != 10) pass = false;
  if (nt3.note()[0].begin != 2) pass = false;
  if (nt3.note()[0].duration != 3) pass = false;
  if (nt3.note()[1].note != 20) pass = false;
  if (nt3.note()[1].begin != 6) pass = false;
  if (nt3.note()[1].duration != 1) pass = false;
  displayAndReset(pass, fail, "TR06");

  //TR07: Clone test
  Track* et3 = et2.clone();
  if (et3->size() != et2.size()) pass = false;
  for (std::size_t i = 0; i < et3->size(); i++)
    {
      if (et2.data()[i] != et3->data()[i]) pass = false;
    }
  delete et3;
  et3 = nt3.clone();
  if (et3->size() != nt3.size()) pass = false;
  for (std::size_t i = 0; i < et3->size(); i++)
    {
      if (nt3.data()[i] != et3->data()[i]) pass = false;
    }
  delete et3;
  displayAndReset(pass, fail, "TR07");

  //-----MIDI TESTS-----//
  std::cout << std::endl << "--MIDI TESTS--" << std::endl;

  //MD01: Type 0 construction and header check
  //At this point, it's too much to check all the track data. Just check header.
  MIDI_Type0 md1(nt2, td1);
  if (md1.size() != nt2.size() + 14) pass = false;
  if (md1.data()[0] != 'M') pass = false;
  if (md1.data()[1] != 'T') pass = false;
  if (md1.data()[2] != 'h') pass = false;
  if (md1.data()[3] != 'd') pass = false;
  if (md1.data()[4] != 0) pass = false;
  if (md1.data()[5] != 0) pass = false;
  if (md1.data()[6] != 0) pass = false;
  if (md1.data()[7] != 6) pass = false;
  if (md1.data()[8] != 0) pass = false;
  if (md1.data()[9] != 0) pass = false;
  if (md1.data()[10] != 0) pass = false;
  if (md1.data()[11] != 1) pass = false;
  if (md1.data()[12] != td1.data()[0]) pass = false;
  if (md1.data()[13] != td1.data()[1]) pass = false;
  displayAndReset(pass, fail, "MD01");

  //MD02: Type 1 construction and header check
  MIDI_Type1 md2(td1);
  md2.addTrack(nt2);
  md2.addTrack(nt2);
  if (md2.size() != 2*nt2.size() + 14) pass = false;
  if (md2.data()[9] != 1) pass = false;
  if (md2.data()[11] != 2) pass = false;
  displayAndReset(pass, fail, "MD02");

  //MD02: Type 2 construction and header check
  MIDI_Type2 md3(td1);
  md3.addTrack(nt2);
  md3.addTrack(nt2);
  if (md3.size() != 2*nt2.size() + 14) pass = false;
  if (md3.data()[9] != 2) pass = false;
  if (md3.data()[11] != 2) pass = false;
  displayAndReset(pass, fail, "MD02");

  //MD03: Clear check
  md3.clear();
  if (md3.size() != 14) pass = false;
  displayAndReset(pass, fail, "MD03");

  //MD04: Write to file
  //Create a short, but noticable track
  EventTrack nt4;
  Instrument inst = Instrument::MUTED_TRUMPET;
  nt4.add(TimeSignatureEvent(0, 4, 4, 24, 8));
  nt4.add(ProgramChangeEvent(0, 0, inst));
  nt4.add(ProgramChangeEvent(0, 1, Instrument::HONKY_TONK_PIANO));
  nt4.add(NoteOnEvent(0, 0, 48, 127));
  nt4.add(NoteOnEvent(0, 1, 48, 127));
  nt4.add(NoteOffEvent(500, 0, 48, 127));
  nt4.add(NoteOffEvent(0, 1, 48, 127));
  nt4.add(NoteOnEvent(0, 0, 49, 127));
  nt4.add(NoteOnEvent(0, 1, 49, 127));
  nt4.add(NoteOffEvent(500, 0, 49, 127));
  nt4.add(NoteOffEvent(0, 1, 49, 127));
  nt4.add(NoteOnEvent(0, 0, 50, 127));
  nt4.add(NoteOnEvent(0, 1, 50, 127));
  nt4.add(NoteOffEvent(500, 0, 50, 127));
  nt4.add(NoteOffEvent(0, 1, 50, 127));
  nt4.add(NoteOnEvent(0, 0, 51, 127));
  nt4.add(NoteOnEvent(0, 1, 51, 127));
  nt4.add(NoteOffEvent(500, 0, 51, 127));
  nt4.add(NoteOffEvent(0, 1, 51, 127));
  nt4.add(NoteOnEvent(0, 0, 52, 127));
  nt4.add(NoteOnEvent(0, 1, 52, 127));
  nt4.add(NoteOffEvent(500, 0, 52, 127));
  nt4.add(NoteOffEvent(0, 1, 52, 127));
  nt4.add(NoteOnEvent(0, 0, 53, 127));
  nt4.add(NoteOnEvent(0, 1, 53, 127));
  nt4.add(NoteOffEvent(500, 0, 53, 127));
  nt4.add(NoteOffEvent(0, 1, 53, 127));
  nt4.add(NoteOnEvent(0, 0, 54, 127));
  nt4.add(NoteOnEvent(0, 1, 54, 127));
  nt4.add(NoteOffEvent(500, 0, 54, 127));
  nt4.add(NoteOffEvent(0, 1, 54, 127));
  nt4.add(EndOfTrackEvent(0));
  MIDI_Type0 md4(nt4, TimeDivision(26, 20));
  md4.write("test.mid");
  displayAndReset(pass, fail, "MD04");
  std::cout << "  Try playing test.mid!" << std::endl;

  //MD05: Write type 2 to file
  EventTrack nt5;
  nt5.add(TimeSignatureEvent(0, 4, 4, 24, 8));
  nt5.add(ProgramChangeEvent(0, 0, midi::Instrument::STRING_ENSEMBLE_1));
  nt5.add(NoteOnEvent(0, 0, 36, 127));
  nt5.add(NoteOffEvent(40000, 0, 36, 127));
  nt5.add(EndOfTrackEvent(0));
  MIDI_Type1 md5(TimeDivision(25,120));
  md5.addTrack(nt4);
  md5.addTrack(nt5);
  md5.write("test2.mid");
  displayAndReset(pass, fail, "MD05");
  std::cout << "  Try playing test2.mid!" << std::endl;

  //MD06: Write NoteTrack to file
  NoteTrack nt6;
  nt6.add("C5", 0, 5000);
  nt6.add("D5", 5000, 5000);
  nt6.add("E5", 10000, 5000);
  nt6.add("F5", 15000, 5000);
  nt6.add("G5", 20000, 5000);
  nt6.add("F5", 25000, 5000);
  nt6.add("E5", 30000, 5000);
  nt6.add("D5", 35000, 5000);
  nt6.add("C5", 40000, 20000);
  nt6.add("C4", 0, 50000);
  nt6.add("E4", 0, 50000);
  nt6.add("G4", 0, 50000);

  nt6.add("D5",  60000, 5000);
  nt6.add("E5",  65000, 5000);
  nt6.add("F#5", 70000, 5000);
  nt6.add("G5",  75000, 5000);
  nt6.add("A5",  80000, 5000);
  nt6.add("G5",  85000, 5000);
  nt6.add("F#5", 90000, 5000);
  nt6.add("E5",  95000, 5000);
  nt6.add("D5",  100000, 10000);
  nt6.add("D4",  60000, 50000);
  nt6.add("F#4", 60000, 50000);
  nt6.add("A4",  60000, 50000);

  MIDI_Type1 md6(TimeDivision(25,120));
  md6.addTrack(nt6);
  md6.write("test3.mid");
  displayAndReset(pass, fail, "MD06");
  std::cout << "  Try playing test3.mid!" << std::endl;

  //MD07: Multi-instrument NoteTrack
  NoteTrack nt7;
  nt7.add("C5", 0, 1000, Instrument::ACOUSTIC_GRAND_PIANO);
  nt7.add("D5", 1000, 1000, Instrument::XYLOPHONE);
  nt7.add("E5", 2000, 1000, Instrument::TUBA);
  nt7.add("F5", 3000, 1000, Instrument::ACOUSTIC_GRAND_PIANO);
  nt7.add("G5", 4000, 1000, Instrument::FLUTE);
  nt7.add("F5", 5000, 1000, Instrument::VIOLIN);
  nt7.add("E5", 6000, 1000, Instrument::FX_2);
  nt7.add("E5", 6500, 500, Instrument::FX_SOUNDTRACK);
  nt7.add("D5", 7000, 1000, Instrument::ALTO_SAX);
  nt7.add("D5", 7500, 500, Instrument::TENOR_SAX);
  nt7.add("C5", 8000, 2000, Instrument::ACOUSTIC_GRAND_PIANO);
  nt7.add("C5", 8500, 1500, Instrument::XYLOPHONE);
  nt7.add("C4", 0, 10000);
  nt7.add("E4", 0, 10000);
  nt7.add("G4", 0, 10000);

  MIDI_Type0 md7(nt7, TimeDivision(26, 20));
  md7.write("test4.mid");
  displayAndReset(pass, fail, "MD07");
  std::cout << "  Try playing test4.mid!" << std::endl;

  //-----SCALE TESTS-----//
  std::cout << std::endl << "--SCALE TESTS--" << std::endl;

  //SC01: C Major scale construction
  if (majorScale("C3",1) != "C3") pass = false;
  if (majorScale("C3",2) != "D3") pass = false;
  if (majorScale("C3",3) != "E3") pass = false;
  if (majorScale("C3",4) != "F3") pass = false;
  if (majorScale("C3",5) != "G3") pass = false;
  if (majorScale("C3",6) != "A3") pass = false;
  if (majorScale("C3",7) != "B3") pass = false;
  if (majorScale("C3",8) != "C4") pass = false;
  if (majorScale("C3",9) != "D4") pass = false;
  if (majorScale("C3",10) != "E4") pass = false;
  if (majorScale("C3",11) != "F4") pass = false;
  if (majorScale("C3",12) != "G4") pass = false;
  if (majorScale("C3",13) != "A4") pass = false;
  if (majorScale("C3",14) != "B4") pass = false;
  if (majorScale("C3",15) != "C5") pass = false;
  displayAndReset(pass, fail, "SC01");

  //SC02: Db Major scale construction
  if (majorScale("Db3",1) != "Db3") pass = false;
  if (majorScale("Db3",2) != "Eb3") pass = false;
  if (majorScale("Db3",3) != "F3") pass = false;
  if (majorScale("Db3",4) != "Gb3") pass = false;
  if (majorScale("Db3",5) != "Ab3") pass = false;
  if (majorScale("Db3",6) != "Bb3") pass = false;
  if (majorScale("Db3",7) != "C4") pass = false;
  if (majorScale("Db3",8) != "Db4") pass = false;
  displayAndReset(pass, fail, "SC02");

  //SC03: A Natural Minor scale construction
  if (natMinorScale("A3",1) != "A3") pass = false;
  if (natMinorScale("A3",2) != "B3") pass = false;
  if (natMinorScale("A3",3) != "C4") pass = false;
  if (natMinorScale("A3",4) != "D4") pass = false;
  if (natMinorScale("A3",5) != "E4") pass = false;
  if (natMinorScale("A3",6) != "F4") pass = false;
  if (natMinorScale("A3",7) != "G4") pass = false;
  if (natMinorScale("A3",8) != "A4") pass = false;
  displayAndReset(pass, fail, "SC03");

  //SC04: E Natural Minor scale construction
  if (natMinorScale("E3",1) != "E3") pass = false;
  if (natMinorScale("E3",2) != "Gb3") pass = false;
  if (natMinorScale("E3",3) != "G3") pass = false;
  if (natMinorScale("E3",4) != "A3") pass = false;
  if (natMinorScale("E3",5) != "B3") pass = false;
  if (natMinorScale("E3",6) != "C4") pass = false;
  if (natMinorScale("E3",7) != "D4") pass = false;
  if (natMinorScale("E3",8) != "E4") pass = false;
  displayAndReset(pass, fail, "SC04");

  //SC05: A Harmonic Minor scale construction
  if (harMinorScale("A3",1) != "A3") pass = false;
  if (harMinorScale("A3",2) != "B3") pass = false;
  if (harMinorScale("A3",3) != "C4") pass = false;
  if (harMinorScale("A3",4) != "D4") pass = false;
  if (harMinorScale("A3",5) != "E4") pass = false;
  if (harMinorScale("A3",6) != "F4") pass = false;
  if (harMinorScale("A3",7) != "G#4") pass = false;
  if (harMinorScale("A3",8) != "A4") pass = false;
  displayAndReset(pass, fail, "SC05");

  //-----CHORD TESTS-----//
  std::cout << std::endl << "--CHORD TESTS--" << std::endl;

  //CH01: C triad contruction
  if (!majTriad("C3").contains("C3")) pass = false;
  if (!majTriad("C3").contains("E3")) pass = false;
  if (!majTriad("C3").contains("G3")) pass = false;
  if (!minTriad("C3").contains("C3")) pass = false;
  if (!minTriad("C3").contains("Eb3")) pass = false;
  if (!minTriad("C3").contains("G3")) pass = false;
  if (!dimTriad("C3").contains("C3")) pass = false;
  if (!dimTriad("C3").contains("Eb3")) pass = false;
  if (!dimTriad("C3").contains("Gb3")) pass = false;
  if (!augTriad("C3").contains("C3")) pass = false;
  if (!augTriad("C3").contains("E3")) pass = false;
  if (!augTriad("C3").contains("G#3")) pass = false;
  displayAndReset(pass, fail, "CH01");

  //CH02: E triad construction
  if (!majTriad("E3").contains("E3")) pass = false;
  if (!majTriad("E3").contains("G#3")) pass = false;
  if (!majTriad("E3").contains("B3")) pass = false;
  if (!minTriad("E3").contains("E3")) pass = false;
  if (!minTriad("E3").contains("G3")) pass = false;
  if (!minTriad("E3").contains("B3")) pass = false;
  if (!dimTriad("E3").contains("E3")) pass = false;
  if (!dimTriad("E3").contains("G3")) pass = false;
  if (!dimTriad("E3").contains("Bb3")) pass = false;
  if (!augTriad("E3").contains("E3")) pass = false;
  if (!augTriad("E3").contains("G#3")) pass = false;
  if (!augTriad("E3").contains("B#3")) pass = false;
  displayAndReset(pass, fail, "CH02");

  //CH03: C sevenths construction
  if (!majSeventh("C3").contains("C3")) pass = false;
  if (!majSeventh("C3").contains("E3")) pass = false;
  if (!majSeventh("C3").contains("G3")) pass = false;
  if (!majSeventh("C3").contains("B3")) pass = false;
  if (!minSeventh("C3").contains("C3")) pass = false;
  if (!minSeventh("C3").contains("Eb3")) pass = false;
  if (!minSeventh("C3").contains("G3")) pass = false;
  if (!minSeventh("C3").contains("Bb3")) pass = false;
  if (!domSeventh("C3").contains("C3")) pass = false;
  if (!domSeventh("C3").contains("E3")) pass = false;
  if (!domSeventh("C3").contains("G3")) pass = false;
  if (!domSeventh("C3").contains("Bb3")) pass = false;
  if (!dimSeventh("C3").contains("C3")) pass = false;
  if (!dimSeventh("C3").contains("Eb3")) pass = false;
  if (!dimSeventh("C3").contains("Gb3")) pass = false;
  if (!dimSeventh("C3").contains("A3")) pass = false;
  if (!halfDimSeventh("C3").contains("C3")) pass = false;
  if (!halfDimSeventh("C3").contains("Eb3")) pass = false;
  if (!halfDimSeventh("C3").contains("Gb3")) pass = false;
  if (!halfDimSeventh("C3").contains("A#3")) pass = false;
  if (!minMajSeventh("C3").contains("C3")) pass = false;
  if (!minMajSeventh("C3").contains("Eb3")) pass = false;
  if (!minMajSeventh("C3").contains("G3")) pass = false;
  if (!minMajSeventh("C3").contains("B3")) pass = false;
  if (!augMajSeventh("C3").contains("C3")) pass = false;
  if (!augMajSeventh("C3").contains("E3")) pass = false;
  if (!augMajSeventh("C3").contains("G#3")) pass = false;
  if (!augMajSeventh("C3").contains("B3")) pass = false;
  displayAndReset(pass, fail, "CH03");
  
  //Print total results
  std::cout << std::endl << "---------------------------------" << std::endl;
  std::cout << "            RESULTS" << std::endl;
  std::cout << fail << " tests failed." << std::endl;
  if (fail == 0)
    {
      std::cout << "All is good!" << std::endl;
    }
  else
    {
      std::cout << "Go fix dem bugs!" << std::endl;
    }
}
