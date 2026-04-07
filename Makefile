CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = program
SRC = main.c  parcing.c queue.c coder.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c *h
	$(CC) $(CFLAGS) -c $< -o  $@

run:
	./program 2  1 1  1000  100 1 1000  fifo
clean:
	rm -f  *.o