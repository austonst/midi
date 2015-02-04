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

#include <stdint.h>

namespace midi
{

  typedef uint8_t Instrument;
  
  const uint8_t INST_ACOUSTIC_GRAND_PIANO = 1;
  const uint8_t INST_BRIGHT_ACOUSTIC_PIANO = 2;
  const uint8_t INST_ELECTRIC_GRAND_PIANO = 3;
  const uint8_t INST_HONKY_TONK_PIANO = 4;
  const uint8_t INST_ELECTRIC_PIANO_1 = 5;
  const uint8_t INST_ELECTRIC_PIANO_2 = 6;
  const uint8_t INST_HARPSICHORD = 7;
  const uint8_t INST_CLAVI = 8;
  const uint8_t INST_CELESTA = 9;
  const uint8_t INST_GLOCKENSPIEL = 10;
  const uint8_t INST_MUSIC_BOX = 11;
  const uint8_t INST_VIBRAPHONE = 12;
  const uint8_t INST_MARIMBA = 13;
  const uint8_t INST_XYLOPHONE = 14;
  const uint8_t INST_TUBULAR_BELLS = 15;
  const uint8_t INST_DULCIMER = 16;
  const uint8_t INST_DRAWBAR_ORGAN = 17;
  const uint8_t INST_PERCUSSIVE_ORGAN = 18;
  const uint8_t INST_ROCK_ORGAN = 19;
  const uint8_t INST_CHURCH_ORGAN = 20;
  const uint8_t INST_REED_ORGAN = 21;
  const uint8_t INST_ACCORDION = 22;
  const uint8_t INST_HARMONICA = 23;
  const uint8_t INST_TANGO_ACCORDION = 24;
  const uint8_t INST_ACOUSTIC_GUITAR_NYLON = 25;
  const uint8_t INST_ACOUSTIC_GUITAR_STEEL = 26;
  const uint8_t INST_ELECTRIC_GUITAR_JAZZ = 27;
  const uint8_t INST_ELECTRIC_GUITAR_CLEAN = 28;
  const uint8_t INST_ELECTRIC_GUITAR_MUTED = 29;
  const uint8_t INST_OVERDRIVEN_GUITAR = 30;
  const uint8_t INST_DISTORTION_GUITAR = 31;
  const uint8_t INST_GUITAR_HARMONICS = 32;
  const uint8_t INST_ACOUSTIC_BASS = 33;
  const uint8_t INST_ELECTRIC_BASS_FINGER = 34;
  const uint8_t INST_ELECTRIC_BASS_PICK = 35;
  const uint8_t INST_FRETLESS_BASS = 36;
  const uint8_t INST_SLAP_BASS_1 = 37;
  const uint8_t INST_SLAP_BASS_2 = 38;
  const uint8_t INST_SYNTH_BASS_1 = 39;
  const uint8_t INST_SYNTH_BASS_2 = 40;
  const uint8_t INST_VIOLIN = 41;
  const uint8_t INST_VIOLA = 42;
  const uint8_t INST_CELLO = 43;
  const uint8_t INST_CONTRABASS = 44;
  const uint8_t INST_TREMOLO_STRINGS = 45;
  const uint8_t INST_PIZZICATO_STRINGS = 46;
  const uint8_t INST_ORCHESTRAL_HARP = 47;
  const uint8_t INST_TIMPANI = 48;
  const uint8_t INST_STRING_ENSEMBLE_1 = 49;
  const uint8_t INST_STRING_ENSEMBLE_2 = 50;
  const uint8_t INST_SYNTHSTRINGS_1 = 51;
  const uint8_t INST_SYNTHSTRINGS_2 = 52;
  const uint8_t INST_CHOIR_AAHS = 53;
  const uint8_t INST_CHOIR_OOHS = 54;
  const uint8_t INST_SYNTH_VOICE = 55;
  const uint8_t INST_ORCHESTRA_HIT = 56;
  const uint8_t INST_TRUMPET = 57;
  const uint8_t INST_TROMBONE = 58;
  const uint8_t INST_TUBA = 59;
  const uint8_t INST_MUTED_TRUMPET = 60;
  const uint8_t INST_FRENCH_HORN = 61;
  const uint8_t INST_BRASS_SECTION = 62;
  const uint8_t INST_SYNTHBRASS_1 = 63;
  const uint8_t INST_SYNTHBRASS_2 = 64;
  const uint8_t INST_SOPRANO_SAX = 65;
  const uint8_t INST_ALTO_SAX = 66;
  const uint8_t INST_TENOR_SAX = 67;
  const uint8_t INST_BARITONE_SAX = 68;
  const uint8_t INST_OBOE = 69;
  const uint8_t INST_ENGLISH_HORN = 70;
  const uint8_t INST_BASSOON = 71;
  const uint8_t INST_CLARINET = 72;
  const uint8_t INST_PICCOLO = 73;
  const uint8_t INST_FLUTE = 74;
  const uint8_t INST_RECORDER = 75;
  const uint8_t INST_PAN_FLUTE = 76;
  const uint8_t INST_BLOWN_BOTTLE = 77;
  const uint8_t INST_SHAKUHACHI = 78;
  const uint8_t INST_WHISTLE = 79;
  const uint8_t INST_OCARINA = 80;
  const uint8_t INST_LEAD_1 = 81;
  const uint8_t INST_LEAD_SQUARE = 81;
  const uint8_t INST_LEAD_2 = 82;
  const uint8_t INST_LEAD_SAWTOOTH = 82;
  const uint8_t INST_LEAD_3 = 83;
  const uint8_t INST_LEAD_CALLIOPE = 83;
  const uint8_t INST_LEAD_4 = 84;
  const uint8_t INST_LEAD_CHIFF = 84;
  const uint8_t INST_LEAD_5 = 85;
  const uint8_t INST_LEAD_CHARANG = 85;
  const uint8_t INST_LEAD_6 = 86;
  const uint8_t INST_LEAD_VOICE = 86;
  const uint8_t INST_LEAD_7 = 87;
  const uint8_t INST_LEAD_FIFTHS = 87;
  const uint8_t INST_LEAD_8 = 88;
  const uint8_t INST_LEAD_BASS_LEAD = 88;
  const uint8_t INST_PAD_1 = 89;
  const uint8_t INST_PAD_NEW_AGE = 89;
  const uint8_t INST_PAD_2 = 90;
  const uint8_t INST_PAD_WARM = 90;
  const uint8_t INST_PAD_3 = 91;
  const uint8_t INST_PAD_POLYSYNTH = 91;
  const uint8_t INST_PAD_4 = 92;
  const uint8_t INST_PAD_CHOIR = 92;
  const uint8_t INST_PAD_5 = 93;
  const uint8_t INST_PAD_BOWED = 93;
  const uint8_t INST_PAD_6 = 94;
  const uint8_t INST_PAD_METALLIC = 94;
  const uint8_t INST_PAD_7 = 95;
  const uint8_t INST_PAD_HALO = 95;
  const uint8_t INST_PAD_8 = 96;
  const uint8_t INST_PAD_SWEEP = 96;
  const uint8_t INST_FX_1 = 97;
  const uint8_t INST_FX_RAIN = 97;
  const uint8_t INST_FX_2 = 98;
  const uint8_t INST_FX_SOUNDTRACK = 98;
  const uint8_t INST_FX_3 = 99;
  const uint8_t INST_FX_CRYSTAL = 99;
  const uint8_t INST_FX_4 = 100;
  const uint8_t INST_FX_ATMOSPHERE = 100;
  const uint8_t INST_FX_5 = 101;
  const uint8_t INST_FX_BRIGHTNESS = 101;
  const uint8_t INST_FX_6 = 102;
  const uint8_t INST_FX_GOBLINS = 102;
  const uint8_t INST_FX_7 = 103;
  const uint8_t INST_FX_ECHOES = 104;
  const uint8_t INST_FX_8 = 104;
  const uint8_t INST_FX_SCI_FI = 104;
  const uint8_t INST_SITAR = 105;
  const uint8_t INST_BANJO = 106;
  const uint8_t INST_SHAMISEN = 107;
  const uint8_t INST_KOTO = 108;
  const uint8_t INST_KALIMBA = 109;
  const uint8_t INST_BAG_PIPE = 110;
  const uint8_t INST_FIDDLE = 111;
  const uint8_t INST_SHANAI = 112;
  const uint8_t INST_TINKLE_BELL = 113;
  const uint8_t INST_AGOGO = 114;
  const uint8_t INST_STEEL_DRUMS = 115;
  const uint8_t INST_WOODBLOCK = 116;
  const uint8_t INST_TAIKO_DRUM = 117;
  const uint8_t INST_MELODIC_TOM = 118;
  const uint8_t INST_SYNTH_DRUM = 119;
  const uint8_t INST_REVERSE_CYMBAL = 120;
  const uint8_t INST_GUITAR_FRET_NOISE = 121;
  const uint8_t INST_BREATH_NOISE = 122;
  const uint8_t INST_SEASHORE = 123;
  const uint8_t INST_BIRD_TWEET = 124;
  const uint8_t INST_TELEPHONE_RING = 125;
  const uint8_t INST_HELICOPTER = 126;
  const uint8_t INST_APPLAUSE = 127;
  const uint8_t INST_GUNSHOT = 128;
  
} //Namespace

#endif
