# 1. Definições
CC = gcc
CFLAGS = -Wall -Wextra -I headers
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = programa

# 2. Regra Principal
all: $(EXEC)
	@rm -f src/*.o
	@./$(EXEC)

# 3. Linkagem
$(EXEC): $(OBJ)
	@$(CC) $(OBJ) -o $(EXEC)

# 4. Compilação
# O "@" no início esconde o comando "gcc -c ..." do terminal
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# 5. Limpeza
clean:
	@rm -f src/*.o $(EXEC)