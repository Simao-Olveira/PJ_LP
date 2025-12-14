#ifndef MENU_H
#define MENU_H

#include "ocorrencia.h"
#include "bombeiro.h"
#include "ocorrencia.h"
#include "intervencao.h"
#include "equipamento.h"
#include "quartel.h"

void menuPrincipal(Ocorrencias *ocorrencias, Intervencoes *intervencoes, Bombeiros *bombeiros, Equipamentos *equipamentos, Quarteis *quarteis);
void menuOcorrencias(Ocorrencias *ocorrencias);
void menuIntervencoes(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos);
void menuBombeiros(Bombeiros *bombeiros);
void menuEquipamentos(Equipamentos *equipamentos);
void menuQuarteis(Quarteis *quarteis);
void menuRelatorios(Ocorrencias *ocorrencias, Intervencoes *intervencoes, Bombeiros *bombeiros, Equipamentos *equipamentos, Quarteis *quarteis);

#endif