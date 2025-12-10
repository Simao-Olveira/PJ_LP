#ifndef INTERVENCAO_H
#define INTERVENCAO_H

#include "enums.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "ocorrencia.h"

typedef struct {
    int id;
    Ocorrencia *ocorrencia;
    Bombeiro *bombeiros;  
    int numBombeiros;
    Equipamento *equipamentos;
    int numEquipamentos;
    EstadoIntervencao estado;
    int ativo; // 1 para ativo, 0 para inativo
} Intervencao;

void adicionarIntervencao(Intervencao **intervencoes, int *numIntervencoes);
void listarIntervencao(Intervencao **intervencoes, int *numIntervencoes);
void atualizarIntervencao(Intervencao *intervencoes, int numIntervencoes);
void removerIntervencao (Intervencao *intervencoes, int numIntervencoes);
void guardarIntervencoesEmFicheiros(Intervencao *intervencoes, int numIntervencoes);
void carregarIntervencoesDeFicheiros(Intervencao **intervencoes, int *numIntervencoes);

#endif
