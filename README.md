#MIDI

This is a simple C++ MIDI editing library. The library is really (currently) at its best when used to create MIDI files from scratch. It does not itself offer a high level interface for complex operations or audio playback, but does have a few key features:

* Write a MIDI track in terms of Events represented as C++ objects.
* Write a MIDI track in terms of notes, times, and instruments.
* Support for a variety of chords, scales, and instruments.
* Encapsulation of various music and MIDI concepts into classes which can be easily used to create higher level programs

##Building
There are no dependencies, save for a recently up-to-date C++ compiler. I've only tested it using g++ 4.7-4.8 under 32 bit Linux, though I think it should be entirely cross-platform.

The build system for this library is still very primitive (hand-written Linux Makefile). Currently, assuming you have *make* and *g++*, you should be able to build and run the unit tests with:
```bash
make
./testmidi
```
Then check the produced .mid files and make sure they play what sound like reasonable snippets of music.

##To-do
I mainly wrote this as a component of another project (procedural music generation), so I didn't really need some of the features you would expect from a general purpose MIDI library. So, there are many places where things could be improved. Some ideas:

* Add ability to load a MIDI file into a MIDI class.
* Add operations to better edit a MIDI (right now it's best to arrange the events yourself, then copy them over).
* Modify build system to allow building the library into .a or .so files, installing to the usual locations, or building the unit tests.

This is all under the MIT license, so feel free to play around with any components, or contribute to the library itself.