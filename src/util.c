#include "util.h"
#include <math.h>

void desenhaTabela(BITMAP *bmp, int nx, int ny){
     int i;
     
     rectfill( bmp, 0, 0, ny * LADO_CELULA, nx * LADO_CELULA, makecol(255,255,255));
	
	 for(i = 0; i <= nx; i++)	
		hline( bmp, 0, i * LADO_CELULA, LADO_CELULA * ny, makecol(0,0,0));
		
	 for(i = 0; i <= ny; i++)
		vline( bmp, i * LADO_CELULA, LADO_CELULA * ny, 0, makecol(0,0,0));
}

void aguarda(JOGO_T *jogo, int tempo){
     int i;
     
     for(i = 0; i < tempo; i++){
        atualizaTela(jogo);
        rest(1);
     }
}

FILE* abreArquivo(char *caminho, char *modo){
    FILE *f = fopen(caminho, modo);
    
    if(!f){
           printf("ERRO: O arquivo nao existe\n<ENTER>");
           getchar();
           exit(0);
    }
    return f;
}

void fechaArquivo(FILE *f){
    if(fclose(f)){
        printf("ERRO: Problemas ao fechar o arquivo\n<ENTER>");
        getchar();
     }
}
