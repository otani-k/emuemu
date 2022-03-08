CC = g++
CFLAGS = -Wall
TARGET = emu
SRCS = parse/parse.cpp
SRCS += ppu/ppu.cpp
SRCS += main.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

all: clean $(OBJS) $(TARGET)

clean:
	-rm -f $(OBJS) $(TARGET) *.d

