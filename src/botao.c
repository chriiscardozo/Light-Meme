#include "botao.h"

void constroiBotao(BOTAO_T *botao, TIPOBOTAO_T tipo){
     int i;
     
     for(i = 0; i < tipo; i++)
        botao->imagem[i] = create_bitmap(TAMANHO_X_BOTAO, TAMANHO_Y_BOTAO);

     if (i = 1)
          botao->imagem[i] = NULL;
}

void constroiBotoes(JOGO_T *jogo){
     constroiBotao(&jogo->botoes[0], RESET);
     constroiBotao(&jogo->botoes[1], START);
}

void initBotao(BOTAO_T *botao, int x, int y, TIPOBOTAO_T tipo ){
     botao->x = x;
     botao->y = y;
}

void initBotoes(JOGO_T *jogo){
     initBotao(&jogo->botoes[0], X_BOTAO_RESET, Y_BOTAO_RESET, RESET);
     initBotao(&jogo->botoes[1], X_BOTAO_START, Y_BOTAO_START, START);
}

void desenhaBotao(BOTAO_T *botao, int tipo){
     if(tipo == 1)
        botao->imagem[0] = load_bitmap("images/botoes/botao_reset.bmp", NULL );
     
     else{
          botao->imagem[0] = load_bitmap("images/botoes/botao_start.bmp", NULL );
          botao->imagem[1] = load_bitmap("images/botoes/botao_stop.bmp", NULL );
     }
}

void desenhaBotoes(JOGO_T *jogo){
     desenhaBotao(&jogo->botoes[0], RESET);
     desenhaBotao(&jogo->botoes[1], START);
}

void printaBotao(JOGO_T *jogo, BOTAO_T *botao, int pos){
     draw_sprite(jogo->bmpbuffer, botao->imagem[pos], botao->x, botao->y);
}
     
void printaBotoes(JOGO_T *jogo){
     printaBotao(jogo, &jogo->botoes[0], 0);
     printaBotao(jogo, &jogo->botoes[1], 0);
}
