#ifndef FUNCAO_H
    
    #define FUNCAO_H
    #include "game.h"

    void initFuncao(FUNCAO_T *funcao, int x, int y, int n_pos);
    void initFuncoesAuxiliares(JOGO_T *jogo);
    void initFuncoes(JOGO_T *jogo);
    
    void constroiFuncao(FUNCAO_T *funcao, int n_pos);
    void constroiFuncoesAuxiliares(JOGO_T *jogo);
    void constroiFuncoes(JOGO_T *jogo);
    
    void printaFuncoes(JOGO_T *jogo);
    void desenhaFuncoes(JOGO_T *jogo);
    
    int executaFuncao(JOGO_T *jogo, FUNCAO_T *funcao, int n_acoes, int *startStop);
#endif
