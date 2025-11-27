#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include "enums.h"

typedef struct {
    int id;
    char nome[100];
    EstadoEquipamento estado;
} Equipamento;

#endif
