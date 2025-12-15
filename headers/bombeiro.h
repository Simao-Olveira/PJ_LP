/**
 * @file bombeiro.h
 * @brief Definição das estruturas de dados e tipos relativos aos bombeiros.
 *
 * Este ficheiro contém a definição da estrutura base de um bombeiro,
 * bem como a estrutura de gestão para arrays dinâmicos de bombeiros.
 */

#ifndef BOMBEIRO_H
#define BOMBEIRO_H

#include "enums.h"

/**
 * @struct Bombeiro
 * @brief Representa um bombeiro individual.
 *
 * Estrutura que armazena as informações pessoais e operacionais
 * de um único bombeiro.
 */
typedef struct {
    int id;                              /**< Identificador único do bombeiro */
    char *nome;                          /**< Nome completo do bombeiro */
    EspecialidadeBombeiro especialidade; /**< Especialidade técnica do bombeiro */
    EstadoBombeiro estado;               /**< Estado operacional atual (ex: Disponível, Ocupado) */
    int quartel;                         /**< Identificador do quartel ao qual o bombeiro está alocado */
} Bombeiro;

/**
 * @struct Bombeiros
 * @brief Estrutura de gestão para uma coleção de bombeiros.
 *
 * Esta estrutura é utilizada para gerir um array dinâmico de bombeiros,
 * mantendo o registo da memória alocada e do número de elementos.
 */
typedef struct {
    Bombeiro *bombeiros; /**< Ponteiro para o array dinâmico de bombeiros */
    int totalBombeiros;  /**< Capacidade total (número máximo) de bombeiros que a memória alocada suporta atualmente */
    int numBombeiros;    /**< Número real de bombeiros registados no array */
} Bombeiros;

#endif