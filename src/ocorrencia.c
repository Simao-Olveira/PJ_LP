const char* tipoToString(TipodeOcorrencia e) {
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

void adicionarOcorrencia(Ocorrencia **ocorrencias, int *numOcorrencias) {
    Ocorrencia novaOcorrencia;
    int op;

    novaOcorrencia.id = (*numOcorrencias) + 1;

    printf("\n--- Localização da Ocorrencia ---\n");
    scanf("%s", novaOcorrencia.localizacao);

    printf("\n--- Data e hora da Ocorrencia ---\n");





    printf("\n--- Tipo de Ocorrencia ---\n");
    printf("0 - Florestal\n1 - Urbano\n2 - Industrial\n");
    printf("Escolha uma opcao:\n ");
    scanf("%d", &op);
    novaOcorrencia.tipo = (TipodeOcorrencia) op;

    printf("\n--- Prioridade da Ocorrencia ---\n");
    printf("0 - Baixa\n1 - Normal\n2 - Alta\n");
    printf("Escolha uma opcao:\n ");
    scanf("%d", &op);
    novaOcorrencia.prioridade = (PrioridadedaOcorrencia) op;

    printf("\n--- Estado da Ocorrencia ---\n");
    printf("0 - Reportada\n1 - Em Intervencao\n2 - Concluida\n");
    printf("Escolha uma opcao:\n ");
    scanf("%d", &op);
    novaOcorrencia.tipo = (EstadodaOcorrenciaOcorrencia) op;

    (*numOcorrencias)++;
    *ocorrencias = realloc(*ocorrencias, (*numOcorrencias) * sizeof(Ocorrencia));
    (*ocorrencias)[(*numOcorrencias) - 1] = novaOcorrencia;

}

void listarOcorrencia(Ocorrencia **ocorrencias, int *numOcorrencias) {
    for (int i = 0; i < numOcorrencias; i++) {
        printf("ID: %d\n", ocorrencias[i].id);
        printf("Localizacao: %s\n", ocorrencias[i].localizacao);
        printf("Data e Hora: %d\n", ocorrencias[i].dataehora);
        printf("Tipo: %s\n", tipoToString(ocorrencias[i].tipo));
        printf("Prioridade: %s\n", prioridadeToString(ocorrencias[i].prioridade));
        printf("Estado: %s\n", estadoToString(ocorrencias[i].estado));
    }
}

void atualizarOcorrencia(Ocorrencia *ocorrencias, int numOcorrencias) {
    int id, opcao;

    printf("\nDigite o ID da Ocorrencia a ser atualizada:\n")
    scanf("%d", &id);

    if (id <= 0 || id > numOcorrencias) {
        printf("\nOcorrencia não encontrada.\n");
        return;
    }
    Ocorrencia *o = &ocorrencias[id - 1];
    printf("\nO que deseja atualizar?\n");
    printf("1 - Localização\n");
    printf("2 - Data e hora\n");
    printf("3 - Tipo\n");
    printf("4 - Prioridade\n");
    printf("5 - Estado\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Nova localizacao:\n");
            scanf("%s", o->localizacao);
            break;
            ------------------------------------
        case 2:
            int op;
            printf("\n--- Data e hora ---\n");
            printf("0 - Combate Florestal\n1 - Combate Aereo\n2 - Resgate\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            o->dataehora = (DataehoraOcorrencia) op;
            break;
                ----------------------------------
        case 3:
            int op;
            printf("\n--- Tipo ---\n");
            printf("0 - Florestal\n1 - Urbano\n2 - Industrial\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            o->tipo = (TipoOcorrencia) op;
            break;
        case 4:
            int op;
            printf("\n--- Prioridade ---\n");
            printf("0 - Baixa\n1 - Normal\n2 - Alta\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            o->prioridade = (PrioridadeOcorrencia) op;
            break;
        case 5:
            int op;
            printf("\n--- Estado ---\n");
            printf("0 - Reportada\n1 - Em Intervencao\n2 - Concluida\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            o->estado = (EstadoOcorrencia) op;
            break;

        default:
            printf("Opção inválida!\n");
            return;
    }
    printf("\nOcorrencia atualizada com sucesso!\n");
}

void removerOcorrencia (Ocorrencia *ocorrencias, int numOcorrencias) {
    int id;

    printf("\nDigite o ID da ocorrencia a ser removida:\n ");
    scanf("%d", &id);

    if (id <= 0 || id > numOcorrencias) {
        printf("\nOcorrencia não encontrado.");
        return;
    }
    //ativa=1 e inativa=0
    ocorrencia[id - 1].ativa = 0;
    printf("\nOcorrencia %d marcada como inativa.", id);

}

void guardarOcorrenciasEmFicheiros(Ocorrencia *ocorrencias, int numOcorrencias) {
    FILE *f = fopen("ocorrencias.txt", "w");

    if (!f) {
        printf("\nErro ao abrir ficheiro de ocorrencias.");
        return;
    }

    for (int i = 0; i < numOcorrencias; i++) {
        if (ocorrencias[i].ativa != 0) {  // Guarda apenas tarefas ativas
            fprintf(f, "%d,%s,%d,%d,%d,%d\n", o[i].id, o[i].localizacao, o[i].dataehora, o[i].tipo, o[i].prioridade, o[i].estado);
    }
        fclose(f);
}

void carregarOcorrenciasDeFicheiros(Ocorrencias **ocorrencias, int *numOcorrencias) {
    FILE *f = fopen("ocorrencias.txt", "r");

    if (!f) {
        printf("\nFicheiro de ocorrencias não encontrado.");
        return;
    }

    while (!feof(f)) {
        Ocorrencias o;
        int estado;
        if (fscanf(f, "\n%d,%99[^,],%10[^,],%10[^,],%d,%d", &t.id, t.localizacao, t.datehora, t.tipo, t.prioridade, &estado) == 6)
        {
            o.estado = estado;
            (*numOcorrencias)++;
            *ocorrencias = realloc(*ocorrencias, (*numOcorrencias) * sizeof(Ocorrencia));
            (*ocorrencias)[(*numOcorrencias) - 1] = o;
        }
    }
    fclose(f);
}
