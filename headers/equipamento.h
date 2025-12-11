#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include "enums.h"

typedef struct {
    int id;
    char nome[100];
    EstadoEquipamento estado;
} Equipamento;

typedef struct {
    Equipamento *equipamentos; // Ponteiro para o array dinâmico
    int totalEquipamentos;  // Capacidade total alocada
    int numEquipamentos;    // Quantidade atual de equipamentos
} Equipamentos;

#endif
