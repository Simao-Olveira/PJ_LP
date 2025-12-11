
#ifndef PJ_LP_BOMBEIROGESTAO_H
#define PJ_LP_BOMBEIROGESTAO_H

#include "bombeiro.h"

int procurarBombeiro(Bombeiros bombeiros, int id);
void adicionarBombeiro(Bombeiros bombeiros);
void libertarMemBombeiros(Bombeirosbombeiros);
void imprimirBombeiro(Bombeiro bombeiro);
void listarBombeiros(Bombeiros bombeiros);
void atualizarDadosBombeiro(Bombeiro bombeiro);
void editarBombeiro(Bombeirosbombeiros);
void eliminarBombeiro(Bombeiros bombeiros);
void guardarBombeiros(Bombeiros *bombeiros);
void carregarBombeiros(Bombeirosbombeiros);

#endif //PJ_LP_BOMBEIROGESTAO_H