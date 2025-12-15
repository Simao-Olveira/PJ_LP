/**
 * @file quartel.h
 * @brief Definição das estruturas de dados relativas aos quartéis.
 *
 * Este ficheiro contém a definição da estrutura base de um quartel,
 * bem como a estrutura de gestão para arrays dinâmicos de quartéis.
 */

#ifndef QUARTEL_H
#define QUARTEL_H

#include "enums.h"

/**
 * @struct Quartel
 * @brief Representa um quartel (unidade estrutural) individual.
 *
 * Estrutura que armazena as informações de identificação, localização
 * e capacidade operacional de um quartel.
 */
typedef struct {
    int id;             /**< Identificador único do quartel */
    char *nome;         /**< Nome do quartel (string dinâmica) */
    char *local;        /**< Localização geográfica ou morada do quartel */
    int capacidade;     /**< Capacidade máxima de recursos/operacionais que o quartel suporta */
    TipoQuartel tipo;   /**< Classificação do quartel (ex: Sede, Posto Avançado) */
} Quartel;

/**
 * @struct Quarteis
 * @brief Estrutura de gestão para uma coleção de quartéis.
 *
 * Esta estrutura é utilizada para gerir um array dinâmico de quartéis,
 * mantendo o registo da memória alocada e do número de elementos.
 */
typedef struct {
    Quartel *quarteis;  /**< Ponteiro para o array dinâmico de quartéis */
    int totalQuarteis;  /**< Capacidade total (número máximo) de quartéis que a memória alocada suporta atualmente */
    int numQuarteis;    /**< Número real de quartéis registados no array */
} Quarteis;

#endif