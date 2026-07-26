CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
TARGET = test
SRC = $(wildcard src/*.c)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	sudo ./$(TARGET)

clean:
	rm -f $(TARGET)
