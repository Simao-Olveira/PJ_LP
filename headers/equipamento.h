#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include "enums.h"

typedef struct {
    int id;
    char *nome;
    EstadoEquipamento estado;
    TipoEquipamento tipo;
    int ativo; // 1 para ativo, 0 para inativo
} Equipamento;

typedef struct {
    Equipamento *equipamentos;  // Ponteiro para o array dinâmico
    int totalEquipamentos;      // Capacidade total alocada
    int numEquipamentos;        // Quantidade atual de bombeiros
} Equipamentos;

#endif
