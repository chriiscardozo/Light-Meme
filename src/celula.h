#ifndef CELULAS_H

    #define CELULAS_H
    #include "game.h"
    
    void initPremios(JOGO_T *jogo, int x[], int y[], int n_premios);
    void initParedes(JOGO_T *jogo, int x[], int y[], int n_paredes);
    
    void initCelulas(JOGO_T *jogo);
    void constroiCelulas(JOGO_T *jogo);

#endif
