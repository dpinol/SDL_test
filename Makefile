CC=clang
# sanitizer works, but c++11 does not https://trac.macports.org/ticket/41033
#CXX=g++-4.9
CXX=clang++
RM=rm -f
CPPFLAGS:=$(shell /usr/local/bin/pkg-config --cflags sdl2)
LDFLAGS:=-g $(shell /usr/local/bin/pkg-config --libs sdl2)

CPPFLAGS:=$(CPPFLAGS) -Wall -Wextra -Wno-ignored-qualifiers -Wno-sign-compare -Wno-reorder
CPPFLAGS:=$(CPPFLAGS) -Werror=address -Werror=array-bounds  -Werror=c++0x-compat -Werror=char-subscripts
CPPFLAGS:=$(CPPFLAGS) -Werror=enum-compare -Werror=implicit-int -Werror=implicit-function-declaration -Werror=comment -Werror=conversion-null -Werror=div-by-zero
CPPFLAGS:=$(CPPFLAGS) -Werror=format -Werror=format-security -Werror=format-extra-args -Werror=init-self  -Werror=int-to-pointer-cast -Werror=missing-braces  -Werror=missing-field-initializers -Werror=return-type -Werror=nonnull
CPPFLAGS:=$(CPPFLAGS) -Werror=overloaded-virtual
CPPFLAGS:=$(CPPFLAGS) -Werror=parentheses -Werror=pointer-arith -Werror=pointer-sign  -Werror=return-type -Werror=sequence-point -Werror=strict-overflow=1
CPPFLAGS:=$(CPPFLAGS) -Werror=trigraphs -Werror=type-limits -Werror=unused-value -Werror=volatile-register-var -fdiagnostics-show-option
CPPFLAGS:=$(CPPFLAGS) -Werror=overflow -Werror=uninitialized
CPPFLAGS:=$(CPPFLAGS) -Wshadow
ifeq ($(CXX),clang++)
  CPPFLAGS:=$(CPPFLAGS) -Wno-constant-logical-operand -Werror=string-plus-int
endif



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
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

%.o: %.cpp
	@echo "compiling $<"
	@$(CXX) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend
