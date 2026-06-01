CC=gcc
CFLAGS=-Wall -Wextra -std=c11
TARGET=pes

all:
	$(CC) $(CFLAGS) phase-00/src/main.c -lm -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)