#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define VALOR_INVALIDO "O valor inserido é invalido"
#define MAX_INT 2147483647
#define SIZE_BUFFER 100
#define CODE 3500

void cleanInputBuffer();

int obterInteiro(int minValor, int maxValor, char *msg);

void lerString(char *string, unsigned int tamanho, char *msg);

#endif
