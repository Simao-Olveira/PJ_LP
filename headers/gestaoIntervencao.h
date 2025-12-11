
#ifndef PJ_LP_INTERVENCAOGESTAO_H
#define PJ_LP_INTERVENCAOGESTAO_H

int procurarIntervencao(Intervencoes intervencoes, int id);
void adicionarIntervencao(Intervencoes intervencoes);
void libertarMemIntervencoes(Intervencoesintervencoes);
void imprimirIntervencao(Intervencao intervencao);
void listarIntervencoes(Intervencoes intervencoes);
void atualizarDadosIntervencao(Intervencao intervencao);
void editarIntervencao(Intervencoesintervencoes);
void eliminarIntervencao(Intervencoes intervencoes);
void guardarIntervencoes(Intervencoes *intervencoes);
void carregarIntervencoes(Intervencoesintervencoes);

#endif //PJ_LP_INTERVENCAOGESTAO_H