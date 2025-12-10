#ifndef GESTAOBOMBEIRO_H
#define GESTAOBOMBEIRO_H

#include "bombeiro.h"

int procurarBombeiro(Bombeiros bombeiros, int id);
void adicionarBombeiro(Bombeiros *bombeiros);
void libertarMemBombeiros(Bombeiros *bombeiros);
void imprimirBombeiro(Bombeiro bombeiro);
void listarBombeiros(Bombeiros bombeiros);
void atualizarDadosBombeiro(Bombeiro *bombeiro);
void editarBombeiro(Bombeiros *bombeiros);
void eliminarBombeiro(Bombeiros *bombeiros);
void readBombeiros(Bombeiros *bombeiros);
void writeBombeiros(Bombeiros *bombeiros);

#endif