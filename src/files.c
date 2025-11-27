#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/bombeiro.h"
#include "../headers/files.h"
#include "../headers/ocorrencia.h"
#include "../headers/equipamento.h"
#include "../headers/enums.h"

// Abre um ficheiro para leitura e verifica erros
FILE* abrirParaLeitura(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (f == NULL) {
        printf("Erro: nao foi possivel abrir o ficheiro %s\n", caminho);
        return NULL;
    }
    return f;
}

// Conta quantas linhas o ficheiro tem
int contarLinhas(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (f == NULL) return 0;

    int linhas = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), f)) {
        linhas++;
    }

    fclose(f);
    return linhas;
}

// Le uma linha de forma segura
char* lerLinha(FILE *f, char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, f)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove '\n'
        return buffer;
    }
    return NULL;
}

//#########################################################################
// Funções específicas para ler e escrever estruturas
//#########################################################################

Ocorrencia* carregarOcorrencias(const char *caminho, int *tamanho) {
    FILE *f = abrirParaLeitura(caminho);
    if (f == NULL) return NULL;

    *tamanho = contarLinhas(caminho);
    Ocorrencia *ocorrencias = malloc((*tamanho) * sizeof(Ocorrencia));
    if (ocorrencias == NULL) {
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < *tamanho; i++) {
        fscanf(f, "%d;%99[^;];%d;%d;%d\n",
                &ocorrencias[i].id,
                ocorrencias[i].local,
                (int*)&ocorrencias[i].tipo,
                (int*)&ocorrencias[i].prioridade,
                (int*)&ocorrencias[i].estado);
    }

    fclose(f);
    return ocorrencias;
}


Bombeiro* carregarBombeiros(const char *caminho, int *tamanho) {
    FILE *f = abrirParaLeitura(caminho);
    if (f == NULL) return NULL;

    *tamanho = contarLinhas(caminho);
    Bombeiro *bombeiros = malloc((*tamanho) * sizeof(Bombeiro));
    if (bombeiros == NULL) {
        fclose(f);
        return NULL;
    }

    for (int i = 0; i < *tamanho; i++) {
        fscanf(f, "%d;%99[^;];%d;%d;%d\n",
                &bombeiros[i].id,
                bombeiros[i].nome,
                &bombeiros[i].idade,
                (int*)&bombeiros[i].especialidade,
                (int*)&bombeiros[i].estado);
    }

    fclose(f);
    return bombeiros;
}

