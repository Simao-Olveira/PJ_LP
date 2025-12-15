/**
 * @file equipamento.h
 * @brief Definição das estruturas de dados e tipos relativos aos equipamentos.
 *
 * Este ficheiro contém a definição da estrutura base de um equipamento,
 * bem como a estrutura de gestão para arrays dinâmicos de equipamentos.
 */

#ifndef EQUIPAMENTO_H
#define EQUIPAMENTO_H

#include "enums.h"

/**
 * @struct Equipamento
 * @brief Representa um equipamento individual.
 *
 * Estrutura que armazena as informações de identificação e estado
 * de um único item de equipamento.
 */
typedef struct {
    int id;                   /**< Identificador único do equipamento */
    char *nome;               /**< Nome do equipamento */
    EstadoEquipamento estado; /**< Estado atual do equipamento (ex: Disponível, Avariado) */
    TipoEquipamento tipo;     /**< Tipo ou categoria do equipamento (ex: EPI, Veículo) */
} Equipamento;

/**
 * @struct Equipamentos
 * @brief Estrutura de gestão para uma coleção de equipamentos.
 *
 * Esta estrutura é utilizada para gerir um array dinâmico de equipamentos,
 * mantendo o registo da memória alocada e do número de elementos.
 */
typedef struct {
    Equipamento *equipamentos; /**< Ponteiro para o array dinâmico de equipamentos */
    int totalEquipamentos;     /**< Capacidade total (número máximo) de equipamentos que a memória alocada suporta atualmente */
    int numEquipamentos;       /**< Número real de equipamentos registados no array */
} Equipamentos;

#endif