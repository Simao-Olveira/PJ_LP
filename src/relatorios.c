#include <stdio.h>
#include "relatorios.h"
#include "enums.h"
#include "log.h"
#include "input.h"

#include "bombeiro.h"
#include "gestaoBombeiro.h"
#include "intervencao.h"
#include "gestaoIntervencao.h"
#include "ocorrencia.h"
#include "gestaoOcorrencia.h"
#include "equipamento.h"
#include "gestaoEquipamento.h"

// ----------- Relatorios do Bombeiro ------------

void relatorioDisponibilidade(Bombeiros bombeiros) {
    int florestal = 0, aereo = 0, resgate = 0;
    int totalDisponiveis = 0;

    printf("\n=== Relatório de Disponibilidade Operacional ===\n");

    for (int i = 0; i < bombeiros.numBombeiros; i++) {
        if (bombeiros.bombeiros[i].estado == EB_DISPONIVEL) {
            totalDisponiveis++;
            switch (bombeiros.bombeiros[i].especialidade) {
                case COMBATE_FLORESTAL: 
                    florestal++; 
                    break;
                case COMBATE_AEREO:     
                    aereo++; 
                    break;
                case RESGATE:           
                    resgate++; 
                    break;
            }
        }
    }

    printf("Total de Operacionais Disponíveis: %d\n", totalDisponiveis);
    printf("----------------------------------------\n");
    printf("| Especialidade      | Qtd. Disponível |\n");
    printf("----------------------------------------\n");
    printf("| Combate Florestal  | %-15d |\n", florestal);
    printf("| Combate Aéreo      | %-15d |\n", aereo);
    printf("| Resgate            | %-15d |\n", resgate);
    printf("----------------------------------------\n");
    logMsg("Relatório de Disponibilidade por Especialidade gerado.");
}

void relatorioHistoricoBombeiro(Intervencoes intervencoes, Bombeiros bombeiros) {
    listarBombeiros(bombeiros);
    int idB = obterInteiro(0, MAX_INT, "\nID do Bombeiro para ver histórico: ");
    int idxB = procurarBombeiro(bombeiros, idB);

    if (idxB == -1) {
        printf("Bombeiro não encontrado.\n");
        return;
    }

    printf("\n=== Histórico de Intervenções: %s ===\n", bombeiros.bombeiros[idxB].nome);
    printf("-------------------------------------------------------------\n");
    int count = 0;

    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        // Verifica se o ID do bombeiro está na lista desta intervenção
        if (intervencoes.intervencoes[i].idsBombeiros != NULL) {
            for (int k = 0; k < intervencoes.intervencoes[i].numBombeiros; k++) {
                if (intervencoes.intervencoes[i].idsBombeiros[k] == idB) {
                    
                    printf("Intervenção ID: %d | Data: %02d/%02d/%d | Estado: ", 
                        intervencoes.intervencoes[i].id,
                        intervencoes.intervencoes[i].dataInicio.dia,
                        intervencoes.intervencoes[i].dataInicio.mes,
                        intervencoes.intervencoes[i].dataInicio.ano);
                    
                    imprimirEstadoIntervencao(intervencoes.intervencoes[i].estado);
                    printf("\n");
                    count++;
                }
            }
        }
    }

    if (count == 0) {
        printf("Este bombeiro ainda não participou em intervenções.\n");
    } else {
        printf("Total de participações: %d\n", count);
    }
    printf("-------------------------------------------------------------\n");
}

// Estrutura auxiliar interna para o ranking
typedef struct {
    int idBombeiro;
    char nome[100];
    int totalIntervencoes;
    int tempoTotalResposta; // Minutos acumulados (Início Intervenção - Registo Ocorrência)
} StatsBombeiro;

// Função auxiliar para calcular diferença em minutos entre duas datas/horas
int calcularDiferencaMinutos(Data d1, Hora h1, Data d2, Hora h2) {

    //Convertendo tudo para minutos
    //1 dia = 1440 minutos & 1 hora = 60 minutos
    long minutos1 = (d1.dia * 1440) + (h1.horas * 60) + h1.minutos;
    long minutos2 = (d2.dia * 1440) + (h2.horas * 60) + h2.minutos;
    
    return (int)(minutos2 - minutos1);
}

void relatorioRankingBombeiros(Intervencoes intervencoes, Ocorrencias ocorrencias, Bombeiros bombeiros) {
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


void relatoriosBombeiros(Intervencoes intervencoes, Ocorrencias ocorrencias, Bombeiros bombeiros) {
    if (bombeiros.numBombeiros == 0) {
        logMsg("Sem bombeiros para gerar relatórios.");
        printf("Sem bombeiros para gerar relatórios.\n");
        return;
    }
    int opcao;
    do {
        printf("==============================\n");
        printf("      RELATÓRIOS BOMBEIROS    \n");
        printf("==============================\n");
        printf("1. Disponibilidade por especialidade\n");
        printf("2. Histórico de Intervenções por Bombeiro\n");
        printf("3. Ranking de Bombeiros por Intervenções Concluídas\n");
        printf("0. Voltar ao Menu dos Relatórios\n");
        printf("==============================\n");
        opcao = obterInteiro(0, 3, "Escolha uma opcao: ");
        switch(opcao) {
            case 1:
                logMsg("A gerar relatório de disponibilidade operacional.");
                relatorioDisponibilidade(bombeiros);
                break;
            case 2:
                logMsg("A gerar relatório de histórico de intervenções por bombeiro.");
                relatorioHistoricoBombeiro(intervencoes, bombeiros);
                break;
            case 3:
                logMsg("A gerar relatório de ranking de bombeiros por intervenções concluídas.");
                relatorioRankingBombeiros(intervencoes, ocorrencias, bombeiros);
                break;
            case 0:
                logMsg("A sair do menu de relatórios de bombeiros.");
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); 
        }
    } while(opcao != 0);
}

// ----------- Relatorios Equipamentos ------------

// Relatório 1: Inventário Geral (Resumo por Tipo e Estado)
void relatorioInventario(Equipamentos equipamentos) {
    int qtdVestuario = 0, qtdVeiculos = 0, qtdFerramentas = 0, qtdComunicacao = 0;
    int qtdDisponivel = 0, qtdEmUso = 0, qtdManutencao = 0;

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        // Contagem por Tipo
        switch (equipamentos.equipamentos[i].tipo) {
            case VESTUARIO:   qtdVestuario++; break;
            case VEICULOS:    qtdVeiculos++; break;
            case FERRAMENTAS: qtdFerramentas++; break;
            case COMUNICACAO: qtdComunicacao++; break;
        }

        // Contagem por Estado
        switch (equipamentos.equipamentos[i].estado) {
            case EQ_DISPONIVEL: qtdDisponivel++; break;
            case EQ_EM_USO:     qtdEmUso++; break;
            case EQ_MANUTENCAO: qtdManutencao++; break;
        }
    }

    printf("\n=== INVENTÁRIO DE EQUIPAMENTOS ===\n");
    printf("Total de Equipamentos: %d\n", equipamentos.numEquipamentos);
    
    printf("\n--- Por Categoria ---\n");
    printf("Veículos:      %d\n", qtdVeiculos);
    printf("Ferramentas:   %d\n", qtdFerramentas);
    printf("Comunicação:   %d\n", qtdComunicacao);
    printf("Vestuário:     %d\n", qtdVestuario);

    printf("\n--- Por Estado ---\n");
    printf("Disponíveis:   %d\n", qtdDisponivel);
    printf("Em Uso:        %d\n", qtdEmUso);
    printf("Em Manutenção: %d\n", qtdManutencao);
    printf("==================================\n");
}

// Relatório 2: Lista de Equipamentos em Manutenção
void relatorioManutencao(Equipamentos equipamentos) {
    printf("\n=== EQUIPAMENTOS EM MANUTENÇÃO ===\n");
    int encontrou = 0;

    printf("%-5s | %-20s | %-15s\n", "ID", "Nome", "Tipo");
    printf("----------------------------------------------\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        if (equipamentos.equipamentos[i].estado == EQ_MANUTENCAO) {
            printf("%-5d | %-20s | ", equipamentos.equipamentos[i].id, equipamentos.equipamentos[i].nome);
            
            // Pequeno switch local para imprimir o tipo alinhado na tabela
            switch(equipamentos.equipamentos[i].tipo) {
                case VESTUARIO:   
                    printf("Vestuário\n"); 
                    break;
                case VEICULOS:    
                    printf("Veículo\n"); 
                    break;
                case FERRAMENTAS: 
                    printf("Ferramenta\n"); 
                    break;
                case COMUNICACAO: 
                    printf("Comunicação\n"); 
                    break;
                default:
                    printf("Outro\n"); 
                    break;
            }
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf(">> Nenhum equipamento em manutenção no momento.\n");
    }
    printf("----------------------------------------------\n");
}

void relatorioTopEquipamentos(Intervencoes intervencoes, Equipamentos equipamentos) {
    if (equipamentos.numEquipamentos == 0) {
        printf("Sem equipamentos registados.\n");
        return;
    }

    // 1. Arrays Temporários
    int *contagem = (int*) calloc(equipamentos.numEquipamentos, sizeof(int));
    int *indices = (int*) malloc(equipamentos.numEquipamentos * sizeof(int));

    // Inicializar índices
    for (int i = 0; i < equipamentos.numEquipamentos; i++) indices[i] = i;

    // 2. Contar utilizações em TODAS as intervenções (concluídas ou não)
    for (int i = 0; i < intervencoes.numIntervencoes; i++) {
        if (intervencoes.intervencoes[i].idsEquipamentos != NULL) {
            for (int k = 0; k < intervencoes.intervencoes[i].numEquipamentos; k++) {
                int idEquip = intervencoes.intervencoes[i].idsEquipamentos[k];
                int idxE = procurarEquipamento(equipamentos, idEquip);
                
                if (idxE != -1) {
                    contagem[idxE]++;
                }
            }
        }
    }

    // 3. Ordenar (Bubble Sort decrescente)
    for (int i = 0; i < equipamentos.numEquipamentos - 1; i++) {
        for (int j = 0; j < equipamentos.numEquipamentos - i - 1; j++) {
            int idxAtual = indices[j];
            int idxProx = indices[j+1];
            
            if (contagem[idxAtual] < contagem[idxProx]) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }

    // 4. Imprimir Top 5 (ou todos)
    printf("\n=== RANKING DE UTILIZAÇÃO DE EQUIPAMENTOS ===\n");
    printf("%-5s | %-20s | %-15s | %s\n", "Rank", "Nome", "Tipo", "Uso");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < equipamentos.numEquipamentos; i++) {
        int realIdx = indices[i];
        if (contagem[realIdx] > 0) {
            printf("%-5d | %-20s | ", i + 1, equipamentos.equipamentos[realIdx].nome);
            
            switch(equipamentos.equipamentos[realIdx].tipo) {
                case VESTUARIO:   printf("%-15s | ", "Vestuário"); break;
                case VEICULOS:    printf("%-15s | ", "Veículo"); break;
                case FERRAMENTAS: printf("%-15s | ", "Ferramenta"); break;
                case COMUNICACAO: printf("%-15s | ", "Comunicação"); break;
                default:          printf("%-15s | ", "Outro"); break;
            }
            
            printf("%d vezes\n", contagem[realIdx]);
        }
    }
    printf("----------------------------------------------------------\n");

    free(contagem);
    free(indices);
}


void relatorioUtilizacaoTipoIntervencao(Equipamentos equipamentos) {

}
void relatoriosEquipamentos(Intervencoes intervencoes, Ocorrencias ocorrencias, Equipamentos equipamentos) {
    if (equipamentos.numEquipamentos == 0) {
        logMsg("Sem equipamentos para gerar relatórios.");
        printf("Sem equipamentos para gerar relatórios.\n");
        return;
    }
    int opcao;
    do {
        printf("==============================\n");
        printf("     RELATÓRIOS EQUIPAMENTOS   \n");
        printf("==============================\n");
        printf("1. Inventário Geral\n");
        printf("2. Equipamentos em Manutenção\n");
        printf("3. Ranking de Utilização de Equipamentos\n");
        printf("4. Análise de Equipamentos por Tipo de Intervenção\n");
        printf("0. Voltar ao Menu dos Relatórios\n");
        printf("==============================\n");
        opcao = obterInteiro(0, 4, "Escolha uma opcao: ");
        switch(opcao) {
            case 1:
                logMsg("A gerar relatório de inventário geral de equipamentos.");
                relatorioInventario(equipamentos);
                break;
            case 2:
                logMsg("A gerar relatório de equipamentos em manutenção.");
                relatorioManutencao(equipamentos);
                break;
            case 3:
                logMsg("A gerar relatório de ranking de utilização de equipamentos.");
                relatorioTopEquipamentos(intervencoes, equipamentos);
                break;
            case 4:
                logMsg("A gerar relatório de análise de equipamentos por tipo de intervenção.");
                relatorioUtilizacaoTipoIntervencao(equipamentos);
                break;
            case 0:
                logMsg("A sair do menu de relatórios de equipamentos.");
                printf("A Sair...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        if(opcao != 0) {
            printf("Pressione ENTER para voltar ao menu...");
            getchar(); 
        }
    } while(opcao != 0);
}

// ----------- Relatorios Quarteis ------------