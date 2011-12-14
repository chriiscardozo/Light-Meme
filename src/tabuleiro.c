#include "tabuleiro.h"

void initTabuleiro(JOGO_T *jogo){
     jogo->tabuleiro.n_celulas_x = N_CELULAS_X;
	 jogo->tabuleiro.n_celulas_y = N_CELULAS_Y;
	 jogo->tabuleiro.n_celulas = N_CELULAS_X * N_CELULAS_Y;
	 jogo->tabuleiro.bmpx0 = X_TABULEIRO;
	 jogo->tabuleiro.bmpy0 = Y_TABULEIRO;
	 jogo->tabuleiro.lado_celula = LADO_CELULA;
	 
	 initCelulas(jogo);
}

void constroiTabuleiro(JOGO_T *jogo){
	 
	 jogo->tabuleiro.imagem = create_bitmap( N_CELULAS_X * LADO_CELULA + EXTENSAO_EXTRA_TABULEIRO + 1, 
											 N_CELULAS_Y * LADO_CELULA + EXTENSAO_EXTRA_TABULEIRO + 1);

	 constroiCelulas(jogo);
}

void pintaCelulaTabuleiro(JOGO_T *jogo, int x, int y){
     int x1 = x * jogo->tabuleiro.lado_celula +1;
     int y1 = y * jogo->tabuleiro.lado_celula +1;
     
     rectfill( jogo->tabuleiro.imagem,
               x1, y1,
               jogo->tabuleiro.lado_celula - 2 + x1,
               jogo->tabuleiro.lado_celula - 2 + y1, jogo->tabuleiro.celula[y][x].cor);
                 
     printaTabuleiro(jogo);
}

void pintaTodasCelulasTabuleiro(JOGO_T *jogo){
     int i, j;
     
     for(i = 0; i < jogo->tabuleiro.n_celulas_y; i++)
        for(j = 0; j < jogo->tabuleiro.n_celulas_x; j++)
           pintaCelulaTabuleiro(jogo, i, j);
}

void desenhaTabuleiro(JOGO_T *jogo){
     int i;
     
     rectfill( jogo->tabuleiro.imagem, 
               0, 0, 
               jogo->tabuleiro.n_celulas_x * jogo->tabuleiro.lado_celula, 
			   jogo->tabuleiro.n_celulas_y * jogo->tabuleiro.lado_celula, 
			   makecol(255,255,255));

	
	 for(i = 0; i <= jogo->tabuleiro.n_celulas_x; i++)	
		hline( jogo->tabuleiro.imagem, 
			   0, 
			   i * jogo->tabuleiro.lado_celula, 
			   jogo->tabuleiro.lado_celula * jogo->tabuleiro.n_celulas_x, 
			   makecol(0,0,0));
		
	 for(i = 0; i <= jogo->tabuleiro.n_celulas_y; i++)
		vline( jogo->tabuleiro.imagem, 
			   i*jogo->tabuleiro.lado_celula, 
			   jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_y, 
			   0, 
			   makecol(0,0,0));

     pintaTodasCelulasTabuleiro(jogo);
           
     triangle( jogo->tabuleiro.imagem, 1, jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_y + 1,
               EXTENSAO_EXTRA_TABULEIRO, jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_y + 1,
               EXTENSAO_EXTRA_TABULEIRO, jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_y + EXTENSAO_EXTRA_TABULEIRO,
               COR_DEFAULT);
     
     triangle( jogo->tabuleiro.imagem, jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_x + 1, 1,
               jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_x + 1, EXTENSAO_EXTRA_TABULEIRO,
               jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_x + EXTENSAO_EXTRA_TABULEIRO, EXTENSAO_EXTRA_TABULEIRO,
               COR_DEFAULT);
     
     rectfill( jogo->tabuleiro.imagem, 
               EXTENSAO_EXTRA_TABULEIRO, jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_y+1,
               jogo->tabuleiro.n_celulas_x * jogo->tabuleiro.lado_celula + EXTENSAO_EXTRA_TABULEIRO,
			   jogo->tabuleiro.n_celulas_y * jogo->tabuleiro.lado_celula + EXTENSAO_EXTRA_TABULEIRO,
			   COR_DEFAULT);
      
     rectfill( jogo->tabuleiro.imagem, 
               jogo->tabuleiro.n_celulas_x * jogo->tabuleiro.lado_celula + 1, EXTENSAO_EXTRA_TABULEIRO,
               jogo->tabuleiro.n_celulas_x * jogo->tabuleiro.lado_celula + EXTENSAO_EXTRA_TABULEIRO,
			   jogo->tabuleiro.n_celulas_y * jogo->tabuleiro.lado_celula,
			   COR_DEFAULT);

     line( jogo->tabuleiro.imagem, jogo->tabuleiro.lado_celula * jogo->tabuleiro.n_celulas_x, jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_y,
           jogo->tabuleiro.lado_celula * jogo->tabuleiro.n_celulas_x + EXTENSAO_EXTRA_TABULEIRO, jogo->tabuleiro.lado_celula*jogo->tabuleiro.n_celulas_y + EXTENSAO_EXTRA_TABULEIRO, makecol(0,0,0));
}

void printaTabuleiro(JOGO_T *jogo){
     
     rotate_sprite( jogo->bmpbuffer, jogo->tabuleiro.imagem,
                    jogo->tabuleiro.bmpx0, jogo->tabuleiro.bmpy0, itofix(ANGULO_INT));
     
     /*draw_sprite(jogo->bmpbuffer, jogo->tabuleiro.imagem,
                 jogo->tabuleiro.bmpx0 , jogo->tabuleiro.bmpy0);*/
}
