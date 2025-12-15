/**
 * @file enums.h
 * @brief Definição de todas as enumerações utilizadas no sistema.
 *
 * Este ficheiro contém os tipos enumerados que categorizam ocorrências,
 * estados, prioridades, especialidades e tipos de equipamentos/quartéis.
 */

#ifndef ENUMS_H
#define ENUMS_H

/**
 * @enum TipoOcorrencia
 * @brief Define a tipologia da ocorrência ou incêndio.
 */
typedef enum {
    FLORESTAL,  
    URBANO,     
    INDUSTRIAL  
} TipoOcorrencia;

/**
 * @enum Prioridade
 * @brief Níveis de urgência para classificação de ocorrências.
 */
typedef enum {
    BAIXA,  
    NORMAL, 
    ALTA    
} Prioridade;

/**
 * @enum EstadoOcorrencia
 * @brief Ciclo de vida administrativo de uma ocorrência.
 */
typedef enum {
    OCORR_REPORTADA,  
    OCORR_INTERVENCAO, 
    OCORR_CONCLUIDA   
} EstadoOcorrencia;

/**
 * @enum EstadoIntervencao
 * @brief Fases operacionais de uma intervenção específica.
 */
typedef enum {
    INT_PLANEAMENTO,
    INT_EXECUCAO,    
    INT_CONCLUIDA   
} EstadoIntervencao;

/**
 * @enum EspecialidadeBombeiro
 * @brief Áreas de especialização técnica dos bombeiros.
 */
typedef enum {
    COMBATE_FLORESTAL, 
    COMBATE_AEREO,     
    RESGATE           
} EspecialidadeBombeiro;

/**
 * @enum EstadoBombeiro
 * @brief Situação atual de disponibilidade do bombeiro.
 */
typedef enum {
    EB_DISPONIVEL,  
    EB_INTERVENCAO, 
    EB_TREINO       
} EstadoBombeiro;

/**
 * @enum EstadoEquipamento
 * @brief Condição de funcionamento e alocação de equipamentos.
 */
typedef enum {
    EQ_DISPONIVEL,
    EQ_EM_USO,    
    EQ_MANUTENCAO 
} EstadoEquipamento;

/**
 * @enum TipoEquipamento
 * @brief Categorização dos recursos materiais.
 */
typedef enum {
    VESTUARIO, 
    VEICULOS, 
    FERRAMENTAS,
    COMUNICACAO  
} TipoEquipamento;

/**
 * @enum TipoQuartel
 * @brief Classificação da entidade detentora do quartel.
 */
typedef enum {
    VOLUNTARIO, 
    SAPADOR,    
    MUNICIPAL 
} TipoQuartel;

#endif