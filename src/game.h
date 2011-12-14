#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include "define.h"


//Definições extras
typedef enum 	_TipoCelula {VAZIA, OCUPADA, PAREDE, PREMIO}                   TIPOCELULA_T ;
typedef enum	_Direcao	{NORTE, LESTE, SUL, OESTE} 			               DIRECAO_T;
typedef enum 	_Acoes		{ACENDE, ANDA, G_HORARIO, G_ANTIHORARIO, FUNCAO}   ACOES_T;
typedef enum    _TipoBotao  {RESET = 1, START = 2}                             TIPOBOTAO_T;

//Tipos definidos
typedef struct _Jogo 		JOGO_T;
typedef struct _Tabuleiro 	TABULEIRO_T;
typedef struct _Funcao      FUNCAO_T;
typedef struct _Acao        ACAO_T;
typedef struct _Celula      CELULA_T;
typedef struct _Robo 		ROBO_T;
typedef struct _Painel      PAINEL_T;
typedef struct _Botao       BOTAO_T;
typedef struct _Fase        FASE_T;

//Estruturas
struct _Celula{
	       int cor;
           TIPOCELULA_T valor;
};

struct _Robo{
           BITMAP *img[4];
           int x;
           int y;
           int direcao;
};

struct _Tabuleiro{
	BITMAP *imagem;
	int n_celulas_x;
	int n_celulas_y;
	int n_celulas; //Apenas para enxugar o código!
	int lado_celula;
	int bmpx0;
	int bmpy0;
	CELULA_T **celula;
};

struct _Acao{
    BITMAP *imagem;
    ACOES_T tipo;
    FUNCAO_T *funcao;
};

struct _Funcao{
    BITMAP *imagem;
    int x;
    int y;
    int n_pos;
    ACAO_T **acoes;
};

struct _Painel{
    BITMAP *imagem;
    int x;
    int y;
    ACAO_T *acoes; //Reutilização da struct _Acao como atributo do _Painel
};

struct _Botao{
    BITMAP *imagem[2];
    int x;
    int y;
};

struct _Fase{
    int nivel;
    int nParedes;
    int nPremios;
    int *paredeX, *paredeY;
    int *premioX, *premioY;
};

struct _Jogo{
	BITMAP *bmpbuffer, *background;
    PAINEL_T painel;
	TABULEIRO_T tabuleiro;
	ROBO_T robo;
	FUNCAO_T main;
	FUNCAO_T *auxiliares;
	FASE_T fase;
	ACAO_T *dragTemp;
	BOTAO_T botoes[2];
	int faseAtual;
	int qtdPremios;
};


//Protótipos das funções
void init();
void deinit();

void initJogo(JOGO_T *jogo);
void novoJogo(JOGO_T *jogo);

void atualizaTela(JOGO_T *jogo);
void splashInicial(JOGO_T *jogo);

int dragSobreArea(JOGO_T *jogo, int x, int y, int *indiceImagem);
void dropSobreArea(JOGO_T *jogo, int x, int y, int indiceImagem);

void anda(JOGO_T *jogo);
void giraAntiHorario(JOGO_T *jogo);
void giraHorario(JOGO_T *jogo);
int acende(JOGO_T *jogo);

void mouseClickEsquerdo(JOGO_T *jogo, int *grab, int *draggedImage);
void stop(JOGO_T *jogo, int *startStop);
void mouseClickDireito(JOGO_T *jogo);
