/**
 * @file menus.h
 * @brief Menus de navegação e interação com o utilizador.
 */

#ifndef MENU_H
#define MENU_H

#include "ocorrencia.h"
#include "bombeiro.h"
#include "intervencao.h"
#include "equipamento.h"
#include "quartel.h"

/** @brief Menu principal que orquestra a navegação entre todos os módulos. */
void menuPrincipal(Ocorrencias *ocorrencias, Intervencoes *intervencoes, Bombeiros *bombeiros, Equipamentos *equipamentos, Quarteis *quarteis);

/** @brief Submenu para gestão de ocorrências. */
void menuOcorrencias(Ocorrencias *ocorrencias);

/** @brief Submenu para gestão de intervenções (requer acesso a todas as entidades). */
void menuIntervencoes(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos);

/** @brief Submenu para gestão de bombeiros. */
void menuBombeiros(Bombeiros *bombeiros, Quarteis *quarteis);

/** @brief Submenu para gestão de equipamentos. */
void menuEquipamentos(Equipamentos *equipamentos);

/** @brief Submenu para gestão de quartéis. */
void menuQuarteis(Quarteis *quarteis);

/** @brief Submenu para visualização de estatísticas e relatórios globais. */
void menuRelatorios(Ocorrencias *ocorrencias, Intervencoes *intervencoes, Bombeiros *bombeiros, Equipamentos *equipamentos, Quarteis *quarteis);

#endif