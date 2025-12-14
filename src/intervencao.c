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

void imprimirEstadoIntervencao(EstadoIntervencao estado) {
    switch (estado) {
        case INT_PLANEAMENTO:
            printf("Planeamento"); 
            break;
        case INT_EXECUCAO:
            printf("Em Execução"); 
            break;
        case INT_CONCLUIDA:
            printf("Concluída"); 
            break;
        default:    
            printf("Desconhecido");
            break;
    }
}

int procurarIntervencao(Intervencoes intervencoes, int id) {
    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        if (intervencoes.intervencoes[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarIntervencao(Intervencoes *intervencoes, Ocorrencias *ocorrencias, Bombeiros *bombeiros, Equipamentos *equipamentos) {
    
    // 1. VALIDAÇÃO CRÍTICA (Apenas Ocorrências são estritamente obrigatórias)
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

    // Verificar memória da lista de intervenções
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


    // --- 3. ALOCAR BOMBEIROS (OPCIONAL) ---
    if (bombeiros != NULL && bombeiros->numBombeiros > 0) {
        printf("\n--- Alocar Bombeiros ---\n");
        listarBombeiros(*bombeiros);
        
        intervencoes->intervencoes[i].numBombeiros = obterInteiro(0, bombeiros->numBombeiros, "Quantos bombeiros quer alocar? ");
        
        if (intervencoes->intervencoes[i].numBombeiros > 0) {
            intervencoes->intervencoes[i].idsBombeiros = (int*) malloc(intervencoes->intervencoes[i].numBombeiros * sizeof(int));
            
            for (int k = 0; k < intervencoes->intervencoes[i].numBombeiros; k++) {
                int idBomb, aux;
                do {
                    aux = 0;
                    printf("Bombeiro %d/%d: ", k+1, intervencoes->intervencoes[i].numBombeiros);
                    idBomb = obterInteiro(0, MAX_INT, "ID do Bombeiro: ");
                    
                    if(procurarBombeiro(*bombeiros, idBomb) == -1){
                        printf("Aviso: Bombeiro com ID %d não encontrado.\n", idBomb);
                        aux = 1;
                    } 
                    // Verificação de duplicados
                    else {
                        for (int j = 0; j < k; j++) {
                            if (intervencoes->intervencoes[i].idsBombeiros[j] == idBomb) {
                                printf("Erro: O ID %d já foi adicionado.\n", idBomb);
                                aux = 1;
                                break;
                            }
                        }
                    }
                } while (aux == 1);
                intervencoes->intervencoes[i].idsBombeiros[k] = idBomb;
            }
        } else {
            intervencoes->intervencoes[i].idsBombeiros = NULL;
        }
    } else {
        printf("\n(Aviso: Sem bombeiros registados. Alocação ignorada.)\n");
        intervencoes->intervencoes[i].numBombeiros = 0;
        intervencoes->intervencoes[i].idsBombeiros = NULL;
    }


    // --- 4. ALOCAR EQUIPAMENTOS (OPCIONAL) ---
    if (equipamentos != NULL && equipamentos->numEquipamentos > 0) {
        printf("\n--- Alocar Equipamentos ---\n");
        listarEquipamentos(*equipamentos);
        
        intervencoes->intervencoes[i].numEquipamentos = obterInteiro(0, equipamentos->numEquipamentos, "Quantos equipamentos quer alocar? ");
        
        if (intervencoes->intervencoes[i].numEquipamentos > 0) {
            intervencoes->intervencoes[i].idsEquipamentos = (int*) malloc(intervencoes->intervencoes[i].numEquipamentos * sizeof(int));
            
             for (int k = 0; k < intervencoes->intervencoes[i].numEquipamentos; k++) {
                int idEquip, aux;
                do {
                    aux = 0;
                    printf("Equipamento %d/%d: ", k+1, intervencoes->intervencoes[i].numEquipamentos);
                    idEquip = obterInteiro(0, MAX_INT, "ID do Equipamento: ");
                    
                    if(procurarEquipamento(*equipamentos, idEquip) == -1){
                        printf("Aviso: Equipamento com ID %d não encontrado.\n", idEquip);
                        aux = 1;
                    } 
                    // Verificação de duplicados
                    else {
                        for (int j = 0; j < k; j++) {
                            if (intervencoes->intervencoes[i].idsEquipamentos[j] == idEquip) {
                                printf("Erro: O ID %d já foi adicionado.\n", idEquip);
                                aux = 1;
                                break;
                            }
                        }
                    }
                } while (aux == 1);
                intervencoes->intervencoes[i].idsEquipamentos[k] = idEquip;
            }

        } else {
            intervencoes->intervencoes[i].idsEquipamentos = NULL;
        }
    } else {
        // Se não houver equipamentos, não faz mal, continua!
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

void libertarMemIntervencoes(Intervencoes *intervencoes) {
    if (intervencoes->intervencoes != NULL) {
        for (int i = 0; i < intervencoes->numIntervencoes; i++) {
            free(intervencoes->intervencoes[i].idsBombeiros);
            free(intervencoes->intervencoes[i].idsEquipamentos);
        }
        free(intervencoes->intervencoes);
        intervencoes->intervencoes = NULL;
    }
    intervencoes->numIntervencoes = 0;
    intervencoes->totalIntervencoes = 0;
}

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

void listarIntervencoes(Intervencoes intervencoes) {
    if (intervencoes.numIntervencoes > 0) {
        for (int i = 0; i < intervencoes.numIntervencoes; i++) {
            imprimirIntervencao(intervencoes.intervencoes[i]);
        }
    } else {
        printf("Não existem intervenções registadas.\n");
    }
}

void atualizarDadosIntervencao(Intervencao *intervencao) {
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
                intervencao->estado = (EstadoIntervencao)obterInteiro(0, 2, "Novo Estado: ");
                if (intervencao->estado == INT_CONCLUIDA) {
                    printf("\n--- Data de Fim ---\n");
                    intervencao->dataFim.dia = obterInteiro(1, 31, "Dia: ");
                    intervencao->dataFim.mes = obterInteiro(1, 12, "Mês: ");
                    intervencao->dataFim.ano = obterInteiro(2000, 2100, "Ano: ");
                    printf("\n--- Hora de Fim ---\n");
                    intervencao->horaFim.horas = obterInteiro(0, 23, "Horas: ");
                    intervencao->horaFim.minutos = obterInteiro(0, 59, "Minutos: ");
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

void editarIntervencao(Intervencoes *intervencoes) {
    listarIntervencoes(*intervencoes);
    printf("Editar dados da intervenção:\n");
    
    int id = obterInteiro(0, MAX_INT, "Insira o ID da intervenção a alterar: ");
    int idx = procurarIntervencao(*intervencoes, id);

    if (idx != -1) {
        imprimirIntervencao(intervencoes->intervencoes[idx]);
        atualizarDadosIntervencao(&intervencoes->intervencoes[idx]);
        printf("Intervenção atualizada com sucesso!\n");
    } else {
        printf("Intervenção não existe!!\n");
    }
}

void eliminarIntervencao(Intervencoes *intervencoes) {
    int id = obterInteiro(0, MAX_INT, "ID a eliminar: ");
    int idx = procurarIntervencao(*intervencoes, id);

    if (idx != -1) {
        // Libertar sub-arrays antes de apagar
        free(intervencoes->intervencoes[idx].idsBombeiros);
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

// --- FICHEIROS ---


void readIntervencoes(Intervencoes *intervencoes) {
    FILE *ficheiro = fopen("data/intervencoes.bin", "rb");
    
    // Inicialização segura (como explicado anteriormente)
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
        intervencoes->totalIntervencoes = 5; // Garante tamanho mínimo
        intervencoes->intervencoes = (Intervencao*) malloc(intervencoes->totalIntervencoes * sizeof(Intervencao));
        fclose(ficheiro);
        return;
    }

    intervencoes->intervencoes = (Intervencao*) malloc(intervencoes->totalIntervencoes * sizeof(Intervencao));

    for (int i = 0; i < intervencoes->numIntervencoes; i++) {
        // Dados estáticos
        fread(&intervencoes->intervencoes[i].id, sizeof(int), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].idOcorrencia, sizeof(int), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].estado, sizeof(EstadoIntervencao), 1, ficheiro);
        
        // Datas
        fread(&intervencoes->intervencoes[i].dataInicio, sizeof(Data), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].horaInicio, sizeof(Hora), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].dataFim, sizeof(Data), 1, ficheiro);
        fread(&intervencoes->intervencoes[i].horaFim, sizeof(Hora), 1, ficheiro);

        // Array Bombeiros
        fread(&intervencoes->intervencoes[i].numBombeiros, sizeof(int), 1, ficheiro);
        if (intervencoes->intervencoes[i].numBombeiros > 0) {
            intervencoes->intervencoes[i].idsBombeiros = (int*) malloc(intervencoes->intervencoes[i].numBombeiros * sizeof(int));
            fread(intervencoes->intervencoes[i].idsBombeiros, sizeof(int), intervencoes->intervencoes[i].numBombeiros, ficheiro);
        } else {
            intervencoes->intervencoes[i].idsBombeiros = NULL;
        }

        // Array Equipamentos
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

void writeIntervencoes(Intervencoes *intervencoes) {
    FILE *ficheiro = fopen("data/intervencoes.bin", "wb");
    if (ficheiro == NULL) { 
        printf("\nErro ao criar ficheiro 'intervencoes.bin'.\n");
        logMsg("Erro ao criar ficheiro 'intervencoes.bin'.");
        return; 
    }

    fwrite(&intervencoes->totalIntervencoes, sizeof(int), 1, ficheiro);
    fwrite(&intervencoes->numIntervencoes, sizeof(int), 1, ficheiro);

    for (int i = 0; i < intervencoes->numIntervencoes; i++) {
        // Dados estáticos
        fwrite(&intervencoes->intervencoes[i].id, sizeof(int), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].idOcorrencia, sizeof(int), 1, ficheiro); // Guarda ID, não ponteiro
        fwrite(&intervencoes->intervencoes[i].estado, sizeof(EstadoIntervencao), 1, ficheiro);
        
        // Datas
        fwrite(&intervencoes->intervencoes[i].dataInicio, sizeof(Data), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].horaInicio, sizeof(Hora), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].dataFim, sizeof(Data), 1, ficheiro);
        fwrite(&intervencoes->intervencoes[i].horaFim, sizeof(Hora), 1, ficheiro);

        // Array Dinâmico Bombeiros
        fwrite(&intervencoes->intervencoes[i].numBombeiros, sizeof(int), 1, ficheiro);
        if (intervencoes->intervencoes[i].numBombeiros > 0) {
            fwrite(intervencoes->intervencoes[i].idsBombeiros, sizeof(int), intervencoes->intervencoes[i].numBombeiros, ficheiro);
        }

        // Array Dinâmico Equipamentos
        fwrite(&intervencoes->intervencoes[i].numEquipamentos, sizeof(int), 1, ficheiro);
        if (intervencoes->intervencoes[i].numEquipamentos > 0) {
            fwrite(intervencoes->intervencoes[i].idsEquipamentos, sizeof(int), intervencoes->intervencoes[i].numEquipamentos, ficheiro);
        }
    }
    fclose(ficheiro);
    logMsg("Intervenções guardadas com sucesso no ficheiro.");
}