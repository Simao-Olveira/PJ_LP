#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../headers/enums.h"
#include "../headers/input.h" // Para o obterInteiro

// Includes das Entidades
#include "../headers/ocorrencia.h"
#include "../headers/gestaoOcorrencia.h"

#include "../headers/intervencao.h"
#include "../headers/gestaoIntervencao.h"

#include "../headers/bombeiro.h"
#include "../headers/gestaoBombeiro.h"

#include "../headers/intervencao.h"

#include "../headers/equipamento.h"
#include "../headers/gestaoEquipamento.h"

#include "../headers/quartel.h"
#include "../headers/gestaoQuartel.h"

// --- ESTRUTURAS AUXILIARES LOCAIS ---
typedef struct {
    int id;
    int contagem;
} ContadorRecurso;

// Estrutura auxiliar interna para o ranking
typedef struct {
    int idBombeiro;
    char nome[100];
    int totalIntervencoes;
    int tempoTotalResposta; // Minutos acumulados (Início Intervenção - Registo Ocorrência)
} StatsBombeiro;

// --- FUNÇÕES AUXILIARES (CONVERSÃO ENUM -> TEXTO) ---
char* getStrEstadoOcorrencia(EstadoOcorrencia est) {
    switch(est) {
        case OCORR_REPORTADA: return "Reportada";
        case OCORR_INTERVENCAO: return "Em Intervencao";
        case OCORR_CONCLUIDA: return "Concluida";
        default: return "N/A";
    }
}

char* getStrTipoEquipamento(TipoEquipamento tipo) {
    switch(tipo) {
        case VESTUARIO: return "Vestuario";
        case VEICULOS: return "Veiculos";
        case FERRAMENTAS: return "Ferramentas";
        case COMUNICACAO: return "Comunicacao";
        default: return "Outro";
    }
}

char* getStrEstadoEquipamento(EstadoEquipamento est) {
    switch(est) {
        case EQ_DISPONIVEL: return "Disponivel";
        case EQ_EM_USO: return "Em Uso";
        case EQ_MANUTENCAO: return "Manutencao";
        default: return "N/A";
    }
}

// Função para calcular minutos totais de uma data/hora (para comparações)
long calcularMinutosTotais(Data d, Hora h) {
    return (d.ano * 525600) + (d.mes * 43800) + (d.dia * 1440) + (h.horas * 60) + h.minutos;
}

// Função auxiliar para calcular diferença em minutos entre duas datas/horas
int calcularDiferencaMinutos(Data d1, Hora h1, Data d2, Hora h2) {
    //Convertendo tudo para minutos
    //1 dia = 1440 minutos & 1 hora = 60 minutos
    long minutos1 = (d1.dia * 1440) + (h1.horas * 60) + h1.minutos;
    long minutos2 = (d2.dia * 1440) + (h2.horas * 60) + h2.minutos;
    
    return (int)(minutos2 - minutos1);
}

// =================================================================================
//                           RELATÓRIOS OCORRÊNCIA
// =================================================================================

void relatorioEstatisticasGerais(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias == 0) {
        printf("Nao existem ocorrencias para gerar estatisticas.\n");
        return;
    }

    int cFlorestal = 0, cUrbano = 0, cIndustrial = 0;
    int cBaixa = 0, cNormal = 0, cAlta = 0;
    int cReportada = 0, cIntervencao = 0, cConcluida = 0;

    for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
        switch (ocorrencias.ocorrencias[i].tipo) {
            case FLORESTAL: cFlorestal++; break;
            case URBANO: cUrbano++; break;
            case INDUSTRIAL: cIndustrial++; break;
        }
        switch (ocorrencias.ocorrencias[i].prioridade) {
            case BAIXA: cBaixa++; break;
            case NORMAL: cNormal++; break;
            case ALTA: cAlta++; break;
        }
        switch (ocorrencias.ocorrencias[i].estado) {
            case OCORR_REPORTADA: cReportada++; break;
            case OCORR_INTERVENCAO: cIntervencao++; break;
            case OCORR_CONCLUIDA: cConcluida++; break;
        }
    }

    printf("\n========= ESTATISTICAS DAS OCORRENCIAS =========\n");
    printf("[POR ESTADO]\n");
    printf("Reportadas:     %d\nEm Intervencao: %d\nConcluidas:     %d\n", cReportada, cIntervencao, cConcluida);
    printf("\n[POR TIPO]\n");
    printf("Florestal:      %d\nUrbano:         %d\nIndustrial:     %d\n", cFlorestal, cUrbano, cIndustrial);
    printf("\n[POR PRIORIDADE]\n");
    printf("Alta:           %d\nNormal:         %d\nBaixa:          %d\n", cAlta, cNormal, cBaixa);
    printf("===============================================\n");
}

void relatorioTempoMedioResposta(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias == 0) return;

    time_t agora;
    time(&agora); 

    double somaSegundos = 0;
    int count = 0;

    printf("\n================== TEMPO MEDIO DE RESPOSTA ======================\n");
    printf("| %s | %-15s | %-20s |\n", "ID", "Estado", "Tempo Decorrido (h)");
    printf("|----|-----------------|----------------------|\n");

    for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
        struct tm reg = {0};
        reg.tm_year = ocorrencias.ocorrencias[i].dataRegisto.ano - 1900;
        reg.tm_mon  = ocorrencias.ocorrencias[i].dataRegisto.mes - 1;
        reg.tm_mday = ocorrencias.ocorrencias[i].dataRegisto.dia;
        reg.tm_hour = ocorrencias.ocorrencias[i].horaRegisto.horas;
        reg.tm_min  = ocorrencias.ocorrencias[i].horaRegisto.minutos;
        reg.tm_sec  = 0;
        reg.tm_isdst = -1;

        time_t tempoRegisto = mktime(&reg);

        if (tempoRegisto != -1) {
            double diferenca = difftime(agora, tempoRegisto);
            double horas = diferenca / 3600.0;

            if(horas >= 0) { // Evita tempos negativos por erro de data
                somaSegundos += diferenca;
                count++;
                printf("| %d | %-15s | %18.2f h |\n",
                    ocorrencias.ocorrencias[i].id,
                    getStrEstadoOcorrencia(ocorrencias.ocorrencias[i].estado),
                    horas);
            }
        }
    }

    if (count > 0) {
        double mediaHoras = (somaSegundos / count) / 3600.0;
        printf("====================================================\n");
        printf("Tempo Medio desde o registo: %.2f horas\n", mediaHoras);
    }
}

void relatorioLocalizacaoEFrequencia(Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias == 0) return;

    typedef struct { char nome[100]; int qtd; } LocFreq;
    LocFreq *listaLocais = malloc(sizeof(LocFreq) * ocorrencias.numOcorrencias);
    int totalLocaisUnicos = 0;

    for (int i = 0; i < ocorrencias.numOcorrencias; i++) {
        char *locAtual = ocorrencias.ocorrencias[i].local;
        int encontrado = 0;

        for (int j = 0; j < totalLocaisUnicos; j++) {
            if (strcmp(listaLocais[j].nome, locAtual) == 0) {
                listaLocais[j].qtd++;
                encontrado = 1;
                break;
            }
        }
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
}

// =================================================================================
//                           RELATÓRIOS INTERVENÇÃO
// =================================================================================

void relatorioIntervencoesEstado(Intervencoes intervencoes) {
    int cPlaneamento = 0, cExecucao = 0, cConcluida = 0;

    if (intervencoes.numIntervencoes == 0) {
        printf("Sem dados para gerar relatorio.\n");
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
    printf("| Em Planeamento| %3d | %5.1f%%      |\n", cPlaneamento, (float)cPlaneamento/intervencoes.numIntervencoes * 100);
    printf("| Em Execucao   | %3d | %5.1f%%      |\n", cExecucao, (float)cExecucao/intervencoes.numIntervencoes * 100);
    printf("| Concluidas    | %3d | %5.1f%%      |\n", cConcluida, (float)cConcluida/intervencoes.numIntervencoes * 100);
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

            if (duracao < 0) duracao = 0;

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
    int maxCapacidade = 100; 
    ContadorRecurso *contBombeiros = (ContadorRecurso*) calloc(maxCapacidade, sizeof(ContadorRecurso));
    ContadorRecurso *contEquip = (ContadorRecurso*) calloc(maxCapacidade, sizeof(ContadorRecurso));
    int totalDiffBomb = 0;
    int totalDiffEquip = 0;

    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        // Contar Bombeiros
        if(intervencoes.intervencoes[i].idsBombeiros != NULL){
            for (int k = 0; k < intervencoes.intervencoes[i].numBombeiros; k++) {
                int idAtual = intervencoes.intervencoes[i].idsBombeiros[k];
                int encontrado = 0;
                for(int j=0; j<totalDiffBomb; j++){
                    if(contBombeiros[j].id == idAtual){
                        contBombeiros[j].contagem++;
                        encontrado = 1; break;
                    }
                }
                if(!encontrado){
                    contBombeiros[totalDiffBomb].id = idAtual;
                    contBombeiros[totalDiffBomb].contagem = 1;
                    totalDiffBomb++;
                }
            }
        }

        // Contar Equipamentos
        if(intervencoes.intervencoes[i].idsEquipamentos != NULL){
            for (int k = 0; k < intervencoes.intervencoes[i].numEquipamentos; k++) {
                int idAtual = intervencoes.intervencoes[i].idsEquipamentos[k];
                int encontrado = 0;
                for(int j=0; j<totalDiffEquip; j++){
                    if(contEquip[j].id == idAtual){
                        contEquip[j].contagem++;
                        encontrado = 1; break;
                    }
                }
                if(!encontrado){
                    contEquip[totalDiffEquip].id = idAtual;
                    contEquip[totalDiffEquip].contagem = 1;
                    totalDiffEquip++;
                }
            }
        }
    }

    printf("\n=== RECURSOS MAIS UTILIZADOS ===\n");
    printf(">> Bombeiros (Top 3):\n");
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
        printf("ID %d (%d intervenções)\n", contBombeiros[i].id, contBombeiros[i].contagem);
    }

    printf("\n>> Equipamentos (Top 3):\n");
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
        printf("ID %d (%d intervenções)\n", contEquip[i].id, contEquip[i].contagem);
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
    printf("Média de Recursos: %.1f Bombeiros/Ocorr. | %.1f Equip/Ocorr.\n", mediaBombeiros, mediaEquip);
    printf("=========================================\n");
}

// =================================================================================
//                           RELATÓRIOS BOMBEIRO
// =================================================================================

void relatorioDisponibilidadeEspecialidade(Bombeiros bombeiros) {
    // 3 = Tamanho do Enum EspecialidadeBombeiro (0, 1, 2)
    int contadores[3] = {0};

    printf("\n=== RELATÓRIO: Disponibilidade por Especialidade ===\n");

    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        // CORREÇÃO: "EB_DISPONIVEL" é o enum correto da tua struct
        if (bombeiros.bombeiros[i].estado == EB_DISPONIVEL) {
            contadores[bombeiros.bombeiros[i].especialidade]++;
        }
    }

    printf("Combate Florestal: %d disponíveis\n", contadores[COMBATE_FLORESTAL]);
    printf("Combate Aereo:     %d disponíveis\n", contadores[COMBATE_AEREO]);
    printf("Resgate:           %d disponíveis\n", contadores[RESGATE]);
    printf("----------------------------------------------------\n");
}

// CORREÇÃO: Precisa receber INTERVENCOES para contar (struct Bombeiro não tem contador)
void relatorioParticipacaoIntervencoes(Bombeiros bombeiros, Intervencoes intervencoes) {
    printf("\n=== RELATÓRIO: Participação em Intervenções ===\n");
    printf("%-5s | %-30s | %-15s\n", "ID", "Nome", "Intervenções");
    printf("--------------------------------------------------------\n");

    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        // Calcular em tempo real
        int count = 0;
        for(int k=0; k < intervencoes.numIntervencoes; k++){
            if(intervencoes.intervencoes[k].idsBombeiros != NULL){
                for(int j=0; j < intervencoes.intervencoes[k].numBombeiros; j++){
                    if(intervencoes.intervencoes[k].idsBombeiros[j] == bombeiros.bombeiros[i].id){
                        count++;
                    }
                }
            }
        }
        
        printf("%-d | %-30s | %-15d\n",
            bombeiros.bombeiros[i].id,
            bombeiros.bombeiros[i].nome,
            count);
    }
    printf("--------------------------------------------------------\n");
}

void relatorioRankingDesempenho(Intervencoes intervencoes, Ocorrencias ocorrencias, Bombeiros bombeiros) {
    if (bombeiros.numBombeiros == 0) {
        printf("Sem bombeiros para classificar.\n");
        return;
    }

    // 1. Criar array temporário para estatísticas
    StatsBombeiro *stats = (StatsBombeiro*) malloc(bombeiros.numBombeiros * sizeof(StatsBombeiro));
    
    // Inicializar
    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        stats[i].idBombeiro = bombeiros.bombeiros[i].id;
        strcpy(stats[i].nome, bombeiros.bombeiros[i].nome);
        stats[i].totalIntervencoes = 0;
        stats[i].tempoTotalResposta = 0;
    }

    // 2. Processar Intervenções CONCLUÍDAS
    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        if (intervencoes.intervencoes[i].estado == INT_CONCLUIDA) {
            
            // Calcular tempo de resposta (Se tivermos a ocorrência)
            int tempoResposta = 0;
            int idxOcor = procurarOcorrencia(ocorrencias, intervencoes.intervencoes[i].idOcorrencia);
            
            if (idxOcor != -1) {
                tempoResposta = calcularDiferencaMinutos(
                    ocorrencias.ocorrencias[idxOcor].dataRegisto,
                    ocorrencias.ocorrencias[idxOcor].horaRegisto,
                    intervencoes.intervencoes[i].dataInicio,
                    intervencoes.intervencoes[i].horaInicio
                );
            }

            // Atribuir stats aos bombeiros desta intervenção
            if (intervencoes.intervencoes[i].idsBombeiros != NULL) {
                for (int k = 0; k < intervencoes.intervencoes[i].numBombeiros; k++) {
                    int idB = intervencoes.intervencoes[i].idsBombeiros[k];
                    
                    // Encontrar o bombeiro no array de stats
                    for (int j = 0; j < bombeiros.numBombeiros; j++) {
                        if (stats[j].idBombeiro == idB) {
                            stats[j].totalIntervencoes++;
                            stats[j].tempoTotalResposta += tempoResposta;
                            break;
                        }
                    }
                }
            }
        }
    }

    // 3. Ordenar (Bubble Sort simples pela qtd intervenções)
    for (int i = 0; i < bombeiros.numBombeiros - 1; i++) {
        for (int j = 0; j < bombeiros.numBombeiros - i - 1; j++) {
            if (stats[j].totalIntervencoes < stats[j+1].totalIntervencoes) {
                StatsBombeiro temp = stats[j];
                stats[j] = stats[j+1];
                stats[j+1] = temp;
            }
        }
    }
    
    // 4. Imprimir Ranking
    printf("\n=== Ranking de Desempenho de Intervenções Concluídas) ===\n");
    printf("%-5s | %-20s | %-10s | %-15s\n", "Rank", "Nome", "Qtd.", "Temp. Médio Resposta");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        if (stats[i].totalIntervencoes > 0) {
            int mediaTempo = stats[i].tempoTotalResposta / stats[i].totalIntervencoes;
            printf("%-5d | %-20s | %-10d | %d min\n", 
                   i + 1, 
                   stats[i].nome, 
                   stats[i].totalIntervencoes,
                   mediaTempo);
        }
    }
    printf("-------------------------------------------------------------\n");

    free(stats);
}

// =================================================================================
//                           RELATÓRIOS EQUIPAMENTO
// =================================================================================

void relatorioInventarioEquipamentos(Equipamentos equipamentos) {
    int totalVeiculos = 0, totalFerramentas = 0, totalVestuario = 0, totalComunicacao = 0;
    int totalGeral = 0;

    printf("\n====================================================================\n");
    printf("                 INVENTARIO GERAL DE EQUIPAMENTOS                   \n");
    printf("====================================================================\n");
    // CORREÇÃO: Removida coluna "Localização" pois não existe na struct
    printf("| %s | %-20s | %-12s | %-12s |\n", "ID", "Nome", "Tipo", "Estado");
    printf("|----|----------------------|--------------|--------------|\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        Equipamento eq = equipamentos.equipamentos[i];

        printf("| %d | %-20s | %-12s | %-12s |\n",
            eq.id, eq.nome, getStrTipoEquipamento(eq.tipo), getStrEstadoEquipamento(eq.estado));

        totalGeral++;
        switch (eq.tipo) {
            case VEICULOS: totalVeiculos++; break;
            case FERRAMENTAS: totalFerramentas++; break;
            case VESTUARIO: totalVestuario++; break;
            case COMUNICACAO: totalComunicacao++; break;
            default: break;
        }
    }
    printf("====================================================================\n");
    printf("TOTAL: %d | Veic: %d | Ferr: %d | Vest: %d | Com: %d\n",
            totalGeral, totalVeiculos, totalFerramentas, totalVestuario, totalComunicacao);
}

void relatorioUtilizacaoTipoIntervencao(Equipamentos equipamentos) {
    int count = 0;
    printf("\n========================================================\n");
    printf("          RELATORIO DE UTILIZACAO (EM USO)              \n");
    printf("========================================================\n");
    // CORREÇÃO: Removida localização
    printf("| %s | %-20s | %-12s |\n", "ID", "Nome", "Tipo");
    printf("|----|----------------------|--------------|\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        if (equipamentos.equipamentos[i].estado == EQ_EM_USO) {
            Equipamento eq = equipamentos.equipamentos[i];
            printf("| %d | %-20s | %-12s |\n",
                eq.id, eq.nome, getStrTipoEquipamento(eq.tipo));
            count++;
        }
    }

    if (count == 0) printf("|          Nenhum equipamento esta a ser utilizado.      |\n");
    printf("========================================================\n");
    printf("Total em Uso: %d\n", count);
}

void relatorioManutencaoEquipamentos(Equipamentos equipamentos) {
    int count = 0;
    printf("\n========================================================\n");
    printf("              EQUIPAMENTOS EM MANUTENCAO                \n");
    printf("========================================================\n");
    printf("| %s | %-20s | %-12s |\n", "ID", "Nome", "Tipo");
    printf("|----|----------------------|--------------|\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        if (equipamentos.equipamentos[i].estado == EQ_MANUTENCAO) {
            Equipamento eq = equipamentos.equipamentos[i];
            printf("| %d | %-20s | %-12s |\n",
                eq.id, eq.nome, getStrTipoEquipamento(eq.tipo));
            count++;
        }
    }

    if (count == 0) printf("|       Nenhum equipamento está em manutencao.           |\n");
    printf("========================================================\n");
    printf("Total em Manutencao: %d\n", count);
}

// =================================================================================
//                           RELATÓRIOS QUARTÉIS
// =================================================================================

// 1. DEFINIR PRIMEIRO AS FUNÇÕES DE RELATÓRIO
void relatorioCapacidadeQuarteis(Quarteis quarteis) {
    printf("\n=== CAPACIDADE DOS QUARTEIS ===\n");
    printf("| %s | %-20s | %-12s | %-10s |\n", "ID", "Nome", "Tipo", "Capacidade");
    printf("|----|----------------------|--------------|------------|\n");
    
    for(int i=0; i < quarteis.numQuarteis; i++) {
        char *tipoStr = "Desc.";
        switch(quarteis.quarteis[i].tipo) {
            case VOLUNTARIO: tipoStr = "Voluntario"; break;
            case SAPADOR: tipoStr = "Sapador"; break;
            case MUNICIPAL: tipoStr = "Municipal"; break;
        }
        // Ajusta se a tua struct tiver o campo capacidade, senão mete "N/A"
        printf("| %d | %-20s | %-12s | %-10d |\n", 
           quarteis.quarteis[i].id, quarteis.quarteis[i].nome, tipoStr, quarteis.quarteis[i].capacidade);
    }
    printf("===========================================================\n");
}

void relatorioDistribuicaoQuarteis(Quarteis quarteis) {
    int cVol = 0, cSap = 0, cMun = 0;
    for(int i=0; i < quarteis.numQuarteis; i++) {
        switch(quarteis.quarteis[i].tipo) {
            case VOLUNTARIO: cVol++; break;
            case SAPADOR: cSap++; break;
            case MUNICIPAL: cMun++; break;
        }
    }
    printf("\n=== DISTRIBUICAO DA REDE DE QUARTEIS ===\n");
    printf("Bombeiros Voluntarios:   %d\n", cVol);
    printf("Companhias de Sapadores: %d\n", cSap);
    printf("Bombeiros Municipais:    %d\n", cMun);
    printf("========================================\n");
}

// =================================================================================
//                               MENUS ATUALIZADOS
// =================================================================================

void menuRelatoriosBombeiros(Intervencoes intervencoes, Ocorrencias ocorrencias, Bombeiros bombeiros) {
    if (bombeiros.numBombeiros == 0) {
        printf("Sem bombeiros para gerar relatórios.\n");
        return;
    }
    int opcao;
    do {
        printf("\n=== RELATÓRIOS BOMBEIROS ===\n");
        printf("1. Disponibilidade por especialidade\n");
        printf("2. Histórico de Intervenções por Bombeiro\n");
        printf("3. Ranking de Bombeiros por Intervenções Concluídas\n");
        printf("0. Voltar\n");
        printf("===============================\n");
        opcao = obterInteiro(0, 3, "Opcao: ");
        
        switch(opcao) {
            case 1: 
                relatorioDisponibilidadeEspecialidade(bombeiros); 
                break;
            case 2: 
                relatorioParticipacaoIntervencoes(bombeiros, intervencoes); 
                break; // Atualizado
            case 3: 
                relatorioRankingDesempenho(intervencoes, ocorrencias, bombeiros);
                break; // Atualizado
        }
        if(opcao != 0) { 
            printf("Enter para continuar..."); 
            getchar(); 
        }
    } while(opcao != 0);
}

void menuRelatoriosEquipamentos(Intervencoes intervencoes, Ocorrencias ocorrencias, Equipamentos equipamentos) {
    if (equipamentos.numEquipamentos == 0) {
        printf("Sem equipamentos para gerar relatórios.\n");
        return;
    }
    int opcao;
    do {
        printf("\n=== RELATÓRIOS EQUIPAMENTOS ===\n");
        printf("1. Inventário Geral\n");
        printf("2. Equipamentos em Manutenção\n");
        printf("3. Equipamentos em Uso\n");
        printf("4. Ranking de Utilização\n");
        printf("0. Voltar\n");
        printf("=================================\n");
        opcao = obterInteiro(0, 4, "Opcao: ");

        switch(opcao) {
            case 1: 
                relatorioInventarioEquipamentos(equipamentos); 
                break;
            case 2: 
                relatorioManutencaoEquipamentos(equipamentos); 
                break;
            case 3: 
                relatorioUtilizacaoTipoIntervencao(equipamentos); 
                break;
            case 4: 
                relatorioRecursosMaisUtilizados(intervencoes); 
                break;
            case 0: 
                printf("A voltar...\n"); 
                break;

        }
        if(opcao != 0) { 
            printf("Enter para continuar..."); 
            getchar(); 
        }
    } while(opcao != 0);
}

void menuRelatoriosIntervencoes(Intervencoes intervencoes) {
    if (intervencoes.numIntervencoes == 0) {
        printf("Sem dados para gerar relatorio.\n");
        return;
    }
    int opcao;
    do {
        printf("\n=== RELATORIOS INTERVENCOES ===\n");
        printf("1. Estado das Intervencoes\n");
        printf("2. Tempo Medio de Duracao\n");
        printf("3. Recursos Mais Utilizados\n");
        printf("4. Analise de Eficiencia Operacional\n");
        printf("0. Voltar\n");
        printf("==================================\n");
        opcao = obterInteiro(0, 4, "Opcao: ");

        switch(opcao) {
            case 1: 
                relatorioIntervencoesEstado(intervencoes); 
                break;
            case 2: 
                relatorioTempoDuracao(intervencoes); 
                break;
            case 3: 
                relatorioRecursosMaisUtilizados(intervencoes); 
                break;
            case 4: 
                relatorioEficiencia(intervencoes); 
                break;
            case 0: 
                printf("A voltar...\n"); 
                break;
        }
        if(opcao != 0) { 
            printf("Enter para continuar..."); 
            getchar(); 
        }
    } while(opcao != 0);
}

void menuRelatoriosOcorrencias(Intervencoes intervencoes, Ocorrencias ocorrencias) {
    if (ocorrencias.numOcorrencias == 0) {
        printf("Sem ocorrencias para gerar relatorios.\n");
        return;
    }
    int opcao;
    do {
        printf("\n=== RELATORIOS OCORRENCIAS ===\n");
        printf("1. Estatisticas Gerais\n");
        printf("2. Tempo Medio de Resposta\n");
        printf("3. Localizacao e Frequencia\n");
        printf("0. Voltar\n");
        printf("=================================\n");
        opcao = obterInteiro(0, 3, "Opcao: ");

        switch(opcao) {
            case 1:
                relatorioEstatisticasGerais(ocorrencias);
                break;
            case 2:
                relatorioTempoMedioResposta(ocorrencias);
                break;
            case 3:
                relatorioLocalizacaoEFrequencia(ocorrencias);
                break;
            case 0:
                printf("A voltar...\n");
                break;
        }
        if(opcao != 0) { 
            printf("Pressione ENTER para continuar..."); 
            getchar(); 
        }
    } while(opcao != 0);
}

void menuRelatoriosQuarteis(Quarteis quarteis) {
    if (quarteis.numQuarteis == 0) {
        printf("Sem quarteis para gerar relatorios.\n");
        return;
    }
    int opcao;
    do {
        printf("\n=== RELATORIOS QUARTEIS ===\n");
        printf("1. Capacidade e Lista de Quarteis\n");
        printf("2. Distribuicao por Tipo\n");
        printf("0. Voltar\n");
        printf("=============================\n");
        opcao = obterInteiro(0, 2, "Opcao: ");

        switch(opcao) {
            case 1:
                relatorioCapacidadeQuarteis(quarteis);
                break;
            case 2:
                relatorioDistribuicaoQuarteis(quarteis);
                break;
            case 0:
                printf("A voltar...\n");
                break;
        }
        if(opcao != 0) { 
            printf("Pressione ENTER para continuar..."); 
            getchar(); 
        }
    } while(opcao != 0);
}