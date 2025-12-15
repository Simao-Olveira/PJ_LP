#ifndef GESTAOBOMBEIRO_H
#define GESTAOBOMBEIRO_H

#include "bombeiro.h"
#include "quartel.h"

// --- Protótipos ---
int procurarBombeiro(Bombeiros bombeiros, int id);
void adicionarBombeiro(Bombeiros *bombeiros, Quarteis *quarteis);
void libertarMemBombeiros(Bombeiros *bombeiros);
void imprimirBombeiro(Bombeiro bombeiro);
void listarBombeiros(Bombeiros bombeiros);
void atualizarDadosBombeiro(Bombeiro *bombeiro, Quarteis *quarteis);
void editarBombeiro(Bombeiros *bombeiros, Quarteis *quarteis);
void eliminarBombeiro(Bombeiros *bombeiros);

// Funções de Ficheiros
void carregarBombeiros(Bombeiros *bombeiros);
void guardarBombeiros(Bombeiros *bombeiros);

#endif