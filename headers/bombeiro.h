#ifndef BOMBEIRO_H
#define BOMBEIRO_H

#include "enums.h"

typedef struct {
    int id;
    char nome[100];
    int idade;
    EspecialidadeBombeiro especialidade;
    EstadoBombeiro estado;
    int ativo;
} Bombeiro;

void criarBombeiro(Bombeiro **bombeiros, int *numBombeiros);

#endif
