/**
 * @file main.c
 * @brief Ponto de entrada da aplicação (Fire Station Management System).
 */

#include <stdio.h>
#include <stdlib.h>
#include "iniciar.h"
#include "log.h"

/** * @brief Função principal do programa.
 * * Lógica de Execução:
 * 1. Regista imediatamente o início da execução no sistema de logs para auditoria.
 * 2. Delega a responsabilidade total de inicialização (alocação de memória, 
 * leitura de ficheiros e execução do menu) para a função `iniciarSistema`.
 * 3. Verifica o código de retorno: se `iniciarSistema` devolver um valor diferente 
 * de 0, significa que houve um erro crítico (ex: falta de memória), forçando 
 * o encerramento com código de erro 1.
 * @return 0 em caso de sucesso, 1 em caso de erro fatal.
 */
int main() {
    logMsg("Iniciar sistema.");

    // A função iniciarSistema() encapsula todo o ciclo de vida do programa
    if (iniciarSistema() != 0) {
        printf("Erro ao iniciar o sistema. A encerrar.\n");
        logMsg("Erro fatal ao iniciar o sistema. A encerrar.");
        return 1;
    }

    logMsg("Sistema encerrado corretamente.\n");
    return 0;
}