
#ifndef PJ_LP_EQUIPAMENTOGESTAO_H
#define PJ_LP_EQUIPAMENTOGESTAO_H

#include "equipamento.h"

int procurarEquipamento(Equipamentos equipamentos, int id);
void adicionarEquipamento(Equipamentos equipamentos);
void libertarMemEquipamentos(Equipamentosequipamentos);
void imprimirEquipamento(Equipamento equipamento);
void listarEquipamentos(Equipamentos equipamentos);
void atualizarDadosEquipamento(Equipamento equipamento);
void editarEquipamento(Equipamentosequipamentos);
void eliminarEquipamento(Equipamentos equipamentos);
void guardarEquipamentos(Equioamentos *equipamentos);
void carregarEquipamentos(Equipamentosequipamentos);

#endif //PJ_LP_EQUIPAMENTOGESTAO_H