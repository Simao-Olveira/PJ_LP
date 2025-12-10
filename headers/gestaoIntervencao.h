#ifndef GESTAO_INTERVENCAO_H
#define GESTAO_INTERVENCAO_H

#include "intervencao.h"    

void adicionarIntervencao(Intervencao **intervencoes, int *numIntervencoes);
void listarIntervencao(Intervencao **intervencoes, int *numIntervencoes);
void atualizarIntervencao(Intervencao *intervencoes, int numIntervencoes);
void removerIntervencao (Intervencao *intervencoes, int numIntervencoes);
void guardarIntervencoesEmFicheiros(Intervencao *intervencoes, int numIntervencoes);
void carregarIntervencoesDeFicheiros(Intervencao **intervencoes, int *numIntervencoes);

#endif
