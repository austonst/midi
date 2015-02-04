#MIDI

This is a simple C++ MIDI editing library. The library is really (currently) at its best when used to create MIDI files from scratch. It does not itself offer a high level interface for complex operations or audio playback, but does have a few key features:

* Write a MIDI track in terms of Events represented as C++ objects.
* Write a MIDI track in terms of notes, times, and instruments.
* Support for a variety of chords, scales, and instruments.
* Encapsulation of various music and MIDI concepts into classes which can be easily used to create higher level programs

##Building
The only requirements for building are CMake >=2.8.8 and a compiler which supports C++11. I've only tested it using g++ 4.7-4.9 under 32 and 64 bit Linux, though I think it should be entirely cross-platform.

CMake should produce a library (static by default; set BUILD_SHARED_LIBS to build shared libraries instead) and a statically linked test suite *testmidi*. Running testmidi will test out the library components and create some midi files. Check the produced .mid files and make sure they play what sound like reasonable snippets of music.

##To-do
I mainly wrote this as a component of another project (procedural music generation), so I didn't really need some of the features you would expect from a general purpose MIDI library. So, there are many places where things could be improved. Some ideas:

* Add ability to load a MIDI file into a MIDI class.
* Add operations to better edit a MIDI (right now it's best to arrange the events yourself, then copy them over).
* Modify build system to allow building the library into .a or .so files, installing to the usual locations, or building the unit tests.

This is all under the MIT license, so feel free to play around with any components, or contribute to the library itself.