
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enums.h"
#include "bombeiro.h"
#include "gestaoBombeiro.h"
#include "input.h"

// Função auxiliar para imprimir o texto dos Enums (Exemplo genérico)
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
        case EM_DISPONIVEL:
            printf("Disponível");
            break;
        case EM_INTERVENCAO:
            printf("Em Intervenção");
            break;
        case EM_TREINO:
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
int id;
printf("Criar bombeiro:\n");
id = bombeiros->numBombeiros + 1;

    if (procurarBombeiro(*bombeiros, id) == -1) {

        // Realocação de memória se o array estiver cheio
        if ((*bombeiros).totalBombeiros == (*bombeiros).numBombeiros) {
            (*bombeiros).totalBombeiros += 3; // Expande de 3 em 3
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

        // Leitura do Nome (Array fixo, usa strcpy)
        char buffer[100];
        lerString(buffer, 100, "Nome: ");
        strcpy((*bombeiros).bombeiros[(*bombeiros).numBombeiros].nome, buffer);


        // Exemplo dentro de adicionarBombeiro:
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
    free(bombeiros->bombeiros);
    bombeiros->bombeiros = NULL;
    bombeiros->numBombeiros = 0;
    bombeiros->totalBombeiros = 0;
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
    int i;
    if (bombeiros.numBombeiros > 0) {
        for (i = 0; i < bombeiros.numBombeiros; i++) {
            if(bombeiros.bombeiros->ativo == 1) imprimirBombeiro(bombeiros.bombeiros[i]);
        }
    } else {
        printf("Não existem bombeiros registados!!\n");
    }
}

void atualizarDadosBombeiro(Bombeiro *bombeiro) {
    int escolha;
    char buffer[100];

    do {
        printf("\nAlterar:\n1- Nome\n2- Especialidade\n3- Estado\n4- Atividade (Ativo/Inativo)\n0- Voltar\n");
        escolha = obterInteiro(0, 4, "\nEscolha uma opção: ");

        switch (escolha) {
            case 0:
                break;
            case 1:
                lerString(buffer, 100, "Novo Nome: ");
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
    int id = procurarBombeiro(*bombeiros, obterInteiro(0, 999999, "Insira o ID do bombeiro a alterar: "));

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

void guardarBombeiros(Bombeiros *bombeiros) {
    FILE *ficheiro = fopen("data/bombeiros.bin", "wb"); // "wb" = Write Binary
    if (ficheiro == NULL) {
        printf("\nErro ao criar o ficheiro 'data/bombeiros.bin'. Verifica se a pasta 'data' existe.\n");
        return;
    }

    fwrite(&bombeiros->totalBombeiros, sizeof(int), 1, ficheiro);
    fwrite(&bombeiros->numBombeiros, sizeof(int), 1, ficheiro);

    if (bombeiros->numBombeiros > 0) {
        fwrite(bombeiros->bombeiros, sizeof(Bombeiro), bombeiros->numBombeiros, ficheiro);
    }

    fclose(ficheiro);
    printf("\nDados guardados em 'data/bombeiros.bin' com sucesso.\n");
}

void carregarBombeiros(Bombeiros *bombeiros) {
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

    bombeiros->bombeiros = (Bombeiro*) malloc(bombeiros->totalBombeiros * sizeof(Bombeiro));

    if (bombeiros->bombeiros == NULL) {
        printf("Erro fatal: Falha de memória ao carregar ficheiro.\n");
        fclose(ficheiro);
        return;
    }

    if (bombeiros->numBombeiros > 0) {
        fread(bombeiros->bombeiros, sizeof(Bombeiro), bombeiros->numBombeiros, ficheiro);
    }

    fclose(ficheiro);
    printf("\nCarregados %d bombeiros do ficheiro binário.\n", bombeiros->numBombeiros);
}





