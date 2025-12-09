#include <stdio.h>
#include <stdlib.h>
#include "../headers/bombeiro.h"
#include "../headers/ocorrencia.h"
#include "../headers/intervencao.h"
#include "../headers/equipamento.h"
#include "../headers/quartel.h"
#include "../headers/enums.h"
#include "../headers/menus.h"

void libertarMemoria(Bombeiro *bombeiros, Ocorrencia *ocorrencias, Intervencao *intervencoes, Equipamento *equipamentos, Quartel *quartel) {
    free(bombeiros);
    free(ocorrencias);
    free(intervencoes);
    free(equipamentos);
    free(quartel);
}

int main() {
    Bombeiro *bombeiros = NULL;
    Ocorrencia *ocorrencias = NULL;
    Intervencao *intervencoes = NULL;
    Equipamento *equipamentos = NULL;
    Quartel *quartel = NULL;

    int numBombeiros = 0, numOcorrencias = 0, numIntervencoes = 0, numEquipamentos = 0, numQuartel = 0;

    menuPrincipal(&bombeiros, &numBombeiros, ocorrencias, &numOcorrencias, intervencoes, &numIntervencoes, equipamentos, &numEquipamentos, quartel, &numQuartel);
    return 0;
}