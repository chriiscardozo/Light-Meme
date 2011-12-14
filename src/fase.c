#include "fase.h"

/* Estrutura do arquivo
1: (int) nivel
2: (int) nParedes
3: (int) nPremios
4: (int*) paredeX
5: (int*) paredeY
5: (int*) premioX
6: (int*) premioY
*/
void constroiFase(JOGO_T *jogo, int fase){
     int i;
     FILE *f = NULL;
     char caminho[13] = "";
     char str_fase[2] = "";

     itoa(fase, str_fase, 10);     
     strcat(caminho, "fases/");
     strcat(caminho, str_fase);
     strcat(caminho, ".conf");

     f = abreArquivo(caminho, "r");
     
     fscanf(f, "%d", &jogo->fase.nivel);
     fscanf(f, "%d", &jogo->fase.nParedes);
     fscanf(f, "%d", &jogo->fase.nPremios);
     
     jogo->fase.paredeX = (int*) malloc(jogo->fase.nParedes * sizeof(int));
     jogo->fase.paredeY = (int*) malloc(jogo->fase.nParedes * sizeof(int));
     jogo->fase.premioX = (int*) malloc(jogo->fase.nPremios * sizeof(int));
     jogo->fase.premioY = (int*) malloc(jogo->fase.nPremios * sizeof(int));
     
     for(i = 0; i < jogo->fase.nParedes; i++)
        fscanf(f, "%d", &jogo->fase.paredeX[i]);
        
     for(i = 0; i < jogo->fase.nParedes; i++)
        fscanf(f, "%d", &jogo->fase.paredeY[i]);
        
     for(i = 0; i < jogo->fase.nPremios; i++)
        fscanf(f, "%d", &jogo->fase.premioX[i]);
        
     for(i = 0; i < jogo->fase.nPremios; i++)
        fscanf(f, "%d", &jogo->fase.premioY[i]);
     
     fechaArquivo(f);
}
