#ifndef OCORRENCIA_H
#define OCORRENCIA_H
#include "input.h"

#include "enums.h"

typedef struct {
    int id;
    char *local;
    TipoOcorrencia tipo;
    Prioridade prioridade;
    EstadoOcorrencia estado;
    Data dataRegisto;
    Hora horaRegisto;
} Ocorrencia;

typedef struct {
    Ocorrencia *ocorrencias;
    int totalOcorrencias; 
    int numOcorrencias;
} Ocorrencias;

#endif
