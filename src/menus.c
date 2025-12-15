#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#include "menus.h"
#include "log.h"
#include "../headers/relatorios.h"

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


void menuPrincipal(Ocorrencias *ocorrencias, Intervencoes *intervencoes, Bombeiros *bombeiros, Equipamentos *equipamentos, Quarteis *quarteis) {
    int opcao;
    do {
        printf("==============================\n");
        printf("         MENU PRINCIPAL       \n");
        printf("==============================\n");
        printf("1. Gestão de Ocorrências\n");
        printf("2. Gestão de Intervenções\n");
        printf("3. Gestão de Bombeiros\n");
        printf("4. Gestão de Equipamentos\n");
        printf("5. Gestão de Quarteis\n");
        printf("6. Relatórios\n");
        printf("0. Sair\n");
        printf("==============================\n");
        opcao = obterInteiro(0, 6, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                logMsg("A entrar no menu de ocorrências.");
                menuOcorrencias(ocorrencias);
                break;
            case 2:
                logMsg("A entrar no menu de intervenções.");
                menuIntervencoes(intervencoes, ocorrencias, bombeiros, equipamentos);
                break;
            case 3:
                logMsg("A entrar no menu de bombeiros.");
                menuBombeiros(bombeiros);
                break;
            case 4:
                logMsg("A entrar no menu de equipamentos.");
                menuEquipamentos(equipamentos);
                break;
            case 5:
                logMsg("A entrar no menu de quarteis.");
                menuQuarteis(quarteis);
                break;
            case 6:
                logMsg("A entrar no menu de relatórios.");
                menuRelatorios(ocorrencias, intervencoes, bombeiros, equipamentos, quarteis);
                break;
            case 0:
                logMsg("A sair do sistema.");
                printf("A Sair...\n");
                libertarMemBombeiros(bombeiros);
                libertarMemEquipamentos(equipamentos);
                libertarMemIntervencoes(intervencoes);
                libertarMemOcorrencias(ocorrencias);
                libertarMemQuarteis(quarteis);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

void menuOcorrencias(Ocorrencias *ocorrencias) {
    int opcao;
    do {
        printf("==============================\n");
        printf("       GESTAO OCORRENCIAS     \n");
        printf("==============================\n");
        printf("1. Listar Ocorrencias\n");
        printf("2. Adicionar Ocorrencia\n");
        printf("3. Atualizar Ocorrencia\n");
        printf("4. Remover Ocorrencia\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("==============================\n");
        opcao = obterInteiro(0, 4, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                logMsg("A listar ocorrências.");
                listarOcorrencias(*ocorrencias);
                break;
            case 2:
                logMsg("A adicionar uma nova ocorrência.");
                adicionarOcorrencia(ocorrencias);
                break;
            case 3:
                logMsg("A editar uma ocorrência.");
                editarOcorrencia(ocorrencias);
                break;
            case 4:
                logMsg("A eliminar uma ocorrência.");
                eliminarOcorrencia(ocorrencias);
                break;
            case 0:
                logMsg("A sair do menu de ocorrências.");
                printf("A Sair...\n");
                logMsg("A guardar ocorrências no ficheiro.");
                guardarOcorrencias(ocorrencias);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
        }

    } while(opcao != 0);
}

void menuIntervencoes(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos) {
    int opcao;
    do {
        printf("==============================\n");
        printf("      GESTAO INTERVENCOES     \n");
        printf("==============================\n");
        printf("1. Listar Intervencoes\n");
        printf("2. Adicionar Intervencao\n");
        printf("3. Atualizar Intervencao\n");
        printf("4. Remover Intervencao\n");\
        printf("0. Voltar ao Menu Principal\n");
        printf("==============================\n");
        opcao = obterInteiro(0, 4, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                logMsg("A listar intervenções.");
                listarIntervencoes(*intervencoes);
                break;
            case 2:
                logMsg("A adicionar uma nova intervenção.");
                adicionarIntervencao(intervencoes, ocorrencias, bombeiros, equipamentos);
                break;
            case 3:
                logMsg("A editar uma intervenção.");
                editarIntervencao(intervencoes);
                break;
            case 4:
                logMsg("A eliminar uma intervenção.");
                eliminarIntervencao(intervencoes);
                break;
            case 0:
                logMsg("A sair do menu de intervenções.");
                printf("A Sair...\n");
                logMsg("A guardar intervenções no ficheiro.");
                guardarIntervencoes(intervencoes);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
        }
    } while(opcao != 0);
}

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
                logMsg("A listar bombeiros.");
                listarBombeiros(*bombeiros);
                break;
            case 2:
                logMsg("A adicionar um novo bombeiro.");
                adicionarBombeiro(bombeiros);
                break;
            case 3:
                logMsg("A editar um bombeiro.");
                editarBombeiro(bombeiros);
                break;
            case 4:
                logMsg("A eliminar um bombeiro.");
                eliminarBombeiro(bombeiros);
                break;
            case 0:
                logMsg("A sair do menu de bombeiros.");
                printf("A Sair...\n");
                logMsg("A guardar bombeiros no ficheiro.");
                guardarBombeiros(bombeiros);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
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
                logMsg("A listar equipamentos.");
                listarEquipamentos(*equipamentos);
                break;
            case 2:
                logMsg("A adicionar um novo equipamento.");
                adicionarEquipamento(equipamentos);
                break;
            case 3:
                logMsg("A editar um equipamento.");
                editarEquipamento(equipamentos);
                break;
            case 4:
                logMsg("A eliminar um equipamento.");
                eliminarEquipamento(equipamentos);
                break;
            case 0:
                logMsg("A sair do menu de equipamentos.");
                printf("A Sair...\n");
                logMsg("A guardar equipamentos no ficheiro.");
                guardarEquipamentos(equipamentos);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar();
        }

    } while(opcao != 0);
}

void menuQuarteis(Quarteis *quarteis) {
    int opcao;
    do {
        printf("==============================\n");
        printf("       GESTAO QUARTEIS      \n");
        printf("==============================\n");
        printf("1. Listar Quarteis\n");
        printf("2. Adicionar Quarteis\n");
        printf("3. Atualizar Quarteis\n");
        printf("4. Remover Quarteis\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("--------------//--------------\n");
        opcao = obterInteiro(0, 4, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                logMsg("A listar quarteis.");
                listarQuarteis(*quarteis);
                break;
            case 2:
                logMsg("A adicionar um novo quartel.");
                adicionarQuartel(quarteis);
                break;
            case 3:
                logMsg("A editar um quartel.");
                editarQuartel(quarteis);
                break;
            case 4:
                logMsg("A eliminar um quartel.");
                eliminarQuartel(quarteis);
                break;
            case 0:
                logMsg("A sair do menu de quarteis.");
                printf("A Sair...\n");
                logMsg("A guardar quarteis no ficheiro.");
                guardarQuarteis(quarteis);
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...\n");
            getchar();
        }

    } while(opcao != 0);
}

void menuRelatorios(Ocorrencias *ocorrencias, Intervencoes *intervencoes, Bombeiros *bombeiros, Equipamentos *equipamentos, Quarteis *quarteis) {
    int opcao;
    do {
        printf("==============================\n");
        printf("         MENU RELATÓRIOS      \n");
        printf("==============================\n");
        printf("1. Relatórios das Ocorrencias\n");
        printf("2. Relatorio das Intervenções\n");
        printf("3. Relatório dos Bombeiros\n");
        printf("4. Relatório dos Equipamentos\n");
        printf("5. Relatório dos Quarteis\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("==============================\n");
        opcao = obterInteiro(0, 5, "Escolha uma opcao: ");

        switch(opcao) {
            case 1:
                //logMsg("A abrir menu de relatórios de ocorrências.");
                menuRelatoriosOcorrencias(*intervencoes, *ocorrencias);
                break;
            case 2:
                logMsg("A abrir menu de relatórios de intervenções.");
                menuRelatoriosIntervencoes(*intervencoes);
                break;
            case 3:
                logMsg("A abrir menu de relatórios de bombeiros.");
                menuRelatoriosBombeiros(*intervencoes, *ocorrencias, *bombeiros);
                break;
            case 4:
                logMsg("A abrir menu de relatórios de equipamentos.");
                menuRelatoriosEquipamentos(*intervencoes, *ocorrencias, *equipamentos);
                break;
            case 5:
                logMsg("A abrir menu de relatórios de quarteis.");
                menuRelatoriosQuarteis(*quarteis);
                break;
            case 0:
                logMsg("A sair do menu de relatórios.");
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
}