#ifndef BOMBEIRO_H
#define BOMBEIRO_H

#include "enums.h"

typedef struct {
    int id;
    char nome[100];
    EspecialidadeBombeiro especialidade;
    EstadoBombeiro estado;
    int ativo; // 1 para ativo, 0 para inativo
} Bombeiro;

#endif
