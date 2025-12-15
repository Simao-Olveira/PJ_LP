/**
 * @file input.c
 * @brief Implementação de funções utilitárias para entrada de dados segura.
 */

#include "input.h"
#include <stdio.h>
#include <string.h>

/** * @brief Limpa o buffer de entrada (stdin).
 * * Lógica: Consome todos os caracteres pendentes no buffer de entrada num ciclo 
 * até encontrar uma quebra de linha ('\\n') ou o fim do ficheiro (EOF). 
 * Isto impede que caracteres "lixo" deixados por leituras anteriores (como um Enter 
 * pendente) afetem a próxima solicitação de dados.
 */
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/** * @brief Solicita um número inteiro dentro de um intervalo específico.
 * * Lógica de Validação:
 * 1. Exibe a mensagem ao utilizador.
 * 2. Utiliza um ciclo `while` que verifica três condições de erro simultaneamente:
 * - Se o `scanf` falhou em ler um número (retorno != 1).
 * - Se o valor é menor que o mínimo permitido.
 * - Se o valor é maior que o máximo permitido.
 * 3. Se houver erro, limpa o buffer e pede novamente.
 * @return O valor inteiro validado.
 */
int obterInteiro(int minValor, int maxValor, char *msg) {
    int valor;
    printf("%s", msg);
    while (scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(VALOR_INVALIDO);
        cleanInputBuffer();
        printf("%s", msg);
    }
    cleanInputBuffer(); // Limpa o '\n' que fica no buffer após a leitura do número
    return valor;
}

/** * @brief Lê uma string do teclado de forma segura.
 * * Lógica de Leitura:
 * 1. Utiliza `fgets` para garantir que nunca lê mais caracteres do que o tamanho do buffer.
 * 2. Verifica o último caracter lido:
 * - Se for um `\\n` (Enter), substitui-o por `\\0` (fim de string) para o texto ficar limpo.
 * - Se NÃO for um `\\n`, significa que o utilizador escreveu mais texto do que cabia.
 * Nesse caso, chama `cleanInputBuffer` para descartar o excesso e impedir erros futuros.
 */
void lerString(char *string, unsigned int tamanho, char *msg){
    printf("%s", msg);

    if(fgets(string, tamanho, stdin) != NULL){
        unsigned int len = strlen(string) - 1;
        
        if(string[len] == '\n'){
            string[len] = '\0'; // Remove a quebra de linha final
        } else {
            cleanInputBuffer(); // Limpa o excesso de caracteres se a string for muito longa
        }
    }
}