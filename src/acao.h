#ifndef ACAO_H
    
    #define ACAO_H
    #include "game.h"
    
    void initAcoesFixas(JOGO_T *jogo);
    void initAcoesAuxiliares(JOGO_T *jogo);
    void initAcoes(JOGO_T *jogo);
    
    void alocaImagemAcao(JOGO_T *jogo, int i);
    void constroiAcoes(JOGO_T *jogo);
    
    void desenhaAcoes(JOGO_T *jogo);
    
#endif
