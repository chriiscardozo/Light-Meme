#ifndef UTIL_H
    
    #define UTIL_H
    #include "game.h"

    void desenhaTabela(BITMAP *bmp, int nx, int ny);
    void aguarda(JOGO_T *jogo, int tempo);
    FILE* abreArquivo(char caminho[], char modo[]);
    void fechaArquivo(FILE *f);
    
#endif
