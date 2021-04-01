# makefile for Project 1  - assignment2
# warning for unused-private-field is turned off

# generic makefile template:  change PROG to desired executable name
PROG = proj1

# source code files, edit to reflect actual files for program
SOURCES = proj1.cpp game.cpp player.cpp hand.cpp chickenYard.cpp field.cpp playedList.cpp freeList.cpp bone.cpp

# objects to be linked
OBJS = $(SOURCES:.cpp=.o)

# C++ compiler flags: get rid of -Wno-unused-private-field when all classes are finished
CC = g++
DEBUG = -g
CPPFLAGS = -m32 -std=c++14 -Wall -Wno-write-strings $(DEBUG)
LDFLAGS = -m32

default: 		$(PROG)

$(PROG): 		$(OBJS)
	$(CC) $(CPPFLAGS) -o $(PROG) $(OBJS)

proj1.o: 		game.h

game.o: 		game.h player.h chickenYard.h field.h freeList.h bone.h

player.o: 		player.h hand.h chickenYard.h

chickenYard.o:	chickenYard.h bone.h

field.o: 		field.h freeList.h playedList.h bone.h

playedList.o:	playedList.h bone.h chickenYard.h

hand.o: 		hand.h freeList.h bone.h

freeList.o:		freeList.h

bone.o: 		bone.h

# cleaning the directory
.PHONY: clean

clean:
	rm -f *.o $(PROG)
