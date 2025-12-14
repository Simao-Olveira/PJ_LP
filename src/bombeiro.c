#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bombeiro.h"
#include "gestaoBombeiro.h"
#include "enums.h"
#include "input.h"
#include "log.h"

// Função auxiliar para imprimir o texto dos Enums
void imprimirEspecialidade(EspecialidadeBombeiro esp) {
    switch (esp) {
        case COMBATE_FLORESTAL:
            printf("Combate Florestal");
            break;
        case COMBATE_AEREO:
            printf("Combate Aéreo");
            break;
        case RESGATE:
            printf("Resgate");
            break;
        default:
            printf("Desconhecido");
            break;
    }
}

// Converte o Enum Estado em texto
void imprimirEstado(EstadoBombeiro est) {
    switch (est) {
        case EB_DISPONIVEL:
            printf("Disponível");
            break;
        case EB_INTERVENCAO:
            printf("Em Intervenção");
            break;
        case EB_TREINO:
            printf("Em Treino");
            break;
        default:
            printf("Desconhecido");
            break;
    }
}

int procurarBombeiro(Bombeiros bombeiros, int id) {
    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        if (bombeiros.bombeiros[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarBombeiro(Bombeiros *bombeiros) {
    printf("\n--- Novo Bombeiro ---\n");

    int maiorId = 0;
    for(int i = 0; i < bombeiros->numBombeiros; i++) {
        if(bombeiros->bombeiros[i].id > maiorId) {
            maiorId = bombeiros->bombeiros[i].id;
        }
    }
    int id = maiorId + 1;

    if (procurarBombeiro(*bombeiros, id) == -1) {

        if ((*bombeiros).totalBombeiros == (*bombeiros).numBombeiros) {
            (*bombeiros).totalBombeiros += 3; 
            Bombeiro *temp = (Bombeiro*) realloc((*bombeiros).bombeiros, ((*bombeiros).totalBombeiros) * sizeof(Bombeiro));
            if (temp == NULL) {
                printf("Erro ao alocar memória!\n");
                return;
            }
            (*bombeiros).bombeiros = temp;
        }

        // Preenchimento dos dados
        (*bombeiros).bombeiros[(*bombeiros).numBombeiros].id = id;

        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Nome: ");
        (*bombeiros).bombeiros[(*bombeiros).numBombeiros].nome = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*bombeiros).bombeiros[(*bombeiros).numBombeiros].nome != NULL) {
            strcpy((*bombeiros).bombeiros[(*bombeiros).numBombeiros].nome, buffer);
        }
        
        printf("\nEspecialidades:\n0 - Combate Florestal\n1 - Combate Aéreo\n2 - Resgate\n");
        int espInput = obterInteiro(0, 2, "Escolha a Especialidade: ");
        (*bombeiros).bombeiros[(*bombeiros).numBombeiros].especialidade = (EspecialidadeBombeiro)espInput;

        printf("\nEstados:\n0 - Disponível\n1 - Em Intervenção\n2 - Em Treino\n");
        int estInput = obterInteiro(0, 2, "Defina o Estado inicial: ");
        (*bombeiros).bombeiros[(*bombeiros).numBombeiros].estado = (EstadoBombeiro)estInput;

        (*bombeiros).numBombeiros++;
        printf("Bombeiro criado com sucesso!\n");
    } else {
        printf("O bombeiro com esse ID já existe!!\n");
    }
}

void libertarMemBombeiros(Bombeiros *bombeiros) {
    for (int i = 0; i < bombeiros->numBombeiros; i++) {
        free(bombeiros->bombeiros[i].nome);
    }
    free(bombeiros->bombeiros);
}

void imprimirBombeiro(Bombeiro bombeiro) {
    printf("\n----------------------------");
    printf("\nID: %d", bombeiro.id);
    printf("\nNome: %s", bombeiro.nome);
    
    printf("\nEspecialidade: ");
    imprimirEspecialidade(bombeiro.especialidade);
    
    printf("\nEstado Atual: ");
    imprimirEstado(bombeiro.estado);
    printf("\n----------------------------\n");
}

void listarBombeiros(Bombeiros bombeiros) {
    if (bombeiros.numBombeiros > 0) {
        for (int i = 0; i < bombeiros.numBombeiros; i++) {
            imprimirBombeiro(bombeiros.bombeiros[i]);
        }
    } else {
        printf("Não existem bombeiros registados!!\n");
    }
}

void atualizarDadosBombeiro(Bombeiro *bombeiro) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Nome\n");
        printf("2- Especialidade\n");
        printf("3- Estado\n");
        printf("0- Voltar\n");
        escolha = obterInteiro(0, 5, "\nEscolha uma opção: ");
        switch (escolha) {
            case 0:
                break;
            case 1:
                lerString(buffer, SIZE_BUFFER, "Novo Nome: ");
                bombeiro->nome = realloc(bombeiro->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(bombeiro->nome, buffer);
                break;
            case 2:
                printf("\nEspecialidades:\n0 - Combate Florestal\n1 - Combate Aéreo\n2 - Resgate\n");
                bombeiro->especialidade = (EspecialidadeBombeiro)obterInteiro(0, 2, "Escolha a nova Especialidade: ");
                break;
            case 3:
                printf("\nEstados:\n0 - Disponível\n1 - Em Intervenção\n2 - Em Treino\n");
                bombeiro->estado = (EstadoBombeiro)obterInteiro(0, 2, "Escolha o novo Estado: ");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (escolha != 0);
}

void editarBombeiro(Bombeiros *bombeiros) {
    listarBombeiros(*bombeiros);
    printf("Editar dados do bombeiro:\n");
    int id = procurarBombeiro(*bombeiros, obterInteiro(0, MAX_INT, "Insira o ID do bombeiro a alterar: "));

    if (id != -1) {
        imprimirBombeiro((*bombeiros).bombeiros[id]);
        atualizarDadosBombeiro(&(*bombeiros).bombeiros[id]);
        printf("Bombeiro atualizado com sucesso!\n");
    } else {
        printf("\nBombeiro não existe!!\n\n");
    }
}

void eliminarBombeiro(Bombeiros *bombeiros) {    
    listarBombeiros(*bombeiros);
    printf("Eliminar bombeiro:\n");
    
    int idBusca = obterInteiro(0, MAX_INT, "Insira o ID do bombeiro a eliminar: ");
    int indice = procurarBombeiro(*bombeiros, idBusca);

    if (indice != -1) {
        free(bombeiros->bombeiros[indice].nome);

        for(int i = indice; i < bombeiros->numBombeiros - 1; i++){
            bombeiros->bombeiros[i] = bombeiros->bombeiros[i+1];
        }

        bombeiros->numBombeiros--;
        
        printf("Bombeiro eliminado com sucesso.\n");

    } else {
        printf("Bombeiro não encontrado!!\n");
    }
}

// ------ FICHEIROS ------

void readBombeiros(Bombeiros *bombeiros) {
    FILE *ficheiro = fopen("data/bombeiros.bin", "rb");
    
    if (ficheiro == NULL) {
        logMsg("Ficheiro 'bombeiros.bin' não foi encontrado. A iniciar a lista vazia.");
        bombeiros->numBombeiros = 0;
        bombeiros->totalBombeiros = 5; 
        bombeiros->bombeiros = (Bombeiro*) malloc(bombeiros->totalBombeiros * sizeof(Bombeiro));
        return;
    }

    fread(&bombeiros->totalBombeiros, sizeof(int), 1, ficheiro);
    fread(&bombeiros->numBombeiros, sizeof(int), 1, ficheiro);

    if (bombeiros->numBombeiros == 0) {
        bombeiros->totalBombeiros = 5; // Garante tamanho mínimo
        bombeiros->bombeiros = (Bombeiro*) malloc(bombeiros->totalBombeiros * sizeof(Bombeiro));
        fclose(ficheiro);
        logMsg("\nLista de bombeiros importada vazia.\n");
        return;
    }

    bombeiros->bombeiros = (Bombeiro*) malloc(bombeiros->totalBombeiros * sizeof(Bombeiro));

    for (int i = 0; i < bombeiros->numBombeiros; i++) {
        fread(&bombeiros->bombeiros[i].id, sizeof(int), 1, ficheiro);
        fread(&bombeiros->bombeiros[i].especialidade, sizeof(EspecialidadeBombeiro), 1, ficheiro);
        fread(&bombeiros->bombeiros[i].estado, sizeof(EstadoBombeiro), 1, ficheiro);
        
        int bufferTam;
        fread(&bufferTam, sizeof (int), 1, ficheiro);
        bombeiros->bombeiros[i].nome = (char*) malloc(sizeof (char) * (bufferTam + 1));
        fread(bombeiros->bombeiros[i].nome, sizeof (char), bufferTam, ficheiro);
        bombeiros->bombeiros[i].nome[bufferTam] = '\0';
    }
    
    fclose(ficheiro);
    logMsg("Bombeiros carregados com sucesso do ficheiro.");
}
void writeBombeiros(Bombeiros *bombeiros) {
    FILE *ficheiro = fopen("data/bombeiros.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro.\n");
        logMsg("Erro ao criar ficheiro 'bombeiros.bin'.");
        return;
    }

    fwrite(&bombeiros->totalBombeiros, sizeof(int), 1, ficheiro);
    fwrite(&bombeiros->numBombeiros, sizeof(int), 1, ficheiro);

    for (int i = 0; i < bombeiros->numBombeiros; i++) {
        fwrite(&bombeiros->bombeiros[i].id, sizeof(int), 1, ficheiro);
        fwrite(&bombeiros->bombeiros[i].especialidade, sizeof(EspecialidadeBombeiro), 1, ficheiro);
        fwrite(&bombeiros->bombeiros[i].estado, sizeof(EstadoBombeiro), 1, ficheiro);
        int buffer = strlen(bombeiros->bombeiros[i].nome); 
        fwrite(&buffer, sizeof(int), 1, ficheiro);
        fwrite(bombeiros->bombeiros[i].nome, sizeof (char), buffer, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Bombeiros guardados com sucesso no ficheiro.");
}