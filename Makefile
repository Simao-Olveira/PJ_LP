CC = gcc
CFLAGS = -Wall -Wextra -g -I headers
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = programa

all: $(EXEC)
	@rm -f src/*.o
	@./$(EXEC)

$(EXEC): $(OBJ)
	@$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f src/*.o $(EXEC)