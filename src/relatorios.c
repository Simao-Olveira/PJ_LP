#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "enums.h"
#include "relatorios.h"
#include "gestaoRelatorios.h"
#include "input.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "relatorios.h"
#include "gestaoOcorrencia.h"
#include "gestaoIntervencao.h"
#include "gestaoBombeiro.h"
#include "gestaoEquipamento.h"
#include "gestaoQuartel.h"
#include "ocorrencia.h"
#include "intervencao.h"
#include "bombeiro.h"
#include "equipamento.h"
#include "quartel.h"


// ----------- Relatorios da Ocorrencia ------------

// Relatório 1: Estatísticas por Estado, Tipo e Prioridade
void relatorioEstatisticasGerais(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias == 0) {
        printf("Nao existem ocorrencias para gerar estatisticas.\n");
        return;
    }

    // Contadores
    int cFlorestal = 0, cUrbano = 0, cIndustrial = 0;
    int cBaixa = 0, cNormal = 0, cAlta = 0;
    int cReportada = 0, cIntervencao = 0, cConcluida = 0;

    for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
        // Contagem Tipo
        switch (ocorrencias.ocorrencias[i].tipo) {
            case FLORESTAL: cFlorestal++; break;
            case URBANO: cUrbano++; break;
            case INDUSTRIAL: cIndustrial++; break;
        }
        // Contagem Prioridade
        switch (ocorrencias.ocorrencias[i].prioridade) {
            case BAIXA: cBaixa++; break;
            case NORMAL: cNormal++; break;
            case ALTA: cAlta++; break;
        }
        // Contagem Estado
        switch (ocorrencias.ocorrencias[i].estado) {
            case OCORR_REPORTADA: cReportada++; break;
            case OCORR_INTERVENCAO: cIntervencao++; break;
            case OCORR_CONCLUIDA: cConcluida++; break;
        }
    }

    printf("\n========= ESTATISTICAS DAS OCORRENCIAS =========\n");

    printf("\n[POR ESTADO]\n");
    printf("Reportadas:     %d\n", cReportada);
    printf("Em Intervencao: %d\n", cIntervencao);
    printf("Concluidas:     %d\n", cConcluida);

    printf("\n[POR TIPO]\n");
    printf("Florestal:      %d\n", cFlorestal);
    printf("Urbano:         %d\n", cUrbano);
    printf("Industrial:     %d\n", cIndustrial);

    printf("\n[POR PRIORIDADE]\n");
    printf("Alta:           %d\n", cAlta);
    printf("Normal:         %d\n", cNormal);
    printf("Baixa:          %d\n", cBaixa);
    printf("===============================================\n");

    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}

void relatorioTempoMedioResposta(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias == 0) return;

    time_t agora;
    time(&agora); // Obtém hora atual do sistema

    double somaSegundos = 0;
    int count = 0;

    printf("\n========= IDADE DAS OCORRENCIAS =========\n");
    printf("| %-4s | %-15s | %-20s |\n", "ID", "Estado", "Tempo Decorrido (h)");
    printf("|------|-----------------|----------------------|\n");

    for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
        struct tm reg = {0};
        reg.tm_year = ocorrencias.ocorrencias[i].dataRegisto.ano - 1900;
        reg.tm_mon  = ocorrencias.ocorrencias[i].dataRegisto.mes - 1;
        reg.tm_mday = ocorrencias.ocorrencias[i].dataRegisto.dia;
        reg.tm_hour = ocorrencias.ocorrencias[i].horaRegisto.horas;
        reg.tm_min  = ocorrencias.ocorrencias[i].horaRegisto.minutos;
        reg.tm_sec  = 0;
        reg.tm_isdst = -1; // Automático

        time_t tempoRegisto = mktime(&reg);

        if (tempoRegisto != -1) {
            double diferenca = difftime(agora, tempoRegisto); // Diferença em segundos
            double horas = diferenca / 3600.0;

            somaSegundos += diferenca;
            count++;

            printf("| %04d | %-15s | %18.2f h |\n",
                ocorrencias.ocorrencias[i].id,
                strEstadoOcorrencia(ocorrencias.ocorrencias[i].estado),
                horas);
        }
    }

    if (count > 0) {
        double mediaHoras = (somaSegundos / count) / 3600.0;
        printf("==========================================\n");
        printf("Tempo Medio desde o registo: %.2f horas\n", mediaHoras);
    }

    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}

void relatorioLocalizacaoEFrequencia(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias == 0) return;

    // Estrutura temporária para contagem (simplificada)
    typedef struct {
        char nome[100];
        int qtd;
    } LocFreq;

    LocFreq *listaLocais = malloc(sizeof(LocFreq) * ocorrencias.numOcorrencias);
    int totalLocaisUnicos = 0;

    for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
        char *locAtual = ocorrencias.ocorrencias[i].local;
        int encontrado = 0;

        // Verifica se já existe na lista temporária
        for (int j = 0; j < totalLocaisUnicos; j++) {
            if (strcmp(listaLocais[j].nome, locAtual) == 0) {
                listaLocais[j].qtd++;
                encontrado = 1;
                break;
            }
        }

        // Se não encontrou, adiciona novo
        if (!encontrado) {
            strcpy(listaLocais[totalLocaisUnicos].nome, locAtual);
            listaLocais[totalLocaisUnicos].qtd = 1;
            totalLocaisUnicos++;
        }
    }

    printf("\n======= FREQUENCIA POR LOCALIZACAO =======\n");
    printf("| %-25s | %-5s |\n", "Localizacao", "Qtd");
    printf("|---------------------------|-------|\n");

    for (int i = 0; i < totalLocaisUnicos; i++) {
        printf("| %-25s | %-5d |\n", listaLocais[i].nome, listaLocais[i].qtd);
    }
    printf("==========================================\n");

    free(listaLocais);
    printf("Pressione ENTER para continuar...");
    getchar(); getchar();
}

//----------- Relatorios da Intervencao ------------
void relatorioIntervencoesEstado(Intervencoes intervencoes) {
    int cPlaneamento = 0, cExecucao = 0, cConcluida = 0;

    if (intervencoes.numIntervencoes == 0) {
        printf("Sem dados para gerar relatório.\n");
        return;
    }

    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        switch (intervencoes.intervencoes[i].estado) {
            case INT_PLANEAMENTO: cPlaneamento++; break;
            case INT_EXECUCAO:    cExecucao++; break;
            case INT_CONCLUIDA:   cConcluida++; break;
        }
    }

    printf("\n=== RELATÓRIO: ESTADO DAS INTERVENÇÕES ===\n");
    printf("| Estado        | Qtd | Percentagem |\n");
    printf("|---------------|-----|-------------|\n");
    printf("| Em Planeamento   | %3d | %5.1f%%      |\n", cPlaneamento, (float)cPlaneamento/intervencoes.numIntervencoes * 100);
    printf("| Em Execução   | %3d | %5.1f%%      |\n", cExecucao, (float)cExecucao/intervencoes.numIntervencoes * 100);
    printf("| Concluídas    | %3d | %5.1f%%      |\n", cConcluida, (float)cConcluida/intervencoes.numIntervencoes * 100);
    printf("| TOTAL         | %3d | 100.0%%      |\n", intervencoes.numIntervencoes);
    printf("=========================================\n");
}

void relatorioTempoDuracao(Intervencoes intervencoes) {
    long totalMinutos = 0;
    int qtdConcluidas = 0;
    long maiorDuracao = 0;
    int idMaior = -1;

    printf("\n=== RELATÓRIO: DURAÇÃO DE INTERVENÇÕES (Concluídas) ===\n");

    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        if (intervencoes.intervencoes[i].estado == INT_CONCLUIDA) {
            long inicio = calcularMinutosTotais(intervencoes.intervencoes[i].dataInicio, intervencoes.intervencoes[i].horaInicio);
            long fim = calcularMinutosTotais(intervencoes.intervencoes[i].dataFim, intervencoes.intervencoes[i].horaFim);

            long duracao = fim - inicio;

            if (duracao < 0) duracao = 0; // Proteção contra datas erradas

            totalMinutos += duracao;
            qtdConcluidas++;

            if (duracao > maiorDuracao) {
                maiorDuracao = duracao;
                idMaior = intervencoes.intervencoes[i].id;
            }
        }
    }

    if (qtdConcluidas > 0) {
        double media = (double)totalMinutos / qtdConcluidas;
        printf("Total de Intervenções Concluídas: %d\n", qtdConcluidas);
        printf("Tempo Médio de Duração: %.2f minutos (%.1f horas)\n", media, media/60);
        printf("Intervenção mais longa: ID %d com %ld minutos\n", idMaior, maiorDuracao);
    } else {
        printf("Não existem intervenções concluídas para calcular médias.\n");
    }
    printf("=======================================================\n");
}

void relatorioRecursosMaisUtilizados(Intervencoes intervencoes) {
    // Nota: Esta lógica assume um ID máximo razoável ou usa arrays temporários.
    // Usaremos uma abordagem simples de arrays dinâmicos temporários para contar.

    int maxCapacidade = 100; // Começamos com espaço para 100 IDs diferentes
    ContadorRecurso *contBombeiros = (ContadorRecurso*) calloc(maxCapacidade, sizeof(ContadorRecurso));
    ContadorRecurso *contEquip = (ContadorRecurso*) calloc(maxCapacidade, sizeof(ContadorRecurso));
    int totalDiffBomb = 0;
    int totalDiffEquip = 0;

    // --- CONTAGEM ---
    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        // Contar Bombeiros
        for (int k = 0; k < intervencoes.intervencoes[i].numBombeiros; k++) {
            int idAtual = intervencoes.intervencoes[i].idsBombeiros[k];
            int encontrado = 0;

            for(int j=0; j<totalDiffBomb; j++){
                if(contBombeiros[j].id == idAtual){
                    contBombeiros[j].contagem++;
                    encontrado = 1;
                    break;
                }
            }
            if(!encontrado){
                contBombeiros[totalDiffBomb].id = idAtual;
                contBombeiros[totalDiffBomb].contagem = 1;
                totalDiffBomb++;
            }
        }

        // Contar Equipamentos
        for (int k = 0; k < intervencoes.intervencoes[i].numEquipamentos; k++) {
            int idAtual = intervencoes.intervencoes[i].idsEquipamentos[k];
            int encontrado = 0;

            for(int j=0; j<totalDiffEquip; j++){
                if(contEquip[j].id == idAtual){
                    contEquip[j].contagem++;
                    encontrado = 1;
                    break;
                }
            }
            if(!encontrado){
                contEquip[totalDiffEquip].id = idAtual;
                contEquip[totalDiffEquip].contagem = 1;
                totalDiffEquip++;
            }
        }
    }

    // --- IMPRESSÃO BOMBEIROS (TOP 3 SIMPLIFICADO) ---
    printf("\n=== RECURSOS MAIS UTILIZADOS ===\n");
    printf(">> Bombeiros (IDs mais frequentes):\n");
    // Bubble sort simples para ordenar por contagem decrescente
    for(int i=0; i<totalDiffBomb-1; i++){
        for(int j=0; j<totalDiffBomb-i-1; j++){
            if(contBombeiros[j].contagem < contBombeiros[j+1].contagem){
                ContadorRecurso temp = contBombeiros[j];
                contBombeiros[j] = contBombeiros[j+1];
                contBombeiros[j+1] = temp;
            }
        }
    }
    for(int i=0; i<totalDiffBomb && i<3; i++){
        printf("1º Lugar: Bombeiro ID %d (%d intervenções)\n", contBombeiros[i].id, contBombeiros[i].contagem);
    }

    // --- IMPRESSÃO EQUIPAMENTOS ---
    printf("\n>> Equipamentos (IDs mais frequentes):\n");
    // Bubble sort equipamentos
    for(int i=0; i<totalDiffEquip-1; i++){
        for(int j=0; j<totalDiffEquip-i-1; j++){
            if(contEquip[j].contagem < contEquip[j+1].contagem){
                ContadorRecurso temp = contEquip[j];
                contEquip[j] = contEquip[j+1];
                contEquip[j+1] = temp;
            }
        }
    }
    for(int i=0; i<totalDiffEquip && i<3; i++){
        printf("1º Lugar: Equipamento ID %d (%d intervenções)\n", contEquip[i].id, contEquip[i].contagem);
    }
    printf("================================\n");

    free(contBombeiros);
    free(contEquip);
}

void relatorioEficiencia(Intervencoes intervencoes) {
    if (intervencoes.numIntervencoes == 0) return;

    int totalBombeirosAlocados = 0;
    int totalEquipAlocados = 0;
    int concluidas = 0;

    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        totalBombeirosAlocados += intervencoes.intervencoes[i].numBombeiros;
        totalEquipAlocados += intervencoes.intervencoes[i].numEquipamentos;

        if (intervencoes.intervencoes[i].estado == INT_CONCLUIDA) {
            concluidas++;
        }
    }

    float mediaBombeiros = (float)totalBombeirosAlocados / intervencoes.numIntervencoes;
    float mediaEquip = (float)totalEquipAlocados / intervencoes.numIntervencoes;
    float taxaConclusao = ((float)concluidas / intervencoes.numIntervencoes) * 100;

    printf("\n=== ANÁLISE DE EFICIÊNCIA OPERACIONAL ===\n");
    printf("Taxa de Conclusão Global: %.2f%%\n", taxaConclusao);
    printf("-----------------------------------------\n");
    printf("Média de Recursos por Intervenção:\n");
    printf(" - Bombeiros: %.1f por ocorrência\n", mediaBombeiros);
    printf(" - Equipamentos: %.1f por ocorrência\n", mediaEquip);

    if (taxaConclusao < 50.0) {
        printf("\n[ALERTA] A taxa de conclusão está baixa (<50%%).\nConsidere rever os processos de planeamento.\n");
    } else {
        printf("\n[INFO] Bom ritmo de resolução de intervenções.\n");
    }
    printf("=========================================\n");
}


// ----------- Relatorios do Bombeiro ------------

void relatorioDisponibilidadeEspecialidade(Bombeiros bombeiros) {
    // Array para contar disponíveis por especialidade.
    // O tamanho 6 vem do número de itens no enum EspecialidadeBombeiro
    int contadores[3] = {0};
    int i;

    printf("\n=== RELATÓRIO: Disponibilidade por Especialidade ===\n");

    for (i = 0; i < bombeiros.numBombeiros; i++) {
        // Verifica se está ativo e se o estado é EM_DISPONIVEL
        if (bombeiros.bombeiros[i].ativo && bombeiros.bombeiros[i].estado == EM_DISPONIVEL) {
            contadores[bombeiros.bombeiros[i].especialidade]++;
        }
    }

    // Imprimir resultados
    printf("Combate Florestal: %d disponíveis\n", contadores[COMBATE_FLORESTAL]);
    printf("Combate Aereo: %d disponíveis\n", contadores[COMBATE_AEREO]);
    printf("Resgate: %d disponíveis\n", contadores[RESGATE]);
    printf("----------------------------------------------------\n");
}

void relatorioParticipacaoIntervencoes(Bombeiros bombeiro) {
int i;
    printf("\n=== RELATÓRIO: Participação em Intervenções ===\n");
    printf("%-5s | %-30s | %-15s\n", "ID", "Nome", "Intervenções");
    printf("--------------------------------------------------------\n");

    for (i = 0; i < bombeiros.numBombeiros; i++) {
        if (bombeiros.bombeiros[i].ativo) {
            printf("%-5d | %-30s | %-15d\n",
                bombeiros.bombeiros[i].id,
                bombeiros.bombeiros[i].nome,
                bombeiros.bombeiros[i].numIntervencoes);
        }
    }
    printf("--------------------------------------------------------\n");
}

// -------------------------------------------------------------------------
// 3. Relatório: Ranking de Desempenho
// Critério: Mais intervenções primeiro. Desempate: Menor tempo médio.
// -------------------------------------------------------------------------
void relatorioRankingDesempenho(Bombeiros bombeiros) {
    if (bombeiros.numBombeiros == 0) {
        printf("Sem dados para ranking.\n");
        return;
    }

    // Criar uma cópia temporária para não alterar a ordem original do array (que é por ID)
    Bombeiro *tempLista = malloc(sizeof(Bombeiro) * bombeiros.numBombeiros);
    if (tempLista == NULL) {
        printf("Erro de memória ao gerar ranking.\n");
        return;
    }

    // Copiar apenas bombeiros ativos para a lista temporária
    int countAtivos = 0;
    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        if (bombeiros.bombeiros[i].ativo) {
            tempLista[countAtivos] = bombeiros.bombeiros[i];
            countAtivos++;
        }
    }

    // Algoritmo de ordenação (Bubble Sort simples para o exemplo)
    for (int i = 0; i < countAtivos - 1; i++) {
        for (int j = 0; j < countAtivos - i - 1; j++) {
            // Critério 1: Quem tem MENOS intervenções vai para o fim (Ordem Decrescente)
            int troca = 0;
            if (tempLista[j].numIntervencoes < tempLista[j+1].numIntervencoes) {
                troca = 1;
            }
            // Critério 2: Desempate (se intervenções iguais, menor tempo ganha)
            else if (tempLista[j].numIntervencoes == tempLista[j+1].numIntervencoes) {
                if (tempLista[j].tempoMedioResposta > tempLista[j+1].tempoMedioResposta) {
                    troca = 1;
                }
            }

            if (troca) {
                Bombeiro aux = tempLista[j];
                tempLista[j] = tempLista[j+1];
                tempLista[j+1] = aux;
            }
        }
    }

    // Exibir Ranking
    printf("\n=== RELATÓRIO: Ranking de Desempenho ===\n");
    printf("TOP | %-20s | %-12s | %s\n", "Nome", "Nº Interv.", "Tempo Médio");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < countAtivos; i++) {
        printf("#%d  | %-20s | %-12d | %.2f min\n",
            i + 1,
            tempLista[i].nome,
            tempLista[i].numIntervencoes,
            tempLista[i].tempoMedioResposta);
    }
    printf("----------------------------------------------------------\n");

    free(tempLista); // Libertar a memória da cópia
}


// ----------- Relatorios do Equipamento ------------

void relatorioInventarioEquipamentos(Equipamentos equipamentos) {
    int totalVeiculos = 0, totalFerramentas = 0, totalVestuario = 0, totalComunicacao = 0;
    int totalGeral = 0;

    printf("\n=================================================================================\n");
    printf("                           INVENTARIO GERAL DE EQUIPAMENTOS                      \n");
    printf("=================================================================================\n");
    printf("| %-4s | %-20s | %-12s | %-12s | %-15s |\n", "ID", "Nome", "Tipo", "Estado", "Localizacao");
    printf("|------|----------------------|--------------|--------------|-----------------|\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        if (equipamentos.equipamentos[i].ativo == 1) { // Apenas ativos
            Equipamento eq = equipamentos.equipamentos[i];

            printf("| %04d | %-20s | %-12s | %-12s | %-15s |\n",
                eq.id, eq.nome, getStrTipo(eq.tipo), getStrEstado(eq.estado), eq.localizacao);

            // Contagens
            totalGeral++;
            switch (eq.tipo) {
                case VEICULOS: totalVeiculos++; break;
                case FERRAMENTAS: totalFerramentas++; break;
                case VESTUARIO: totalVestuario++; break;
                case COMUNICACAO: totalComunicacao++; break;
                default: break;
            }
        }
    }
    printf("=================================================================================\n");
    printf("TOTAL: %d | Veiculos: %d | Ferramentas: %d | Vestuario: %d | Comunicacao: %d\n",
            totalGeral, totalVeiculos, totalFerramentas, totalVestuario, totalComunicacao);

    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}

void relatorioUtilizacaoTipoIntervencao(Equipamentos equipamentos) {
    int count = 0;
    printf("\n========================================================\n");
    printf("          RELATORIO DE UTILIZACAO (EM INTERVENCAO)      \n");
    printf("========================================================\n");
    printf("| %-4s | %-20s | %-12s | %-15s |\n", "ID", "Nome", "Tipo", "Localizacao");
    printf("|------|----------------------|--------------|-----------------|\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        // Filtra pelo estado EQ_EM_USO
        if (equipamentos.equipamentos[i].ativo == 1 &&
            equipamentos.equipamentos[i].estado == EQ_EM_USO) {

            Equipamento eq = equipamentos.equipamentos[i];
            printf("| %04d | %-20s | %-12s | %-15s |\n",
                eq.id, eq.nome, getStrTipo(eq.tipo), eq.localizacao);
            count++;
            }
    }

    if (count == 0) {
        printf("|          Nenhum equipamento esta a ser utilizado.      |\n");
    }
    printf("========================================================\n");
    printf("Total em Uso: %d\n", count);

    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}

void relatorioManutencaoEquipamentos(Equipamentos equipamentos) {
    int count = 0;
    printf("\n========================================================\n");
    printf("              EQUIPAMENTOS EM MANUTENCAO                \n");
    printf("========================================================\n");
    printf("| %-4s | %-20s | %-12s | %-15s |\n", "ID", "Nome", "Tipo", "Localizacao");
    printf("|------|----------------------|--------------|-----------------|\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        // Verifica se esta ativo E se o estado é Manutenção
        if (equipamentos.equipamentos[i].ativo == 1 &&
            equipamentos.equipamentos[i].estado == EQ_MANUTENCAO) {

            Equipamento eq = equipamentos.equipamentos[i];
            printf("| %04d | %-20s | %-12s | %-15s |\n",
                eq.id, eq.nome, getStrTipo(eq.tipo), eq.localizacao);
            count++;
            }
    }

    if (count == 0) {
        printf("|              Nenhum equipamento está em manutencao.         |\n");
    }
    printf("========================================================\n");
    printf("Total em Manutencao: %d\n", count);

    printf("\nPressione ENTER para continuar...");
    getchar(); getchar();
}


// ----------- Relatorios do Quartel ------------
