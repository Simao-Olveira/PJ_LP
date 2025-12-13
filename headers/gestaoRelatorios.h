
#ifndef PJ_LP_GESTAORELATORIOS_H
#define PJ_LP_GESTAORELATORIOS_H

#include "ocorrencia.h"

//------------- Relatorio da Ocorrencia -------------
void relatorioEstado(Ocorrencia oc[], int n);
void relatorioTipo(Ocorrencia oc[], int n);
void relatorioPrioridade(Ocorrencia oc[], int n);
void relatorioTempoMedioResposta(Ocorrencia oc[], int n);
void relatorioAnaliseLocalizacao(Ocorrencia oc[], int n);
void relatorioFrequenciaIncidentes(Ocorrencia oc[], int n);

#endif //PJ_LP_GESTAORELATORIOS_H