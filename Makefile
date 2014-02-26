CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
#LDFLAGS=-g $(shell root-config --ldflags)
#LDLIBS=$(shell root-config --libs)
LDFLAGS=-g
LDLIBS=

SRCS=*.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: tool

SDL_test: $(OBJS)
	g++ $(LDFLAGS) -o SDL_test $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
