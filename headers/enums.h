#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    FLORESTAL,
    URBANO,
    INDUSTRIAL
} TipoOcorrencia;

typedef enum {
    BAIXA,
    NORMAL,
    ALTA
} Prioridade;

typedef enum {
    OCORR_REPORTADA,
    OCORR_INTERVENCAO,
    OCORR_CONCLUIDA
} EstadoOcorrencia;

typedef enum {
    INT_PLANEAMENTO,
    INT_EXECUCAO,
    INT_CONCLUIDA
} EstadoIntervencao;

typedef enum {
    COMBATE_FLORESTAL,
    COMBATE_AEREO,
    RESGATE
} EspecialidadeBombeiro;
 
typedef enum {
    EB_DISPONIVEL,
    EB_INTERVENCAO,
    EB_TREINO
} EstadoBombeiro;

typedef enum {
    EQ_DISPONIVEL,
    EQ_EM_USO,
    EQ_MANUTENCAO
} EstadoEquipamento;

typedef enum {
    VESTUARIO,
    VEICULOS,
    FERRAMENTAS,
    COMUNICACAO
} TipoEquipamento;

typedef enum {
    VOLUNTARIO,
    SAPADOR,
    MUNICIPAL
} TipoQuartel;
#endif
