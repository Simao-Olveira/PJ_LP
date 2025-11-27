#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

void menuPrincipal() {
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
        printf("5. Relatórios\n");
        printf("0. Sair\n");
        printf("==============================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuOcorrencias();
                break;
            case 2:
                menuIntervencoes();
                break;
            case 3:
                menuBombeiros();
                break;
            case 4:
                menuEquipamentos();
                break;
            case 5:
                menuRelatorios();
                break;
            case 0:
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while(opcao != 0);
}

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
                
                break;
            case 2:
                
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
}

void menuBombeiros() {
    // Implementar menu de bombeiros
}

void menuEquipamentos() {
    // Implementar menu de equipamentos
}

void menuRelatorios() {
    // Implementar menu de relatórios
}