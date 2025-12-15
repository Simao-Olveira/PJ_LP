/**
 * @file iniciar.c
 * @brief Implementação do fluxo de inicialização do sistema.
 */

#include <stdio.h>
#include <stdlib.h>
#include "iniciar.h"
#include "menus.h"
#include "log.h"

// Includes dos cabeçalhos das entidades
#include "../headers/ocorrencia.h"
#include "../headers/gestaoOcorrencia.h"

#include "../headers/intervencao.h"
#include "../headers/gestaoIntervencao.h"

#include "../headers/bombeiro.h"
#include "../headers/gestaoBombeiro.h"

#include "../headers/equipamento.h"
#include "../headers/gestaoEquipamento.h"

#include "../headers/quartel.h"
#include "../headers/gestaoQuartel.h"

/** * @brief Inicializa o sistema, carrega dados e arranca o menu principal.
 * * Lógica do Algoritmo:
 * 1. Declara as estruturas de controlo (Ocorrencias, Bombeiros, etc.) na stack.
 * 2. Chama as funções de carregamento (ex: carregarBombeiros). Estas funções são
 * responsáveis por alocar a memória dinâmica necessária. Se os ficheiros não
 * existirem, elas inicializam as estruturas vazias prontas a usar.
 * 3. Transfere o controlo para o Menu Principal.
 * 4. Após o fecho do menu (encerramento do programa), chama as funções de libertação
 * de memória para garantir um encerramento limpo.
 * @return 0 em caso de sucesso.
 */
int iniciarSistema() {
    // 1. Declaração das estruturas de gestão
    Ocorrencias ocorrencias;
    Intervencoes intervencoes;
    Bombeiros bombeiros;
    Equipamentos equipamentos;
    Quarteis quarteis;

    // 2. Carregamento de dados (e alocação de memória)
    logMsg("A iniciar o carregamento dos dados e alocação de memória.");

    // Nota: As funções 'carregar' tratam da alocação de memória (malloc/realloc).
    // Não devemos fazer malloc aqui para evitar fugas de memória (memory leaks).
    carregarOcorrencias(&ocorrencias);
    carregarIntervencoes(&intervencoes);
    carregarBombeiros(&bombeiros);
    carregarEquipamentos(&equipamentos);
    carregarQuarteis(&quarteis);
    
    // 3. Execução do Menu Principal
    logMsg("Dados carregados. A iniciar o menu principal.");
    menuPrincipal(&ocorrencias, &intervencoes, &bombeiros, &equipamentos, &quarteis);

    // 4. Limpeza de memória antes de sair (Boas práticas)
    logMsg("A encerrar o sistema e a libertar memória.");
    libertarMemOcorrencias(&ocorrencias);
    libertarMemIntervencoes(&intervencoes);
    libertarMemBombeiros(&bombeiros);
    libertarMemEquipamentos(&equipamentos);
    libertarMemQuarteis(&quarteis);

    return 0;
}