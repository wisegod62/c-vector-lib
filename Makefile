CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror -fsanitize=address -g -fno-omit-frame-pointer

TARGET = vector_tests

OBJS = main.o vector.o

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

test: $(TARGET)
	./$(TARGET)

main.o: main.c vector.h
	$(CC) $(CFLAGS) -c main.c

vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c

clean:
	rm -f $(OBJS) $(TARGET)

