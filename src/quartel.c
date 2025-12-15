/**
 * @file quartel.c
 * @brief Implementação das funções de gestão de quartéis.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quartel.h"
#include "gestaoQuartel.h"
#include "input.h"
#include "enums.h"
#include "log.h"

/** @brief Converte o tipo de quartel (enum) em texto para impressão. */
void imprimirTipoQuartel(TipoQuartel tipo) {
    switch (tipo) {
        case VOLUNTARIO: printf("Bombeiros Voluntários"); break;
        case SAPADOR:    printf("Companhia de Sapadores"); break;
        case MUNICIPAL:  printf("Bombeiros Municipais"); break;
        default:         printf("Desconhecido"); break;
    }
}

/** * @brief Procura um quartel pelo ID.
 * * Percorre sequencialmente a lista de quartéis até encontrar o ID correspondente.
 * @return O índice no array ou -1 se não encontrar.
 */
int procurarQuartel(Quarteis quarteis, int id) {
    for (int i = 0; i < quarteis.numQuarteis; i++) {
        if (quarteis.quarteis[i].id == id) {
            return i;
        }
    }
    return -1;
}

/** * @brief Adiciona um novo quartel ao sistema.
 * * Lógica de Criação:
 * 1. Gera um ID sequencial.
 * 2. Redimensiona o array principal se estiver cheio.
 * 3. Aloca memória dinâmica para **duas** strings diferentes: 'nome' e 'local'.
 * O tamanho alocado é estritamente o necessário (strlen + 1) para otimizar memória.
 */
void adicionarQuartel(Quarteis *quarteis) {
    printf("\n--- Novo Quartel ---\n");

    int maiorId = 0;
    for(int i = 0; i < quarteis->numQuarteis; i++) {
        if(quarteis->quarteis[i].id > maiorId) {
            maiorId = quarteis->quarteis[i].id;
        }
    }
    int id = maiorId + 1;

    if (procurarQuartel(*quarteis, id) == -1) {

        if ((*quarteis).totalQuarteis == (*quarteis).numQuarteis) {
            (*quarteis).totalQuarteis += 2; 
            Quartel *temp = (Quartel*) realloc((*quarteis).quarteis, ((*quarteis).totalQuarteis) * sizeof(Quartel));
            if (temp == NULL) {
                printf("Erro ao alocar memória!\n");
                return;
            }
            (*quarteis).quarteis = temp;
        }

        // Preenchimento dos dados
        (*quarteis).quarteis[(*quarteis).numQuarteis].id = id;

        char buffer[SIZE_BUFFER];
        
        // Alocação para o Nome
        lerString(buffer, SIZE_BUFFER, "Nome: ");
        (*quarteis).quarteis[(*quarteis).numQuarteis].nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*quarteis).quarteis[(*quarteis).numQuarteis].nome != NULL) {
            strcpy((*quarteis).quarteis[(*quarteis).numQuarteis].nome, buffer);
        }
        
        // Alocação para a Localização
        lerString(buffer, SIZE_BUFFER, "Localização: ");
        (*quarteis).quarteis[(*quarteis).numQuarteis].local = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*quarteis).quarteis[(*quarteis).numQuarteis].local != NULL) {
            strcpy((*quarteis).quarteis[(*quarteis).numQuarteis].local, buffer);
        }

        // Outros campos
        (*quarteis).quarteis[(*quarteis).numQuarteis].capacidade = obterInteiro(1, 1000, "Capacidade: ");

        printf("\nTipos de Quartel:\n0 - Voluntário\n1 - Sapador\n2 - Municipal\n");
        int tipoInput = obterInteiro(0, 2, "Selecione o tipo: ");
        (*quarteis).quarteis[(*quarteis).numQuarteis].tipo = (TipoQuartel)tipoInput;

        (*quarteis).numQuarteis++;
        printf("Quartel criado com sucesso!\n");
    } else {
        printf("O quartel com esse ID já existe!!\n");
    }
}

/** * @brief Liberta toda a memória associada aos quartéis.
 * * Itera sobre o array para libertar individualmente as strings 'nome' e 'local'
 * de cada registo antes de libertar o array de estruturas.
 */
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

/** @brief Imprime os detalhes de um único quartel. */
void imprimirQuartel(Quartel q) {
    printf("\n----------------------------");
    printf("\nID: %d", q.id);
    printf("\nNome: %s", q.nome);
    printf("\nLocal: %s", q.local);
    printf("\nCapacidade: %d", q.capacidade);
    printf("\nTipo: "); imprimirTipoQuartel(q.tipo);
    printf("\n----------------------------\n");
}

/** @brief Lista todos os quartéis registados. */
void listarQuarteis(Quarteis quarteis) {
    if (quarteis.numQuarteis > 0) {
        for (int i = 0; i < quarteis.numQuarteis; i++) {
            imprimirQuartel(quarteis.quarteis[i]);
        }
    } else {
        printf("Não existem quarteis registados!!\n");
    }
}

/** * @brief Submenu para atualizar dados de um quartel.
 * * Permite a edição individual de campos. O uso de `realloc` nas strings 
 * (nome e local) garante que a memória se ajusta ao tamanho dos novos dados.
 */
void atualizarDadosQuartel(Quartel *quartel) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Nome\n2- Local\n3- Capacidade\n4- Tipo\n0- Voltar\n");
        escolha = obterInteiro(0, 4, "\nEscolha uma opção: ");
        switch (escolha) {
            case 0: break;
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
            default: printf("Opção inválida\n"); break;
        }
    } while (escolha != 0);
}

/** @brief Procura o quartel e inicia o menu de edição. */
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

/** * @brief Elimina um quartel do sistema.
 * * Liberta a memória das strings 'nome' e 'local', e reorganiza o array 
 * (shift left) para preencher a posição eliminada.
 */
void eliminarQuartel(Quarteis *quarteis) {    
    listarQuarteis(*quarteis);
    printf("Eliminar quartel:\n");
    
    int idBusca = obterInteiro(0, MAX_INT, "Insira o ID do quartel a eliminar: ");
    int indice = procurarQuartel(*quarteis, idBusca);

    if (indice != -1) {
        // Libertar memória das duas strings
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

/** * @brief Carrega dados dos quartéis do ficheiro binário.
 * * Lê os contadores iniciais. Para cada quartel, lê os dados primitivos e, 
 * sequencialmente, o tamanho e o conteúdo das strings 'nome' e 'local', 
 * alocando memória dinâmica para cada uma.
 */
void carregarQuarteis(Quarteis *quarteis) {
    FILE *ficheiro = fopen("data/quarteis.bin", "rb");
    
    if (ficheiro == NULL) {
        logMsg("Ficheiro 'quarteis.bin' não foi encontrado. A iniciar a lista vazia.");
        quarteis->numQuarteis = 0;
        quarteis->totalQuarteis = 5; 
        quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));
        return;
    }

    fread(&quarteis->totalQuarteis, sizeof(int), 1, ficheiro);
    fread(&quarteis->numQuarteis, sizeof(int), 1, ficheiro);

    if (quarteis->numQuarteis == 0) {
        quarteis->totalQuarteis = 5; 
        quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));
        fclose(ficheiro);
        logMsg("\nLista de quarteis importada vazia.\n");
        return;
    }

    quarteis->quarteis = (Quartel*) malloc(quarteis->totalQuarteis * sizeof(Quartel));

    for (int i = 0; i < quarteis->numQuarteis; i++) {
        fread(&quarteis->quarteis[i].id, sizeof(int), 1, ficheiro);
        fread(&quarteis->quarteis[i].capacidade, sizeof(int), 1, ficheiro);
        fread(&quarteis->quarteis[i].tipo, sizeof(TipoQuartel), 1, ficheiro);
        
        // Leitura da String Nome
        int bufferTamNome;
        fread(&bufferTamNome, sizeof(int), 1, ficheiro);
        quarteis->quarteis[i].nome = (char*) malloc(sizeof(char) * (bufferTamNome + 1));
        fread(quarteis->quarteis[i].nome, sizeof(char), bufferTamNome, ficheiro);
        quarteis->quarteis[i].nome[bufferTamNome] = '\0';

        // Leitura da String Local
        int bufferTamLocal;
        fread(&bufferTamLocal, sizeof(int), 1, ficheiro);
        quarteis->quarteis[i].local = (char*) malloc(sizeof(char) * (bufferTamLocal + 1));
        fread(quarteis->quarteis[i].local, sizeof(char), bufferTamLocal, ficheiro);
        quarteis->quarteis[i].local[bufferTamLocal] = '\0';
    }
    
    fclose(ficheiro);
    logMsg("Quarteis carregados com sucesso do ficheiro.");
}

/** * @brief Guarda dados dos quartéis em ficheiro binário.
 * * Serializa a estrutura escrevendo os campos fixos e, para cada string 
 * ('nome' e 'local'), escreve primeiro o tamanho em bytes e depois os caracteres.
 */
void guardarQuarteis(Quarteis *quarteis) {
    FILE *ficheiro = fopen("data/quarteis.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro 'quarteis.bin'.\n");
        logMsg("Erro ao criar ficheiro 'quarteis.bin'.");
        return;
    }

    fwrite(&quarteis->totalQuarteis, sizeof(int), 1, ficheiro);
    fwrite(&quarteis->numQuarteis, sizeof(int), 1, ficheiro);

    for (int i = 0; i < quarteis->numQuarteis; i++) {
        fwrite(&quarteis->quarteis[i].id, sizeof(int), 1, ficheiro);
        fwrite(&quarteis->quarteis[i].capacidade, sizeof(int), 1, ficheiro);
        fwrite(&quarteis->quarteis[i].tipo, sizeof(TipoQuartel), 1, ficheiro);
        
        // Escrita da String Nome
        int bufferNome = strlen(quarteis->quarteis[i].nome); 
        fwrite(&bufferNome, sizeof(int), 1, ficheiro);
        fwrite(quarteis->quarteis[i].nome, sizeof(char), bufferNome, ficheiro);

        // Escrita da String Local
        int bufferLocal = strlen(quarteis->quarteis[i].local); 
        fwrite(&bufferLocal, sizeof(int), 1, ficheiro);
        fwrite(quarteis->quarteis[i].local, sizeof(char), bufferLocal, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Quarteis guardados com sucesso no ficheiro.");
}