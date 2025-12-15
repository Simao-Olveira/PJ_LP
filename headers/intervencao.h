/**
 * @file intervencao.h
 * @brief Definição das estruturas de dados para a gestão de intervenções.
 *
 * Este ficheiro contém as estruturas que relacionam as ocorrências com os
 * recursos utilizados (bombeiros e equipamentos), registando os detalhes
 * operacionais e temporais de cada ação.
 */

#ifndef INTERVENCAO_H
#define INTERVENCAO_H

#include "input.h"
#include "enums.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "ocorrencia.h"

/**
 * @struct Intervencao
 * @brief Representa uma intervenção (ação operacional) numa ocorrência.
 *
 * Esta estrutura faz a ligação entre uma ocorrência e os recursos alocados
 * (bombeiros e equipamentos), registando também os tempos de início e fim.
 */
typedef struct {
    int id;               /**< Identificador único da intervenção */
    int idOcorrencia;     /**< Identificador da ocorrência à qual a intervenção se refere */
    int *idsBombeiros;    /**< Array dinâmico de IDs dos bombeiros alocados à intervenção */
    int numBombeiros;     /**< Quantidade de bombeiros atualmente alocados */
    int *idsEquipamentos; /**< Array dinâmico de IDs dos equipamentos utilizados */
    int numEquipamentos;  /**< Quantidade de equipamentos utilizados */
    EstadoIntervencao estado; /**< Estado atual da intervenção (ex: Em curso, Terminada) */
    Data dataInicio;      /**< Data de início da intervenção */
    Hora horaInicio;      /**< Hora de início da intervenção */
    Data dataFim;         /**< Data de conclusão da intervenção */
    Hora horaFim;         /**< Hora de conclusão da intervenção */
} Intervencao;

/**
 * @struct Intervencoes
 * @brief Estrutura de gestão para uma coleção de intervenções.
 *
 * Esta estrutura gere um array dinâmico de intervenções, controlando
 * a memória alocada e o número total de registos.
 */
typedef struct {
    Intervencao *intervencoes;  /**< Ponteiro para o array dinâmico de intervenções */
    int totalIntervencoes;      /**< Capacidade total (número máximo) de intervenções que a memória alocada suporta atualmente */
    int numIntervencoes;        /**< Número real de intervenções registadas no array */
} Intervencoes;

#endif