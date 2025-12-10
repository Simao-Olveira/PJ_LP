#include <stdio.h>
#include <stdlib.h>
#include "../headers/bombeiro.h"
#include "../headers/ocorrencia.h"
#include "../headers/intervencao.h"
#include "../headers/equipamento.h"
#include "../headers/quartel.h"
#include "../headers/enums.h"
#include "../headers/menus.h"
#include "../headers/gestaoBombeiro.h"
#include "../headers/gestaoEquipamento.h"

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

    readBombeiros(&bombeiros);
    readEquipamentos(&equipamentos);

    menuPrincipal(&bombeiros, &equipamentos);
    return 0;
}