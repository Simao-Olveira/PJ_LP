#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enums.h"
#include "bombeiro.h"
#include "gestaoBombeiro.h"
#include "input.h"

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
    int i;
    for (i = 0; i < bombeiros.numBombeiros; i++) {
        if (bombeiros.bombeiros[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarBombeiro(Bombeiros *bombeiros) {
    printf("Criar bombeiro:\n");
    int id = bombeiros->numBombeiros + 1;

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
        (*bombeiros).bombeiros[(*bombeiros).numBombeiros].ativo = 1; // Define como ativo por defeito

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
            if(bombeiros.bombeiros[i].ativo == 1) imprimirBombeiro(bombeiros.bombeiros[i]);
        }
    } else {
        printf("Não existem bombeiros registados!!\n");
    }
}

void atualizarDadosBombeiro(Bombeiro *bombeiro) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\nAlterar:\n1- Nome\n2- Especialidade\n3- Estado\n4- Atividade (Ativo/Inativo)\n0- Voltar\n");
        escolha = obterInteiro(0, 4, "\nEscolha uma opção: ");
        
        switch (escolha) {
            case 0:
                break;
            case 1:
                lerString(buffer, SIZE_BUFFER, "Nome: ");
                bombeiro->nome = realloc(bombeiro->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(bombeiro->nome, buffer);
                break;
            case 2:
                bombeiro->especialidade = (EspecialidadeBombeiro)obterInteiro(0, 10, "Nova Especialidade: ");
                break;
            case 3:
                bombeiro->estado = (EstadoBombeiro)obterInteiro(0, 10, "Novo Estado: ");
                break;
            case 4:
                bombeiro->ativo = obterInteiro(0, 1, "Definir ativo (1-Sim, 0-Não): ");
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
    } else {
        printf("Bombeiro não existe!!\n");
    }
}

void eliminarBombeiro(Bombeiros *bombeiros) {    
    listarBombeiros(*bombeiros);
    printf("Eliminar bombeiro:\n");
    
    int idBusca = obterInteiro(0, 999999, "Insira o ID do bombeiro a eliminar: ");
    int indice = procurarBombeiro(*bombeiros, idBusca);

    if (indice != -1) {
        int i;
        for(i = indice; i < bombeiros->numBombeiros - 1; i++){
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
    FILE *ficheiro = fopen("data/bombeiros.bin", "rb"); // "rb" = Read Binary
    if (ficheiro == NULL) {
        printf("\nO ficheiro 'bombeiros.bin' não foi encontrado. A iniciar a lista vazia.\n");
        bombeiros->numBombeiros = 0;
        bombeiros->totalBombeiros = 5; 
        bombeiros->bombeiros = (Bombeiro*) malloc(bombeiros->totalBombeiros * sizeof(Bombeiro));
        return;
    }

    fread(&bombeiros->totalBombeiros, sizeof(int), 1, ficheiro);
    fread(&bombeiros->numBombeiros, sizeof(int), 1, ficheiro);

     if (bombeiros->numBombeiros == 0) {
        fclose(ficheiro);
        printf("\nNao existem bombeiros para importar\n");

    } else {
        bombeiros->bombeiros = (Bombeiro*) realloc((*bombeiros).bombeiros, ((*bombeiros).totalBombeiros) * sizeof (Bombeiro));
        for (int i = 0; i < bombeiros->numBombeiros; i++) {
            fread(&bombeiros->bombeiros[i].id, sizeof(int), 1, ficheiro);
            fread(&bombeiros->bombeiros[i].especialidade, sizeof(EspecialidadeBombeiro), 1, ficheiro);
            fread(&bombeiros->bombeiros[i].estado, sizeof(EstadoBombeiro), 1, ficheiro);
            fread(&bombeiros->bombeiros[i].ativo, sizeof(int), 1, ficheiro);
            int buffer;
            fread(&buffer, sizeof (int), 1, ficheiro);
            bombeiros->bombeiros[i].nome = (char*) malloc(sizeof (char) * (buffer + 1));
            fread(bombeiros->bombeiros[i].nome, sizeof (char), buffer, ficheiro);
            bombeiros->bombeiros[i].nome[buffer] = '\0';
        }
        fclose(ficheiro);
        printf("\nCarregados %d bombeiros.\n", bombeiros->numBombeiros);
    }
}

void writeBombeiros(Bombeiros *bombeiros) {
    FILE *ficheiro = fopen("data/bombeiros.bin", "wb");
    if (ficheiro == NULL) {
        printf("\nErro ao criar ficheiro.\n");
        return;
    }

    fwrite(&bombeiros->totalBombeiros, sizeof(int), 1, ficheiro);
    fwrite(&bombeiros->numBombeiros, sizeof(int), 1, ficheiro);

    for (int i = 0; i < bombeiros->numBombeiros; i++) {
        fwrite(&bombeiros->bombeiros[i].id, sizeof(int), 1, ficheiro);
        fwrite(&bombeiros->bombeiros[i].especialidade, sizeof(EspecialidadeBombeiro), 1, ficheiro);
        fwrite(&bombeiros->bombeiros[i].estado, sizeof(EstadoBombeiro), 1, ficheiro);
        fwrite(&bombeiros->bombeiros[i].ativo, sizeof(int), 1, ficheiro);
        int buffer = strlen(bombeiros->bombeiros[i].nome); 
        fwrite(&buffer, sizeof(int), 1, ficheiro);
        fwrite(bombeiros->bombeiros[i].nome, sizeof (char), buffer, ficheiro);
    }

    fclose(ficheiro);
    printf("\nBombeiros guardados com sucesso.\n");
}