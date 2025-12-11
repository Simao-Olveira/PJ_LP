#include <stdio.h>
#include <stdlib.h>

#include "../headers/bombeiro.h"
#include "../headers/gestaoBombeiro.h"

#include "../headers/ocorrencia.h"

#include "../headers/intervencao.h"

#include "../headers/equipamento.h"
#include "../headers/gestaoEquipamento.h"

#include "../headers/quartel.h"
#include "../headers/gestaoQuartel.h"

#include "../headers/enums.h"
#include "../headers/menus.h"



int main() {
    Bombeiros bombeiros;
    bombeiros.numBombeiros = 0;
    bombeiros.totalBombeiros = 5; 

    bombeiros.bombeiros = (Bombeiro*) malloc(sizeof(Bombeiro) * bombeiros.totalBombeiros);
    if (bombeiros.bombeiros == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        free(bombeiros.bombeiros);
        return 1; 
    }

    Equipamentos equipamentos;
    equipamentos.numEquipamentos = 0;
    equipamentos.totalEquipamentos = 5;

    equipamentos.equipamentos = (Equipamento*) malloc(sizeof(Equipamento) * equipamentos.totalEquipamentos);
    if (equipamentos.equipamentos == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        free(equipamentos.equipamentos);
        return 1; 
    }

    Quarteis quarteis;
    quarteis.numQuarteis = 0;
    quarteis.totalQuarteis = 2;

    quarteis.quarteis = (Quartel*) malloc(sizeof(Quartel) * quarteis.totalQuarteis);
    if (quarteis.quarteis == NULL) {
        printf("Erro fatal: Falha na alocação de memória.\n");
        free(quarteis.quarteis);
        return 1;
    }

    readBombeiros(&bombeiros);
    readEquipamentos(&equipamentos);
    readQuarteis(&quarteis);

    menuPrincipal(&bombeiros, &equipamentos, &quarteis);
    return 0;
}