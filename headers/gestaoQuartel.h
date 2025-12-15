/**
 * @file gestaoQuartel.h
 * @brief Gestão de quartéis (CRUD e Ficheiros).
 */

#ifndef GESTAOQUARTEL_H
#define GESTAOQUARTEL_H

#include "quartel.h"

// --- Funções Principais ---

/** @brief Procura um quartel pelo ID e devolve o índice (ou -1 caso não encontre). */
int procurarQuartel(Quarteis quarteis, int id);

/** @brief Adiciona um novo quartel ao sistema. */
void adicionarQuartel(Quarteis *quarteis);

/** @brief Liberta toda a memória alocada para os quartéis. */
void libertarMemQuarteis(Quarteis *quarteis);

/** @brief Mostra os dados de um único quartel. */
void imprimirQuartel(Quartel quartel);

/** @brief Lista todos os quartéis registados. */
void listarQuarteis(Quarteis quarteis);

/** @brief Atualiza dados de um quartel (função auxiliar). */
void atualizarDadosQuartel(Quartel *quartel);

/** @brief Menu interativo para editar um quartel. */
void editarQuartel(Quarteis *quarteis);

/** @brief Remove um quartel do sistema. */
void eliminarQuartel(Quarteis *quarteis);

// --- Persistência de Dados ---

/** @brief Carrega os dados do ficheiro binário. */
void carregarQuarteis(Quarteis *quarteis);

/** @brief Guarda os dados no ficheiro binário. */
void guardarQuarteis(Quarteis *quarteis);

#endif