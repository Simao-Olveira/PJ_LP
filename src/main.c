#include <stdio.h>
#include <stdlib.h>
#include "../headers/bombeiro.h"
#include "../headers/ocorrencia.h"
#include "../headers/intervencao.h"
#include "../headers/equipamento.h"
#include "../headers/quartel.h"
#include "../headers/enums.h"
#include "../headers/menus.h"


int main() {
    Bombeiros bombeiros;
   
    bombeiros.numBombeiros = 0;
    bombeiros.totalBombeiros = 5; 

    bombeiros.bombeiros = (Bombeiro*) malloc(sizeof(Bombeiro) * bombeiros.totalBombeiros);
    if (bombeiros.bombeiros == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        return 1; 
    }

    readBombeiros(&bombeiros);
    
    menuPrincipal(&bombeiros);
    return 0;
}