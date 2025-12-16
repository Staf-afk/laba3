CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = sort_program
SOURCES = main.c stack.c sort.c fileio.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = stack.h sort.h fileio.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) --file numbers.txt

.PHONY: all clean run test
