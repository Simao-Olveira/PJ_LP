#ifndef INTERVENCAO_H
#define INTERVENCAO_H

#include "input.h"
#include "enums.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "ocorrencia.h"

typedef struct {
    int id; //id da intervenção
    int idOcorrencia;        
    int *idsBombeiros;       
    int numBombeiros;
    int *idsEquipamentos;    
    int numEquipamentos;
    EstadoIntervencao estado;
    Data dataInicio;
    Hora horaInicio;
    Data dataFim;
    Hora horaFim;
} Intervencao;

typedef struct {
    Intervencao *intervencoes;  // Ponteiro para o array dinâmico
    int totalIntervencoes;      // Capacidade total alocada
    int numIntervencoes;        // Quantidade atual de intervenções
} Intervencoes;

#endif
