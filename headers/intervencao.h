#ifndef INTERVENCAO_H
#define INTERVENCAO_H

#include "enums.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "ocorrencia.h"

typedef struct {
    int id;
    Ocorrencia *ocorrencia;

    Bombeiro *bombeiros;   // lista dinâmica
    int numBombeiros;

    Equipamento *equipamentos; // lista dinâmica
    int numEquipamentos;

    EstadoIntervencao estado;
} Intervencao;

void adicionarIntervencao(Intervencao **intervencoes, int *numIntervencoes);
void listarIntervencao(Intervencao **intervencoes, int *numIntervencoes);
void atualizarIntervencao(Intervencao *intervencoes, int numIntervencoes);
void removerIntervencao (Intervencao *intervencoes, int numIntervencoes);
void guardarIntervencoesEmFicheiros(Intervencao *intervencoes, int numIntervencoes);
void carregarIntervencoesDeFicheiros(Intervencoes **intervencoes, int *numIntervencoes);

#endif
