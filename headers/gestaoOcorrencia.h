
#ifndef PJ_LP_OCORRENCIAGESTAO_H
#define PJ_LP_OCORRENCIAGESTAO_H

#include "ocorrencia.h"

void imprimirTipoOcorrencia(TipoOcorrencia tipo);
void imprimirPrioridade(Prioridade prioridade);
void imprimirEstadoOcorrencia(EstadoOcorrencia estado);
int procurarOcorrencia(Ocorrencias ocorrencias, int id);
void adicionarOcorrencia(Ocorrencias *ocorrencias);
void libertarMemOcorrencias(Ocorrencias *ocorrencias);
void imprimirOcorrencia(Ocorrencia oc);
void listarOcorrencias(Ocorrencias ocorrencias);
void atualizarDadosOcorrencia(Ocorrencia *ocorrencia);
void editarOcorrencia(Ocorrencias *ocorrencias);
void eliminarOcorrencia(Ocorrencias *ocorrencias);
void carregarOcorrencias(Ocorrencias *ocorrencias);
void guardarOcorrencias(Ocorrencias *ocorrencias);

#endif //PJ_LP_OCORRENCIAGESTAO_H