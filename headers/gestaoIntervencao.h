/**
 * @file gestaoIntervencao.h
 * @brief Gestão de intervenções (CRUD e Ficheiros).
 */

#ifndef GESTAOINTERVENCAO_H
#define GESTAOINTERVENCAO_H

#include "intervencao.h"
#include "ocorrencia.h"
#include "bombeiro.h"
#include "equipamento.h"

/** @brief Traduz o estado da intervenção (enum) para uma string legível. */
void imprimirEstadoIntervencao(EstadoIntervencao estado);

// --- Funções Principais ---

/** @brief Procura uma intervenção pelo ID e devolve o índice (ou -1 caso não encontre). */
int procurarIntervencao(Intervencoes intervencoes, int id);

/** @brief Cria uma intervenção (usa 'Ocorrencias', 'Bombeiros' e 'Equipamentos' para associar recursos existentes). */
void adicionarIntervencao(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos);

/** @brief Liberta toda a memória alocada para as intervenções. */
void libertarMemIntervencoes(Intervencoes *intervencoes);

/** @brief Mostra os dados de uma única intervenção. */
void imprimirIntervencao(Intervencao intervencao);

/** @brief Lista todas as intervenções registadas. */
void listarIntervencoes(Intervencoes intervencoes);

/** @brief Atualiza dados (valida a existência de novos bombeiros, equipamentos ou ocorrências). */
void atualizarDadosIntervencao(Intervencao *intervencao, Bombeiros *bombeiros, Ocorrencias *ocorrencias, Equipamentos *equipamentos);

/** @brief Menu para editar uma intervenção (mantém a integridade com as outras entidades). */
void editarIntervencao(Intervencoes *intervencoes, Bombeiros *bombeiros, Ocorrencias *ocorrencias, Equipamentos *equipamentos);

/** @brief Remove uma intervenção do sistema. */
void eliminarIntervencao(Intervencoes *intervencoes);

// --- Persistência de Dados ---

/** @brief Carrega os dados do ficheiro binário. */
void carregarIntervencoes(Intervencoes *intervencoes);

/** @brief Guarda os dados no ficheiro binário. */
void guardarIntervencoes(Intervencoes *intervencoes);

#endif