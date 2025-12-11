#ifndef GESTAOQUARTEL_H
#define GESTAOQUARTEL_H

#include "quartel.h"

// --- Protótipos ---
int procurarQuartel(Quarteis quarteis, int id);
void adicionarQuartel(Quarteis *quarteis);
void libertarMemQuarteis(Quarteis *quarteis);
void imprimirQuartel(Quartel quartel);
void listarQuarteis(Quarteis quarteis);
void atualizarDadosQuartel(Quartel *quartel);
void editarQuartel(Quarteis *quarteis);
void eliminarQuartel(Quarteis *quarteis);

// Funções de Ficheiros
void readQuarteis(Quarteis *quarteis);
void writeQuarteis(Quarteis *quarteis);

#endif