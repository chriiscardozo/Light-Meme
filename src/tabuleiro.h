#ifndef TABULEIRO_H

    #define TABULEIRO_H
    #include "game.h"

    void initTabuleiro(JOGO_T *jogo);
    void constroiTabuleiro(JOGO_T *jogo);
    
    void pintaCelulaTabuleiro(JOGO_T *jogo, int x, int y);
    void pintaTodasCelulasTabuleiro(JOGO_T *jogo);

    void desenhaTabuleiro(JOGO_T *jogo);
    void printaTabuleiro(JOGO_T *jogo);
    
#endif
