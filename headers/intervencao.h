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

typedef struct {
    Intervencao *intervencoes;  // Ponteiro para o array dinâmico
    int totalIntervencoes;      // Capacidade total alocada
    int numIntervencoes;        // Quantidade atual de intervenções
} Intervencoes;

#endif
