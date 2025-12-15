/**
 * @file log.h
 * @brief Utilitários para registo de histórico (logs) do sistema.
 */

#ifndef LOG_H
#define LOG_H

#include <time.h>

/** @brief Escreve uma mensagem no ficheiro de log (adicionando data/hora atual automaticamente). */
void logMsg(char *msg);

#endif