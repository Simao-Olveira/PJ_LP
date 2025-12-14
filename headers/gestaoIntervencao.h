#ifndef GESTAO_INTERVENCAO_H
#define GESTAO_INTERVENCAO_H

#include "intervencao.h"
#include "ocorrencia.h"
#include "bombeiro.h"
#include "equipamento.h"

void imprimirEstadoIntervencao(EstadoIntervencao estado);

int procurarIntervencao(Intervencoes intervencoes, int id);
void adicionarIntervencao(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos);
void libertarMemIntervencoes(Intervencoes *intervencoes);
void imprimirIntervencao(Intervencao intervencao);
void listarIntervencoes(Intervencoes intervencoes);
void atualizarDadosIntervencao(Intervencao *intervencao);
void editarIntervencao(Intervencoes *intervencoes);
void eliminarIntervencao(Intervencoes *intervencoes);

// Funções de Ficheiros
void readIntervencoes(Intervencoes *intervencoes);
void writeIntervencoes(Intervencoes *intervencoes);
#endif
