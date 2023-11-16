CC = gcc
CXX = g++
CFLAGS = -Wall -Iinclude
LDFLAGS = -lavformat -lavcodec -lavutil -lswscale

SRCDIR = src
CPP_SOURCES = $(shell find $(SRCDIR) -name '*.cpp')
C_SOURCES = $(shell find $(SRCDIR) -name '*.c')
CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)
C_OBJECTS = $(C_SOURCES:.c=.o)
OBJECTS = $(CPP_OBJECTS) $(C_OBJECTS)
EXECUTABLE = playback

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(CPP_OBJECTS) $(C_OBJECTS) $(EXECUTABLE)

re: clean all

.PHONY: all run clean re
