#ifndef GESTAO_EQUIPAMENTO_H
#define GESTAO_EQUIPAMENTO_H

#include "equipamento.h"

void imprimirTipoEquipamento(TipoEquipamento tipo);

// --- Protótipos ---
int procurarEquipamento(Equipamentos Equipamentos, int id);
void adicionarEquipamento(Equipamentos *Equipamentos);
void libertarMemEquipamentos(Equipamentos *Equipamentos);
void imprimirEquipamento(Equipamento Equipamento);
void listarEquipamentos(Equipamentos Equipamentos);
void atualizarDadosEquipamento(Equipamento *Equipamento);
void editarEquipamento(Equipamentos *Equipamentos);
void eliminarEquipamento(Equipamentos *Equipamentos);

// Funções de Ficheiros
void readEquipamentos(Equipamentos *equipamentos);
void writeEquipamentos(Equipamentos *equipamentos);

#endif
