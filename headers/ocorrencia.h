#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "enums.h"

typedef struct {
    int id;
    char local[100];
    TipoOcorrencia tipo;
    Prioridade prioridade;
    EstadoOcorrencia estado;
    int ativo; // 1 para ativo, 0 para inativo
} Ocorrencia;

#endif
