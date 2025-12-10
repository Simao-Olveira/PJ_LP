#ifndef QUARTEL_H
#define QUARTEL_H

#include "enums.h"

typedef struct {
    int id;
    char nome[100];
    char local[100];
} Quartel;

typedef struct {
    Quartel *quarteis;  // Ponteiro para o array dinâmico
    int totalQuarteis;  // Capacidade total alocada
    int numQuarteis;    // Quantidade atual de bombeiros
} Quarteis;

#endif
