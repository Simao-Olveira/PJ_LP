#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "enums.h"

typedef struct {
    int id;
    char *local;
    TipoOcorrencia tipo;
    Prioridade prioridade;
    EstadoOcorrencia estado;
} Ocorrencia;

#endif
