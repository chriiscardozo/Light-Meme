#include "robo.h"

void initRobo(JOGO_T *jogo){
     jogo->robo.direcao = SUL;
     jogo->robo.x = 4;
	 jogo->robo.y = 2;
	 //imagens do robo
}

void constroiRobo(JOGO_T *jogo){
     int i;
     
     for(i = 0; i < 4; i++)
        jogo->robo.img[i] = create_bitmap( LADO_CELULA, LADO_CELULA );
}

void desenhaRobo(JOGO_T *jogo){
     
     jogo->robo.img[0] = load_bitmap("images/robo/robo_norte.bmp", NULL);
     jogo->robo.img[1] = load_bitmap("images/robo/robo_leste.bmp", NULL);
     jogo->robo.img[2] = load_bitmap("images/robo/robo_sul.bmp", NULL);
     jogo->robo.img[3] = load_bitmap("images/robo/robo_oeste.bmp", NULL);
     
}

void printaRobo(JOGO_T *jogo){
     int direcao = jogo->robo.direcao;
     int x = jogo->robo.x * LADO_CELULA;
     int y = jogo->robo.y * LADO_CELULA;
     
     draw_sprite(jogo->tabuleiro.imagem, jogo->robo.img[direcao], x, y);
     printaTabuleiro(jogo);
}
