CXXFLAGS = -g -Wall -std=c++11 aa
LDLIBS = -lGL \
-lglfw
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = sample


${TARGET} : ${OBJECTS}
${LINK.cc} $^ ${LOADLIBES} ${LDLIBS} -o $@

.PHONY : clean
clean :
    -${RM} ${TARGET} ${OBJECTS} *~ .*~ core
