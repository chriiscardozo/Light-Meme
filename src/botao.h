#ifndef BOTAO_H
   
   #define BOTAO_H
   #include "game.h"
   
   void constroiBotoes(JOGO_T *jogo);
   void initBotoes(JOGO_T *jogo);
   
   void desenhaBotoes(JOGO_T *jogo);
   
   void printaBotao(JOGO_T *jogo, BOTAO_T *botao, int pos);
   void printaBotoes(JOGO_T *jogo);

#endif
