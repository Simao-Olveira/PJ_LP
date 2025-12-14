
#ifndef PJ_LP_GESTAORELATORIOS_H
#define PJ_LP_GESTAORELATORIOS_H

#include "ocorrencia.h"
#include "intervencao.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "quartel.h"

int procurarRelatorio(Relatorios relatorios, int id);
//------------- Relatorio da Ocorrencia -------------
void relatorioEstatisticasGerais(Ocorrencias ocorrencias);
void relatorioTempoMedioResposta(Ocorrencias ocorrencias);
void relatorioLocalizacaoEFrequencia(Ocorrencias ocorrencias);


//------------- Relatorio da Intervencao -------------
void relatorioIntervencoesEstado(Intervencoes intervencoes);
void relatorioTempoDuracao(Intervencoes intervencoes);
void relatorioRecursosMaisUtilizados(Intervencoes intervencoes);
void relatorioEficiencia(Intervencoes intervencoes);

//------------- Relatorio do Bombeiro -------------
void relatorioDisponibilidadeEspecialidade(Bombeiros bombeiros);
void relatorioParticipacaoIntervencoes(Bombeiros bombeiro);
void relatorioRankingDesempenho(Bombeiros bombeiros);


// ----------- Relatorios do Equipamento ------------
void relatorioInventarioEquipamentos(Equipamentos equipamentos);
void relatorioUtilizacaoTipoIntervencao(Equipamentos equipamentos);
void relatorioManutencaoEquipamentos(Equipamentos equipamentos);


//------------- Relatorio do Quartel -------------




//------------- Relatorio do Quartel -------------



#endif //PJ_LP_GESTAORELATORIOS_H