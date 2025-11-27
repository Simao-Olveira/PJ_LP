#ifndef FILES_H
#define FILES_H

#include <stdio.h>
#include "bombeiro.h"
#include "ocorrencia.h"
#include "equipamento.h"
#include "intervencao.h"
#include "enums.h"

// Helpers
FILE* abrirParaLeitura(const char *caminho);
int contarLinhas(const char *caminho);
char* lerLinha(FILE *f, char *buffer, int tamanho);

// Funções de carregamento
Bombeiro* carregarBombeiros(const char *caminho, int *tamanho);
Ocorrencia* carregarOcorrencias(const char *caminho, int *tamanho); 
Equipamento* carregarEquipamentos(const char *caminho, int *tamanho);
Intervencao* carregarIntervencoes(const char *caminho, int *tamanho);

#endif