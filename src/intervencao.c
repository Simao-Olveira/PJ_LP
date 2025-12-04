const char* especialidadeToString(EspecialidadeBombeiro e) {
    switch (e) {
        case COMANDO: return "Comando";
        case TRIPULANTE: return "Tripulante";
        case MOTORISTA: return "Motorista";
        case SOCORRISTA: return "Socorrista";
        default: return "Desconhecida";
    }
}

const char* estadoToString(EstadoBombeiro e) {
    switch (e) {
        case ATIVO: return "Ativo";
        case INATIVO: return "Inativo";
        case FERIDO: return "Ferido";
        default: return "Desconhecido";
    }
}

void adicionarIntervencao(Intervencao **intervencoes, int *numIntervencoes) {
Intervencao novaIntervencao;
int op;

novaIntervencao.id = (*numIntervencoes) + 1;

    printf("\n--- ID da Ocorrencia ---\n");
    scanf("%d", ocorrencias[i].id--------);

    printf("\n--- Data e hora do inicio da Intervencao ---\n");
    scanf("%d", ----------------);




    printf("\n--- Data e hora do final da Intervencao ---\n");
    scanf("%d", ----------------);





    printf("\n--- Estado da Intervencao ---\n");
    printf("0 - Em Planeamento\n1 - Em Execucao\n2 - Concluida\n");
    printf("Escolha uma opcao:\n ");
    scanf("%d", &op);
    novaIntervencao.estado = (EstadoIntervencao) op;

    (*numIntervencoes)++;
    *intervencoes = realloc(*intervencoes, (*numIntervencoes) * sizeof(Intervencao));
    (*intervencoes)[(*numIntervencoes) - 1] = novoIntervencao;

}

void listarIntervencao(Intervencao **intervencoes, int *numIntervencoes) {
    for (int i = 0; i < numIntervencoes; i++) {
        printf("ID: %d\n", intervencoes[i].id);
        printf("ID da ocorrencia: %d\n", intervencoes[i].idOcorrencia---------);
        printf("Data e hora no inicio: %d\0n", intervencoes[i].dataehoraInicio);
        printf("Data e hora no final: %d\0n", intervencoes[i].dataehoraFinal);
        printf("Estado: %s\n", estadoToString(intervencoes[i].estado));
    }
}

void atualizarIntervencao(Intervencao *intervencoes, int numIntervencoes) {
    int id, opcao;

    printf("\nDigite o ID da Intervencao a ser atualizada:\n")
    scanf("%d", &id);

    if (id <= 0 || id > numIntervencoes) {
        printf("\nIntervencao não encontrada.\n");
        return;
    }
    Intervencao *i = &intervencoes[id - 1];
    printf("\nO que deseja atualizar?\n");
    printf("1 - ID da Ocorrencia\n");
    printf("2 - Data e hora do inicio\n");
    printf("3 - Data e hora do final\n");
    printf("4 - Estado\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Novo ID da ocorrencia:\n");
            scanf("%d", i->idOcorrencia);
            break;
---------------------------------------------------------
        case 2:
            printf("Nova data e hora do inicio:\n");
            scanf("%d", i->idOcorrencia);

        case 3
            printf("Nova data e hora do final:\n");
            scanf("%d", i->idOcorrencia);
---------------------------------------------------------
        case 4:
            int op;
            printf("\n--- Estado da Intervencao ---\n");
            printf("0 - Em Planeamento\n1 - Em Execucao\n2 - Concluida\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            I->estado = (EstadoIntervencao) op;
            break;

        default:
            printf("Opção inválida!\n");
            return;
    }
    printf("\nIntervencao atualizada com sucesso!\n");
}

void removerIntervencao (Intervencao *intervencoes, int numIntervencoes) {
    int id;

    printf("\nDigite o ID da intervencao a ser removida:\n ");
    scanf("%d", &id);

    if (id <= 0 || id > numBIntervencoes) {
        printf("\nIntervencao não encontrada.");
        return;
    }
    //ativa=1 e inativa=0
    intervencoes[id - 1].ativa = 0;
    printf("\nIntervencao %d marcada como inativa.", id);

}

void guardarIntervencoesEmFicheiros(Intervencao *intervencoes, int numIntervencoes) {
    FILE *f = fopen("intervencoes.txt", "w");

    if (!f) {
        printf("\nErro ao abrir ficheiro de intervencoes.");
        return;
    }

    for (int i = 0; i < numIntervencoes; i++) {
        if (intervencoes[i].ativo != 0) {  // Guarda apenas tarefas ativas
            fprintf(f, "%d,%d,%d,%d,%d\n", i[i].id, i[i].idOcorrencia, i[i].dataehorsInicio, i[i].dataehorsFinal, i[i].estado);
        }
        fclose(f);
    }

    void carregarIntervencoesDeFicheiros(Intervencoes **intervencoes, int *numIntervencoes) {
        FILE *f = fopen("intervencoes.txt", "r");

        if (!f) {
            printf("\nFicheiro de intervencoes não encontrado.");
            return;
        }

        while (!feof(f)) {
            Intervencoes i;
            int estado;
            if (fscanf(f, "\n%d,%99[^,],%10[^,],%10[^,],%d,%d", &i.id, i.idOcorrencia, i.dataehorsInicio, i.dataehorsInicio, &estado) == 5)
            {
                i.estado = estado;
                (*numIntervencoes)++;
                *intervencoes = realloc(*intervencoes, (*numIntervencoes) * sizeof(Intervencao));
                (*intervencoes)[(*numIntervencoes) - 1] = i;
            }
        }
        fclose(f);
    }