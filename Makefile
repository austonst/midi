# Copyright (c) 2014 Auston Sterling
# See LICENSE for copying permission.

CC = g++ -g
CFLAGS = -Wall -Wextra -c
LFLAGS =

TESTMIDI_OBJ = testmidi.o midi.o track.o timedivision.o varlength.o event.o note.o scales.o chords.o

test: testmidi

testmidi: $(TESTMIDI_OBJ)
	$(CC) $(TESTMIDI_OBJ) $(LFLAGS) -o testmidi

testmidi.o: testmidi.cpp midi.o
	$(CC) testmidi.cpp $(CFLAGS)

midi.o: midi.cpp midi.hpp track.o timedivision.o
	$(CC) midi.cpp $(CFLAGS)

track.o: track.cpp track.hpp event.o note.o
	$(CC) track.cpp $(CFLAGS)

timedivision.o: timedivision.cpp timedivision.hpp
	$(CC) timedivision.cpp $(CFLAGS)

event.o: event.cpp event.hpp varlength.o instruments.hpp
	$(CC) event.cpp $(CFLAGS)

note.o: note.cpp note.hpp
	$(CC) note.cpp $(CFLAGS)

varlength.o: varlength.cpp varlength.hpp
	$(CC) varlength.cpp $(CFLAGS)

scales.o: scales.cpp scales.hpp note.o
	$(CC) scales.cpp $(CFLAGS)

chords.o: chords.cpp chords.hpp note.o
	$(CC) chords.cpp $(CFLAGS)

clean:
	rm -v *.o *.mid testmidi
