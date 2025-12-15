/**
 * @file intervencao.c
 * @brief Implementação das funções de gestão de intervenções.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gestaoIntervencao.h"
#include "gestaoOcorrencia.h"
#include "gestaoBombeiro.h"
#include "gestaoEquipamento.h"
#include "intervencao.h"
#include "ocorrencia.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "input.h"
#include "enums.h"
#include "log.h"

/** @brief Converte o estado da intervenção em texto para impressão. */
void imprimirEstadoIntervencao(EstadoIntervencao estado) {
    switch (estado) {
        case INT_PLANEAMENTO: printf("Planeamento"); break;
        case INT_EXECUCAO:    printf("Em Execução"); break;
        case INT_CONCLUIDA:   printf("Concluída"); break;
        default:              printf("Desconhecido"); break;
    }
}

/** * @brief Procura uma intervenção pelo ID.
 * * Percorre sequencialmente a lista até encontrar o identificador fornecido.
 * @return O índice no array ou -1 se não encontrar.
 */
int procurarIntervencao(Intervencoes intervencoes, int id) {
    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        if (intervencoes.intervencoes[i].id == id) {
            return i;
        }
    }
    return -1;
}

/** * @brief Cria uma nova intervenção e aloca recursos (Bombeiros/Equipamentos).
 * * Lógica Complexa de Validação e Alocação:
 * 1. Pré-condição: Verifica se existem ocorrências registadas.
 * 2. Gera ID automático e redimensiona a memória (realloc) se necessário.
 * 3. Associa a uma Ocorrência existente (validação de chave estrangeira).
 * 4. **Alocação de Bombeiros**:
 * - Conta quantos bombeiros têm estado 'DISPONIVEL'.
 * - Solicita ao utilizador quantos quer alocar (limitado aos disponíveis).
 * - Para cada bombeiro escolhido: valida se existe, se não é duplicado na lista
 * e se está realmente disponível.
 * - IMPORTANTE: Altera o estado do bombeiro para 'EM_INTERVENCAO'.
 * 5. **Alocação de Equipamentos**:
 * - Segue a mesma lógica dos bombeiros. Altera o estado para 'EM_USO'.
 * 6. Regista as datas e horas de início.
 */
void adicionarIntervencao(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos) {
    
    // 1. VALIDAÇÃO CRÍTICA
    if (ocorrencias == NULL || ocorrencias->numOcorrencias <= 0) {
        printf("Erro: Não existem ocorrências registadas. Crie uma ocorrência primeiro.\n");
        return;
    }

    printf("\n--- Nova Intervenção ---\n");

    // Gerar ID Automático
    int maiorId = 0;
    for(int i = 0; i < intervencoes->numIntervencoes; i++) {
        if(intervencoes->intervencoes[i].id > maiorId) {
            maiorId = intervencoes->intervencoes[i].id;
        }
    }
    int id = maiorId + 1;

    // Verificar memória do array principal
    if (intervencoes->totalIntervencoes == intervencoes->numIntervencoes) {
        intervencoes->totalIntervencoes += 5;
        Intervencao *temp = (Intervencao*) realloc(intervencoes->intervencoes, intervencoes->totalIntervencoes * sizeof(Intervencao));
        if (temp == NULL) { printf("Erro de memória.\n"); return; }
        intervencoes->intervencoes = temp;
    }

    int i = intervencoes->numIntervencoes;
    intervencoes->intervencoes[i].id = id;
    intervencoes->intervencoes[i].estado = INT_PLANEAMENTO;

    // --- 2. ASSOCIAR OCORRÊNCIA ---
    listarOcorrencias(*ocorrencias);
    int idOcorrencia;
    int valida = 0;
    do {
        idOcorrencia = obterInteiro(0, MAX_INT, "Associe o ID da Ocorrência: ");
        if (procurarOcorrencia(*ocorrencias, idOcorrencia) != -1) {
            valida = 1;
        } else {
            printf("Ocorrência não encontrada.\n");
        }
    } while(!valida);
    intervencoes->intervencoes[i].idOcorrencia = idOcorrencia;


    // --- 3. ALOCAR BOMBEIROS (Limitado aos Disponíveis) ---
    if (bombeiros != NULL && bombeiros->numBombeiros > 0) {
        printf("\n--- Alocar Bombeiros ---\n");
        listarBombeiros(*bombeiros); 

        // 3.1. Contar apenas os disponíveis para definir o limite
        int disponiveis = 0;
        for(int k=0; k < bombeiros->numBombeiros; k++){
            if(bombeiros->bombeiros[k].estado == EB_DISPONIVEL) disponiveis++;
        }
        printf(">> Total de Bombeiros Disponíveis: %d\n", disponiveis);

        if (disponiveis > 0) {
            int qtdPedida = obterInteiro(0, disponiveis, "Quantos bombeiros quer alocar? ");
            
            if (qtdPedida > 0) {
                // Aloca array dinâmico interno para guardar os IDs
                intervencoes->intervencoes[i].idsBombeiros = (int*) malloc(qtdPedida * sizeof(int));
                
                for (int k = 0; k < qtdPedida; k++) {
                    int idBomb, aux;
                    int idxBomb = -1; 

                    do {
                        aux = 0;
                        printf("Bombeiro %d/%d: ", k+1, qtdPedida);
                        idBomb = obterInteiro(0, MAX_INT, "ID do Bombeiro: ");

                        idxBomb = procurarBombeiro(*bombeiros, idBomb);

                        // Valida existência
                        if(idxBomb == -1){
                            printf("Aviso: Bombeiro com ID %d não encontrado.\n", idBomb);
                            aux = 1;
                        } else {
                            // Valida duplicados na mesma intervenção
                            for (int j = 0; j < k; j++) {
                                if (intervencoes->intervencoes[i].idsBombeiros[j] == idBomb) {
                                    printf("Erro: O ID %d já foi adicionado.\n", idBomb);
                                    aux = 1;
                                    break;
                                }
                            }
                        }

                        // Valida Estado (se está disponível)
                        if (aux == 0 && idxBomb != -1) {
                            if (bombeiros->bombeiros[idxBomb].estado != EB_DISPONIVEL) {
                                printf("ERRO: O bombeiro %s não está Disponível.\n", bombeiros->bombeiros[idxBomb].nome);
                                aux = 1; 
                            }
                        }

                    } while (aux == 1);
                    
                    // Inserir na lista da intervenção e MUDAR ESTADO NA LISTA GERAL
                    intervencoes->intervencoes[i].idsBombeiros[k] = idBomb;
                    bombeiros->bombeiros[idxBomb].estado = EB_INTERVENCAO;
                }
                
                intervencoes->intervencoes[i].numBombeiros = qtdPedida;

            } else {
                intervencoes->intervencoes[i].numBombeiros = 0;
                intervencoes->intervencoes[i].idsBombeiros = NULL;
            }
        } else {
            printf(">> Não há bombeiros disponíveis para alocar.\n");
            intervencoes->intervencoes[i].numBombeiros = 0;
            intervencoes->intervencoes[i].idsBombeiros = NULL;
        }

    } else {
        printf("\n(Aviso: Sem bombeiros registados. Alocação ignorada.)\n");
        intervencoes->intervencoes[i].numBombeiros = 0;
        intervencoes->intervencoes[i].idsBombeiros = NULL;
    }

    // --- 4. ALOCAR EQUIPAMENTOS (Limitado aos Disponíveis) ---
    if (equipamentos != NULL && equipamentos->numEquipamentos > 0) {
        printf("\n--- Alocar Equipamentos ---\n");
        listarEquipamentos(*equipamentos);
        
        int eqDisponiveis = 0;
        for(int k=0; k < equipamentos->numEquipamentos; k++){
            if(equipamentos->equipamentos[k].estado == EQ_DISPONIVEL) eqDisponiveis++;
        }
        printf(">> Total de Equipamentos Disponíveis: %d\n", eqDisponiveis);

        if (eqDisponiveis > 0) {
            int qtdPedida = obterInteiro(0, eqDisponiveis, "Quantos equipamentos quer alocar? ");
            
            if (qtdPedida > 0) {
                // Aloca array dinâmico interno para guardar os IDs
                intervencoes->intervencoes[i].idsEquipamentos = (int*) malloc(qtdPedida * sizeof(int));
                
                for (int k = 0; k < qtdPedida; k++) {
                    int idEquip, aux;
                    int idxEquip = -1;

                    do {
                        aux = 0;
                        printf("Equipamento %d/%d: ", k+1, qtdPedida);
                        idEquip = obterInteiro(0, MAX_INT, "ID do Equipamento: ");

                        idxEquip = procurarEquipamento(*equipamentos, idEquip);

                        if(idxEquip == -1){
                            printf("Aviso: Equipamento com ID %d não encontrado.\n", idEquip);
                            aux = 1;
                        } else {
                            for (int j = 0; j < k; j++) {
                                if (intervencoes->intervencoes[i].idsEquipamentos[j] == idEquip) {
                                    printf("Erro: O ID %d já foi adicionado.\n", idEquip);
                                    aux = 1;
                                    break;
                                }
                            }
                        }

                        if (aux == 0 && idxEquip != -1) {
                            if (equipamentos->equipamentos[idxEquip].estado != EQ_DISPONIVEL) {
                                printf("ERRO: O equipamento %s não está Disponível.\n", equipamentos->equipamentos[idxEquip].nome);
                                aux = 1;
                            }
                        }

                    } while (aux == 1);
                    
                    // Inserir na lista da intervenção e MUDAR ESTADO NA LISTA GERAL
                    intervencoes->intervencoes[i].idsEquipamentos[k] = idEquip;
                    equipamentos->equipamentos[idxEquip].estado = EQ_EM_USO;
                }

                intervencoes->intervencoes[i].numEquipamentos = qtdPedida;

            } else {
                intervencoes->intervencoes[i].numEquipamentos = 0;
                intervencoes->intervencoes[i].idsEquipamentos = NULL;
            }
        } else {
            printf(">> Não há equipamentos disponíveis para alocar.\n");
            intervencoes->intervencoes[i].numEquipamentos = 0;
            intervencoes->intervencoes[i].idsEquipamentos = NULL;
        }

    } else {
        printf("\n(Aviso: Sem equipamentos registados. Alocação ignorada.)\n");
        intervencoes->intervencoes[i].numEquipamentos = 0;
        intervencoes->intervencoes[i].idsEquipamentos = NULL;
    }

    // --- 5. DATAS ---
    printf("\n--- Data de Início ---\n");
    intervencoes->intervencoes[i].dataInicio.dia = obterInteiro(1, 31, "Dia: ");
    intervencoes->intervencoes[i].dataInicio.mes = obterInteiro(1, 12, "Mês: ");
    intervencoes->intervencoes[i].dataInicio.ano = obterInteiro(2000, 2100, "Ano: ");
    printf("\n--- Hora de Início ---\n");
    intervencoes->intervencoes[i].horaInicio.horas = obterInteiro(0, 23, "Horas: ");
    intervencoes->intervencoes[i].horaInicio.minutos = obterInteiro(0, 59, "Minutos: ");

    intervencoes->intervencoes[i].dataFim = (Data){0, 0, 0};
    intervencoes->intervencoes[i].horaFim = (Hora){0, 0};

    intervencoes->numIntervencoes++;
    printf("Intervenção registada com sucesso!\n");
}

/** * @brief Liberta toda a memória das intervenções.
 * * IMPORTANTE: Como cada intervenção tem arrays dinâmicos internos (IDs de 
 * bombeiros e IDs de equipamentos), é necessário libertar esses arrays num ciclo 
 * antes de libertar o array principal de intervenções.
 */
void libertarMemIntervencoes(Intervencoes *intervencoes) {
    if (intervencoes->intervencoes != NULL) {
        for (int i = 0; i < intervencoes->numIntervencoes; i++) {
            if (intervencoes->intervencoes[i].idsBombeiros)
                free(intervencoes->intervencoes[i].idsBombeiros);
            if (intervencoes->intervencoes[i].idsEquipamentos)
                free(intervencoes->intervencoes[i].idsEquipamentos);
        }
        if (intervencoes->intervencoes)
            free(intervencoes->intervencoes);
        intervencoes->intervencoes = NULL;
    }
    intervencoes->numIntervencoes = 0;
    intervencoes->totalIntervencoes = 0;
}

/** @brief Imprime os detalhes de uma intervenção, incluindo recursos alocados. */
void imprimirIntervencao(Intervencao intervencao) {
    printf("\n========================================");
    printf("\nID Intervenção: %d", intervencao.id);
    printf("\nID Ocorrência Associada: %d", intervencao.idOcorrencia);
    printf("\nEstado: "); imprimirEstadoIntervencao(intervencao.estado);
    
    printf("\n\n-- Recursos --");
    printf("\nBombeiros alocados: %d", intervencao.numBombeiros);
    if(intervencao.numBombeiros > 0) {
        printf(" (IDs: ");
        for(int k=0; k<intervencao.numBombeiros; k++) printf("%d ", intervencao.idsBombeiros[k]);
        printf(")");
    }

    printf("\nEquipamentos alocados: %d", intervencao.numEquipamentos);
    if(intervencao.numEquipamentos > 0) {
        printf(" (IDs: ");
        for(int k=0; k<intervencao.numEquipamentos; k++) printf("%d ", intervencao.idsEquipamentos[k]);
        printf(")");
    }

    printf("\n\nInício: %02d/%02d/%d às %02d:%02d", 
           intervencao.dataInicio.dia, intervencao.dataInicio.mes, intervencao.dataInicio.ano,
           intervencao.horaInicio.horas, intervencao.horaInicio.minutos);

    if (intervencao.estado == INT_CONCLUIDA) {
        printf("\nFim:    %02d/%02d/%d às %02d:%02d", 
               intervencao.dataFim.dia, intervencao.dataFim.mes, intervencao.dataFim.ano,
               intervencao.horaFim.horas, intervencao.horaFim.minutos);
    }
    printf("\n========================================\n");
}

/** @brief Lista todas as intervenções registadas. */
void listarIntervencoes(Intervencoes intervencoes) {
    if (intervencoes.numIntervencoes > 0) {
        for (int i = 0; i < intervencoes.numIntervencoes; i++) {
            imprimirIntervencao(intervencoes.intervencoes[i]);
        }
    } else {
        printf("Não existem intervenções registadas.\n");
    }
}



/** * @brief Atualiza dados e gere o ciclo de vida da intervenção.
 * * Lógica de Conclusão:
 * Quando o utilizador altera o estado para 'INT_CONCLUIDA':
 * 1. O sistema pede a data de fim.
 * 2. Percorre a lista de bombeiros alocados a esta intervenção e altera o seu estado 
 * na lista geral de 'EM_INTERVENCAO' para 'DISPONIVEL'.
 * 3. Faz o mesmo para os equipamentos (volta para 'DISPONIVEL').
 * 4. Fecha automaticamente a Ocorrência associada (passa para 'CONCLUIDA').
 */
void atualizarDadosIntervencao(Intervencao *intervencao, Bombeiros *bombeiros, Ocorrencias *ocorrencias, Equipamentos *equipamentos) {
    int escolha;

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Estado\n");
        printf("2- Data Início\n");
        if (intervencao->estado == INT_CONCLUIDA) printf("3- Data Fim\n");
        printf("0- Voltar\n");
        escolha = obterInteiro(0, 3, "\nEscolha uma opção: ");
        
        switch (escolha) {
            case 0:
                break;
            case 1:
                printf("\nEstados:\n0 - Planeamento\n1 - Em Execução\n2 - Concluída\n");
                EstadoIntervencao novoEstado = (EstadoIntervencao)obterInteiro(0, 2, "Novo Estado: ");
                
                // Se mudar para CONCLUIDA (Lógica de libertação de recursos)
                if (novoEstado == INT_CONCLUIDA && intervencao->estado != INT_CONCLUIDA) {
                    
                    // 1. PEDIR DATAS
                    printf("\n--- Data de Fim ---\n");
                    intervencao->dataFim.dia = obterInteiro(1, 31, "Dia: ");
                    intervencao->dataFim.mes = obterInteiro(1, 12, "Mês: ");
                    intervencao->dataFim.ano = obterInteiro(2000, 2100, "Ano: ");
                    printf("\n--- Hora de Fim ---\n");
                    intervencao->horaFim.horas = obterInteiro(0, 23, "Horas: ");
                    intervencao->horaFim.minutos = obterInteiro(0, 59, "Minutos: ");
                    
                    // 2. ATUALIZAR ESTADO
                    intervencao->estado = INT_CONCLUIDA;

                    // 3. LIBERTAR BOMBEIROS (Devolve à disponibilidade)
                    if (intervencao->idsBombeiros != NULL && bombeiros != NULL) {
                        for (int k = 0; k < intervencao->numBombeiros; k++) {
                            int idBomb = intervencao->idsBombeiros[k];
                            int idx = procurarBombeiro(*bombeiros, idBomb);
                            
                            if (idx != -1) {
                                bombeiros->bombeiros[idx].estado = EB_DISPONIVEL;
                            }
                        }
                    }

                    // 4. LIBERTAR EQUIPAMENTOS (Devolve à disponibilidade)
                    if (intervencao->idsEquipamentos != NULL && equipamentos != NULL) {
                        for (int k = 0; k < intervencao->numEquipamentos; k++) {
                            int idEq = intervencao->idsEquipamentos[k];
                            int idx = procurarEquipamento(*equipamentos, idEq);
                            
                            if (idx != -1) {
                                equipamentos->equipamentos[idx].estado = EQ_DISPONIVEL;
                            }
                        }
                    }

                    // 5. FECHAR OCORRÊNCIA AUTOMATICAMENTE
                    if (ocorrencias != NULL) {
                        int idxOcc = procurarOcorrencia(*ocorrencias, intervencao->idOcorrencia);
                        if (idxOcc != -1) {
                            ocorrencias->ocorrencias[idxOcc].estado = OCORR_CONCLUIDA;
                        }
                    }

                } else {
                    intervencao->estado = novoEstado;
                }
                break;
            case 2:
                printf(">> Nova Data de Início:\n");
                intervencao->dataInicio.dia = obterInteiro(1, 31, "Dia: ");
                intervencao->dataInicio.mes = obterInteiro(1, 12, "Mês: ");
                intervencao->dataInicio.ano = obterInteiro(2000, 2100, "Ano: ");
                printf(">> Nova Hora de Início:\n");
                intervencao->horaInicio.horas = obterInteiro(0, 23, "Horas: ");
                intervencao->horaInicio.minutos = obterInteiro(0, 59, "Minutos: ");
                break;
            case 3:
                printf(">> Nova Data de Fim:\n");
                intervencao->dataFim.dia = obterInteiro(1, 31, "Dia: ");
                intervencao->dataFim.mes = obterInteiro(1, 12, "Mês: ");
                intervencao->dataFim.ano = obterInteiro(2000, 2100, "Ano: ");
                printf(">> Nova Hora de Fim:\n");
                intervencao->horaFim.horas = obterInteiro(0, 23, "Horas: ");
                intervencao->horaFim.minutos = obterInteiro(0, 59, "Minutos: ");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (escolha != 0);
}

/** @brief Procura a intervenção e inicia o menu de edição. */
void editarIntervencao(Intervencoes *intervencoes, Bombeiros *bombeiros, Ocorrencias *ocorrencias, Equipamentos *equipamentos) {
    listarIntervencoes(*intervencoes);
    printf("Editar dados da intervenção:\n");
    
    int id = obterInteiro(0, MAX_INT, "Insira o ID da intervenção a alterar: ");
    int idx = procurarIntervencao(*intervencoes, id);

    if (idx != -1) {
        imprimirIntervencao(intervencoes->intervencoes[idx]);
        // Passa todas as listas para a função auxiliar para permitir libertação de recursos
        atualizarDadosIntervencao(&intervencoes->intervencoes[idx], bombeiros, ocorrencias, equipamentos);
        printf("Intervenção atualizada com sucesso!\n");
    } else {
        printf("Intervenção não existe!!\n");
    }
}

/** * @brief Elimina uma intervenção.
 * * Liberta os arrays dinâmicos internos (bombeiros e equipamentos) antes de 
 * remover a intervenção do array principal e reorganizar a lista.
 */
void eliminarIntervencao(Intervencoes *intervencoes) {
    int id = obterInteiro(0, MAX_INT, "ID a eliminar: ");
    int idx = procurarIntervencao(*intervencoes, id);

    if (idx != -1) {
        if (intervencoes->intervencoes[idx].idsBombeiros)
            free(intervencoes->intervencoes[idx].idsBombeiros);
        if (intervencoes->intervencoes[idx].idsEquipamentos) 
            free(intervencoes->intervencoes[idx].idsEquipamentos);

        for (int i = idx; i < intervencoes->numIntervencoes - 1; i++) {
            intervencoes->intervencoes[i] = intervencoes->intervencoes[i+1];
        }
        intervencoes->numIntervencoes--;
        printf("Eliminada com sucesso.\n");
    } else {
        printf("Não encontrada.\n");
    }
}

// ------ FICHEIROS ------

/** * @brief Carrega dados das intervenções (incluindo arrays aninhados).
 * * Lógica de Desserialização Complexa:
 * 1. Lê os contadores principais.
 * 2. Para cada intervenção, lê os dados básicos.
 * 3. Lê o contador de bombeiros alocados (`numBombeiros`).
 * 4. Se `numBombeiros > 0`, aloca memória (malloc) para o array `idsBombeiros` 
 * e lê os IDs do ficheiro.
 * 5. Repete o processo para os equipamentos.
 */
void carregarIntervencoes(Intervencoes *intervencoes) {
    FILE *ficheiro = fopen("data/intervencoes.bin", "rb");
    
    if (ficheiro == NULL) {
        logMsg("Ficheiro 'intervencoes.bin' não foi encontrado. A iniciar a lista vazia.");
        intervencoes->numIntervencoes = 0;
        intervencoes->totalIntervencoes = 5;
        intervencoes->intervencoes = (Intervencao*) malloc(intervencoes->totalIntervencoes * sizeof(Intervencao));
        return;
    }

    fread(&intervencoes->totalIntervencoes, sizeof(int), 1, ficheiro);
    fread(&intervencoes->numIntervencoes, sizeof(int), 1, ficheiro);

    if (intervencoes->numIntervencoes == 0) {
        intervencoes->totalIntervencoes = 5; 
        intervencoes->intervencoes = (Intervencao*) malloc(intervencoes->totalIntervencoes * sizeof(Intervencao));
        fclose(ficheiro);
        return;
    }

    intervencoes->intervencoes = (Intervencao*) malloc(intervencoes->totalIntervencoes * sizeof(Intervencao));

    for (int i = 0; i < intervencoes->numIntervencoes; i++) {
        fread(&intervencoes->intervencoes[i].id, sizeof(int), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].idOcorrencia, sizeof(int), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].estado, sizeof(EstadoIntervencao), 1, ficheiro);
        
        fread(&intervencoes->intervencoes[i].dataInicio, sizeof(Data), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].horaInicio, sizeof(Hora), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].dataFim, sizeof(Data), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].horaFim, sizeof(Hora), 1, ficheiro);

        // Carregar Array de Bombeiros Aninhado
        fread(&intervencoes->intervencoes[i].numBombeiros, sizeof(int), 1, ficheiro);
        if (intervencoes->intervencoes[i].numBombeiros > 0) {
            intervencoes->intervencoes[i].idsBombeiros = (int*) malloc(intervencoes->intervencoes[i].numBombeiros * sizeof(int));
            fread(intervencoes->intervencoes[i].idsBombeiros, sizeof(int), intervencoes->intervencoes[i].numBombeiros, ficheiro);
        } else {
            intervencoes->intervencoes[i].idsBombeiros = NULL;
        }

        // Carregar Array de Equipamentos Aninhado
        fread(&intervencoes->intervencoes[i].numEquipamentos, sizeof(int), 1, ficheiro);
        if (intervencoes->intervencoes[i].numEquipamentos > 0) {
            intervencoes->intervencoes[i].idsEquipamentos = (int*) malloc(intervencoes->intervencoes[i].numEquipamentos * sizeof(int));
            fread(intervencoes->intervencoes[i].idsEquipamentos, sizeof(int), intervencoes->intervencoes[i].numEquipamentos, ficheiro);
        } else {
            intervencoes->intervencoes[i].idsEquipamentos = NULL;
        }
    }
    fclose(ficheiro);
    logMsg("Intervenções carregadas com sucesso do ficheiro.");
}

/** * @brief Guarda dados das intervenções.
 * * Lógica de Serialização:
 * Escreve os dados primitivos e, para os arrays dinâmicos internos (bombeiros e equipamentos), 
 * escreve primeiro o tamanho do array seguido dos próprios elementos (IDs), 
 * garantindo a integridade dos dados aninhados.
 */
void guardarIntervencoes(Intervencoes *intervencoes) {
    FILE *ficheiro = fopen("data/intervencoes.bin", "wb");
    if (ficheiro == NULL) { 
        printf("\nErro ao criar ficheiro 'intervencoes.bin'.\n");
        logMsg("Erro ao criar ficheiro 'intervencoes.bin'.");
        return; 
    }

    fwrite(&intervencoes->totalIntervencoes, sizeof(int), 1, ficheiro);
    fwrite(&intervencoes->numIntervencoes, sizeof(int), 1, ficheiro);

    for (int i = 0; i < intervencoes->numIntervencoes; i++) {
        fwrite(&intervencoes->intervencoes[i].id, sizeof(int), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].idOcorrencia, sizeof(int), 1, ficheiro); 
        fwrite(&intervencoes->intervencoes[i].estado, sizeof(EstadoIntervencao), 1, ficheiro);
        
        fwrite(&intervencoes->intervencoes[i].dataInicio, sizeof(Data), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].horaInicio, sizeof(Hora), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].dataFim, sizeof(Data), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].horaFim, sizeof(Hora), 1, ficheiro);

        // Guardar Array de Bombeiros
        fwrite(&intervencoes->intervencoes[i].numBombeiros, sizeof(int), 1, ficheiro);
        if (intervencoes->intervencoes[i].numBombeiros > 0) {
            fwrite(intervencoes->intervencoes[i].idsBombeiros, sizeof(int), intervencoes->intervencoes[i].numBombeiros, ficheiro);
        }

        // Guardar Array de Equipamentos
        fwrite(&intervencoes->intervencoes[i].numEquipamentos, sizeof(int), 1, ficheiro);
        if (intervencoes->intervencoes[i].numEquipamentos > 0) {
            fwrite(intervencoes->intervencoes[i].idsEquipamentos, sizeof(int), intervencoes->intervencoes[i].numEquipamentos, ficheiro);
        }
    }
    fclose(ficheiro);
    logMsg("Intervenções guardadas com sucesso no ficheiro.");
}