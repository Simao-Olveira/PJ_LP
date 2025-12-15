/**
 * @file gestaoRelatorios.h
 * @brief Módulo de estatísticas e relatórios do sistema.
 */

#ifndef GESTAORELATORIOS_H
#define GESTAORELATORIOS_H

#include "bombeiro.h"
#include "intervencao.h"
#include "ocorrencia.h"
#include "equipamento.h"
#include "quartel.h"

/** @brief Relatórios de produtividade/atuação dos bombeiros (cruza dados com intervenções). */
void menuRelatoriosBombeiros(Intervencoes intervencoes, Ocorrencias ocorrencias, Bombeiros bombeiros);

/** @brief Relatórios de utilização e estado dos equipamentos nas intervenções. */
void menuRelatoriosEquipamentos(Intervencoes intervencoes, Equipamentos equipamentos);

/** @brief Estatísticas globais sobre ocorrências (tipos, locais, frequência). */
void menuRelatoriosOcorrencias(Ocorrencias ocorrencias);

/** @brief Análise de dados das intervenções (tempos médios, datas, eficácia). */
void menuRelatoriosIntervencoes(Intervencoes intervencoes);

/** @brief Relatórios operacionais dos quartéis (lotação e distribuição de efetivos). */
void menuRelatoriosQuarteis(Quarteis quarteis, Bombeiros bombeiros);

#endif