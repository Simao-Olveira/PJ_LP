#ifndef BOMBEIRO_H
#define BOMBEIRO_H
#include "enums.h"

typedef struct {
    int id;
    char *nome;
    EspecialidadeBombeiro especialidade;
    EstadoBombeiro estado;
} Bombeiro;

typedef struct {
    Bombeiro *bombeiros; // Ponteiro para o array dinâmico
    int totalBombeiros;  // Capacidade total alocada
    int numBombeiros;    // Quantidade atual de bombeiros
} Bombeiros;

#endif