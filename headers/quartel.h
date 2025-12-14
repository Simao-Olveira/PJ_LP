#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quartel.h"
#include "gestaoQuartel.h"
#include "enums.h"
#include "input.h"
#include "log.h

#ifndef QUARTEL_H
#define QUARTEL_H

#include "enums.h"

typedef struct {
    int id;
    char nome;
    charlocal;
    int capacidade;
    TipoQuartel tipo;
} Quartel;

typedef struct {
    Quartel *quarteis;  // Ponteiro para o array dinâmico
    int totalQuarteis;  // Capacidade total alocada
    int numQuarteis;    // Quantidade atual de bombeiros
} Quarteis;

#endif