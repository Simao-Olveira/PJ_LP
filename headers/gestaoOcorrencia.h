/**
 * @file gestao_ocorrencia.h
 * @brief Gestão de ocorrências (CRUD e Ficheiros).
 */

#ifndef GESTAOOCORRENCIA_H
#define GESTAOOCORRENCIA_H

#include "ocorrencia.h"

// --- Funções Principais ---

/** @brief Procura uma ocorrência pelo ID e devolve o índice (ou -1 caso não encontre). */
int procurarOcorrencia(Ocorrencias ocorrencias, int id);

/** @brief Regista uma nova ocorrência no sistema. */
void adicionarOcorrencia(Ocorrencias *ocorrencias);

/** @brief Liberta toda a memória alocada para as ocorrências. */
void libertarMemOcorrencias(Ocorrencias *ocorrencias);

/** @brief Mostra os detalhes de uma única ocorrência. */
void imprimirOcorrencia(Ocorrencia ocorrencia);

/** @brief Lista todas as ocorrências registadas. */
void listarOcorrencias(Ocorrencias ocorrencias);

/** @brief Atualiza dados de uma ocorrência (função auxiliar). */
void atualizarDadosOcorrencia(Ocorrencia *ocorrencia);

/** @brief Menu interativo para editar uma ocorrência. */
void editarOcorrencia(Ocorrencias *ocorrencias);

/** @brief Remove uma ocorrência do sistema. */
void eliminarOcorrencia(Ocorrencias *ocorrencias);

// --- Persistência de Dados ---

/** @brief Carrega os dados do ficheiro binário. */
void carregarOcorrencias(Ocorrencias *ocorrencias);

/** @brief Guarda os dados no ficheiro binário. */
void guardarOcorrencias(Ocorrencias *ocorrencias);

#endif