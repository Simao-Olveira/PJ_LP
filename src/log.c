/**
 * @file log.c
 * @brief Implementação do sistema de registo de logs (histórico) do sistema.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "log.h"

/** * @brief Escreve uma mensagem no ficheiro de log com carimbo temporal.
 * Captura a hora atual do sistema (time/localtime).
 * Tenta abrir o ficheiro "log.txt" em modo de "append" ('a'). Este modo é crucial
 * para garantir que as mensagens anteriores não são apagadas, acrescentando 
 * a nova linha ao final do ficheiro.
 * Validação Crítica: Se não for possível abrir o ficheiro (ex: permissões, disco cheio),
 * o programa encerra forçosamente (exit), pois um sistema sem logs não é auditável.
 * Formata e escreve a string: "AAAA-MM-DD HH:MM:SS - Mensagem".
 * Fecha o ficheiro imediatamente para garantir a persistência dos dados em disco.
 * * @param msg A mensagem de texto a ser registada.
 */
void logMsg(char *msg) {

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    FILE *fp = fopen("log.txt", "a");
    if (fp == NULL) {
        // Se falhar o log, encerra o programa por segurança
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d - %s\n", 
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, 
            tm->tm_hour, tm->tm_min, tm->tm_sec, msg);

    fclose(fp);
}