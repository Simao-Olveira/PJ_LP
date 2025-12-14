#include <stdio.h>
#include <stdlib.h>
#include "iniciar.h"
#include "log.h"

int main() {
    logMsg("Iniciar sistema.");
    if (iniciarSistema() != 0) {
        printf("Erro ao iniciar o sistema. A encerrar.\n");
        logMsg("Erro ao iniciar o sistema. A encerrar.");
        return 1;
    }
    logMsg("Sistema encerrado.\n");
    return 0;
}