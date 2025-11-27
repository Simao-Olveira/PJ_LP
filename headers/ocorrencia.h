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

#endif
