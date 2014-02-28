CC=clang
# sanitizer works, but c++11 does not https://trac.macports.org/ticket/41033
#CXX=g++-4.9
CXX=clang++
RM=rm -f
CPPFLAGS:=$(shell pkg-config --cflags sdl2)
LDFLAGS:=-g $(shell pkg-config --libs sdl2)

#-I$(CURDIR) would allow <utils/..> , but would override system headers. And OSX is case insenstive!
CPPFLAGS:=$(CPPFLAGS) -std=c++0x
LDFLAGS:=$(LDFLAGS)
LDLIBS:=-lSDL2_mixer -lSDL2_image $(LDLIBS) -ltinyxml -lz

#release
#CPPFLAGS=$(CPPFLAGS) -DNDEBUG -O3 -mssse3

#debug
CPPFLAGS:=$(CPPFLAGS) -g
#-fsanitize=address
LDFLAGS:=$(LDFLAGS) -g
#-fsanitize=address


SRCS=$(wildcard *.cpp) $(wildcard utils/*.cpp)
OBJS=$(subst .cpp,.o,$(SRCS))

all: SDL_test

SDL_test: $(OBJS)
	$(CXX) -o SDL_test $(OBJS) $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
