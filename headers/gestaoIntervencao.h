
#ifndef PJ_LP_INTERVENCAOGESTAO_H
#define PJ_LP_INTERVENCAOGESTAO_H

#include "intervencao.h"

void imprimirEstadoIntervencao(EstadoIntervencao estado);
int procurarIntervencao(Intervencoes intervencoes, int id);
void adicionarIntervencao(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos);
void libertarMemIntervencoes(Intervencoes *intervencoes);
void imprimirIntervencao(Intervencao intervencao);
void listarIntervencoes(Intervencoes intervencoes);
void atualizarDadosIntervencao(Intervencao *intervencao);
void editarIntervencao(Intervencoes *intervencoes);
void eliminarIntervencao(Intervencoes *intervencoes);
void carregarIntervencoes(Intervencoes *intervencoes);
void guardarIntervencoes(Intervencoes *intervencoes);

#endif //PJ_LP_INTERVENCAOGESTAO_H