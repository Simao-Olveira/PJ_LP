/**
 * @file gestao_ocorrencia.c
 * @brief Implementação das funções de gestão de ocorrências.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ocorrencia.h"
#include "gestaoOcorrencia.h"
#include "enums.h"
#include "input.h"
#include "log.h"

/** @brief Converte o tipo de ocorrência em texto para impressão. */
void imprimirTipoOcorrencia(TipoOcorrencia tipo) {
    switch (tipo) {
        case FLORESTAL:  printf("Florestal"); break;
        case URBANO:     printf("Urbano"); break;
        case INDUSTRIAL: printf("Industrial"); break;
        default:         printf("Outro"); break;
    }
}

/** @brief Converte a prioridade em texto para impressão. */
void imprimirPrioridade(Prioridade prioridade) {
    switch (prioridade) {
        case BAIXA:  printf("Baixa"); break;
        case NORMAL: printf("Normal"); break;
        case ALTA:   printf("Alta"); break;
        default:     printf("Indefinida"); break;
    }
}

/** @brief Converte o estado da ocorrência em texto para impressão. */
void imprimirEstadoOcorrencia(EstadoOcorrencia estado) {
    switch (estado) {
        case OCORR_REPORTADA:   printf("Reportada"); break;
        case OCORR_INTERVENCAO: printf("Em Intervenção"); break;
        case OCORR_CONCLUIDA:   printf("Concluída"); break;
        default:                printf("Desconhecido"); break;
    }
}

/** * @brief Procura uma ocorrência pelo ID.
 * * Percorre o array de ocorrências até encontrar o ID correspondente.
 * @return O índice no array ou -1 se não encontrar.
 */
int procurarOcorrencia(Ocorrencias ocorrencias, int id) {
    for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
        if (ocorrencias.ocorrencias[i].id == id) {
            return i;
        }
    }
    return -1;
}

/** * @brief Adiciona uma nova ocorrência ao sistema.
 * * Gera um novo ID sequencial e verifica se existe espaço no array dinâmico, 
 * redimensionando-o se necessário. Aloca memória específica para a string 
 * 'local' e regista a data/hora atuais e o estado inicial como 'Reportada'.
 */
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
        
        // Verifica capacidade e redimensiona
        if ((*ocorrencias).totalOcorrencias == (*ocorrencias).numOcorrencias) {
            (*ocorrencias).totalOcorrencias += 3;
            Ocorrencia *temp = (Ocorrencia*) realloc((*ocorrencias).ocorrencias, ((*ocorrencias).totalOcorrencias) * sizeof(Ocorrencia));
            if (temp == NULL) {
                printf("Erro de memória.\n");
                return;
            }
            (*ocorrencias).ocorrencias = temp;
        }

        int i = (*ocorrencias).numOcorrencias;
        (*ocorrencias).ocorrencias[i].id = id;

        // Alocação dinâmica da string Local
        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Local da ocorrência: ");
        (*ocorrencias).ocorrencias[i].local = malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*ocorrencias).ocorrencias[i].local != NULL) {
            strcpy((*ocorrencias).ocorrencias[i].local, buffer);
        }

        printf("\nTipo de Ocorrência:\n0-Florestal\n1-Urbano\n2-Industrial\n");
        (*ocorrencias).ocorrencias[i].tipo = (TipoOcorrencia) obterInteiro(0, 2, "Escolha: ");

        printf("\nPrioridade:\n0-Baixa\n1-Normal\n2-Alta\n");
        (*ocorrencias).ocorrencias[i].prioridade = (Prioridade) obterInteiro(0, 2, "Escolha: ");

        (*ocorrencias).ocorrencias[i].estado = OCORR_REPORTADA;

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

/** * @brief Liberta toda a memória associada às ocorrências.
 * * Itera sobre o array para libertar a memória alocada para a string 'local' 
 * de cada ocorrência antes de libertar o ponteiro principal.
 */
void libertarMemOcorrencias(Ocorrencias *ocorrencias) {
    if (ocorrencias->ocorrencias != NULL) {
        for (int i = 0; i < ocorrencias->numOcorrencias; i++) {
            if (ocorrencias->ocorrencias[i].local)
                free(ocorrencias->ocorrencias[i].local);
        }
        if (ocorrencias->ocorrencias)
            free(ocorrencias->ocorrencias);
        ocorrencias->ocorrencias = NULL;
    }
    ocorrencias->numOcorrencias = 0;
    ocorrencias->totalOcorrencias = 0;
}

/** @brief Imprime os detalhes de uma única ocorrência. */
void imprimirOcorrencia(Ocorrencia oc) {
    printf("\n========================================");
    printf("\nID: %d", oc.id);
    printf("\nLocal: %s", oc.local);
    printf("\nTipo: "); imprimirTipoOcorrencia(oc.tipo);
    printf("\nPrioridade: "); imprimirPrioridade(oc.prioridade);
    printf("\nEstado: "); imprimirEstadoOcorrencia(oc.estado);
    printf("\nData: %02d/%02d/%d", oc.dataRegisto.dia, oc.dataRegisto.mes, oc.dataRegisto.ano);
    printf("\nHora: %02d:%02d", oc.horaRegisto.horas, oc.horaRegisto.minutos);
    printf("\n========================================\n");
}

/** @brief Lista todas as ocorrências registadas. */
void listarOcorrencias(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias > 0) {
        for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
            imprimirOcorrencia(ocorrencias.ocorrencias[i]);
        }
    } else {
        printf("Não existem ocorrências registadas!!\n");
    }
}

/** * @brief Submenu para atualizar dados de uma ocorrência.
 * * Permite a edição de campos individuais. Ao alterar o local, a memória 
 * é realocada para se ajustar ao tamanho da nova string.
 */
void atualizarDadosOcorrencia(Ocorrencia *ocorrencia) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Local\n2- Tipo\n3- Prioridade\n4- Estado\n5- Data e Hora\n0- Voltar\n");
        escolha = obterInteiro(0, 5, "\nEscolha uma opção: ");
        
        switch (escolha) {
            case 0: break;
            case 1:
                lerString(buffer, SIZE_BUFFER, "Novo Local: ");
                ocorrencia->local = realloc(ocorrencia->local, (strlen(buffer) + 1) * sizeof (char));
                strcpy(ocorrencia->local, buffer);
                break;
            case 2:
                printf("\n0-Florestal\n1-Urbano\n2-Industrial\n");
                ocorrencia->tipo = (TipoOcorrencia)obterInteiro(0, 2, "Novo Tipo: ");
                break;
            case 3:
                printf("\n0-Baixa\n1-Normal\n2-Alta\n");
                ocorrencia->prioridade = (Prioridade)obterInteiro(0, 2, "Nova Prioridade: ");
                break;
            case 4:
                printf("\n0-Reportada\n1-Em Intervenção\n2-Concluída\n");
                ocorrencia->estado = (EstadoOcorrencia)obterInteiro(0, 2, "Novo Estado: ");
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
            default: printf("Opção inválida\n"); break;
        }
    } while (escolha != 0);
}

/** @brief Procura a ocorrência e inicia o menu de edição. */
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

/** * @brief Elimina uma ocorrência do sistema.
 * * Liberta a memória da string 'local' e reorganiza o array, movendo todos 
 * os elementos seguintes uma posição para trás (shift left) para preencher o vazio.
 */
void eliminarOcorrencia(Ocorrencias *ocorrencias) {
    int id = obterInteiro(0, MAX_INT, "Insira o ID da ocorrência a eliminar: ");
    int indice = procurarOcorrencia(*ocorrencias, id);

    if (indice != -1) {
        if (ocorrencias->ocorrencias[indice].local)
            free(ocorrencias->ocorrencias[indice].local);

        // Movimento Shift Left para manter a ordem da lista
        for (int i = indice; i < ocorrencias->numOcorrencias - 1; i++) {
            ocorrencias->ocorrencias[i] = ocorrencias->ocorrencias[i + 1];
        }

        ocorrencias->numOcorrencias--;
        printf("Ocorrência eliminada.\n");

    } else {
        printf("Ocorrência não existe!!\n");
    }
}

// ------ FICHEIROS ------

/** * @brief Carrega dados das ocorrências do ficheiro binário.
 * * Lê os contadores iniciais para alocar o array. Para cada ocorrência, 
 * lê os dados primitivos e, em seguida, lê o tamanho da string 'local' 
 * para alocar a memória exata antes de ler os caracteres.
 */
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
        ocorrencias->totalOcorrencias = 5; 
        ocorrencias->ocorrencias = (Ocorrencia*) malloc(ocorrencias->totalOcorrencias * sizeof(Ocorrencia));
        fclose(ficheiro);
        logMsg("Lista de ocorrências importada vazia.");
        return;
    }

    ocorrencias->ocorrencias = (Ocorrencia*) malloc((ocorrencias->totalOcorrencias) * sizeof(Ocorrencia));
    
    for (int i = 0; i < ocorrencias->numOcorrencias; i++) {
        fread(&ocorrencias->ocorrencias[i].id, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].tipo, sizeof(TipoOcorrencia), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].prioridade, sizeof(Prioridade), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].estado, sizeof(EstadoOcorrencia), 1, ficheiro);
        
        // Data e Hora
        fread(&ocorrencias->ocorrencias[i].dataRegisto.dia, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].dataRegisto.mes, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].dataRegisto.ano, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].horaRegisto.horas, sizeof(int), 1, ficheiro);
        fread(&ocorrencias->ocorrencias[i].horaRegisto.minutos, sizeof(int), 1, ficheiro);

        // String Dinâmica (Local)
        int Buffer;
        fread(&Buffer, sizeof(int), 1, ficheiro);
        ocorrencias->ocorrencias[i].local = (char*) malloc(sizeof(char) * (Buffer + 1));
        fread(ocorrencias->ocorrencias[i].local, sizeof(char), Buffer, ficheiro);
        ocorrencias->ocorrencias[i].local[Buffer] = '\0';
    }
    fclose(ficheiro);
    logMsg("Ocorrências carregadas com sucesso do ficheiro.");
}

/** * @brief Guarda dados das ocorrências em ficheiro binário.
 * * Escreve a estrutura em disco. Para a string 'local', guarda primeiro 
 * o tamanho em bytes seguido dos caracteres, permitindo a recuperação correta.
 */
void guardarOcorrencias(Ocorrencias *ocorrencias) {
    FILE *ficheiro = fopen("data/ocorrencias.bin", "wb");
    
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro 'ocorrencias.bin'.\n");
        logMsg("Erro ao criar ficheiro 'ocorrencias.bin'.");
        return;
    }

    fwrite(&ocorrencias->totalOcorrencias, sizeof(int), 1, ficheiro);
    fwrite(&ocorrencias->numOcorrencias, sizeof(int), 1, ficheiro);

    for (int i = 0; i < ocorrencias->numOcorrencias; i++) {
        fwrite(&ocorrencias->ocorrencias[i].id, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].tipo, sizeof(TipoOcorrencia), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].prioridade, sizeof(Prioridade), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].estado, sizeof(EstadoOcorrencia), 1, ficheiro);
        
        fwrite(&ocorrencias->ocorrencias[i].dataRegisto.dia, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].dataRegisto.mes, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].dataRegisto.ano, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].horaRegisto.horas, sizeof(int), 1, ficheiro);
        fwrite(&ocorrencias->ocorrencias[i].horaRegisto.minutos, sizeof(int), 1, ficheiro);

        int tam = strlen(ocorrencias->ocorrencias[i].local);
        fwrite(&tam, sizeof(int), 1, ficheiro);
        fwrite(ocorrencias->ocorrencias[i].local, sizeof(char), tam, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Ocorrências guardadas com sucesso no ficheiro.");
}