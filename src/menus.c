#include <stdio.h>
#include <stdlib.h>
#include "menus.h"
#include "ocorrencia.h"
#include "intervencao.h
#include "bombeiro.h"
#include "equipamento.h"
#include "quartel.h"

void menuPrincipal(Bombeiro *bombeiros, int *numBombeiros, Ocorrencia *ocorrencias, int *numOcorrencias, Intervencao *intervencoes, int *numIntervencoes, Equipamento *equipamentos, int *numEquipamentos, Quartel *quarteis, int *numQuarteis) {
    int opcao;
    do {
        //system("clear"); // Limpa a tela (Linux/Mac). Use "cls" para Windows.
        printf("==============================\n");
        printf("         MENU PRINCIPAL       \n");
        printf("==============================\n");
        printf("1. Gestão de Ocorrências\n");
        printf("2. Gestão de Intervenções\n");
        printf("3. Gestão de Bombeiros\n");
        printf("4. Gestão de Equipamentos\n");
        printf("5. Gestão de Quarteis\n");
        printf("0. Sair\n");
        printf("--------------//--------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuOcorrencias(ocorrencias, numOcorrencias);
                break;
            case 2:
                menuIntervencoes(intervencoes, numIntervencoes);
                break;
            case 3:
                menuBombeiros(bombeiros, numBombeiros);
                break;
            case 4:
                menuEquipamentos(equipamentos, numEquipamentos);
                break;
            case 5:
                menuQuarteis(quarteis, numQuarteis);
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
}


void menuOcorrencias(Ocorrencia *ocorrencias, int *numOcorrencias) {
    int opcao;
    do {
        // system("clear"); // Limpa a tela (Linux/Mac). Use "cls" para Windows.
        printf("==============================\n");
        printf("       GESTAO OCORRENCIAS     \n");
        printf("==============================\n");
        printf("1. Adicionar Ocorrencias\n");
        printf("2. Listar Ocorrencia\n");
        printf("3. Atualizar Ocorrencia\n");
        printf("4. Remover Ocorrencia\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarOcorrencia(&ocorrencias, numOcorrencias);
                break;
            case 2:
                listarOcorrencias(ocorrencias, *numOcorrencias);
                break;
            case 3:
                atualizarOcorrencia(ocorrencias, *numOcorrencias);
                break;
            case 4:
                removerOcorrencia(ocorrencias, numOcorrencias);
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); // captura o \n deixado pelo scanf
            getchar(); // espera o ENTER
        }

    } while(opcao != 0);
}

void menuIntervencoes(Intervencao *intervencoes, int *numIntervencoes) {
    int opcao;
    do {
        // system("clear"); // Limpa a tela (Linux/Mac). Use "cls"
        printf("==============================\n");
        printf("      GESTAO INTERVENCOES     \n");
        printf("==============================\n");
        printf("1. Adicionar Intervencoes\n");
        printf("2. Listar Intervencao\n");
        printf("3. Atualizar Intervencao\n");
        printf("4. Remover Intervencao\n");\
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarIntervencao(&intervencoes, numIntervencoes);
                break;
            case 2:
                listarIntervencoes(intervencoes, *numIntervencoes);
                break;
            case 3:
                atualizarIntervencao(intervencoes, *numIntervencoes);
                break;
            case 4:
                removerIntervencao(intervencoes, numIntervencoes);
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); // captura o \n deixado pelo scanf
            getchar(); // espera o ENTER
        }

    } while(opcao != 0);
}

void menuBombeiros(Bombeiro *bombeiros, int *numBombeiros) {
    int opcao;
    do {
        // system("clear"); // Limpa a tela (Linux/Mac). Use "cls"
        printf("==============================\n");
        printf("        GESTAO BOMBEIROS       \n");
        printf("==============================\n");
        printf("1. Adicionar Bombeiros\n");
        printf("2. Listar Bombeiros\n");
        printf("3. Atualizar Bombeiros\n");
        printf("4. Remover Bombeiros\n");\
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        printf("Escolha uma opcao:\n");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarBombeiro(&bombeiros, numBombeiros);
                break;
            case 2:
                listarBombeiros(bombeiros, *numBombeiros);
                break;
            case 3:
                atualizarBombeiro(bombeiros, *numBombeiros);
                break;
            case 4:
                removerBombeiro(bombeiros, numBombeiros);
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); // captura o \n deixado pelo scanf
            getchar(); // espera o ENTER
        }

    } while(opcao != 0);
}

void menuEquipamentos(Equipamento *equipamentos, int *numEquipamentos) {
    int opcao;
    do {
        // system("clear"); // Limpa a tela (Linux/Mac). Use "cls" para Windows.
        printf("==============================\n");
        printf("       GESTAO EQUIPAMENTOS     \n");
        printf("==============================\n");
        printf("1. Adicionar Euipamentos\n");
        printf("2. Listar Equipamentos\n");
        printf("3. Atualizar Equipamentos\n");
        printf("4. Remover Equipamentos\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarEquipamento(&equipamentos, numEquipamentos);
                break;
            case 2:
                listarEquipamentos(equipamentos, *numEquipamentos);
                break;
            case 3:
                atualizarEquipamento(equipamentos, *numEquipamentos);
                break;
            case 4:
                removerEquipamento(equipamentos, numEquipamentos);
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); // captura o \n deixado pelo scanf
            getchar(); // espera o ENTER
        }

    } while(opcao != 0);
}

void menuQuarteis(Quartel *quarteis, int *numQuarteis) {
    int opcao;
    do {
        // system("clear"); // Limpa a tela (Linux/Mac). Use "cls" para Windows.
        printf("==============================\n");
        printf("       GESTAO QUARTEIS      \n");
        printf("==============================\n");
        printf("1. Adicionar Quarteis\n");
        printf("2. Listar Quarteis\n");
        printf("3. Atualizar Quarteis\n");
        printf("4. Remover Quarteis\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                adicionarQuartel(&quarteis, numQuarteis);
                break;
            case 2:
                listarQuarteis(quarteis, *numQuarteis);
                break;
            case 3:
                atualizarQuartel(quarteis, *numQuarteis);
                break;
            case 4:
                removerQuartel(quarteis, numQuarteis);
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); // captura o \n deixado pelo scanf
            getchar(); // espera o ENTER
        }

    } while(opcao != 0);
}