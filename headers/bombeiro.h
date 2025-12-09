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

typedef struct{
    int counter;
    int capacity;
    Bombeiro *bombeiros;
}Bombeiros;


void adicionarBombeiro(Bombeiro *bombeiros, int *numBombeiros);
void listarBombeiro(Bombeiro *bombeiros, int numBombeiros);
void atualizarBombeiro(Bombeiro *bombeiros, int numBombeiros);
void removerBombeiro (Bombeiro *bombeiros, int numBombeiros);

void salvarBombeirosEmFicheiros(Bombeiro *bombeiros, int numBombeiros);
void carregarBombeirosDeFicheiros(Bombeiro **bombeiros, int *numBombeiros);

#endif
