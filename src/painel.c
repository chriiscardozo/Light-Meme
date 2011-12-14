#include "painel.h"

void initPainel(JOGO_T *jogo){
     jogo->painel.x = X_PAINEL;
     jogo->painel.y = Y_PAINEL;
     
     initAcoes(jogo);
}

void constroiPainel(JOGO_T *jogo){
     
     jogo->painel.imagem = create_bitmap((N_ACOES_FIXAS + N_FUNCOES_AUXILIARES) * LADO_CELULA + 1, LADO_CELULA + 1);     
     constroiAcoes(jogo);
}

void desenhaPainel(JOGO_T *jogo){
     
     desenhaTabela(jogo->painel.imagem, 1, N_ACOES_FIXAS + N_FUNCOES_AUXILIARES);
     desenhaAcoes(jogo);
}

void printaPainel(JOGO_T *jogo){
     
     draw_sprite(jogo->bmpbuffer, jogo->painel.imagem, X_PAINEL, Y_PAINEL);
}
