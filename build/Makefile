CC = gcc
CFLAGS = -Wall -Wextra -g
SOURCES = ../src/main.c  ../include/file_explorer.h ../src/file_explorer.c
EXECUTABLE = Artex

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $@ 

clean:
	rm -f $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

.PHONY: all clean run


