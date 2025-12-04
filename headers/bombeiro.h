#ifndef BOMBEIRO_H
#define BOMBEIRO_H

#include "enums.h"

typedef struct {
    int id;
    char nome[100];
    EspecialidadeBombeiro especialidade;
    EstadoBombeiro estado;
} Bombeiro;

void adicionarBombeiro(Bombeiro **bombeiros, int *numBombeiros);
void listarBombeiro(Bombeiro **bombeiros, int *numBombeiros);
void atualizarBombeiro(Bombeiro *bombeiros, int numBombeiros);
void removerBombeiro (Bombeiro *bombeiros, int numBombeiros);
void salvarBombeirosEmFicheiros(Bombeiro *bombeiros, int numBombeiros);
void carregarBombeirosDeFicheiros(Bombeiros **bombeiros, int *numBombeiros);

#endif
