#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipamento.h"
#include "input.h"

// Função auxiliar para imprimir o estado em texto
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

// Função auxiliar para imprimir o TIPO em texto
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
            printf("Sistemas de Comunicação");
            break;
        default:
            printf("Outro");
            break;
    }
}

int procurarEquipamento(Equipamentos equipamentos, int id) {
    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        // Verifica se o ID bate certo E se o equipamento está ativo
        if (equipamentos.equipamentos[i].id == id && equipamentos.equipamentos[i].ativo == 1) {
            return i;
        }
    }
    return -1;
}

void adicionarEquipamento(Equipamentos *equipamentos) {
    printf("\nCriar Equipamento:\n");
    int id = equipamentos->numEquipamentos + 1;

    // Verificação simples (apenas procura se existe ativo com esse ID)
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

        // --- Preenchimento dos dados ---
        equipamentos->equipamentos[equipamentos->numEquipamentos].id = id;
        equipamentos->equipamentos[equipamentos->numEquipamentos].ativo = 1; 

        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Nome: ");
        (*equipamentos).equipamentos[(*equipamentos).numEquipamentos].nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*equipamentos).equipamentos[(*equipamentos).numEquipamentos].nome != NULL) {
             strcpy((*equipamentos).equipamentos[(*equipamentos).numEquipamentos].nome, buffer);
        }
           
        // Pedir Estado
        printf("\nEstados:\n0 - Disponível\n1 - Em Uso\n2 - Manutenção\n");
        int estInput = obterInteiro(0, 2, "Estado inicial: ");
        equipamentos->equipamentos[equipamentos->numEquipamentos].estado = (EstadoEquipamento)estInput;

        // Pedir Tipo (NOVO)
        printf("\nTipos:\n0 - Vestuário\n1 - Veículos\n2 - Ferramentas\n3 - Sistemas de Comunicação\n");
        int tipoInput = obterInteiro(0, 3, "Tipo de Equipamento: ");
        equipamentos->equipamentos[equipamentos->numEquipamentos].tipo = (TipoEquipamento)tipoInput;

        equipamentos->numEquipamentos++;
        printf("Equipamento adicionado com sucesso!\n");

    } else {
        printf("Já existe um equipamento ativo com esse ID!\n");
    }
}

void imprimirEquipamento(Equipamento equipamento) {
    printf("\n--- ID: %d ---", equipamento.id);
    printf("\nNome: %s", equipamento.nome);
    
    printf("\nEstado: ");
    imprimirEstadoEquipamento(equipamento.estado);

    printf("\nTipo: ");
    imprimirTipoEquipamento(equipamento.tipo); // <--- Imprimir o novo campo

    printf("\n----------------\n");
}

void listarEquipamentos(Equipamentos equipamentos) {
    int encontrou = 0;
    if (equipamentos.numEquipamentos > 0) {
        for (int i = 0; i < equipamentos.numEquipamentos; i++) {
            if(equipamentos.equipamentos[i].ativo == 1) { 
                imprimirEquipamento(equipamentos.equipamentos[i]);
                encontrou = 1;
            }
        }
    } 
    
    if (!encontrou && equipamentos.numEquipamentos > 0) {
         printf("Não existem equipamentos ativos.\n");
    } else if (equipamentos.numEquipamentos == 0) {
         printf("Não existem equipamentos registados.\n");
    }
}

void atualizarDadosEquipamento(Equipamento *equipamento) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\nEditar Equipamento %d:\n1- Nome\n2- Estado\n3- Tipo\n0- Voltar\n", equipamento->id);
        escolha = obterInteiro(0, 3, "Opção: ");

        switch (escolha) {
            case 1:
                lerString(buffer, SIZE_BUFFER, "Nome: ");
                equipamento->nome = realloc(equipamento->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(equipamento->nome, buffer);
                break;
            case 2:
                printf("\n0- Disponível | 1- Em Uso | 2- Manutenção\n");
                int novoEstado = obterInteiro(0, 2, "Novo Estado: ");
                equipamento->estado = (EstadoEquipamento)novoEstado;
                break;
            case 3:
                printf("\n0- Vestuário | 1- Veículos | 2- Ferramentas | 3- Comunicação\n");
                int novoTipo = obterInteiro(0, 3, "Novo Tipo: ");
                equipamento->tipo = (TipoEquipamento)novoTipo;
                break;
            case 0:
                break;
        }
    } while (escolha != 0);
}

void editarEquipamento(Equipamentos *equipamentos) {
    listarEquipamentos(*equipamentos);
    int id = obterInteiro(0, 999999, "Insira o ID do equipamento a editar: ");
    int indice = procurarEquipamento(*equipamentos, id);

    if (indice != -1) {
        atualizarDadosEquipamento(&equipamentos->equipamentos[indice]);
    } else {
        printf("Equipamento não encontrado.\n");
    }
}

void eliminarEquipamento(Equipamentos *equipamentos) {
    listarEquipamentos(*equipamentos);
    int id = obterInteiro(0, 999999, "Insira o ID do equipamento a eliminar: ");
    int indice = procurarEquipamento(*equipamentos, id);

    if (indice != -1) {
        // Soft Delete: Apenas marca como inativo.
        // Nota: Não precisas de fazer o loop "for" para puxar os elementos para trás
        // se estiveres a usar a flag 'ativo'. Podes apenas mudar o estado.
        // Se quiseres manter a lógica de puxar para trás (Hard Delete), o 'ativo' torna-se redundante.
        // Vou manter a tua lógica mista (puxa para trás E marca inativo o último espaço):
        
        for (int i = indice; i < equipamentos->numEquipamentos - 1; i++) {
            equipamentos->equipamentos[i] = equipamentos->equipamentos[i + 1];
        }
        
        equipamentos->numEquipamentos--;
        // Limpar dados do último (opcional, mas boa prática)
        equipamentos->equipamentos[equipamentos->numEquipamentos].ativo = 0; 
        
        printf("Equipamento eliminado.\n");
    } else {
        printf("Equipamento não encontrado.\n");
    }
}

void libertarMemEquipamentos(Equipamentos *equipamentos) {
    free(equipamentos->equipamentos);
    equipamentos->equipamentos = NULL;
    equipamentos->numEquipamentos = 0;
    equipamentos->totalEquipamentos = 0;
}

// ------ FICHEIROS ------

void readEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "rb");
    
    if (ficheiro == NULL) {
        printf("\nO ficheiro 'equipamentos.bin' não foi encontrado. A iniciar a lista vazia.\n");
        equipamentos->numEquipamentos = 0;
        equipamentos->totalEquipamentos = 5;
        equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));
        return;
    }

    fread(&equipamentos->totalEquipamentos, sizeof(int), 1, ficheiro);
    fread(&equipamentos->numEquipamentos, sizeof(int), 1, ficheiro);

    equipamentos->equipamentos = (Equipamento*) malloc(equipamentos->totalEquipamentos * sizeof(Equipamento));
    
    if (equipamentos->equipamentos == NULL) {
        printf("Erro fatal de memória.\n");
        fclose(ficheiro);
        return;
    }

    if (equipamentos->numEquipamentos > 0) {
        // Como o struct mudou de tamanho, o fread vai ajustar-se automaticamente.
        // Mas o ficheiro BIN antigo tem dados com tamanho diferente, por isso vai falhar se não o apagares.
        fread(equipamentos->equipamentos, sizeof(Equipamento), equipamentos->numEquipamentos, ficheiro);
    }

    fclose(ficheiro);
    printf("\nCarregados %d equipamentos.\n", equipamentos->numEquipamentos);
}

void writeEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "wb");
    
    if (ficheiro == NULL) {
        printf("\nErro ao abrir ficheiro 'data/equipamentos.bin'.\n");
        return;
    }

    fwrite(&equipamentos->totalEquipamentos, sizeof(int), 1, ficheiro);
    fwrite(&equipamentos->numEquipamentos, sizeof(int), 1, ficheiro);

    if (equipamentos->numEquipamentos > 0) {
        fwrite(equipamentos->equipamentos, sizeof(Equipamento), equipamentos->numEquipamentos, ficheiro);
    }

    fclose(ficheiro);
    printf("\nEquipamentos guardados com sucesso.\n");
}