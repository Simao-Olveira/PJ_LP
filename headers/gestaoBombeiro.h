/**
 * @file gestaobombeiro.h
 * @brief Gestão de bombeiros (CRUD e Ficheiros).
 */

#ifndef GESTAOBOMBEIRO_H
#define GESTAOBOMBEIRO_H

#include "bombeiro.h"
#include "quartel.h"

// --- Funções Principais ---

/** @brief Procura um bombeiro pelo ID e devolve o índice (ou -1 caso não encontre). */
int procurarBombeiro(Bombeiros bombeiros, int id);

/** @brief Cria um novo bombeiro (usa 'Quarteis' para validar se o ID do quartel existe). */
void adicionarBombeiro(Bombeiros *bombeiros, Quarteis *quarteis);

/** @brief Liberta toda a memória alocada para os bombeiros. */
void libertarMemBombeiros(Bombeiros *bombeiros);

/** @brief Mostra os dados de um único bombeiro. */
void imprimirBombeiro(Bombeiro bombeiro);

/** @brief Lista todos os bombeiros registados. */
void listarBombeiros(Bombeiros bombeiros);

/** @brief Atualiza dados de um bombeiro (usa 'Quarteis' para validar trocas de quartel). */
void atualizarDadosBombeiro(Bombeiro *bombeiro, Quarteis *quarteis);

/** @brief Menu para editar um bombeiro (usa 'Quarteis' para garantir consistência). */
void editarBombeiro(Bombeiros *bombeiros, Quarteis *quarteis);

/** @brief Remove um bombeiro do sistema. */
void eliminarBombeiro(Bombeiros *bombeiros);

// --- Persistência de Dados ---

/** @brief Carrega os dados do ficheiro binário. */
void carregarBombeiros(Bombeiros *bombeiros);

/** @brief Guarda os dados no ficheiro binário. */
void guardarBombeiros(Bombeiros *bombeiros);

#endif