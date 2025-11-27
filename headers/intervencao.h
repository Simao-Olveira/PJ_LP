#ifndef INTERVENCAO_H
#define INTERVENCAO_H

#include "enums.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "ocorrencia.h"

typedef struct {
    int id;
    Ocorrencia *ocorrencia;

    Bombeiro *bombeiros;   // lista dinâmica
    int numBombeiros;

    Equipamento *equipamentos; // lista dinâmica
    int numEquipamentos;

    EstadoIntervencao estado;
} Intervencao;

#endif
