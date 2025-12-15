/**
 * @file input.h
 * @brief Utilitários para entrada de dados, validações e estruturas de tempo.
 */

#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VALOR_INVALIDO "O valor inserido é inválido"
#define MAX_INT 2147483647
#define SIZE_BUFFER 100

/** @struct Data @brief Estrutura para representação de datas (DD/MM/AAAA). */
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

/** @struct Hora @brief Estrutura para representação de horários (HH:MM). */
typedef struct {
    int horas;
    int minutos;
} Hora;

// --- Funções de Input ---

/** @brief Limpa o buffer de entrada (stdin) para evitar erros de leitura. */
void cleanInputBuffer();

/** @brief Solicita um número inteiro ao utilizador, validando o intervalo (min/max). */
int obterInteiro(int minValor, int maxValor, char *msg);

/** @brief Lê uma string do teclado de forma segura (remove o \\n final). */
void lerString(char *string, unsigned int tamanho, char *msg);

#endif