#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quartel.h"
#include "input.h"

// Função auxiliar para converter o Enum em texto
void imprimirTipoQuartel(TipoQuartel tipo) {
    switch (tipo) {
        case VOLUNTARIO:
            printf("Bombeiros Voluntários");
            break;
        case SAPADOR:
            printf("Companhia de Sapadores");
            break;
        case MUNICIPAL:
            printf("Bombeiros Municipais");
            break;
        default:
            printf("Desconhecido");
            break;
    }
}

int procurarQuartel(Quarteis quarteis, int id) {
    for (int i = 0; i < quarteis.numQuarteis; i++) {
        if (quarteis.quarteis[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarQuartel(Quarteis *quarteis) {
    printf("\n--- Adicionar Novo Quartel ---\n");
    int id = quarteis->numQuarteis + 1;

    if (procurarQuartel(*quarteis, id) != -1) {
        printf("Erro: Já existe um quartel com esse ID.\n");
        return;
    }

    // 1. Verificar se há espaço no array principal
    if (quarteis->numQuarteis == quarteis->totalQuarteis) {
        quarteis->totalQuarteis += 2; // Expande de 2 em 2
        Quartel *temp = (Quartel*) realloc(quarteis->quarteis, quarteis->totalQuarteis * sizeof(Quartel));
        if (temp == NULL) {
            printf("Erro crítico de memória (realloc falhou).\n");
            return;
        }
        quarteis->quarteis = temp;
    }

    // Ponteiro auxiliar para o novo quartel (para escrever menos código)
    Quartel *novo = &quarteis->quarteis[quarteis->numQuarteis];
    
    novo->id = id;

    char buffer[SIZE_BUFFER];

    // Nome
    lerString(buffer, SIZE_BUFFER, "Nome do Quartel: ");
    novo->nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char)); // Aloca tamanho exato
    strcpy(novo->nome, buffer); // Copia do buffer para a memória alocada

    // Local
    lerString(buffer, SIZE_BUFFER, "Localização: ");
    novo->local = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(novo->local, buffer);

    // 3. Outros dados
    novo->capacidade = obterInteiro(1, 1000, "Capacidade máxima de viaturas/bombeiros: ");

    printf("\nTipos de Quartel:\n0 - Voluntário\n1 - Sapador\n2 - Municipal\n");
    int tipoInput = obterInteiro(0, 2, "Selecione o tipo: ");
    novo->tipo = (TipoQuartel) tipoInput;

    quarteis->numQuarteis++;
    printf("Quartel adicionado com sucesso!\n");
}

void imprimirQuartel(Quartel q) {
    printf("\n--------------------------------");
    printf("\nID: %d", q.id);
    printf("\nNome: %s", q.nome);
    printf("\nLocal: %s", q.local);
    printf("\nCapacidade: %d", q.capacidade);
    printf("\nTipo: ");
    imprimirTipoQuartel(q.tipo);
    printf("\n--------------------------------\n");
}

void listarQuarteis(Quarteis quarteis) {
    if (quarteis.numQuarteis == 0) {
        printf("Não existem quarteis registados.\n");
    } else {
        for (int i = 0; i < quarteis.numQuarteis; i++) {
            imprimirQuartel(quarteis.quarteis[i]);
        }
    }
}

void editarQuartel(Quarteis *quarteis) {
    listarQuarteis(*quarteis);
    int id = obterInteiro(0, quarteis->numQuarteis, "Insira o ID do quartel a editar: ");
    int idx = procurarQuartel(*quarteis, id);

    if (idx == -1) {
        printf("Quartel não encontrado.\n");
        return;
    }

    Quartel *q = &quarteis->quarteis[idx];
    int opcao;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Quartel %d ---\n", q->id);
        printf("1 - Alterar Nome\n");
        printf("2 - Alterar Local\n");
        printf("3 - Alterar Capacidade\n");
        printf("4 - Alterar Tipo\n");
        printf("0 - Voltar\n");
        opcao = obterInteiro(0, 4, "Opção: ");

        switch (opcao) {
            case 1:
                lerString(buffer, SIZE_BUFFER, "Novo Nome: ");
                // Realloc ajusta o tamanho da memória preservando o ponteiro se possível
                q->nome = (char*) realloc(q->nome, (strlen(buffer) + 1) * sizeof(char));
                strcpy(q->nome, buffer);
                break;
            case 2:
                lerString(buffer, SIZE_BUFFER, "Novo Local: ");
                q->local = (char*) realloc(q->local, (strlen(buffer) + 1) * sizeof(char));
                strcpy(q->local, buffer);
                break;
            case 3:
                q->capacidade = obterInteiro(1, 1000, "Nova Capacidade: ");
                break;
            case 4:
                printf("\n0 - Voluntário | 1 - Sapador | 2 - Municipal\n");
                int novoTipo = obterInteiro(0, 2, "Novo Tipo: ");
                q->tipo = (TipoQuartel) novoTipo;
                break;
            case 0:
                break;
        }
    } while (opcao != 0);
}

void eliminarQuartel(Quarteis *quarteis) {
    listarQuarteis(*quarteis);
    int id = obterInteiro(0, MAX_INT, "Insira o ID do quartel a eliminar: ");
    int idx = procurarQuartel(*quarteis, id);

    if (idx == -1) {
        printf("Quartel não encontrado.\n");
        return;
    }

    // 1. IMPORTANTE: Libertar a memória das strings ANTES de apagar a struct
    free(quarteis->quarteis[idx].nome);
    free(quarteis->quarteis[idx].local);

    // 2. Puxar os elementos seguintes para trás
    for (int i = idx; i < quarteis->numQuarteis - 1; i++) {
        quarteis->quarteis[i] = quarteis->quarteis[i + 1];
    }

    quarteis->numQuarteis--;
    printf("Quartel eliminado com sucesso.\n");
}

void libertarMemQuarteis(Quarteis *quarteis) {
    // Liberta as strings de cada quartel individualmente
    for (int i = 0; i < quarteis->numQuarteis; i++) {
        free(quarteis->quarteis[i].nome);
        free(quarteis->quarteis[i].local);
    }
    // Liberta o array principal
    free(quarteis->quarteis);
    quarteis->quarteis = NULL;
    quarteis->numQuarteis = 0;
    quarteis->totalQuarteis = 0;
}

// ==========================================
//      GESTÃO DE FICHEIROS COM PONTEIROS
// ==========================================

void writeQuarteis(Quarteis *quarteis) {
    FILE *fp = fopen("data/quarteis.bin", "wb");
    if (fp == NULL) {
        printf("Erro ao abrir 'data/quarteis.bin' para escrita.\n");
        return;
    }

    // Escreve cabeçalho
    fwrite(&quarteis->totalQuarteis, sizeof(int), 1, fp);
    fwrite(&quarteis->numQuarteis, sizeof(int), 1, fp);

    for (int i = 0; i < quarteis->numQuarteis; i++) {
        Quartel *q = &quarteis->quarteis[i];

        // 1. Escreve dados primitivos (int, enum)
        fwrite(&q->id, sizeof(int), 1, fp);
        fwrite(&q->capacidade, sizeof(int), 1, fp);
        fwrite(&q->tipo, sizeof(TipoQuartel), 1, fp);

        // 2. Escreve NOME (Tamanho + Conteúdo)
        int lenNome = strlen(q->nome) + 1; // +1 para incluir o \0
        fwrite(&lenNome, sizeof(int), 1, fp);
        fwrite(q->nome, sizeof(char), lenNome, fp);

        // 3. Escreve LOCAL (Tamanho + Conteúdo)
        int lenLocal = strlen(q->local) + 1;
        fwrite(&lenLocal, sizeof(int), 1, fp);
        fwrite(q->local, sizeof(char), lenLocal, fp);
    }

    fclose(fp);
    printf("Dados dos quarteis guardados com sucesso.\n");
}

void readQuarteis(Quarteis *quarteis) {
    FILE *fp = fopen("data/quarteis.bin", "rb");
    if (fp == NULL) {
         printf("\nO ficheiro 'quarteis.bin' não foi encontrado. A iniciar a lista vazia.\n");
        quarteis->numQuarteis = 0;
        quarteis->totalQuarteis = 2;
        quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));
        return;
    }

    // Lê cabeçalho
    fread(&quarteis->totalQuarteis, sizeof(int), 1, fp);
    fread(&quarteis->numQuarteis, sizeof(int), 1, fp);

    // Aloca o array principal
    quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));

    for (int i = 0; i < quarteis->numQuarteis; i++) {
        Quartel *q = &quarteis->quarteis[i];

        // 1. Lê dados primitivos
        fread(&q->id, sizeof(int), 1, fp);
        fread(&q->capacidade, sizeof(int), 1, fp);
        fread(&q->tipo, sizeof(TipoQuartel), 1, fp);

        // 2. Lê NOME
        int lenNome;
        fread(&lenNome, sizeof(int), 1, fp);           // Lê tamanho
        q->nome = (char*) malloc(lenNome * sizeof(char)); // Aloca memória
        fread(q->nome, sizeof(char), lenNome, fp);     // Lê conteúdo

        // 3. Lê LOCAL
        int lenLocal;
        fread(&lenLocal, sizeof(int), 1, fp);
        q->local = (char*) malloc(lenLocal * sizeof(char));
        fread(q->local, sizeof(char), lenLocal, fp);
    }

    fclose(fp);
    printf("Carregados %d quarteis do ficheiro.\n", quarteis->numQuarteis);
}