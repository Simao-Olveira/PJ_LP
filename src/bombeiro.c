#include <stdio.h>
#include <stdlib.h>
#include "bombeiro.h"
#include "enums.h"

void criarBombeiro(Bombeiro **bombeiros, int *numBombeiros) {
Bombeiro novoBombeiro;
int op;

novoBombeiro.id = (*numBombeiros) + 1;
    printf("\n--- Nome do Bombeiro---\n");
    scanf("%s", novoBombeiro.nome);

     printf("\n--- Especialidade ---\n");
    printf("0 - Combate Florestal\n1 - Combate Aereo\n2 - Resgate\n3");
    printf("Escolha: ");
    scanf("%d", &op);
    novoBombeiro.especialidade = (EspecialidadeBombeiro) op;

    printf("\n--- Estado do bombeiro ---\n");
    printf("0 - Disponivel\n1 - Em Intervencao\n2 - Em Treino\n3");
    printf("Escolha: ");
    scanf("%d", &op);
    novoBombeiro.estado = (EstadoBombeiro) op;

(*numBombeiros)++;
    *tarefas = realloc(tarefas, (*numTarefas) sizeof(Tarefa));
    (*tarefas)[(*numTarefas) - 1] = novaTarefa;

}