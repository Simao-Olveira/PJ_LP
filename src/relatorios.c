#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enums.h"
#include "relatorios.h"
#include "gestaoRelatorios.h"
#include "input.h"
#include <stdio.h>
#include <time.h>
#include "ocorrencia.h"
#include "relatorios.h"


// ----------- Relatorio da Ocorrencia ------------

void relatorioEstado(Ocorrencia oc[], int n) {
int reportadas = 0, intervencao = 0, concluidas = 0;

    for (int i = 0; i < n; i++) {
        switch (oc[i].estado) {
            case EST_REPORTADA: reportadas++;
            break;
            case EST_EM_INTERVENCAO: intervencao++;
            break;
            case EST_CONCLUIDA: concluidas++;
            break;
        }
    }

    printf("\n------ Relatorio por Estado ------\n");
    printf("Reportadas: %d\n", reportadas);
    printf("Em Intervencao: %d\n", intervencao);
    printf("Concluidas: %d\n", concluidas);
}

void relatorioTipo(Ocorrencia oc[], int n) {
int florestal = 0, urbano = 0, industrial = 0;

    for (int i = 0; i < n; i++) {
        switch (oc[i].tipo) {
            case TIPO_FLORESTAL: florestal++;
            break;
            case TIPO_URBANO: urbano++;
            break;
            case TIPO_INDUSTRIAL: industrial++;
            break;
        }
    }

    printf("\n----- Relatorio por Tipo -----\n");
    printf("Florestal: %d\n", florestal);
    printf("Urbano: %d\n", urbano);
    printf("Industrial: %d\n", industrial);
}

void relatorioPrioridade(Ocorrencia oc[], int n) {
    int baixa = 0, normal = 0, alta = 0;

    for (int i = 0; i < n; i++) {
        switch (oc[i].prioridade) {
            case PRIO_BAIXA: baixa++;
            break;
            case PRIO_NORMAL: normal++;
            break;
            case PRIO_ALTA: alta++;
            break;
        }
    }

    printf("\n----- Relatorio por Prioridade -----\n");
    printf("Baixa: %d\n", baixa);
    printf("Normal: %d\n", normal);
    printf("Alta: %d\n", alta);
}

void relatorioTempoMedioResposta(Ocorrencia oc[], int n) {
double somaSegundos = 0;
int totalValidos = 0;

    for (int i = 0; i < n; i++) {
        if (oc[i].estado != EST_REPORTADA &&
            oc[i].dataHoraIntervencao > oc[i].dataHoraReportada) {

            double diff = difftime(oc[i].dataHoraIntervencao,
                                    oc[i].dataHoraReportada);

            somaSegundos += diff;
            totalValidos++;
            }
    }

    printf("\n--- Relatorio: Tempo Medio de Resposta ---\n");

    if (totalValidos == 0) {
        printf("Sem dados suficientes para calcular.\n");
        return;
    }

    double media = somaSegundos / totalValidos;

    printf("Tempo medio de resposta: %.2f minutos\n", media / 60);
}

void relatorioAnaliseLocalizacao(Ocorrencia oc[], int n) {

printf("\n--- Analise por Localizacao ---\n");

    for (int i = 0; i < n; i++) {

        int jaAnalisado = 0;
        for (int j = 0; j < i; j++)
            if (strcmp(oc[i].local, oc[j].local) == 0)
                jaAnalisado = 1;

        if (jaAnalisado) continue;

        printf("\nLocal: %s\n", oc[i].local);

        for (int k = 0; k < n; k++) {
            if (strcmp(oc[k].local, oc[i].local) == 0) {
                printf("  ID:%d | Tipo:%d | Prioridade:%d | Estado:%d\n",
                       oc[k].id,
                       oc[k].tipo,
                       oc[k].prioridade,
                       oc[k].estado);
            }
        }
    }
}

void relatorioFrequenciaIncidentes(Ocorrencia oc[], int n) {

    printf("\n--- Frequencia de Incidentes por Local ---\n");

    for (int i = 0; i < n; i++) {
        int jaContado = 0;
        for (int j = 0; j < i; j++)
            if (strcmp(oc[i].local, oc[j].local) == 0)
                jaContado = 1;

        if (jaContado) continue;

        int total = 1;
        for (int k = i + 1; k < n; k++)
            if (strcmp(oc[i].local, oc[k].local) == 0)
                total++;

        printf("%s: %d ocorrencias\n", oc[i].local, total);
    }
}