#include "input.h"
#include <stdio.h>
#include <string.h>

void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

int obterInteiro(int minValor, int maxValor, char *msg) {
    int valor;
    printf("%s", msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf("%s", msg);
    }
    cleanInputBuffer();
    return valor;
}

void lerString(char *string, unsigned int tamanho, char *msg){
    fflush(stdin);
    printf("%s",msg);
    if(fgets(string, tamanho, stdin) != NULL){
        unsigned int len = strlen(string) - 1;
        if(string[len] == '\n'){
            string[len] = '\0';
            
        }else{
            cleanInputBuffer();
        }
    }
}