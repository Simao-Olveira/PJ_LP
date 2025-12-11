#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "enums.h"

typedef struct {
    int id;
    char local[100];
    TipoOcorrencia tipo;
    Prioridade prioridade;
    EstadoOcorrencia estado;
} Ocorrencia;

typedef struct {
    Ocorrencia *ocorrencias; // Ponteiro para o array dinâmico
    int totalOcorrencias;  // Capacidade total alocada
    int numOcorrencias;    // Quantidade atual de ocorrencias
} Ocorrencias;

#endif
