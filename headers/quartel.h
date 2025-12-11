#ifndef QUARTEL_H
#define QUARTEL_H

#include "enums.h"

typedef struct {
    int id;
    char *nome;
    char *local;
    int capacidade;
    TipoQuartel tipo;
} Quartel;

typedef struct {
    Quartel *quarteis;  // Ponteiro para o array dinâmico
    int totalQuarteis;  // Capacidade total alocada
    int numQuarteis;    // Quantidade atual de bombeiros
} Quarteis;

#endif
