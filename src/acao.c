#include "acao.h"

void initAcoesFixas(JOGO_T *jogo){
     int i;
     
     jogo->painel.acoes[0].tipo = ACENDE;
     jogo->painel.acoes[1].tipo = ANDA;
     jogo->painel.acoes[2].tipo = G_HORARIO;
     jogo->painel.acoes[3].tipo = G_ANTIHORARIO;
     
     for(i = 0; i < N_ACOES_FIXAS; i++)
        jogo->painel.acoes[i].funcao = NULL;   
}

void initAcoesAuxiliares(JOGO_T *jogo){
     int i;
     
     //caso das funções: seta tipo e linka as funcoes
     for(i = N_ACOES_FIXAS; i < N_ACOES_FIXAS + N_FUNCOES_AUXILIARES; i++){
        jogo->painel.acoes[i].tipo = FUNCAO;
        jogo->painel.acoes[i].funcao = &jogo->auxiliares[i- (N_ACOES_FIXAS)];
     }
}

void initAcoes(JOGO_T *jogo){
     
     initAcoesFixas(jogo);
     initAcoesAuxiliares(jogo);
}



void alocaImagemAcao(JOGO_T *jogo, int i){
     
     jogo->painel.acoes[i].imagem = create_bitmap(LADO_CELULA + 1, LADO_CELULA + 1);
}

void constroiAcoes(JOGO_T *jogo){
     int i;
     
     jogo->painel.acoes = (ACAO_T*) malloc((N_ACOES_FIXAS + N_FUNCOES_AUXILIARES) * sizeof(ACAO_T));
     
     for(i = 0; i < (N_ACOES_FIXAS + N_FUNCOES_AUXILIARES); i++)
        alocaImagemAcao(jogo, i);
}

void desenhaAcoes(JOGO_T *jogo){
     int i;
     
     jogo->painel.acoes[0].imagem = load_bitmap("images/acoes/acende.bmp", NULL);
     jogo->painel.acoes[1].imagem = load_bitmap("images/acoes/anda.bmp", NULL);
     jogo->painel.acoes[2].imagem = load_bitmap("images/acoes/gira_horario.bmp", NULL);
     jogo->painel.acoes[3].imagem = load_bitmap("images/acoes/gira_antihorario.bmp", NULL);
     jogo->painel.acoes[4].imagem = load_bitmap("images/acoes/f1.bmp", NULL);
     jogo->painel.acoes[5].imagem = load_bitmap("images/acoes/f2.bmp", NULL);
     
     for(i = 0; i < N_ACOES_FIXAS + N_FUNCOES_AUXILIARES; i++)
        draw_sprite(jogo->painel.imagem, jogo->painel.acoes[i].imagem, LADO_CELULA * i + 1, 1);
}
