#include "celula.h"

void initPremios(JOGO_T *jogo, int x[], int y[], int n_premios){
     int i;
     
     for(i = 0; i < n_premios; i++){
        jogo->tabuleiro.celula[x[i]][y[i]].cor = COR_PREMIO;
        jogo->tabuleiro.celula[x[i]][y[i]].valor = PREMIO;
     }
}

void initParedes(JOGO_T *jogo, int x[], int y[], int n_paredes){
     int i;
     
     for(i = 0; i < n_paredes; i++){
        jogo->tabuleiro.celula[x[i]][y[i]].cor = COR_PAREDE;
        jogo->tabuleiro.celula[x[i]][y[i]].valor = PAREDE;
     }
}

void initCelulas(JOGO_T *jogo){
     int i, j;
     
     int premiosX[] = {4};
     int premiosY[] = {4};
     int paredesX[] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7};
     int paredesY[] = {0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 7, 7, 7, 7};
     
     for( i = 0; i < jogo->tabuleiro.n_celulas_y; i++ )
          for( j = 0; j < jogo->tabuleiro.n_celulas_x; j++ ){
             jogo->tabuleiro.celula[i][j].valor = VAZIA;
             jogo->tabuleiro.celula[i][j].cor = COR_DEFAULT;
          }
     
     initParedes(jogo, jogo->fase.paredeX, jogo->fase.paredeY, jogo->fase.nParedes);
     initPremios(jogo, jogo->fase.premioX, jogo->fase.premioY, jogo->fase.nPremios);
}

void constroiCelulas(JOGO_T *jogo){
     int i, j;

     jogo->tabuleiro.celula = (CELULA_T**) malloc(N_CELULAS_Y * sizeof(CELULA_T*));
     
     for(i = 0; i < N_CELULAS_Y; i++)
        jogo->tabuleiro.celula[i] = (CELULA_T*) malloc(N_CELULAS_X * sizeof(CELULA_T));

}
