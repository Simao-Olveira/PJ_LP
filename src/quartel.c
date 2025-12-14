#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quartel.h"
#include "gestaoQuartel.h"
#include "input.h"
#include "enums.h"
#include "log.h"

// Função auxiliar para imprimir o texto dos Enums
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
    printf("\n--- Novo Quartel ---\n");

    // Gerar ID Automático (Lógica do Bombeiro)
    int maiorId = 0;
    for(int i = 0; i < quarteis->numQuarteis; i++) {
        if(quarteis->quarteis[i].id > maiorId) {
            maiorId = quarteis->quarteis[i].id;
        }
    }
    int id = maiorId + 1;

    if (procurarQuartel(*quarteis, id) == -1) {

        // Realocação de Memória do Array
        if (quarteis->totalQuarteis == quarteis->numQuarteis) {
            quarteis->totalQuarteis += 2;
            Quartel *temp = (Quartel*) realloc(quarteis->quarteis, quarteis->totalQuarteis * sizeof(Quartel));
            if (temp == NULL) {
                printf("Erro ao alocar memória!\n");
                return;
            }
            quarteis->quarteis = temp;
        }

        // Ponteiro auxiliar para facilitar leitura
        int i = quarteis->numQuarteis;
        quarteis->quarteis[i].id = id;

        // Leitura do Nome (Dinâmico)
        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Nome do Quartel: ");
        quarteis->quarteis[i].nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if (quarteis->quarteis[i].nome != NULL) {
            strcpy(quarteis->quarteis[i].nome, buffer);
        }

        // Leitura do Local (Dinâmico)
        lerString(buffer, SIZE_BUFFER, "Localização: ");
        quarteis->quarteis[i].local = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if (quarteis->quarteis[i].local != NULL) {
            strcpy(quarteis->quarteis[i].local, buffer);
        }

        // Outros Dados
        quarteis->quarteis[i].capacidade = obterInteiro(1, 1000, "Capacidade: ");

        printf("\nTipos de Quartel:\n0 - Voluntário\n1 - Sapador\n2 - Municipal\n");
        int tipoInput = obterInteiro(0, 2, "Selecione o tipo: ");
        quarteis->quarteis[i].tipo = (TipoQuartel) tipoInput;

        quarteis->numQuarteis++;
        printf("Quartel criado com sucesso!\n");
    } else {
        printf("O quartel com esse ID já existe!!\n");
    }
}

void libertarMemQuarteis(Quarteis *quarteis) {
    if (quarteis->quarteis != NULL) {
        for (int i = 0; i < quarteis->numQuarteis; i++) {
            free(quarteis->quarteis[i].nome);
            free(quarteis->quarteis[i].local);
        }
        free(quarteis->quarteis);
        quarteis->quarteis = NULL;
    }
    quarteis->numQuarteis = 0;
    quarteis->totalQuarteis = 0;
}

void imprimirQuartel(Quartel q) {
    printf("\n----------------------------");
    printf("\nID: %d", q.id);
    printf("\nNome: %s", q.nome);
    printf("\nLocal: %s", q.local);
    printf("\nCapacidade: %d", q.capacidade);
    printf("\nTipo: ");
    imprimirTipoQuartel(q.tipo);
    printf("\n----------------------------\n");
}

void listarQuarteis(Quarteis quarteis) {
    if (quarteis.numQuarteis > 0) {
        for (int i = 0; i < quarteis.numQuarteis; i++) {
            imprimirQuartel(quarteis.quarteis[i]);
        }
    } else {
        printf("Não existem quarteis registados!!\n");
    }
}

void atualizarDadosQuartel(Quartel *quartel) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Nome\n");
        printf("2- Local\n");
        printf("3- Capacidade\n");
        printf("4- Tipo\n");
        printf("0- Voltar\n");
        escolha = obterInteiro(0, 4, "\nEscolha uma opção: ");

        switch (escolha) {
            case 0:
                break;
            case 1:
                lerString(buffer, SIZE_BUFFER, "Novo Nome: ");
                quartel->nome = realloc(quartel->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(quartel->nome, buffer);
                break;
            case 2:
                lerString(buffer, SIZE_BUFFER, "Novo Local: ");
                quartel->local = realloc(quartel->local, (strlen(buffer) + 1) * sizeof (char));
                strcpy(quartel->local, buffer);
                break;
            case 3:
                quartel->capacidade = obterInteiro(1, 1000, "Nova Capacidade: ");
                break;
            case 4:
                printf("\nTipos:\n0 - Voluntário\n1 - Sapador\n2 - Municipal\n");
                quartel->tipo = (TipoQuartel)obterInteiro(0, 2, "Novo Tipo: ");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (escolha != 0);
}

void editarQuartel(Quarteis *quarteis) {
    listarQuarteis(*quarteis);
    printf("Editar dados do quartel:\n");
    int id = procurarQuartel(*quarteis, obterInteiro(0, MAX_INT, "Insira o ID do quartel a alterar: "));

    if (id != -1) {
        imprimirQuartel(quarteis->quarteis[id]);
        atualizarDadosQuartel(&quarteis->quarteis[id]);
        printf("Quartel atualizado com sucesso!\n");
    } else {
        printf("Quartel não existe!!\n");
    }
}

void eliminarQuartel(Quarteis *quarteis) {
    listarQuarteis(*quarteis);
    printf("Eliminar quartel:\n");

    int idBusca = obterInteiro(0, MAX_INT, "Insira o ID do quartel a eliminar: ");
    int indice = procurarQuartel(*quarteis, idBusca);

    if (indice != -1) {
        // Libertar memória das strings
        free(quarteis->quarteis[indice].nome);
        free(quarteis->quarteis[indice].local);

        // Shift do array
        for(int i = indice; i < quarteis->numQuarteis - 1; i++){
            quarteis->quarteis[i] = quarteis->quarteis[i+1];
        }

        quarteis->numQuarteis--;
        printf("Quartel eliminado com sucesso.\n");

    } else {
        printf("Quartel não encontrado!!\n");
    }
}

// ------ FICHEIROS ------
void carregarQuarteis(Quarteis *quarteis) {
    FILE *ficheiro = fopen("data/quarteis.bin", "rb");

    // 1. FICHEIRO NÃO EXISTE: Inicia lista vazia e limpa memória
    if (ficheiro == NULL) {
        logMsg("Ficheiro 'quarteis.bin' não foi encontrado. A iniciar a lista vazia.");
        quarteis->numQuarteis = 0;
        quarteis->totalQuarteis = 5;
        quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));
        return;
    }

    // 2. LER CABEÇALHOS
    fread(&quarteis->totalQuarteis, sizeof(int), 1, ficheiro);
    fread(&quarteis->numQuarteis, sizeof(int), 1, ficheiro);

    // 3. SE A LISTA NO FICHEIRO ESTIVER VAZIA
    if (quarteis->numQuarteis == 0) {
        quarteis->totalQuarteis = 5; // Garante tamanho mínimo
        quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));
        fclose(ficheiro);
        logMsg("\nLista de quarteis importada vazia.\n");
        return;
    }

    // 4. ALOCAÇÃO SEGURA (MALLOC)
    // Usamos malloc porque estamos a ler do zero, evitando lixo de memória
    quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));

    // 5. LER DADOS (Campo a campo, incluindo as strings dinâmicas)
    for (int i = 0; i < quarteis->numQuarteis; i++) {
        // Leitura dos dados primitivos
        fread(&quarteis->quarteis[i].id, sizeof(int), 1, ficheiro);
        fread(&quarteis->quarteis[i].capacidade, sizeof(int), 1, ficheiro);
        fread(&quarteis->quarteis[i].tipo, sizeof(TipoQuartel), 1, ficheiro);

        // --- Leitura da String 1: NOME ---
        int bufferTamNome;
        fread(&bufferTamNome, sizeof(int), 1, ficheiro);
        quarteis->quarteis[i].nome = (char*) malloc(sizeof(char) * (bufferTamNome + 1));
        fread(quarteis->quarteis[i].nome, sizeof(char), bufferTamNome, ficheiro);
        quarteis->quarteis[i].nome[bufferTamNome] = '\0';

        // --- Leitura da String 2: LOCAL ---
        int bufferTamLocal;
        fread(&bufferTamLocal, sizeof(int), 1, ficheiro);
        quarteis->quarteis[i].local = (char*) malloc(sizeof(char) * (bufferTamLocal + 1));
        fread(quarteis->quarteis[i].local, sizeof(char), bufferTamLocal, ficheiro);
        quarteis->quarteis[i].local[bufferTamLocal] = '\0';
    }

    fclose(ficheiro);
    logMsg("Quarteis carregados com sucesso do ficheiro.");
}

void guardarQuarteis(Quarteis *quarteis) {
    FILE *ficheiro = fopen("data/quarteis.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro 'quarteis.bin'.\n");
        logMsg("Erro ao criar ficheiro 'quarteis.bin'.");
        return;
    }

    // 1. ESCREVER CABEÇALHOS
    fwrite(&quarteis->totalQuarteis, sizeof(int), 1, ficheiro);
    fwrite(&quarteis->numQuarteis, sizeof(int), 1, ficheiro);

    // 2. ESCREVER DADOS
    for (int i = 0; i < quarteis->numQuarteis; i++) {
        // Escrita dos dados primitivos
        fwrite(&quarteis->quarteis[i].id, sizeof(int), 1, ficheiro);
        fwrite(&quarteis->quarteis[i].capacidade, sizeof(int), 1, ficheiro);
        fwrite(&quarteis->quarteis[i].tipo, sizeof(TipoQuartel), 1, ficheiro);

        // --- Escrita da String 1: NOME ---
        int bufferNome = strlen(quarteis->quarteis[i].nome);
        fwrite(&bufferNome, sizeof(int), 1, ficheiro);
        fwrite(quarteis->quarteis[i].nome, sizeof(char), bufferNome, ficheiro);

        // --- Escrita da String 2: LOCAL ---
        int bufferLocal = strlen(quarteis->quarteis[i].local);
        fwrite(&bufferLocal, sizeof(int), 1, ficheiro);
        fwrite(quarteis->quarteis[i].local, sizeof(char), bufferLocal, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Quarteis guardados com sucesso no ficheiro.");
}