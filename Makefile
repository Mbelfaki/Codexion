CC = cc
TARGET = codexion
CFLAGS = -Werror -Wall -Wextra -pthread
SRC = src/main.c  src/parcing.c src/queue.c src/coder.c src/dongle.c src/monitoring.c src/tool.c src/thread.c src/free_data.c src/utiles.c src/heap.c src/check.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c src/codexion.h
	$(CC) $(CFLAGS) -c $< -o  $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f codexion

re: fclean all
