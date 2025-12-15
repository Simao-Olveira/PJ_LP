/**
 * @file equipamento.c
 * @brief Implementação das funções de gestão de equipamentos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipamento.h"
#include "gestaoEquipamento.h"
#include "enums.h"
#include "input.h"
#include "log.h"

// --- FUNÇÕES AUXILIARES ---

/** @brief Converte o estado do equipamento em texto para impressão. */
void imprimirEstadoEquipamento(EstadoEquipamento est) {
    switch (est) {
        case EQ_DISPONIVEL: printf("Disponível"); break;
        case EQ_EM_USO:     printf("Em Uso"); break;
        case EQ_MANUTENCAO: printf("Em Manutenção"); break;
        default:            printf("Desconhecido"); break;
    }
}

/** @brief Converte o tipo do equipamento em texto para impressão. */
void imprimirTipoEquipamento(TipoEquipamento tipo) {
    switch (tipo) {
        case VESTUARIO:   printf("Vestuário"); break;
        case VEICULOS:    printf("Veículos"); break;
        case FERRAMENTAS: printf("Ferramentas"); break;
        case COMUNICACAO: printf("Comunicação"); break;
        default:          printf("Outro"); break;
    }
}

// --- FUNÇÕES PRINCIPAIS ---

/** * @brief Procura um equipamento pelo ID.
 * * Percorre sequencialmente a lista até encontrar o identificador fornecido, 
 * devolvendo a posição (índice) onde se encontra.
 * @return O índice no array ou -1 se não encontrar.
 */
int procurarEquipamento(Equipamentos equipamentos, int id) {
    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        if (equipamentos.equipamentos[i].id == id) {
            return i;
        }
    }
    return -1;
}

/** * @brief Adiciona um novo equipamento ao sistema.
 * * Gera um ID automático (max+1), verifica a capacidade do array (realocando 
 * memória se estiver cheio) e aloca memória dinâmica específica para o nome 
 * antes de guardar os restantes dados inseridos pelo utilizador.
 */
void adicionarEquipamento(Equipamentos *equipamentos) {
    printf("\n--- Novo Equipamento ---\n");
    
    int maiorId = 0;
    for(int i = 0; i < equipamentos->numEquipamentos; i++) {
        if(equipamentos->equipamentos[i].id > maiorId) {
            maiorId = equipamentos->equipamentos[i].id;
        }
    }
    int id = maiorId + 1;

    if (procurarEquipamento(*equipamentos, id) == -1) {
        
        if (equipamentos->totalEquipamentos == equipamentos->numEquipamentos) {
            equipamentos->totalEquipamentos += 5;
            Equipamento *temp = (Equipamento*) realloc(equipamentos->equipamentos, equipamentos->totalEquipamentos * sizeof(Equipamento));
            if (temp == NULL) {
                printf("Erro de memória!\n");
                return;
            }
            equipamentos->equipamentos = temp;
        }

        int i = equipamentos->numEquipamentos;

        equipamentos->equipamentos[i].id = id;

        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Nome: ");
        equipamentos->equipamentos[i].nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if (equipamentos->equipamentos[i].nome != NULL) {
             strcpy(equipamentos->equipamentos[i].nome, buffer);
        }
           
        printf("\nTipos:\n0 - Vestuário\n1 - Veículos\n2 - Ferramentas\n3 - Comunicação\n");
        int tipoInput = obterInteiro(0, 3, "Tipo de Equipamento: ");
        equipamentos->equipamentos[i].tipo = (TipoEquipamento)tipoInput;

        printf("\nEstados:\n0 - Disponível\n1 - Em Uso\n2 - Manutenção\n");
        int estInput = obterInteiro(0, 2, "Estado inicial: ");
        equipamentos->equipamentos[i].estado = (EstadoEquipamento)estInput;

        equipamentos->numEquipamentos++;
        printf("Equipamento adicionado com sucesso!\n");

    } else {
        printf("Erro: ID duplicado.\n");
    }
}

/** * @brief Liberta toda a memória associada aos equipamentos.
 * * Itera sobre os registos para libertar individualmente as strings (nomes)
 * e, só depois, liberta o bloco de memória do array principal.
 */
void libertarMemEquipamentos(Equipamentos *equipamentos) {
    if (equipamentos->equipamentos != NULL) {
        for(int i = 0; i < equipamentos->numEquipamentos; i++) {
            free(equipamentos->equipamentos[i].nome);
        }
        free(equipamentos->equipamentos);
        equipamentos->equipamentos = NULL;
    }
    equipamentos->numEquipamentos = 0;
    equipamentos->totalEquipamentos = 0;
}

/** @brief Imprime os detalhes de um único equipamento. */
void imprimirEquipamento(Equipamento equipamento) {
    printf("\n----------------------------");
    printf("\nID: %d", equipamento.id);
    printf("\nNome: %s", equipamento.nome);
    printf("\nTipo: "); imprimirTipoEquipamento(equipamento.tipo);
    printf("\nEstado: "); imprimirEstadoEquipamento(equipamento.estado);
    printf("\n----------------------------\n");
}

/** @brief Lista todos os equipamentos registados. */
void listarEquipamentos(Equipamentos equipamentos) {
    if (equipamentos.numEquipamentos > 0) {
        for (int i = 0; i < equipamentos.numEquipamentos; i++) {
             imprimirEquipamento(equipamentos.equipamentos[i]);
        }
    } else {
         printf("Não existem equipamentos registados.\n");
    }
}

/** * @brief Submenu para atualizar dados de um equipamento.
 * * Permite alterar campos individuais. Se o nome for alterado, a memória 
 * da string é realocada para se ajustar ao tamanho do novo texto.
 */
void atualizarDadosEquipamento(Equipamento *equipamento) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Nome\n2- Tipo\n3- Estado\n0- Voltar\n");
        escolha = obterInteiro(0, 3, "\nEscolha uma opção: ");

        switch (escolha) {
            case 0: break;
            case 1:
                lerString(buffer, SIZE_BUFFER, "Novo Nome: ");
                equipamento->nome = realloc(equipamento->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(equipamento->nome, buffer);
                break;
            case 2:
                printf("\n0- Vestuário | 1- Veículos | 2- Ferramentas | 3- Comunicação\n");
                equipamento->tipo = (TipoEquipamento)obterInteiro(0, 3, "Novo Tipo: ");
                break;
            case 3:
                printf("\n0- Disponível | 1- Em Uso | 2- Manutenção\n");
                equipamento->estado = (EstadoEquipamento)obterInteiro(0, 2, "Novo Estado: ");
                break;
            default: printf("Opção inválida\n"); break;
        }
    } while (escolha != 0);
}

/** @brief Procura o equipamento e inicia o menu de edição. */
void editarEquipamento(Equipamentos *equipamentos) {
    listarEquipamentos(*equipamentos);
    printf("Editar dados do equipamento:\n");
    int id = obterInteiro(0, MAX_INT, "Insira o ID do equipamento a editar: ");
    int indice = procurarEquipamento(*equipamentos, id);

    if (indice != -1) {
        imprimirEquipamento(equipamentos->equipamentos[indice]);
        atualizarDadosEquipamento(&equipamentos->equipamentos[indice]);
        printf("Equipamento atualizado com sucesso.\n");
    } else {
        printf("Equipamento não encontrado.\n");
    }
}

/** * @brief Elimina um equipamento do sistema.
 * * Liberta a memória do nome e reorganiza o array, movendo todos os 
 * elementos seguintes uma posição para trás (shift left) para preencher o vazio.
 */
void eliminarEquipamento(Equipamentos *equipamentos) {
    listarEquipamentos(*equipamentos);
    printf("Eliminar equipamento:\n");
    
    int id = obterInteiro(0, MAX_INT, "Insira o ID do equipamento a eliminar: ");
    int indice = procurarEquipamento(*equipamentos, id);

    if (indice != -1) {
        free(equipamentos->equipamentos[indice].nome);

        for (int i = indice; i < equipamentos->numEquipamentos - 1; i++) {
            equipamentos->equipamentos[i] = equipamentos->equipamentos[i + 1];
        }
        
        equipamentos->numEquipamentos--;
        printf("Equipamento eliminado com sucesso.\n");
    } else {
        printf("Equipamento não encontrado.\n");
    }
}

// ------ FICHEIROS ------

/** * @brief Carrega dados do ficheiro binário.
 * * Lê os contadores iniciais para alocar o array. De seguida, para cada 
 * equipamento, lê primeiro o tamanho do nome para alocar a memória exata 
 * antes de ler os caracteres da string.
 */
void carregarEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "rb");
    
    if (ficheiro == NULL) {
        logMsg("Ficheiro 'equipamentos.bin' não foi encontrado. A iniciar a lista vazia.");
        equipamentos->numEquipamentos = 0;
        equipamentos->totalEquipamentos = 5; 
        equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));
        return;
    }

    fread(&equipamentos->totalEquipamentos, sizeof(int), 1, ficheiro);
    fread(&equipamentos->numEquipamentos, sizeof(int), 1, ficheiro);

    if (equipamentos->numEquipamentos == 0) {
        equipamentos->totalEquipamentos = 5; 
        equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));
        fclose(ficheiro);
        logMsg("\nLista de equipamentos importada vazia.\n");
        return;
    }

    equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));

    for (int i = 0; i < equipamentos->numEquipamentos; i++) {
        fread(&equipamentos->equipamentos[i].id, sizeof(int), 1, ficheiro);
        fread(&equipamentos->equipamentos[i].tipo, sizeof(TipoEquipamento), 1, ficheiro);
        fread(&equipamentos->equipamentos[i].estado, sizeof(EstadoEquipamento), 1, ficheiro);
        
        int buffer;
        fread(&buffer, sizeof (int), 1, ficheiro);
        equipamentos->equipamentos[i].nome = (char*) malloc(sizeof (char) * (buffer + 1));
        fread(equipamentos->equipamentos[i].nome, sizeof (char), buffer, ficheiro);
        equipamentos->equipamentos[i].nome[buffer] = '\0';
    }
    
    fclose(ficheiro);
    logMsg("Equipamentos carregados com sucesso do ficheiro.");
}

/** * @brief Guarda dados em ficheiro binário.
 * * Escreve a estrutura em disco. Para a string (nome), guarda o tamanho 
 * em bytes seguido dos caracteres, garantindo a recuperação correta.
 */
void guardarEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro 'equipamentos.bin'.\n");
        logMsg("Erro ao criar ficheiro 'equipamentos.bin'.");
        return;
    }

    fwrite(&equipamentos->totalEquipamentos, sizeof(int), 1, ficheiro);
    fwrite(&equipamentos->numEquipamentos, sizeof(int), 1, ficheiro);

    for (int i = 0; i < equipamentos->numEquipamentos; i++) {
        fwrite(&equipamentos->equipamentos[i].id, sizeof(int), 1, ficheiro);
        fwrite(&equipamentos->equipamentos[i].tipo, sizeof(TipoEquipamento), 1, ficheiro);
        fwrite(&equipamentos->equipamentos[i].estado, sizeof(EstadoEquipamento), 1, ficheiro);
        
        int buffer = strlen(equipamentos->equipamentos[i].nome);
        fwrite(&buffer, sizeof(int), 1, ficheiro);
        fwrite(equipamentos->equipamentos[i].nome, sizeof (char), buffer, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Equipamentos guardados com sucesso no ficheiro.");
}