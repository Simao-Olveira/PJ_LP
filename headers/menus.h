#ifndef MENU_H
#define MENU_H

#include "bombeiro.h"
#include "ocorrencia.h"
#include "intervencao.h"
#include "equipamento.h"
#include "quartel.h"

void menuPrincipal(Bombeiro *bombeiros, int *numBombeiros, Ocorrencia *ocorrencias, int *numOcorrencias,
                    Intervencao *intervencoes, int *numIntervencoes,
                    Equipamento *equipamentos, int *numEquipamentos, Quartel *quartel, int *numQuartel);
void menuOcorrencias();
void menuIntervencoes();
void menuBombeiros(Bombeiro **bombeiros, int numBombeiros);
void menuEquipamentos();
void menuRelatorios();

#endif