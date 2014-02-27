CC=clang
# sanitizer works, but c++11 does not https://trac.macports.org/ticket/41033
#CXX=/usr/local/bin/g++-4.9
CXX=clang++
RM=rm -f
#CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)
CPPFLAGS=-g -I/usr/local/include/SDL2 -std=c++0x
LDFLAGS=-g
LDLIBS=-lSDL2_mixer -lSDL2_image -lSDL2 -ltinyxml -lz

#release
#CPPFLAGS=$(CPPFLAGS) -DNDEBUG -O3 -mssse3

#debug
CPPFLAGS:=$(CPPFLAGS)
#-fsanitize=address
LDFLAGS:=$(LDFLAGS)
#-fsanitize=address

SRCS=$(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: SDL_test

SDL_test: $(OBJS)
	$(CXX) $(LDFLAGS) -o SDL_test $(OBJS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -c $<

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
