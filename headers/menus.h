#ifndef MENU_H
#define MENU_H

#include "gestaoBombeiro.h"
#include "bombeiro.h"
#include "ocorrencia.h"
#include "intervencao.h"
#include "equipamento.h"
#include "quartel.h"

void menuPrincipal(Bombeiros *bombeiros, Equipamentos *equipamentos);
void menuOcorrencias();
void menuIntervencoes();
void menuBombeiros(Bombeiros *bombeiros);
void menuEquipamentos(Equipamentos *equipamentos);
void menuRelatorios();

#endif