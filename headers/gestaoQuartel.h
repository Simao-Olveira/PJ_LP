
#ifndef PJ_LP_QUARTELGESTAO_H
#define PJ_LP_QUARTELGESTAO_H

#include "quartel.h"

void imprimirTipoQuartel(TipoQuartel tipo);
int procurarQuartel(Quarteis quarteis, int id);
void adicionarQuartel(Quarteis *quarteis);
void libertarMemQuarteis(Quarteis *quarteis);
void imprimirQuartel(Quartel q);
void listarQuarteis(Quarteis quarteis);
void atualizarDadosQuartel(Quartel *quartel);
void editarQuartel(Quarteis *quarteis);
void eliminarQuartel(Quarteis *quarteis);
void carregarQuarteis(Quarteis *quarteis);
void guardarQuarteis(Quarteis *quarteis);

#endif //PJ_LP_QUARTELGESTAO_H