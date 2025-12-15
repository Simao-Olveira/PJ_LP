/**
 * @file ocorrencia.h
 * @brief Definição das estruturas de dados para a gestão de ocorrências.
 *
 * Este ficheiro contém as estruturas que definem um incidente ou pedido de socorro,
 * bem como a estrutura de gestão para o array dinâmico de ocorrências.
 */

#ifndef OCORRENCIA_H
#define OCORRENCIA_H

#include "input.h"
#include "enums.h"

/**
 * @struct Ocorrencia
 * @brief Representa uma ocorrência (incidente) individual.
 *
 * Estrutura que armazena os detalhes fundamentais de um pedido de socorro,
 * incluindo localização, classificação e momento do registo.
 */
typedef struct {
    int id;                  /**< Identificador único da ocorrência */
    char *local;             /**< Localização da ocorrência (string dinâmica) */
    TipoOcorrencia tipo;     /**< Tipo de incidente (ex: Incêndio, Acidente, Saúde) */
    Prioridade prioridade;   /**< Nível de prioridade/urgência da ocorrência */
    EstadoOcorrencia estado; /**< Estado atual do processo (ex: Aberto, Em Curso, Fechado) */
    Data dataRegisto;        /**< Data em que a ocorrência foi registada no sistema */
    Hora horaRegisto;        /**< Hora em que a ocorrência foi registada */
} Ocorrencia;

/**
 * @struct Ocorrencias
 * @brief Estrutura de gestão para uma coleção de ocorrências.
 *
 * Esta estrutura gere um array dinâmico de ocorrências, controlando
 * a memória alocada e o número total de registos ativos.
 */
typedef struct {
    Ocorrencia *ocorrencias; /**< Ponteiro para o array dinâmico de ocorrências */
    int totalOcorrencias;    /**< Capacidade total (número máximo) de ocorrências que a memória alocada suporta atualmente */
    int numOcorrencias;      /**< Número real de ocorrências registadas no array */
} Ocorrencias;

#endif