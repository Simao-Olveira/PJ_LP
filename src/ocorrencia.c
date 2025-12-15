#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ocorrencia.h"
#include "gestaoOcorrencia.h"
#include "enums.h"
#include "input.h"
#include "log.h"

void imprimirTipoOcorrencia(TipoOcorrencia tipo) {
    switch (tipo) {
        case FLORESTAL:
            printf("Florestal"); 
            break;
        case URBANO:
            printf("Urbano"); 
            break;
        case INDUSTRIAL:
            printf("Industrial"); 
            break;
        default:
            printf("Outro"); 
            break;
    }
}

void imprimirPrioridade(Prioridade prioridade) {
    switch (prioridade) {
        case BAIXA:
            printf("Baixa"); 
            break;
        case NORMAL:
            printf("Normal"); 
            break;
        case ALTA:
           printf("Alta"); 
            break;
        default:
            printf("Indefinida"); 
            break;
    }
}

void imprimirEstadoOcorrencia(EstadoOcorrencia estado) {
    switch (estado) {
        case OCORR_REPORTADA:
            printf("Reportada"); 
            break;
        case OCORR_INTERVENCAO:
            printf("Em Intervenção"); 
            break;
        case OCORR_CONCLUIDA:   
            printf("Concluída"); 
            break;
        default:
            printf("Desconhecido"); 
            break;
    }
}

int procurarOcorrencia(Ocorrencias ocorrencias, int id) {
    int i;
    for (i = 0; i < ocorrencias.numOcorrencias; i++) {
        if (ocorrencias.ocorrencias[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarOcorrencia(Ocorrencias *ocorrencias) {
    printf("\n--- Nova Ocorrência ---\n");

    int maiorId = 0;
    for(int i = 0; i < ocorrencias->numOcorrencias; i++) {
        if(ocorrencias->ocorrencias[i].id > maiorId) {
            maiorId = ocorrencias->ocorrencias[i].id;
        }
    }
    int id = maiorId + 1;

    if (procurarOcorrencia(*ocorrencias, id) == -1) {
        
        // Realocação de memória (aumenta de 3 em 3, por exemplo)
        if ((*ocorrencias).totalOcorrencias == (*ocorrencias).numOcorrencias) {
            (*ocorrencias).totalOcorrencias += 3;
            (*ocorrencias).ocorrencias = (Ocorrencia*) realloc((*ocorrencias).ocorrencias, ((*ocorrencias).totalOcorrencias) * sizeof(Ocorrencia));
        }

        int i = (*ocorrencias).numOcorrencias;

        (*ocorrencias).ocorrencias[i].id = id;

        // Leitura do Local
        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Local da ocorrência: ");
        (*ocorrencias).ocorrencias[i].local = malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy((*ocorrencias).ocorrencias[i].local, buffer);

        // Leitura dos Enums (Mapeia o inteiro para o Enum)
        printf("\nTipo de Ocorrência:\n0-Florestal\n1-Urbano\n2-Industrial\n");
        (*ocorrencias).ocorrencias[i].tipo = (TipoOcorrencia) obterInteiro(0, 2, "Escolha: ");

        printf("\nPrioridade:\n0-Baixa\n1-Normal\n2-Alta\n");
        (*ocorrencias).ocorrencias[i].prioridade = (Prioridade) obterInteiro(0, 2, "Escolha: ");

        (*ocorrencias).ocorrencias[i].estado = OCORR_REPORTADA;

        // Inserir Data e Hora
        printf("\n--- Data do Registo ---\n");
        (*ocorrencias).ocorrencias[i].dataRegisto.dia = obterInteiro(1, 31, "Dia: ");
        (*ocorrencias).ocorrencias[i].dataRegisto.mes = obterInteiro(1, 12, "Mês: ");
        (*ocorrencias).ocorrencias[i].dataRegisto.ano = obterInteiro(2000, 2100, "Ano: ");

        printf("\n--- Hora do Registo ---\n");
        (*ocorrencias).ocorrencias[i].horaRegisto.horas = obterInteiro(0, 23, "Horas: ");
        (*ocorrencias).ocorrencias[i].horaRegisto.minutos = obterInteiro(0, 59, "Minutos: ");

        (*ocorrencias).numOcorrencias++;
        printf("Ocorrência criada com sucesso!\n");

    } else {
        printf("Erro: Já existe uma ocorrência com esse ID!!\n");
    }
}

void libertarMemOcorrencias(Ocorrencias *ocorrencias) {
    int i;
    for (i = 0; i < ocorrencias->numOcorrencias; i++) {
        free(ocorrencias->ocorrencias[i].local);
    }
    free(ocorrencias->ocorrencias);
    ocorrencias->numOcorrencias = 0;
    ocorrencias->totalOcorrencias = 0;
}

void imprimirOcorrencia(Ocorrencia oc) {
    printf("\n========================================");
    printf("\nID: %d", oc.id);
    printf("\nLocal: %s", oc.local);
    
    printf("\nTipo: ");
    imprimirTipoOcorrencia(oc.tipo);
    
    printf("\nPrioridade: ");
    imprimirPrioridade(oc.prioridade);
    
    printf("\nEstado: ");
    imprimirEstadoOcorrencia(oc.estado);

    printf("\nData: %02d/%02d/%d", oc.dataRegisto.dia, oc.dataRegisto.mes, oc.dataRegisto.ano);
    printf("\nHora: %02d:%02d", oc.horaRegisto.horas, oc.horaRegisto.minutos);
    printf("\n========================================\n");
}

void listarOcorrencias(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias > 0) {
        for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
            imprimirOcorrencia(ocorrencias.ocorrencias[i]);
        }
    } else {
        printf("Não existem ocorrências registadas!!\n");
    }
}

void atualizarDadosOcorrencia(Ocorrencia *ocorrencia) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Local\n");
        printf("2- Tipo\n");
        printf("3- Prioridade\n");
        printf("4- Estado\n");
        printf("5- Data e Hora\n");
        printf("0- Voltar\n");
        escolha = obterInteiro(0, 5, "\nEscolha uma opção: ");
        
        switch (escolha) {
            case 0:
                break;
            case 1:
                lerString(buffer, SIZE_BUFFER, "Novo Local: ");
                ocorrencia->local = realloc(ocorrencia->local, (strlen(buffer) + 1) * sizeof (char));
                strcpy(ocorrencia->local, buffer);
                break;
            case 2:
                printf("\nTipo de Ocorrência:\n0-Florestal\n1-Urbano\n2-Industrial\n");
                ocorrencia->tipo = (TipoOcorrencia)obterInteiro(0, 2, "Escolha o novo Tipo: ");
                break;
            case 3:
                printf("\nPrioridade:\n0-Baixa\n1-Normal\n2-Alta\n");
                ocorrencia->prioridade = (Prioridade)obterInteiro(0, 2, "Escolha a nova Prioridade: ");
                break;
            case 4:
                printf("\nEstado da Ocorrência:\n0-Reportada\n1-Em Intervenção\n2-Concluída\n");
                ocorrencia->estado = (EstadoOcorrencia)obterInteiro(0, 2, "Escolha o novo Estado: ");
                break;
            case 5:
                printf(">> Nova Data\n");
                ocorrencia->dataRegisto.dia = obterInteiro(1, 31, "Dia: ");
                ocorrencia->dataRegisto.mes = obterInteiro(1, 12, "Mês: ");
                ocorrencia->dataRegisto.ano = obterInteiro(2000, 2100, "Ano: ");
                printf(">> Nova Hora\n");
                ocorrencia->horaRegisto.horas = obterInteiro(0, 23, "Horas: ");
                ocorrencia->horaRegisto.minutos = obterInteiro(0, 59, "Minutos: ");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (escolha != 0);
}

void editarOcorrencia(Ocorrencias *ocorrencias) {
    listarOcorrencias(*ocorrencias);
    printf("Editar dados da ocorrência:\n");
    int id = procurarOcorrencia(*ocorrencias, obterInteiro(0, MAX_INT, "Insira o ID da ocorrência a alterar: "));

    if (id != -1) {
        imprimirOcorrencia((*ocorrencias).ocorrencias[id]);
        atualizarDadosOcorrencia(&(*ocorrencias).ocorrencias[id]);
        printf("Ocorrência atualizada com sucesso.\n");
    } else {
        printf("Ocorrência não existe!!\n");
    }
}

void eliminarOcorrencia(Ocorrencias *ocorrencias) {
    int id = obterInteiro(0, MAX_INT, "Insira o ID da ocorrência a eliminar: ");
    int indice = procurarOcorrencia(*ocorrencias, id);

    if (indice != -1) {
        free(ocorrencias->ocorrencias[indice].local);

        if (indice != ocorrencias->numOcorrencias - 1) {
            ocorrencias->ocorrencias[indice] = ocorrencias->ocorrencias[ocorrencias->numOcorrencias - 1];
        }

        ocorrencias->numOcorrencias--;
        printf("Ocorrência eliminada.\n");

    } else {
        printf("Ocorrência não existe!!\n");
    }
}

// ------ FICHEIROS ------

void carregarOcorrencias(Ocorrencias *ocorrencias) {
    FILE *ficheiro = fopen("data/ocorrencias.bin", "rb");
    
    if (ficheiro == NULL) {
        logMsg("Ficheiro 'ocorrencias.bin' não foi encontrado. A iniciar a lista vazia.");
        ocorrencias->numOcorrencias = 0;
        ocorrencias->totalOcorrencias = 5;
        ocorrencias->ocorrencias = (Ocorrencia*) malloc(ocorrencias->totalOcorrencias * sizeof(Ocorrencia));
        return;
    }

    fread(&ocorrencias->totalOcorrencias, sizeof(int), 1, ficheiro);
    fread(&ocorrencias->numOcorrencias, sizeof(int), 1, ficheiro);

    if (ocorrencias->numOcorrencias == 0) {
        ocorrencias->totalOcorrencias = 5; // Garante tamanho mínimo
        ocorrencias->ocorrencias = (Ocorrencia*) malloc(ocorrencias->totalOcorrencias * sizeof(Ocorrencia));
        fclose(ficheiro);
        logMsg("Lista de bombeiros importada vazia.");
        return;
    }

    ocorrencias->ocorrencias = (Ocorrencia*) malloc((ocorrencias->totalOcorrencias) * sizeof(Ocorrencia));
    
    for (int i = 0; i < ocorrencias->numOcorrencias; i++) {
        fread(&ocorrencias->ocorrencias[i].id, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].tipo, sizeof(TipoOcorrencia), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].prioridade, sizeof(Prioridade), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].estado, sizeof(EstadoOcorrencia), 1, ficheiro);
        
        // Ler Data e Hora
        fread(&ocorrencias->ocorrencias[i].dataRegisto.dia, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].dataRegisto.mes, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].dataRegisto.ano, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].horaRegisto.horas, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].horaRegisto.minutos, sizeof(int), 1, ficheiro);

        // Ler String (Local)
        int Buffer;
        fread(&Buffer, sizeof(int), 1, ficheiro);
        ocorrencias->ocorrencias[i].local = (char*) malloc(sizeof(char) * (Buffer + 1));
        fread(ocorrencias->ocorrencias[i].local, sizeof(char), Buffer, ficheiro);
        ocorrencias->ocorrencias[i].local[Buffer] = '\0';
    }
    fclose(ficheiro);
    logMsg("Ocorrências carregadas com sucesso do ficheiro.");
}

void guardarOcorrencias(Ocorrencias *ocorrencias) {
    FILE *ficheiro = fopen("data/ocorrencias.bin", "wb");
    
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro 'ocorrencias.bin'.\n");
        logMsg("Erro ao criar ficheiro 'intervencoes.bin'.");
        return;
    }

    fwrite(&ocorrencias->totalOcorrencias, sizeof(int), 1, ficheiro);
    fwrite(&ocorrencias->numOcorrencias, sizeof(int), 1, ficheiro);

    for (int i = 0; i < ocorrencias->numOcorrencias; i++) {
        fwrite(&ocorrencias->ocorrencias[i].id, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].tipo, sizeof(TipoOcorrencia), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].prioridade, sizeof(Prioridade), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].estado, sizeof(EstadoOcorrencia), 1, ficheiro);
        
        // Data e Hora
        fwrite(&ocorrencias->ocorrencias[i].dataRegisto.dia, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].dataRegisto.mes, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].dataRegisto.ano, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].horaRegisto.horas, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].horaRegisto.minutos, sizeof(int), 1, ficheiro);

        // String
        int tam = strlen(ocorrencias->ocorrencias[i].local);
        fwrite(&tam, sizeof(int), 1, ficheiro);
        fwrite(ocorrencias->ocorrencias[i].local, sizeof(char), tam, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Ocorrências guardadas com sucesso no ficheiro.");
}