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

typedef struct {
    Intervencao *intervencoes; // Ponteiro para o array dinâmico
    int totalIntervencoes;  // Capacidade total alocada
    int numIntervencoes;    // Quantidade atual de intervencoes
} Intervencoes;

#endif
