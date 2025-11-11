TARGET=program
CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC = main.c bitmap.c
ARGS =

$(TARGET): $(SRC)
	clear && $(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	clear && ./$(TARGET) $(ARGS)

clean:
	clear && rm -rf $(TARGET)