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

void adicionarEquipamento(Equipamento **equipamentos, int *numEquipamentos) {
Equipamento novoEquipamento;
int op;

novoEquipamento.id = (*numEquipamentos) + 1;

    printf("\n--- Nome do equipamento ---\n");
    scanf("%s", novoEquipamento.nome);

    printf("\n--- Tipo de equipamento ---\n");
    scanf("%s", novoEquipamento.tipo);

    printf("\n--- Estado do equipamento ---\n");
    printf("0 - Disponível\n1 - Em Uso\n2 - Em Manutencao\n");
    printf("Escolha uma opcao:\n ");
    scanf("%d", &op);
    novoEquipamento.estado = (EstadoEquipamento) op;

    printf("\n--- Localizacao ---\n");
    scanf("%s", novoEquipamento.localizacao);

    (*numEquipamentos)++;
    *equipamentos = realloc(*equipamentos, (*numEquipamentos) * sizeof(Equipamento));
    (*equipamentos)[(*numEquipamentos) - 1] = novoEquipamento;

}

void listarEquipamento(Equipamento **equipamentos, int *numEquipamentos) {
    for (int i = 0; i < numEquipamentos; i++) {
        printf("ID: %d\n", equipamentos[i].id);
        printf("Nome: %s\n", equipamentos[i].nome);
        printf("Tipo: %s\n", equipamentos[i].tipo);
        printf("Estado: %s\0n", estadoToString(equipamentos[i].estado));
        printf("Localizacao: %s\n", equipamentos[i].localizacao);
    }
}

void atualizarEquipamento(Equipamento *equipamentos, int numEquipamentos) {
    int id, opcao;

    printf("\nDigite o ID do Equipamento a ser atualizado:\n")
    scanf("%d", &id);

    if (id <= 0 || id > numEquipamentos) {
        printf("\nEquipamento não encontrado.\n");
        return;
    }
    Equipamento *e = &equipamentos[id - 1];
    printf("\nO que deseja atualizar?\n");
    printf("1 - Nome\n");
    printf("2 - Tipo\n");
    printf("3 - Estado\n");
    printf("4 - Localizacao\n");
    printf("Escolha uma opcao:\n");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Novo nome:\n");
            scanf("%s", e->nome);
            break;

        case 2:
            printf("Novo tipo:\n");
            scanf("%s", e->nome);
            break;

        case 3:
            int op;
            printf("\n--- Estado do equipamento ---\n");
            printf("0 - Disponível\n1 - Em Uso\n2 - Em Manutencao\n");
            printf("Escolha uma opcao:\n ");
            scanf("%d", &op);
            e->estado = (EstadoEquipamento) op;
            break;

        case 4:
            printf("Nova localizacao:\n");
            scanf("%s", e->nome);
            break;

        default:
            printf("Opção inválida!\n");
            return;
    }
    printf("\nEquipamento atualizado com sucesso!\n");
}

void removerEquipamento (Equipamento *equipamentos, int numEquipamentos) {
    int id;

    printf("\nDigite o ID do equipamento a ser removido:\n ");
    scanf("%d", &id);

    if (id <= 0 || id > numEquipamentos) {
        printf("\nEquipamento não encontrado.");
        return;
    }
    //ativo=1 e inativo=0
    equipamentos[id - 1].ativo = 0;
    printf("\nEquipamento %d marcado como inativo.", id);

}

void guardarEquipamentosEmFicheiros(Equipamento *equipamentos, int numEquipamentos) {
    FILE *f = fopen("equipamentos.txt", "w");

    if (!f) {
        printf("\nErro ao abrir ficheiro de equipamentos.");
        return;
    }

    for (int i = 0; i < numEquipamentos; i++) {
        if (equipamentos[i].ativo != 0) {  // Guarda apenas tarefas ativas
            fprintf(f, "%d,%s,%s,%d,%s\n", e[i].id, e[i].nome, e[i].tipo, e[i].estado, e[i].localizacao);
        }
        fclose(f);
    }

void carregarEquipamentosDeFicheiros(Equipamentos **equipamentos, int *numEquipamentos) {
    FILE *f = fopen("equipamentos.txt", "r");

    if (!f) {
        printf("\nFicheiro de equipamentos não encontrado.");
        return;
    }

    while (!feof(f)) {
        Equipamentos e;
        int estado;
        if (fscanf(f, "\n%d,%99[^,],%10[^,],%10[^,],%d,%d", &e.id, e.nome, e.tipo, &estado, e.localizacao) == 5)
        {
            e.estado = estado;
            (*numEquipamentos)++;
            *equipamentos = realloc(*equipamentos, (*numEquipamentos) * sizeof(Equipamento));
            (*equipamentos)[(*numEquipamentos) - 1] = e;
        }
    }
    fclose(f);
}
