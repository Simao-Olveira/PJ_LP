
#ifndef PJ_LP_OCORRENCIAGESTAO_H
#define PJ_LP_OCORRENCIAGESTAO_H

int procurarOcorrencia(Ocorrencias ocorrencias, int id);
void adicionarOcorrencia(Ocorrencias ocorrencias);
void libertarMemOcorrencias(Ocorrenciasocorrencias);
void imprimirOcorrencia(Ocorrencia ocorrencia);
void listarOcorrencias(Ocorrencias ocorrencias);
void atualizarDadosOcorrencia(Ocorrencia ocorrencia);
void editarOcorrencia(Ocorrenciasocorrencias);
void eliminarOcorrencia(Ocorrencias ocorrencias);
void guardarOcorrencias(Ocorrencias *ocorrencias);
void carregarOcorrencias(Ocorrenciasocorrencias);

#endif //PJ_LP_OCORRENCIAGESTAO_H