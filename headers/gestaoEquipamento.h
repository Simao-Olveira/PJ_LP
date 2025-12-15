/**
 * @file gestaoEquipamento.h
 * @brief Gestão de equipamentos (CRUD e Ficheiros).
 */

#ifndef GESTAOEQUIPAMENTO_H
#define GESTAOEQUIPAMENTO_H

#include "equipamento.h"

/** @brief Traduz o tipo de equipamento (enum) para uma string legível. */
void imprimirTipoEquipamento(TipoEquipamento tipo);

// --- Funções Principais ---

/** @brief Procura um equipamento pelo ID e devolve o índice (ou -1 caso não encontre). */
int procurarEquipamento(Equipamentos Equipamentos, int id);

/** @brief Adiciona um novo equipamento ao array dinâmico. */
void adicionarEquipamento(Equipamentos *Equipamentos);

/** @brief Liberta toda a memória alocada para os equipamentos. */
void libertarMemEquipamentos(Equipamentos *Equipamentos);

/** @brief Mostra os dados de um único equipamento. */
void imprimirEquipamento(Equipamento Equipamento);

/** @brief Lista todos os equipamentos registados. */
void listarEquipamentos(Equipamentos Equipamentos);

/** @brief Atualiza dados de um equipamento (função auxiliar). */
void atualizarDadosEquipamento(Equipamento *Equipamento);

/** @brief Menu interativo para editar um equipamento existente. */
void editarEquipamento(Equipamentos *Equipamentos);

/** @brief Remove um equipamento do sistema. */
void eliminarEquipamento(Equipamentos *Equipamentos);

// --- Persistência de Dados ---

/** @brief Carrega os dados do ficheiro binário. */
void carregarEquipamentos(Equipamentos *equipamentos);

/** @brief Guarda os dados no ficheiro binário. */
void guardarEquipamentos(Equipamentos *equipamentos);

#endif