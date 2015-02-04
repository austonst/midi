/*
  Copyright (c) 2014 Auston Sterling
  See LICENSE for copying permissions.
  
  -----Instruments Listing-----
  Auston Sterling
  austonst@gmail.com

  Contains constants to be used to easily set MIDI instruments.
  Uses General MIDI Level 1 Instrument Patches.
*/

#ifndef _instruments_hpp_
#define _instruments_hpp_

#include <cstdint>

namespace midi
{

  typedef std::uint8_t Instrument;
  
  const std::uint8_t INST_ACOUSTIC_GRAND_PIANO = 1;
  const std::uint8_t INST_BRIGHT_ACOUSTIC_PIANO = 2;
  const std::uint8_t INST_ELECTRIC_GRAND_PIANO = 3;
  const std::uint8_t INST_HONKY_TONK_PIANO = 4;
  const std::uint8_t INST_ELECTRIC_PIANO_1 = 5;
  const std::uint8_t INST_ELECTRIC_PIANO_2 = 6;
  const std::uint8_t INST_HARPSICHORD = 7;
  const std::uint8_t INST_CLAVI = 8;
  const std::uint8_t INST_CELESTA = 9;
  const std::uint8_t INST_GLOCKENSPIEL = 10;
  const std::uint8_t INST_MUSIC_BOX = 11;
  const std::uint8_t INST_VIBRAPHONE = 12;
  const std::uint8_t INST_MARIMBA = 13;
  const std::uint8_t INST_XYLOPHONE = 14;
  const std::uint8_t INST_TUBULAR_BELLS = 15;
  const std::uint8_t INST_DULCIMER = 16;
  const std::uint8_t INST_DRAWBAR_ORGAN = 17;
  const std::uint8_t INST_PERCUSSIVE_ORGAN = 18;
  const std::uint8_t INST_ROCK_ORGAN = 19;
  const std::uint8_t INST_CHURCH_ORGAN = 20;
  const std::uint8_t INST_REED_ORGAN = 21;
  const std::uint8_t INST_ACCORDION = 22;
  const std::uint8_t INST_HARMONICA = 23;
  const std::uint8_t INST_TANGO_ACCORDION = 24;
  const std::uint8_t INST_ACOUSTIC_GUITAR_NYLON = 25;
  const std::uint8_t INST_ACOUSTIC_GUITAR_STEEL = 26;
  const std::uint8_t INST_ELECTRIC_GUITAR_JAZZ = 27;
  const std::uint8_t INST_ELECTRIC_GUITAR_CLEAN = 28;
  const std::uint8_t INST_ELECTRIC_GUITAR_MUTED = 29;
  const std::uint8_t INST_OVERDRIVEN_GUITAR = 30;
  const std::uint8_t INST_DISTORTION_GUITAR = 31;
  const std::uint8_t INST_GUITAR_HARMONICS = 32;
  const std::uint8_t INST_ACOUSTIC_BASS = 33;
  const std::uint8_t INST_ELECTRIC_BASS_FINGER = 34;
  const std::uint8_t INST_ELECTRIC_BASS_PICK = 35;
  const std::uint8_t INST_FRETLESS_BASS = 36;
  const std::uint8_t INST_SLAP_BASS_1 = 37;
  const std::uint8_t INST_SLAP_BASS_2 = 38;
  const std::uint8_t INST_SYNTH_BASS_1 = 39;
  const std::uint8_t INST_SYNTH_BASS_2 = 40;
  const std::uint8_t INST_VIOLIN = 41;
  const std::uint8_t INST_VIOLA = 42;
  const std::uint8_t INST_CELLO = 43;
  const std::uint8_t INST_CONTRABASS = 44;
  const std::uint8_t INST_TREMOLO_STRINGS = 45;
  const std::uint8_t INST_PIZZICATO_STRINGS = 46;
  const std::uint8_t INST_ORCHESTRAL_HARP = 47;
  const std::uint8_t INST_TIMPANI = 48;
  const std::uint8_t INST_STRING_ENSEMBLE_1 = 49;
  const std::uint8_t INST_STRING_ENSEMBLE_2 = 50;
  const std::uint8_t INST_SYNTHSTRINGS_1 = 51;
  const std::uint8_t INST_SYNTHSTRINGS_2 = 52;
  const std::uint8_t INST_CHOIR_AAHS = 53;
  const std::uint8_t INST_CHOIR_OOHS = 54;
  const std::uint8_t INST_SYNTH_VOICE = 55;
  const std::uint8_t INST_ORCHESTRA_HIT = 56;
  const std::uint8_t INST_TRUMPET = 57;
  const std::uint8_t INST_TROMBONE = 58;
  const std::uint8_t INST_TUBA = 59;
  const std::uint8_t INST_MUTED_TRUMPET = 60;
  const std::uint8_t INST_FRENCH_HORN = 61;
  const std::uint8_t INST_BRASS_SECTION = 62;
  const std::uint8_t INST_SYNTHBRASS_1 = 63;
  const std::uint8_t INST_SYNTHBRASS_2 = 64;
  const std::uint8_t INST_SOPRANO_SAX = 65;
  const std::uint8_t INST_ALTO_SAX = 66;
  const std::uint8_t INST_TENOR_SAX = 67;
  const std::uint8_t INST_BARITONE_SAX = 68;
  const std::uint8_t INST_OBOE = 69;
  const std::uint8_t INST_ENGLISH_HORN = 70;
  const std::uint8_t INST_BASSOON = 71;
  const std::uint8_t INST_CLARINET = 72;
  const std::uint8_t INST_PICCOLO = 73;
  const std::uint8_t INST_FLUTE = 74;
  const std::uint8_t INST_RECORDER = 75;
  const std::uint8_t INST_PAN_FLUTE = 76;
  const std::uint8_t INST_BLOWN_BOTTLE = 77;
  const std::uint8_t INST_SHAKUHACHI = 78;
  const std::uint8_t INST_WHISTLE = 79;
  const std::uint8_t INST_OCARINA = 80;
  const std::uint8_t INST_LEAD_1 = 81;
  const std::uint8_t INST_LEAD_SQUARE = 81;
  const std::uint8_t INST_LEAD_2 = 82;
  const std::uint8_t INST_LEAD_SAWTOOTH = 82;
  const std::uint8_t INST_LEAD_3 = 83;
  const std::uint8_t INST_LEAD_CALLIOPE = 83;
  const std::uint8_t INST_LEAD_4 = 84;
  const std::uint8_t INST_LEAD_CHIFF = 84;
  const std::uint8_t INST_LEAD_5 = 85;
  const std::uint8_t INST_LEAD_CHARANG = 85;
  const std::uint8_t INST_LEAD_6 = 86;
  const std::uint8_t INST_LEAD_VOICE = 86;
  const std::uint8_t INST_LEAD_7 = 87;
  const std::uint8_t INST_LEAD_FIFTHS = 87;
  const std::uint8_t INST_LEAD_8 = 88;
  const std::uint8_t INST_LEAD_BASS_LEAD = 88;
  const std::uint8_t INST_PAD_1 = 89;
  const std::uint8_t INST_PAD_NEW_AGE = 89;
  const std::uint8_t INST_PAD_2 = 90;
  const std::uint8_t INST_PAD_WARM = 90;
  const std::uint8_t INST_PAD_3 = 91;
  const std::uint8_t INST_PAD_POLYSYNTH = 91;
  const std::uint8_t INST_PAD_4 = 92;
  const std::uint8_t INST_PAD_CHOIR = 92;
  const std::uint8_t INST_PAD_5 = 93;
  const std::uint8_t INST_PAD_BOWED = 93;
  const std::uint8_t INST_PAD_6 = 94;
  const std::uint8_t INST_PAD_METALLIC = 94;
  const std::uint8_t INST_PAD_7 = 95;
  const std::uint8_t INST_PAD_HALO = 95;
  const std::uint8_t INST_PAD_8 = 96;
  const std::uint8_t INST_PAD_SWEEP = 96;
  const std::uint8_t INST_FX_1 = 97;
  const std::uint8_t INST_FX_RAIN = 97;
  const std::uint8_t INST_FX_2 = 98;
  const std::uint8_t INST_FX_SOUNDTRACK = 98;
  const std::uint8_t INST_FX_3 = 99;
  const std::uint8_t INST_FX_CRYSTAL = 99;
  const std::uint8_t INST_FX_4 = 100;
  const std::uint8_t INST_FX_ATMOSPHERE = 100;
  const std::uint8_t INST_FX_5 = 101;
  const std::uint8_t INST_FX_BRIGHTNESS = 101;
  const std::uint8_t INST_FX_6 = 102;
  const std::uint8_t INST_FX_GOBLINS = 102;
  const std::uint8_t INST_FX_7 = 103;
  const std::uint8_t INST_FX_ECHOES = 104;
  const std::uint8_t INST_FX_8 = 104;
  const std::uint8_t INST_FX_SCI_FI = 104;
  const std::uint8_t INST_SITAR = 105;
  const std::uint8_t INST_BANJO = 106;
  const std::uint8_t INST_SHAMISEN = 107;
  const std::uint8_t INST_KOTO = 108;
  const std::uint8_t INST_KALIMBA = 109;
  const std::uint8_t INST_BAG_PIPE = 110;
  const std::uint8_t INST_FIDDLE = 111;
  const std::uint8_t INST_SHANAI = 112;
  const std::uint8_t INST_TINKLE_BELL = 113;
  const std::uint8_t INST_AGOGO = 114;
  const std::uint8_t INST_STEEL_DRUMS = 115;
  const std::uint8_t INST_WOODBLOCK = 116;
  const std::uint8_t INST_TAIKO_DRUM = 117;
  const std::uint8_t INST_MELODIC_TOM = 118;
  const std::uint8_t INST_SYNTH_DRUM = 119;
  const std::uint8_t INST_REVERSE_CYMBAL = 120;
  const std::uint8_t INST_GUITAR_FRET_NOISE = 121;
  const std::uint8_t INST_BREATH_NOISE = 122;
  const std::uint8_t INST_SEASHORE = 123;
  const std::uint8_t INST_BIRD_TWEET = 124;
  const std::uint8_t INST_TELEPHONE_RING = 125;
  const std::uint8_t INST_HELICOPTER = 126;
  const std::uint8_t INST_APPLAUSE = 127;
  const std::uint8_t INST_GUNSHOT = 128;
  
} //Namespace

#endif
