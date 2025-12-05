#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include "enums.h"

typedef struct {
    int id;
    char nome[100];
    EstadoEquipamento estado;
} Equipamento;

void adicionarEquipamento(Equipamento **equipamentos, int *numEquipamentos);
void listarEquipamento(Equipamento **equipamentos, int *numEquipamentos);
void atualizarEquipamento(Equipamento *equipamentos, int numEquipamentos);
void removerEquipamento (Equipamento *equipamentos, int numEquipamentos);
void guardarEquipamentosEmFicheiros(Equipamento *equipamentos, int numEquipamentos);
void carregarEquipamentosDeFicheiros(Equipamentos **equipamentos, int *numEquipamentos);

#endif
