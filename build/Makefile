CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf 
SOURCES = ../src/main.c  ../include/file_explorer.h ../src/file_explorer.c
EXECUTABLE = Artex

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run


