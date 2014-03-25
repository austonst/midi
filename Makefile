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

midi.o: midi.cpp midi.h track.o timedivision.o
	$(CC) midi.cpp $(CFLAGS)

track.o: track.cpp track.h event.o note.o
	$(CC) track.cpp $(CFLAGS)

timedivision.o: timedivision.cpp timedivision.h
	$(CC) timedivision.cpp $(CFLAGS)

event.o: event.cpp event.h varlength.o instruments.h
	$(CC) event.cpp $(CFLAGS)

note.o: note.cpp note.h
	$(CC) note.cpp $(CFLAGS)

varlength.o: varlength.cpp varlength.h
	$(CC) varlength.cpp $(CFLAGS)

scales.o: scales.cpp scales.h note.o
	$(CC) scales.cpp $(CFLAGS)

chords.o: chords.cpp chords.h note.o
	$(CC) chords.cpp $(CFLAGS)

clean:
	rm -v *.o *.mid testmidi
