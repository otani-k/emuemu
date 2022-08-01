FILES := parse/parse.cpp ppu/ppu.cpp main.cpp
CXXFLAGS = -Wall -std=c++11 
LDLIBS = -lGL \
        -lglfw
OBJECTS = $(patsubst %.cpp,%.o,$(FILES))
TARGET = emu


${TARGET} : ${OBJECTS}
	${LINK.cc} $^ ${LOADLIBES} ${LDLIBS} -o $@

.PHONY : clean
clean :
	-${RM} ${TARGET} ${OBJECTS} *~ .*~ core


