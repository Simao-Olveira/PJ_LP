#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "menus.h"
#include "ocorrencia.h"
#include "intervencao.h"
#include "bombeiro.h"
#include "gestaoBombeiro.h"
#include "equipamento.h"
#include "gestaoEquipamento.h"
#include "quartel.h"


void menuPrincipal(Bombeiros *bombeiros, Equipamentos *equipamentos) {
    int opcao;
    do {
        printf("==============================\n");
        printf("         MENU PRINCIPAL       \n");
        printf("==============================\n");
        printf("1. Gestão de Ocorrências\n");
        printf("2. Gestão de Intervenções\n");
        printf("3. Gestão de Bombeiros\n");
        printf("4. Gestão de Equipamentos\n");
        printf("5. Relatórios\n");
        printf("0. Sair\n");
        printf("==============================\n");
        opcao = obterInteiro(0, 5, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                //menuOcorrencias();
                break;
            case 2:
                //menuIntervencoes();
                break;
            case 3:
                menuBombeiros(bombeiros);
                break;
            case 4:
                menuEquipamentos(equipamentos);
                break;
            case 5:
                //menuRelatorios();
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

/*
void menuOcorrencias() {
    int opcao;
    do {
        system("clear"); // Limpa a tela (Linux/Mac). Use "cls" para Windows.
        printf("==============================\n");
        printf("       GESTAO OCORRENCIAS     \n");
        printf("==============================\n");
        printf("1. Listar Ocorrencias\n");
        printf("2. Adicionar Ocorrencia\n");
        printf("3. Atualizar Ocorrencia\n");
        printf("4. Remover Ocorrencia\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("==============================\n");
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

void menuIntervencoes() {
    int opcao;
    do {
        system("clear"); // Limpa a tela (Linux/Mac). Use "cls"
        printf("==============================\n");
        printf("      GESTAO INTERVENCOES     \n");
        printf("==============================\n");
        printf("1. Listar Intervencoes\n");
        printf("2. Adicionar Intervencao\n");
        printf("3. Atualizar Intervencao\n");
        printf("4. Remover Intervencao\n");\
        printf("0. Voltar ao Menu Principal\n");
        printf("==============================\n");
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
 */
void menuBombeiros(Bombeiros *bombeiros) {
    int opcao;
    do {
        printf("==============================\n");
        printf("       GESTAO BOMBEIROS       \n");
        printf("==============================\n");
        printf("1. Listar Bombeiros\n");
        printf("2. Adicionar Bombeiro\n");
        printf("3. Atualizar Bombeiro\n");
        printf("4. Remover Bombeiro\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        opcao = obterInteiro(0, 4, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                listarBombeiros(*bombeiros);
                break;
            case 2:
                adicionarBombeiro(bombeiros);
                break;
            case 3:
                editarBombeiro(bombeiros);
                break;
            case 4:
                eliminarBombeiro(bombeiros);
                break;
            case 0:
                printf("A Sair...\n");
                writeBombeiros(bombeiros);
                libertarMemBombeiros(bombeiros);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            
        }

    } while(opcao != 0);
}

void menuEquipamentos(Equipamentos *equipamentos) {
    int opcao;
    do {
        printf("==============================\n");
        printf("       GESTAO EQUIPAMENTOS       \n");
        printf("==============================\n");
        printf("1. Listar Equipamentos\n");
        printf("2. Adicionar Equipamento\n");
        printf("3. Atualizar Equipamento\n");
        printf("4. Remover Equipamento\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        opcao = obterInteiro(0, 4, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                listarEquipamentos(*equipamentos);
                break;
            case 2:
                adicionarEquipamento(equipamentos);
                break;
            case 3:
                editarEquipamento(equipamentos);
                break;
            case 4:
                eliminarEquipamento(equipamentos);
                break;
            case 0:
                printf("A Sair...\n");
                writeEquipamentos(equipamentos);
                libertarMemEquipamentos(equipamentos);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); // espera o ENTER
        }

    } while(opcao != 0);
}
/*
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
}*/