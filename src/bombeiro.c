#include <stdio.h>
#include <stdlib.h>
#include "bombeiro.h"
#include "enums.h"

const char* especialidadeToString(EspecialidadeBombeiro e) {
    switch (e) {
        case COMANDO: return "Comando";
        case TRIPULANTE: return "Tripulante";
        case MOTORISTA: return "Motorista";
        case SOCORRISTA: return "Socorrista";
        default: return "Desconhecida";
    }
}

const char* estadoToString(EstadoBombeiro e) {
    switch (e) {
        case ATIVO: return "Ativo";
        case INATIVO: return "Inativo";
        case FERIDO: return "Ferido";
        default: return "Desconhecido";
    }
}

void adicionarBombeiro(Bombeiro **bombeiros, int *numBombeiros) {
Bombeiro novoBombeiro;
int op;

novoBombeiro.id = (*numBombeiros) + 1;
    printf("\n--- Nome do Bombeiro---\n");
    scanf("%s", novoBombeiro.nome);

    printf("\n--- Especialidade ---\n");
    printf("0 - Combate Florestal\n1 - Combate Aereo\n2 - Resgate\n");
    printf("Escolha uma opcao:\n ");
    scanf("%d", &op);
    novoBombeiro.especialidade = (EspecialidadeBombeiro) op;

    printf("\n--- Estado do bombeiro ---\n");
    printf("0 - Disponivel\n1 - Em Intervencao\n2 - Em Treino\n");
    printf("Escolha uma opcao:\n ");
    scanf("%d", &op);
    novoBombeiro.estado = (EstadoBombeiro) op;

(*numBombeiros)++;
    *tarefas = realloc(tarefas, (*numTarefas) sizeof(Tarefa));
    (*tarefas)[(*numTarefas) - 1] = novaTarefa;

}

void listarBombeiro(Bombeiro **bombeiros, int *numBombeiros)
for (int i = 0; i < numBombeiros; i++) {
    printf("ID: %d\n", bombeiros[i].id);
    printf("Nome: %s\n", bombeiros[i].nome);
    printf("Especialidade: %s\n", especialidadeToString(bombeiros[i].especialidade));
    printf("Estado: %s\n", estadoToString(bombeiros[i].estado));
    }
}

void atualizarBombeiro(Bombeiro *bombeiros, int numBombeiros) {
int id, opcao;

printf("\nDigite o ID do Bombeiro a ser atualizado:\n")
scanf("%d", &id);

    if (id <= 0 || id > numBombeiros) {
        printf("\nBombeiro não encontrado.\n");
        return;
    }
    Bombeiro *b = &bombeiros[id - 1];
    printf("\nO que deseja atualizar?\n");
    printf("1 - Nome\n");
    printf("2 - Especialidade\n");
    printf("3 - Estado\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Novo nome:\n");
            scanf("%s", b->nome);
            break;

        case 2:
        int op;
            printf("\n--- Especialidade ---\n");
            printf("0 - Combate Florestal\n1 - Combate Aereo\n2 - Resgate\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            b->especialidade = (EspecialidadeBombeiro) op;
            break;

        case 3:
        int op;
            printf("\n--- Estado do bombeiro ---\n");
            printf("0 - Disponivel\n1 - Em Intervencao\n2 - Em Treino\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            b->estado = (EstadoBombeiro) op;
            break;

        default:
            printf("Opção inválida!\n");
            return;
    }
    printf("\nBombeiro atualizado com sucesso!\n");
}

void removerBombeiro (Bombeiro *bombeiros, int numBombeiros) {
int id;

printf("\nDigite o ID do bombeiro a ser removido:\n ");
scanf("%d", &id);

        if (id <= 0 || id > numBombeiros) {
            printf("\nBombeiro não encontrado.");
            return;
        }
        //ativo=1 e inativo=0
        bombeiros[id - 1].ativo = 0;
        printf("\nBombeiro %d marcado como inativo.", id);

}

void salvarBombeirosEmFicheiros(Bombeiro *bombeiros, int numBombeiros) {
FILE *f = fopen("bombeiros.txt", "w");

    if (!f) {
        printf("\nErro ao abrir ficheiro de bombeiros.");
        return;
    }

    for (int i = 0; i < numBombeiros; i++) {
        if (bombeiros[i].ativo != 0) {  // Salva apenas tarefas ativas
            fprintf(f, "%d,%s,%d,%d,%d\n", b[i].id, b[i].nome, b[i].especialidade, b[i].estado);
    }
        fclose(f);
}

void carregarBombeirosDeFicheiros(Bombeiros **bombeiros, int *numBombeiros) {
    FILE *f = fopen("bombeiros.txt", "r");

    if (!f) {
        printf("\nFicheiro de bombeiros não encontrado.");
        return;
    }

    while (!feof(f)) {
        Bombeiros b;
        int estado;
        if (fscanf(f, "\n%d,%99[^,],%10[^,],%10[^,],%d,%d", &t.id, t.nome, t.especialidade, &estado) == 4)
{
            b.estado = estado;
            (*numBombeiros)++;
            *bombeiros = realloc(*bombeiros, (*numBombeiros) * sizeof(Bombeiro));
            (*bombeiros)[(*numBombeiros) - 1] = b;
                   }
    }
    fclose(f);
}



