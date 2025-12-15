#include <stdio.h>
#include <stdlib.h>
#include "iniciar.h"
#include "menus.h"
#include "log.h"

#include "../headers/ocorrencia.h"
#include "../headers/gestaoOcorrencia.h"

#include "../headers/intervencao.h"
#include "../headers/gestaoIntervencao.h"

#include "../headers/bombeiro.h"
#include "../headers/gestaoBombeiro.h"

#include "../headers/intervencao.h"

#include "../headers/equipamento.h"
#include "../headers/gestaoEquipamento.h"

#include "../headers/quartel.h"
#include "../headers/gestaoQuartel.h"

int iniciarSistema() {
    Ocorrencias ocorrencias;
    ocorrencias.numOcorrencias = 0;
    ocorrencias.totalOcorrencias = 5;

    logMsg("A iniciar a alocação de memória para ocorrências.");
    ocorrencias.ocorrencias = (Ocorrencia*) malloc(sizeof(Ocorrencia) * ocorrencias.totalOcorrencias);
    if (ocorrencias.ocorrencias == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        logMsg("Erro fatal: Falha na alocação de memória para ocorrências.");
        free(ocorrencias.ocorrencias);
        return 1;
    }

    Intervencoes intervencoes;
    intervencoes.numIntervencoes = 0;
    intervencoes.totalIntervencoes = 5;

    logMsg("A iniciar a alocação de memória para intervenções.");
    intervencoes.intervencoes = (Intervencao*) malloc(sizeof(Intervencao) * intervencoes.totalIntervencoes);
    if (intervencoes.intervencoes == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        logMsg("Erro fatal: Falha na alocação de memória para intervenções.");
        free(intervencoes.intervencoes);
        return 1;
    }

    logMsg("A iniciar a alocação de memória para bombeiros.");
    Bombeiros bombeiros;
    bombeiros.numBombeiros = 0;
    bombeiros.totalBombeiros = 5; 

    bombeiros.bombeiros = (Bombeiro*) malloc(sizeof(Bombeiro) * bombeiros.totalBombeiros);
    if (bombeiros.bombeiros == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        logMsg("Erro fatal: Falha na alocação de memória para bombeiros.");
        free(bombeiros.bombeiros);
        return 1; 
    }

    
    Equipamentos equipamentos;
    equipamentos.numEquipamentos = 0;
    equipamentos.totalEquipamentos = 5;

    logMsg("A iniciar a alocação de memória para equipamentos.");
    equipamentos.equipamentos = (Equipamento*) malloc(sizeof(Equipamento) * equipamentos.totalEquipamentos);
    if (equipamentos.equipamentos == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        logMsg("Erro fatal: Falha na alocação de memória para equipamentos.");
        free(equipamentos.equipamentos);
        return 1; 
    }

    Quarteis quarteis;
    quarteis.numQuarteis = 0;
    quarteis.totalQuarteis = 5;

    logMsg("A iniciar a alocação de memória para quarteis.");
    quarteis.quarteis = (Quartel*) malloc(sizeof(Quartel) * quarteis.totalQuarteis);
    if (quarteis.quarteis == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        logMsg("Erro fatal: Falha na alocação de memória para quarteis.");
        free(quarteis.quarteis);
        return 1;
    }

    logMsg("A iniciar a leitura dos ficheiros de dados.");
    carregarOcorrencias(&ocorrencias);
    carregarIntervencoes(&intervencoes);
    carregarBombeiros(&bombeiros);
    carregarEquipamentos(&equipamentos);
    carregarQuarteis(&quarteis);
    
    logMsg("A iniciar o menu principal.");
    menuPrincipal(&ocorrencias, &intervencoes, &bombeiros, &equipamentos, &quarteis);
    return 0;
}