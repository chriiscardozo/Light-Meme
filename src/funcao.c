#include "funcao.h"

void initFuncao(FUNCAO_T *funcao, int x, int y, int n_pos){
     int i;
     
     funcao->x = x;
     funcao->y = y;
     funcao->n_pos = n_pos;
     for(i = 0; i < n_pos; i++)
        funcao->acoes[i] = NULL;
}

void initFuncoesAuxiliares(JOGO_T *jogo){
     int i;
     
     for(i = 0; i < N_FUNCOES_AUXILIARES; i++){
        int y = Y_FUNCAO + i*((LADO_CELULA * (N_ACOES_AUXILIARES/4)) + 10);
        initFuncao(&jogo->auxiliares[i], X_FUNCAO, y, N_ACOES_AUXILIARES);
     }
}

void initFuncoes(JOGO_T *jogo){
     //Função main
     initFuncao(&jogo->main, X_MAIN, Y_MAIN, N_ACOES_MAIN);
     //Funções auxiliares
     initFuncoesAuxiliares(jogo);
}

void constroiFuncao(FUNCAO_T *funcao, int n_pos){
     int n_linhas = n_pos / 4; //4 ações por linha
     int i;
     
     funcao->imagem = create_bitmap( 4 * LADO_CELULA + 1,
                                     n_linhas * LADO_CELULA + 1);
     
     funcao->acoes = (ACAO_T**) malloc(n_pos * sizeof(ACAO_T*));     
     for(i = 0; i < n_pos; i++)
        funcao->acoes[i] = NULL;
}

void constroiFuncoesAuxiliares(JOGO_T *jogo){
     int i;
     
     jogo->auxiliares = (FUNCAO_T*) malloc(N_FUNCOES_AUXILIARES * sizeof(FUNCAO_T));
     
     for(i = 0; i < N_FUNCOES_AUXILIARES; i++)
        constroiFuncao(&jogo->auxiliares[i], N_ACOES_AUXILIARES);
}

void constroiFuncoes(JOGO_T *jogo){
     //Função main
     constroiFuncao(&jogo->main, N_ACOES_MAIN);
     //Funções auxiliares
     constroiFuncoesAuxiliares(jogo);
}

void printaFuncoes(JOGO_T *jogo){
     int i;
     //Função main
     draw_sprite( jogo->bmpbuffer, jogo->main.imagem,
                  jogo->main.x , jogo->main.y);
                 
     //Funções auxliares
     for(i = 0; i < N_FUNCOES_AUXILIARES; i++)
        draw_sprite( jogo->bmpbuffer, jogo->auxiliares[i].imagem,
                     jogo->auxiliares[i].x , jogo->auxiliares[i].y);
}

void desenhaFuncoes(JOGO_T *jogo){
     int n_linhas;
     int i;
     //Função main
     n_linhas = N_ACOES_MAIN / 4;
     jogo->main.imagem = create_bitmap( 4 * LADO_CELULA + 1,
										n_linhas * LADO_CELULA + 1);
     desenhaTabela(jogo->main.imagem, n_linhas, 4);
     
     //Funções auxiliares
     n_linhas = N_ACOES_AUXILIARES / 4;
     for(i = 0; i < N_FUNCOES_AUXILIARES; i++){
        jogo->auxiliares[i].imagem = create_bitmap( 4 * LADO_CELULA + 1,
										            n_linhas * LADO_CELULA + 1);
        desenhaTabela( jogo->auxiliares[i].imagem, n_linhas, 4);
     }
     
}

int executaFuncao(JOGO_T *jogo, FUNCAO_T *funcao, int n_acoes, int *startStop){
     int i;
     
     for(i = 0; i < n_acoes; i++){
        if(mouse_b & 1){
           if(mouseClickBotao(jogo)){
              stop(jogo, startStop);
              return 1;
              }
        }
        
        if(funcao->acoes[i]){
            atualizaTela(jogo);
            switch(funcao->acoes[i]->tipo){
                   
                case ACENDE:
                     if(acende(jogo)) return 1; break;
                case ANDA: anda(jogo); break;
                case G_HORARIO: giraHorario(jogo); break;
                case G_ANTIHORARIO: giraAntiHorario(jogo); break;
                case FUNCAO:
                     if(executaFuncao(jogo, funcao->acoes[i]->funcao, N_ACOES_AUXILIARES, startStop)){
                        return 1;
                     }
            }
            aguarda(jogo, 50);
        }
     }
     
     if(funcao->n_pos == N_ACOES_MAIN){
        stop(jogo, startStop);
     }
     return 0;
}
