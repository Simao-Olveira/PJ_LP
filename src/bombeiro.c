/**
 * @file bombeiro.c
 * @brief Implementação das funções de gestão de bombeiros.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bombeiro.h"
#include "gestaoBombeiro.h"
#include "quartel.h" 
#include "gestaoQuartel.h" 
#include "enums.h"
#include "input.h"
#include "log.h"

/** @brief Converte o enum Especialidade numa string para impressão. */
void imprimirEspecialidade(EspecialidadeBombeiro esp) {
    switch (esp) {
        case COMBATE_FLORESTAL: printf("Combate Florestal"); break;
        case COMBATE_AEREO:     printf("Combate Aéreo"); break;
        case RESGATE:           printf("Resgate"); break;
        default:                printf("Desconhecido"); break;
    }
}

/** @brief Converte o enum Estado numa string para impressão. */
void imprimirEstado(EstadoBombeiro est) {
    switch (est) {
        case EB_DISPONIVEL:  printf("Disponível"); break;
        case EB_INTERVENCAO: printf("Em Intervenção"); break;
        case EB_TREINO:      printf("Em Treino"); break;
        default:             printf("Desconhecido"); break;
    }
}

/** * @brief Procura um bombeiro pelo ID.
 * * Percorre sequencialmente a lista de bombeiros até encontrar o identificador 
 * correspondente, devolvendo a posição (índice) onde este se encontra.
 * @return O índice no array se encontrado, ou -1 caso contrário.
 */
int procurarBombeiro(Bombeiros bombeiros, int id) {
    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        if (bombeiros.bombeiros[i].id == id) {
            return i;
        }
    }
    return -1;
}

/** * @brief Adiciona um novo bombeiro ao sistema.
 * * Calcula automaticamente o próximo ID disponível e verifica se existe capacidade 
 * no array dinâmico, redimensionando a memória (realloc) se necessário.
 * A função aloca memória específica para o nome e valida se o quartel indicado 
 * existe na lista de quartéis antes de criar o registo final.
 */
void adicionarBombeiro(Bombeiros *bombeiros, Quarteis *quarteis) {
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
                printf("Erro crítico: Falha ao alocar memória!\n");
                return;
            }
            (*bombeiros).bombeiros = temp;
        }

        (*bombeiros).bombeiros[(*bombeiros).numBombeiros].id = id;

        char buffer[SIZE_BUFFER];
        lerString(buffer, SIZE_BUFFER, "Nome: ");
        
        // Aloca apenas o tamanho exato da string para poupar memória
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

        if (quarteis != NULL && quarteis->numQuarteis > 0) {
            printf("\n--- Associar a Quartel ---\n");
            listarQuarteis(*quarteis);
            
            printf("(Digite 0 para deixar sem quartel)\n");
            int idQ = obterInteiro(0, MAX_INT, "ID do Quartel: ");
            
            if (idQ != 0) {
                if (procurarQuartel(*quarteis, idQ) != -1) {
                    (*bombeiros).bombeiros[(*bombeiros).numBombeiros].quartel = idQ;
                } else {
                    printf("Quartel não encontrado. Ficará sem nenhum atribuído (0).\n");
                    (*bombeiros).bombeiros[(*bombeiros).numBombeiros].quartel = 0;
                }
            } else {
                (*bombeiros).bombeiros[(*bombeiros).numBombeiros].quartel = 0;
            }
        } else {
            printf("\nAviso: Não existem quartéis registados. O bombeiro ficará sem quartel.\n");
            (*bombeiros).bombeiros[(*bombeiros).numBombeiros].quartel = 0;
        }

        (*bombeiros).numBombeiros++;
        printf("Bombeiro criado com sucesso!\n");
    } else {
        printf("O bombeiro com esse ID já existe!!\n");
    }
}

/** * @brief Liberta toda a memória associada aos bombeiros.
 * * Itera sobre todos os registos para libertar individualmente a memória das 
 * strings (nomes) antes de libertar o array principal de estruturas.
 */
void libertarMemBombeiros(Bombeiros *bombeiros) {
    for (int i = 0; i < bombeiros->numBombeiros; i++) {
        free(bombeiros->bombeiros[i].nome);
    }
    free(bombeiros->bombeiros);
}

/** @brief Imprime os detalhes de um único bombeiro no ecrã. */
void imprimirBombeiro(Bombeiro bombeiro) {
    printf("\n----------------------------");
    printf("\nID: %d", bombeiro.id);
    printf("\nNome: %s", bombeiro.nome);
    printf("\nEspecialidade: "); imprimirEspecialidade(bombeiro.especialidade);
    printf("\nEstado Atual: "); imprimirEstado(bombeiro.estado);

    if (bombeiro.quartel != 0) {
        printf("\nQuartel ID: %d", bombeiro.quartel);
    } else {
        printf("\nQuartel: Sem atribuição");
    }
    printf("\n----------------------------\n");
}

/** @brief Lista todos os bombeiros registados. */
void listarBombeiros(Bombeiros bombeiros) {
    if (bombeiros.numBombeiros > 0) {
        for (int i = 0; i < bombeiros.numBombeiros; i++) {
            imprimirBombeiro(bombeiros.bombeiros[i]);
        }
    } else {
        printf("Não existem bombeiros registados!!\n");
    }
}

/** * @brief Submenu para atualizar campos específicos.
 * * Permite a edição parcial dos campos. Ao alterar o nome, a memória é 
 * realocada para se ajustar ao tamanho da nova string. A alteração do 
 * quartel implica uma nova pesquisa para validar se o ID existe.
 */
void atualizarDadosBombeiro(Bombeiro *bombeiro, Quarteis *quarteis) {
    int escolha;
    char buffer[SIZE_BUFFER];

    do {
        printf("\n--- Editar Dados ---\n");
        printf("1- Nome\n2- Especialidade\n3- Estado\n4- Quartel\n0- Voltar\n");
        escolha = obterInteiro(0, 4, "\nEscolha uma opção: ");
        switch (escolha) {
            case 0: break;
            case 1:
                lerString(buffer, SIZE_BUFFER, "Novo Nome: ");
                bombeiro->nome = realloc(bombeiro->nome, (strlen(buffer) + 1) * sizeof (char));
                strcpy(bombeiro->nome, buffer);
                break;
            case 2:
                printf("\n0 - Combate Florestal\n1 - Combate Aéreo\n2 - Resgate\n");
                bombeiro->especialidade = (EspecialidadeBombeiro)obterInteiro(0, 2, "Nova Especialidade: ");
                break;
            case 3:
                printf("\n0 - Disponível\n1 - Em Intervenção\n2 - Em Treino\n");
                bombeiro->estado = (EstadoBombeiro)obterInteiro(0, 2, "Novo Estado: ");
                break;
            case 4:
                if (quarteis != NULL && quarteis->numQuarteis > 0) {
                    listarQuarteis(*quarteis);
                    int idQ = obterInteiro(0, MAX_INT, "Novo ID Quartel (0 para remover): ");
                    
                    if (idQ == 0) {
                        bombeiro->quartel = 0; 
                        printf("Quartel removido.\n");
                    } else if (procurarQuartel(*quarteis, idQ) != -1) {
                        bombeiro->quartel = idQ;
                        printf("Quartel atualizado.\n");
                    } else {
                        printf("Quartel não encontrado.\n");
                    }
                } else {
                    printf("Não existem quartéis registados.\n");
                }
                break;
            default: printf("Opção inválida\n"); break;
        }
    } while (escolha != 0);
}

/** @brief Procura o bombeiro pelo ID e inicia o menu de edição. */
void editarBombeiro(Bombeiros *bombeiros, Quarteis *quarteis) {
    listarBombeiros(*bombeiros);
    printf("Editar dados do bombeiro:\n");
    int id = procurarBombeiro(*bombeiros, obterInteiro(0, MAX_INT, "Insira o ID do bombeiro a alterar: "));

    if (id != -1) {
        imprimirBombeiro((*bombeiros).bombeiros[id]);
        atualizarDadosBombeiro(&(*bombeiros).bombeiros[id], quarteis);
        printf("Bombeiro atualizado com sucesso!\n");
    } else {
        printf("\nBombeiro não existe!!\n\n");
    }
}

/** * @brief Elimina um bombeiro do array.
 * * Liberta a memória alocada para o nome do bombeiro alvo e reorganiza o array, 
 * deslocando todos os elementos seguintes uma posição para trás (shift left) 
 * para preencher o espaço vazio.
 */
void eliminarBombeiro(Bombeiros *bombeiros) {    
    listarBombeiros(*bombeiros);
    printf("Eliminar bombeiro:\n");
    
    int idBusca = obterInteiro(0, MAX_INT, "Insira o ID do bombeiro a eliminar: ");
    int indice = procurarBombeiro(*bombeiros, idBusca);

    if (indice != -1) {
        free(bombeiros->bombeiros[indice].nome);

        for(int i = indice; i < bombeiros->numBombeiros - 1; i++){
            bombeiros->bombeiros[i] = bombeiros->bombeiros[i + 1];
        }

        bombeiros->numBombeiros--;
        printf("Bombeiro eliminado com sucesso.\n");
    } else {
        printf("Bombeiro não encontrado!!\n");
    }
}

// ------ FICHEIROS ------

/** * @brief Carrega dados do ficheiro binário.
 * * Lê inicialmente os totais para alocar o array de estruturas. De seguida, 
 * recupera os dados de cada bombeiro, lendo primeiro o tamanho do nome (int) 
 * para alocar a memória exata necessária antes de ler os caracteres da string.
 */
void carregarBombeiros(Bombeiros *bombeiros) {
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
        bombeiros->totalBombeiros = 5; 
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
        fread(&bombeiros->bombeiros[i].quartel, sizeof(int), 1, ficheiro);
        
        int bufferTam;
        fread(&bufferTam, sizeof (int), 1, ficheiro);
        bombeiros->bombeiros[i].nome = (char*) malloc(sizeof (char) * (bufferTam + 1));
        fread(bombeiros->bombeiros[i].nome, sizeof (char), bufferTam, ficheiro);
        bombeiros->bombeiros[i].nome[bufferTam] = '\0';
    }
    
    fclose(ficheiro);
    logMsg("Bombeiros carregados com sucesso do ficheiro.");
}

/** * @brief Guarda dados em ficheiro binário.
 * * Escreve a estrutura completa em disco. Para as strings dinâmicas (nomes), 
 * guarda primeiro o tamanho da string em bytes seguido dos caracteres, 
 * permitindo a recuperação correta na leitura.
 */
void guardarBombeiros(Bombeiros *bombeiros) {
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
        fwrite(&bombeiros->bombeiros[i].quartel, sizeof(int), 1, ficheiro);
        
        int buffer = strlen(bombeiros->bombeiros[i].nome); 
        fwrite(&buffer, sizeof(int), 1, ficheiro);
        fwrite(bombeiros->bombeiros[i].nome, sizeof (char), buffer, ficheiro);
    }

    fclose(ficheiro);
    logMsg("Bombeiros guardados com sucesso no ficheiro.");
}