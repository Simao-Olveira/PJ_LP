#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipamento.h"
#include "gestaoEquipamento.h"
#include "enums.h"
#include "input.h"
#include "log.h"

// --- FUNÇÕES AUXILIARES ---

void imprimirEstadoEquipamento(EstadoEquipamento est) {
    switch (est) {
        case EQ_DISPONIVEL: 
            printf("Disponível"); 
            break;
        case EQ_EM_USO:     
            printf("Em Uso"); 
            break;
        case EQ_MANUTENCAO: 
            printf("Em Manutenção"); 
            break;
        default:            
            printf("Desconhecido"); 
            break;
    }
}

void imprimirTipoEquipamento(TipoEquipamento tipo) {
    switch (tipo) {
        case VESTUARIO:   
            printf("Vestuário"); 
            break;
        case VEICULOS:    
            printf("Veículos"); 
            break;
        case FERRAMENTAS: 
            printf("Ferramentas"); 
            break;
        case COMUNICACAO: 
            printf("Comunicação"); 
            break;
        default:          
            printf("Outro"); 
            break;
    }
}

// --- FUNÇÕES PRINCIPAIS ---

int procurarEquipamento(Equipamentos equipamentos, int id) {
    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        if (equipamentos.equipamentos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarEquipamento(Equipamentos *equipamentos) {
    printf("\n--- Novo Equipamento ---\n");
    
    // Gerar ID Automático (Max + 1)
    int maiorId = 0;
    for(int i = 0; i < equipamentos->numEquipamentos; i++) {
        if(equipamentos->equipamentos[i].id > maiorId) {
            maiorId = equipamentos->equipamentos[i].id;
        }
    }
    int id = maiorId + 1;

    if (procurarEquipamento(*equipamentos, id) == -1) {
        
        // Realocação do Array Principal
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

        // Preenchimento dos dados
        equipamentos->equipamentos[i].id = id;

        // Nome (String Dinâmica)
        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Nome: ");
        equipamentos->equipamentos[i].nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if (equipamentos->equipamentos[i].nome != NULL) {
             strcpy(equipamentos->equipamentos[i].nome, buffer);
        }
           
        // Tipo
        printf("\nTipos:\n0 - Vestuário\n1 - Veículos\n2 - Ferramentas\n3 - Comunicação\n");
        int tipoInput = obterInteiro(0, 3, "Tipo de Equipamento: ");
        equipamentos->equipamentos[i].tipo = (TipoEquipamento)tipoInput;

        // Estado
        printf("\nEstados:\n0 - Disponível\n1 - Em Uso\n2 - Manutenção\n");
        int estInput = obterInteiro(0, 2, "Estado inicial: ");
        equipamentos->equipamentos[i].estado = (EstadoEquipamento)estInput;

        equipamentos->numEquipamentos++;
        printf("Equipamento adicionado com sucesso!\n");

    } else {
        printf("Erro: ID duplicado.\n");
    }
}

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

void imprimirEquipamento(Equipamento equipamento) {
    printf("\n----------------------------");
    printf("\nID: %d", equipamento.id);
    printf("\nNome: %s", equipamento.nome);
    printf("\nTipo: ");
    imprimirTipoEquipamento(equipamento.tipo);
    printf("\nEstado: ");
    imprimirEstadoEquipamento(equipamento.estado);
    printf("\n----------------------------\n");
}

void listarEquipamentos(Equipamentos equipamentos) {
    if (equipamentos.numEquipamentos > 0) {
        for (int i = 0; i < equipamentos.numEquipamentos; i++) {
             imprimirEquipamento(equipamentos.equipamentos[i]);
        }
    } else {
         printf("Não existem equipamentos registados.\n");
    }
}

void atualizarDadosEquipamento(Equipamento *equipamento) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Nome\n");
        printf("2- Tipo\n");
        printf("3- Estado\n");
        printf("0- Voltar\n");
        escolha = obterInteiro(0, 3, "\nEscolha uma opção: ");

        switch (escolha) {
            case 0:
                break;
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
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (escolha != 0);
}

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

void eliminarEquipamento(Equipamentos *equipamentos) {
    listarEquipamentos(*equipamentos);
    printf("Eliminar equipamento:\n");
    
    int id = obterInteiro(0, MAX_INT, "Insira o ID do equipamento a eliminar: ");
    int indice = procurarEquipamento(*equipamentos, id);

    if (indice != -1) {
        // 1. Libertar memória da string ANTES de apagar
        free(equipamentos->equipamentos[indice].nome);

        // 2. Shift do array (Eliminação Física)
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

void readEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "rb");
    
    // 1. FICHEIRO NÃO EXISTE
    if (ficheiro == NULL) {
        logMsg("Ficheiro 'equipamentos.bin' não foi encontrado. A iniciar a lista vazia.");
        equipamentos->numEquipamentos = 0;
        equipamentos->totalEquipamentos = 5; 
        equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));
        return;
    }

    // 2. LER CONTADORES
    fread(&equipamentos->totalEquipamentos, sizeof(int), 1, ficheiro);
    fread(&equipamentos->numEquipamentos, sizeof(int), 1, ficheiro);

    // 3. SE LISTA VAZIA
    if (equipamentos->numEquipamentos == 0) {
        equipamentos->totalEquipamentos = 5; // Garante tamanho mínimo
        equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));
        fclose(ficheiro);
        logMsg("\nLista de equipamentos importada vazia.\n");
        return;
    }

    // 4. ALOCAÇÃO SEGURA (MALLOC)
    equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));

    // 5. LER DADOS CAMPO A CAMPO (INCLUINDO STRING 'NOME')
    for (int i = 0; i < equipamentos->numEquipamentos; i++) {
        fread(&equipamentos->equipamentos[i].id, sizeof(int), 1, ficheiro);
        fread(&equipamentos->equipamentos[i].tipo, sizeof(TipoEquipamento), 1, ficheiro);
        fread(&equipamentos->equipamentos[i].estado, sizeof(EstadoEquipamento), 1, ficheiro);
        
        // Leitura da String Nome (tamanho + conteúdo)
        int buffer;
        fread(&buffer, sizeof (int), 1, ficheiro);
        equipamentos->equipamentos[i].nome = (char*) malloc(sizeof (char) * (buffer + 1));
        fread(equipamentos->equipamentos[i].nome, sizeof (char), buffer, ficheiro);
        equipamentos->equipamentos[i].nome[buffer] = '\0';
    }
    
    fclose(ficheiro);
    logMsg("Bombeiros carregados com sucesso do ficheiro.");
}

void writeEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro 'equipamentos.bin'.\n");
        logMsg("Erro ao criar ficheiro 'equipamentos.bin'.");
        return;
    }

    // 1. ESCREVER CONTADORES
    fwrite(&equipamentos->totalEquipamentos, sizeof(int), 1, ficheiro);
    fwrite(&equipamentos->numEquipamentos, sizeof(int), 1, ficheiro);

    // 2. ESCREVER DADOS
    for (int i = 0; i < equipamentos->numEquipamentos; i++) {
        fwrite(&equipamentos->equipamentos[i].id, sizeof(int), 1, ficheiro);
        fwrite(&equipamentos->equipamentos[i].tipo, sizeof(TipoEquipamento), 1, ficheiro);
        fwrite(&equipamentos->equipamentos[i].estado, sizeof(EstadoEquipamento), 1, ficheiro);
        
        // Escrita da String Nome (tamanho + conteúdo)
        int buffer = strlen(equipamentos->equipamentos[i].nome);
        fwrite(&buffer, sizeof(int), 1, ficheiro);
        fwrite(equipamentos->equipamentos[i].nome, sizeof (char), buffer, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Equipamentos guardados com sucesso no ficheiro.");
}