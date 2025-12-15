#ifndef GESTAO_OCORRENCIA_H
#define GESTAO_OCORRENCIA_H

#include "ocorrencia.h"

// --- Protótipos ---
int procurarOcorrencia(Ocorrencias ocorrencias, int id);
void adicionarOcorrencia(Ocorrencias *ocorrencias);
void libertarMemOcorrencias(Ocorrencias *ocorrencias);
void imprimirOcorrencia(Ocorrencia ocorrencia);
void listarOcorrencias(Ocorrencias ocorrencias);
void atualizarDadosOcorrencia(Ocorrencia *ocorrencia);
void editarOcorrencia(Ocorrencias *ocorrencias);
void eliminarOcorrencia(Ocorrencias *ocorrencias);

// Funções de Ficheiros
void carregarOcorrencias(Ocorrencias *ocorrencias);
void guardarOcorrencias(Ocorrencias *ocorrencias);

#endif