#include <stdio.h>
#include <stdlib.h>
#include "../headers/files.h"
#include "../headers/bombeiro.h"
#include "../headers/ocorrencia.h"
#include "../headers/equipamento.h"
#include "../headers/enums.h"
#include "../headers/menus.h"

int main() {
    int totalBombeiros = 0, totalOcorrencias = 0;

    Bombeiro *b = carregarBombeiros("data/bombeiros.txt", &totalBombeiros);
    if (b != NULL) {
        printf("%d bombeiros carregados!\n", totalBombeiros);
    }

    printf("Lista de Bombeiros:\n");
    for (int i = 0; i < totalBombeiros; i++) {
        printf("ID: %d, Nome: %s, Idade: %d, Especialidade: %d, Estado: %d\n",
               b[i].id,
               b[i].nome,
               b[i].idade,
               b[i].especialidade,
               b[i].estado);
    }   
    free(b);
    b = NULL;

    Ocorrencia *o = carregarOcorrencias("data/ocorrencias.txt", &totalOcorrencias);
    if (o != NULL) {
        printf("\n%d ocorrencias carregadas!\n", totalBombeiros);
    }
    printf("Lista de Ocorrencias:\n");
    for (int i = 0; i < totalBombeiros; i++) {
        printf("ID: %d, Local: %s, Tipo: %d, Prioridade: %d, Estado: %d\n",
               o[i].id,
               o[i].local,
               o[i].tipo,
               o[i].prioridade,
               o[i].estado);
    }
    free(o);
    o = NULL;

    menuPrincipal();
    
    return 0;
}