#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enums.h"
#include "intervencao.h"
#include "gestaoIntervencao.h"
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

int procurarIntervencao(Intervencoes intervencoes, int id) {
    int i;
    for (i = 0; i < intervencoes.numIntervencoes; i++) {
        if (intervencoes.intervencoes[i].id == id) {
            return i;
        }
    }
    return -1;
}

void adicionarIntervencao(Intervencoes *intervencoes) {
int id;
printf("Criar intervencao:\n");
id = intervencoes->numIntervencoes + 1;

    if (procurarIntervencao(*intervencoes, id) == -1) {

        // Realocação de memória se o array estiver cheio
        if ((*intervencoes).totalIntervencoes == (*intervencoes).numIntervencoes) {
            (*intervencoes).totalIntervencoes += 3; // Expande de 3 em 3
            Intervencao *temp = (Intervencao*) realloc((*intervencoes).intervencoes, ((*intervencoes).totalIntervencoes) * sizeof(Intervencao));
            if (temp == NULL) {
                printf("Erro ao alocar memória!\n");
                return;
            }
            (*intervencoes).intervencoes = temp;
        }

        // Preenchimento dos dados
        (*intervencoes).intervencoes[(*intervencoes).numIntervencoes].id = id;
        (*intervencoes).intervencoes[(*intervencoes).numIntervencoes].ativo = 1; // Define como ativo por defeito

        // Leitura do Nome (Array fixo, usa strcpy)
        char buffer[100];
        lerString(buffer, 100, "ID da Ocorrencia: ");
        strcpy((*bombeiros).bombeiros[(*bombeiros).numBombeiros].nome, buffer);

        // VER O ID DA OCORRENCIA E  DATA E HORA INICIO E FIM ------------------------

        // Exemplo dentro de adicionarIntervencao:
        printf("\nEstados:\n0 - Em Planeamento\n1 - Em Execucao\n2 - Concluida\n");
        int estInput = obterInteiro(0, 2, "Defina o Estado: ");
        (*intervencoes).intervencoes[(*intervencoes).numIntervencoes].estado = (EstadoIntervencao)estInput;

        (*intervencoes).numIntervencoes++;
        printf("Intervencao criada com sucesso!\n");
    } else {
        printf("A intervencao com esse ID já existe!!\n");
    }
}

void libertarMemIntervencoes(Intervencoes *intervencoes) {
    free(intervencoes->intervencoes);
    intervencoes->intervencoes = NULL;
    intervencoes->numIntervencoes = 0;
    intervencoes->totalIntervencoes = 0;
}

void imprimirIntervencao(Intervencao intervencao) {
    printf("\n----------------------------");
    printf("\nID: %d", intervencao.id);
    printf("\nNome: %s", intervencao.nome);
//METER O ID E A DATA E A HORA DO INICIO E FIM -------------------------
    printf("\nEspecialidade: ");
    imprimirEspecialidade(bombeiro.especialidade);

    printf("\nEstado Atual: ");
    imprimirEstado(intervencao.estado);
    printf("\n----------------------------\n");
}

void listarBombeiros(Bombeiros bombeiros) {
    int i;
    if (bombeiros.numBombeiros > 0) {
        for (i = 0; i < bombeiros.numBombeiros; i++) {
            if(bombeiros.bombeiros->ativo == 1) imprimirBombeiro(bombeiros.bombeiros[i]);
        }
    } else {
        printf("Não existem intervencoes registados!!\n");
    }
}

void atualizarDadosIntervencao(Intervencao *intervencao) {
    int escolha;
    char buffer[100];

    do {
        printf("\nAlterar:\n1- ID da Ocorrencia\n2- Data e hora inicial\n3- Data e hora final\n4- Estado\n4- Atividade (Ativo/Inativo)\n0- Voltar\n");
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
    // FAZER O ID DA OCORRENCIA E A DATA E HORA INICIAL E FINAL ----------------------------
            case 3:
                intervencao->estado = (EstadoIntervencao)obterInteiro(0, 10, "Nova Intervencao: ");
                break;
            case 4:
                intervencao->ativo = obterInteiro(0, 1, "Definir ativo (1-Sim, 0-Não): ");
                break;
            default:
                printf("Opção inválida\n");
                break;
        }
    } while (escolha != 0);
}

void editarIntervencao(Intervencoes *intervencoes) {
    listarIntervencoes(*intervencoes);
    printf("Editar dados da intervencao:\n");
    int id = procurarIntervencao(*intervencoes, obterInteiro(0, 999999, "Insira o ID da intervencao a alterar: "));

    if (id != -1) {
        imprimirIntervencao((*intervencoes).intervencoes[id]);
        atualizarDadosIntervencao(&(*intervencoes).intervencoes[id]);
    } else {
        printf("Intervencao não existe!!\n");
    }
}

void eliminarIntervencao(Intervencoes *intervencoes) {
    listarIntervencoes(*intervencoes);
    printf("Eliminar intervencao:\n");

    int idBusca = obterInteiro(0, 999999, "Insira o ID da intervencao a eliminar: ");
    int indice = procurarIntervencao(*intervencoes, idBusca);

    if (indice != -1) {
        int i;
        for(i = indice; i < intervencoes->numIntervencoes - 1; i++){
            intervencoes->intervencoes[i] = intervencoes->intervencoes[i+1];
        }

        intervencoes->numIntervencoes--;

        printf("Intervencao eliminado com sucesso.\n");

    } else {
        printf("Intervencao não encontrada!!\n");
    }
}

// ------ FICHEIROS ------

void guardarIntervencoes(Intervencoes *intervencoes) {
    FILE *ficheiro = fopen("data/intervencoes.bin", "wb"); // "wb" = Write Binary
    if (ficheiro == NULL) {
        printf("\nErro ao criar o ficheiro 'data/intervencoes.bin'. Verifica se a pasta 'data' existe.\n");
        return;
    }

    fwrite(&intervencoes->totalIntervencoes, sizeof(int), 1, ficheiro);
    fwrite(&intervencoes->numIntervencoes, sizeof(int), 1, ficheiro);

    if (intervencoes->numIntervencoes > 0) {
        fwrite(intervencoes->intervencoes, sizeof(Intervencao), intervencoes->numIntervencoes, ficheiro);
    }

    fclose(ficheiro);
    printf("\nDados guardados em 'data/intervencoes.bin' com sucesso.\n");
}

void carregarIntervencoes(Intervencoes *intervencoes) {
    FILE *ficheiro = fopen("data/intervencoes.bin", "rb"); // "rb" = Read Binary
    if (ficheiro == NULL) {
        printf("\nO ficheiro 'intervencoes.bin' não foi encontrado. A iniciar a lista vazia.\n");
        intervencoes->numIntervencoes = 0;
        intervencoes->totalIntervencoes = 5;
        intervencoes->intervencoes = (Intervencao*) malloc(intervencoes->totalIntervencoes * sizeof(Intervencao));
        return;
    }

    fread(&intervencoes->totalIntervencoes, sizeof(int), 1, ficheiro);
    fread(&intervencoes->numIntervencoes, sizeof(int), 1, ficheiro);

    intervencoes->intervencoes = (Intervencao*) malloc(intervencoes->totalIntervencoes * sizeof(Intervencao));

    if (intervencoes->intervencoes == NULL) {
        printf("Erro fatal: Falha de memória ao carregar ficheiro.\n");
        fclose(ficheiro);
        return;
    }

    if (intervencoes->numIntervencoes > 0) {
        fread(intervencoes->intervencoes, sizeof(Intervencao), intervencoes->numIntervencoes, ficheiro);
    }

    fclose(ficheiro);
    printf("\nCarregados %d intervencoes do ficheiro binário.\n", intervencoes->numIntervencoes);
}

