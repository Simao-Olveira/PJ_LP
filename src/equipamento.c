
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enums.h"
#include "equipamento.h"
#include "gestaoEquipamento.h"
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
    int i;
    for (i = 0; i < equipamentos.numEquipamentos; i++) {
        if (equipamentos.equipamentos[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarEquipamento(Equipamentos *equipamentos) {
int id;
printf("Criar bombeiro:\n");
id = equipamentos->numEquipamentos + 1;

    if (procurarEquipamento(*equipamentos, id) == -1) {

        // Realocação de memória se o array estiver cheio
        if ((*equipamentos).totalEquipamentos == (*equipamentos).numEquipamentos) {
            (*equipamentos).totalEquipamentos += 3; // Expande de 3 em 3
            Equipamento *temp = (Equipamento*) realloc((*equipamentos).quipamentos, ((*equipamentos).totalEquipamentos) * sizeof(Equipamento));
            if (temp == NULL) {
                printf("Erro ao alocar memória!\n");
                return;
            }
            (*equipamentos).equipamentos = temp;
        }

        // Preenchimento dos dados
        (*equipamentos).equipamentos[(*equipamentos).numEquipamentos].id = id;
        (*equipamentos).equipamentos[(*equipamentos).numEquipamentos].ativo = 1; // Define como ativo por defeito

        // Leitura do Nome (Array fixo, usa strcpy)
        char buffer[100];
        lerString(buffer, 100, "Nome: ");
        strcpy((*equipamentos).equipamentos[(*equipamentos).numEquipamentos].nome, buffer);


        // Exemplo dentro de adicionarEquipamento:
        printf("\nTipo:\n0 - Vestuários\n1 - Veiculos\n2 - Ferramentas\n3 - Sistemas de Comunicação ");
        int espInput = obterInteiro(0, 2, "Escolha o Tipo: ");
        (*equipamentos).equipamentos[(*equipamentos).numEquipamentos].tipo = (TipoEquipamento)espInput;

        printf("\nEstado:\n0 - Disponivel\n1 - Em Uso\n2 - Em Manuntencao\n");
        int espInput = obterInteiro(0, 2, "Escolha a Estado: ");
        (*equipamentos).equipamentos[(*equipamentos).numEquipamentos].estado = (EstadoEquipamento)espInput;

        lerString(buffer, 100, "Localizacao: ");
        strcpy((*equipamentos).equipamentos[(*equipamentos).numEquipamentos].localizacao, buffer);

        (*equipamentos).numEquipamentos++;
        printf("Equipamento criado com sucesso!\n");
    } else {
        printf("O equipamento com esse ID já existe!!\n");
    }
}

void libertarMemEquipamentos(Equipamentos *equipamentos) {
    free(equipamentos->equipamentos);
    equipamentos->equipamentos = NULL;
    equipamentos->numEquipamentos = 0;
    equipamentos->totalEquipamentos = 0;
}

void imprimirEquipamento(Equipamento equipamento) {
    printf("\n----------------------------");
    printf("\nID: %d", equipamento.id);
    printf("\nNome: %s", equipamento.nome);

    printf("\nTipo: ");
    imprimirTipo(equipamento.tipo);

    printf("\nEstado Atual: ");
    imprimirEstado(equipamento.estado);
    printf("\n----------------------------\n");

    printf("\nLocalizacao: %s", equipamento.localizacao);
}

void listarEquipamentos(Equipamentos equipamentos) {
    int i;
    if (equipamentos.numEquipamentos > 0) {
        for (i = 0; i < equipamentos.numEquipamentos; i++) {
            if(equipamentos.equipamentos->ativo == 1) imprimirEquipamento(equipamentos.equipamentos[i]);
        }
    } else {
        printf("Não existem equipamentos registados!!\n");
    }
}

void atualizarDadosEquipamento(Equipamento *equipamento) {
    int escolha;
    char buffer[100];

    do {
        printf("\nAlterar:\n1- Nome\n2- Tipo\n3- Estado\n4- Localizacao\n5- Atividade (Ativo/Inativo)\n0- Voltar\n");
        escolha = obterInteiro(0, 4, "\nEscolha uma opção: ");

        switch (escolha) {
            case 0:
                break;
            case 1:
                lerString(buffer, 100, "Novo Nome: ");
                strcpy(equipamento->nome, buffer);
                break;
            case 2:
                equipamento->tipo = (TipoEquipamento)obterInteiro(0, 10, "Novo Tipo: ");
                break;
            case 3:
                equipamento->estado = (EstadoEquipamento)obterInteiro(0, 10, "Novo Estado: ");
                break;
            case 4:
                lerString(buffer, 100, "Nova Localizacao: ");
                strcpy(equipamento->localizacao, buffer);
                break;
            case 5:
                equipamento->ativo = obterInteiro(0, 1, "Definir ativo (1-Sim, 0-Não): ");
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
    int id = procurarEquipamento(*equipamentos, obterInteiro(0, 999999, "Insira o ID do equipamento a alterar: "));

    if (id != -1) {
        imprimirEquipamento((*equipamentos).equipamentos[id]);
        atualizarDadosEquipamento(&(*equipamentos).equipamentos[id]);
    } else {
        printf("Equipamento não existe!!\n");
    }
}

void eliminarEquipamento(Equipamentos *equipamentos) {
    listarEquipamentos(*equipamentos);
    printf("Eliminar equipamento:\n");

    int idBusca = obterInteiro(0, 999999, "Insira o ID do equipamento a eliminar: ");
    int indice = procurarEquipamento(*equipamentos, idBusca);

    if (indice != -1) {
        int i;
        for(i = indice; i < equipamentos->numEquipamentos - 1; i++){
            equipamentos->equipamentos[i] = equipamentos->equipamentos[i+1];
        }

        equipamentos->numEquipamentos--;

        printf("Equipamento eliminado com sucesso.\n");

    } else {
        printf("Equipamento não encontrado!!\n");
    }
}

// ------ FICHEIROS ------

void guardarEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "wb"); // "wb" = Write Binary
    if (ficheiro == NULL) {
        printf("\nErro ao criar o ficheiro 'data/equipamentos.bin'. Verifica se a pasta 'data' existe.\n");
        return;
    }

    fwrite(&equipamentos->totalEquipamentos, sizeof(int), 1, ficheiro);
    fwrite(&equipamentos->numEquipamentos, sizeof(int), 1, ficheiro);

    if (equipamentos->numEquipamentos > 0) {
        fwrite(equipamentos->equipamentos, sizeof(Equipamento), equipamentos->numEquipamentos, ficheiro);
    }

    fclose(ficheiro);
    printf("\nDados guardados em 'data/equipamentos.bin' com sucesso.\n");
}

void carregarBEquipamentos(Equipamentos *equipamentos) {
    FILE *ficheiro = fopen("data/equipamentos.bin", "rb"); // "rb" = Read Binary
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
        printf("Erro fatal: Falha de memória ao carregar ficheiro.\n");
        fclose(ficheiro);
        return;
    }

    if (equipamentos->numEquipamentos > 0) {
        fread(equipamentos->equipamentos, sizeof(Equipamento), equipamentos->numEquipamentos, ficheiro);
    }

    fclose(ficheiro);
    printf("\nCarregados %d bombeiros do ficheiro binário.\n", equipamentos->numEquipamentos);
}

