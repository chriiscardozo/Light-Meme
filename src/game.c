#include "game.h"

void init(){
	int depth, res;
	allegro_init();
	
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, HEIGHT, WIDTH, 0, 0);
	
	if (res != 0){
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();

	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	
	show_os_cursor(MOUSE_CURSOR_ARROW);
	select_mouse_cursor(MOUSE_CURSOR_ARROW);
}

void deinit(){
	clear_keybuf();
	allegro_exit();
}

void constroiJogo(JOGO_T *jogo){
    
    /*
       Define as propriedades gerais do jogo
    
       FILE *fconfig = NULL;
	   if (!(fconfig = fopen("lightmeme.conf","r"))) exit(-1);
	*/
    
	jogo->bmpbuffer = create_bitmap(HEIGHT, WIDTH);
	jogo->background = create_bitmap(HEIGHT, WIDTH);
	
	constroiTabuleiro(jogo);
    constroiRobo(jogo);
	constroiFuncoes(jogo);
    constroiPainel(jogo);
    constroiBotoes(jogo);
    constroiFase(jogo, 1);
}

void atualizaTela(JOGO_T *jogo){
    draw_sprite(screen, jogo->bmpbuffer, 0, 0);
}

void splashInicial(JOGO_T *jogo){
	BITMAP *splash = create_bitmap(HEIGHT, WIDTH);

	splash = load_bitmap("images/splash/splash.bmp",NULL);
	draw_sprite(jogo->bmpbuffer, splash, 0, 0);
	atualizaTela(jogo);
	free(splash);
}

void initJogo(JOGO_T *jogo){

	jogo->background = load_bitmap("images/background/background.bmp",NULL);
	jogo->dragTemp = NULL;
	
	jogo->faseAtual = 1;
	
	draw_sprite(jogo->bmpbuffer, jogo->background, 0, 0 );
	
	initTabuleiro(jogo);
    initRobo(jogo);
	initFuncoes(jogo);
    initPainel(jogo);
    initBotoes(jogo);
}

void printaJogo(JOGO_T *jogo){
     printaTabuleiro(jogo);     
     printaRobo(jogo);
     printaFuncoes(jogo);
     printaPainel(jogo);
     printaBotoes(jogo);
}

void desenhaJogo(JOGO_T *jogo){
     desenhaTabuleiro(jogo); 
     desenhaRobo(jogo);
     desenhaFuncoes(jogo);
     desenhaPainel(jogo);
     desenhaBotoes(jogo);
}

void novoJogo(JOGO_T *jogo){

     constroiJogo(jogo);
     initJogo(jogo);
   
//   splashInicial(jogo);

     desenhaJogo(jogo);
     printaJogo(jogo);
     allegro_message("Fase %d ! Challange Accepted", jogo->faseAtual);
}

void giraHorario(JOGO_T *jogo){
     
     pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
     jogo->robo.direcao = (jogo->robo.direcao + 3) % 4;

     printaRobo(jogo);
}

void giraAntiHorario(JOGO_T *jogo){
     
     pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
     jogo->robo.direcao = (jogo->robo.direcao + 1) % 4;

     printaRobo(jogo);
}

int podeAndar(JOGO_T *jogo, int dX, int dY){
    int nX = jogo->robo.x + dX;
    int nY = jogo->robo.y + dY;

    if( (nX >= 0 && nX < jogo->tabuleiro.n_celulas_x) && (nY >= 0 && nY < jogo->tabuleiro.n_celulas_y) &&
        (jogo->tabuleiro.celula[nY][nX].valor != PAREDE))
        return 1;
    
    else return 0;
    
}

void anda(JOGO_T *jogo){
     
     switch (jogo->robo.direcao){
            case NORTE:
               if(podeAndar(jogo, 0, -1)){
                  pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
                  jogo->robo.y -= 1;
               }
               break;
            case LESTE:
               if(podeAndar(jogo, -1, 0)){
                  pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
                  jogo->robo.x -= 1;
               }
               break;
            case SUL:
               if(podeAndar(jogo, 0, 1)){
                  pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
                  jogo->robo.y += 1;
               }
               break;
            case OESTE:
               if(podeAndar(jogo, 1, 0)){
                  pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
                  jogo->robo.x += 1;
               }
               break;
            default:
               allegro_message("Erro fatal! *trollface*");
               exit(1);
     }

     printaRobo(jogo);
}

int acende(JOGO_T *jogo){
     int xAtual = jogo->robo.x;
     int yAtual = jogo->robo.y;
     int acertou = 0;
     BITMAP *meme;
     
     aguarda(jogo, 50);
     pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
     atualizaTela(jogo);
     meme = create_bitmap(LADO_CELULA, LADO_CELULA);
     
     if(jogo->tabuleiro.celula[xAtual][yAtual].valor == PREMIO){
        meme = load_bitmap("images/robo/acende_success.bmp", NULL);
        acertou = 1;
     }
     
     else
        meme = load_bitmap("images/robo/acende_fail.bmp", NULL);
     
     draw_sprite(jogo->tabuleiro.imagem, meme, jogo->robo.x * LADO_CELULA, jogo->robo.y * LADO_CELULA);
     printaTabuleiro(jogo);
     atualizaTela(jogo);
     if(acertou) allegro_message("EPIC WIN!");
     else aguarda(jogo, 150);
     pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
     printaRobo(jogo);
     
     return acertou;
}

int dragSobreArea(JOGO_T *jogo, int x, int y, int* aux){
   int i;
   
   //Drag no Painel
   for (i = 0; i < N_ACOES_FIXAS + N_FUNCOES_AUXILIARES; i++ ){
       if( x > jogo->painel.x + (LADO_CELULA * i) &&
           x < jogo->painel.x + LADO_CELULA + ( i * LADO_CELULA) && 
           y > jogo->painel.y  && y < jogo->painel.y + (LADO_CELULA ) +1) {
              jogo->dragTemp = &jogo->painel.acoes[i];
              set_mouse_sprite(jogo->painel.acoes[i].imagem);
              *aux = i;
              return 1;//mouseSobrePainel(jogo, x, y)
       }
   }
   
   return 0;
}

void dropSobreArea(JOGO_T *jogo, int x, int y, int indiceImagem){
     int h, i, j;
     
     //Drop na função Main
     for (i = 0; i < 4; i++ ){
         for (j = 0; j < jogo->main.n_pos/4; j++){
             if(x > jogo->main.x + (LADO_CELULA * i) &&
			 x < jogo->main.x + LADO_CELULA + (LADO_CELULA * i )&&
			 y > jogo->main.y + (LADO_CELULA * j) &&
			 y < jogo->main.y + LADO_CELULA+(LADO_CELULA * j) ){
			   	 
                 jogo->main.acoes[4 * j + i] = jogo->dragTemp;
                 position_mouse(mouse_x + LADO_CELULA, mouse_y + LADO_CELULA);
                 draw_sprite(jogo->main.imagem, jogo->painel.acoes[indiceImagem].imagem, (LADO_CELULA* i)+1, (LADO_CELULA*j)+1);
			   	 draw_sprite(jogo->bmpbuffer, jogo->main.imagem, jogo->main.x, jogo->main.y);
			   	 draw_sprite(screen, jogo->bmpbuffer, 0, 0);
			   	 position_mouse(mouse_x - LADO_CELULA, mouse_y - LADO_CELULA);
				 return ;
             }
             
         }
     }
     
     //Drop nas funções auxiliares
     for(h = 0; h < N_FUNCOES_AUXILIARES; h++){
         for (i = 0; i < 4; i++ ){
             for (j = 0; j < jogo->auxiliares[h].n_pos/4; j++){
                 if(x > jogo->auxiliares[h].x + (LADO_CELULA * i) &&
    			 x < jogo->auxiliares[h].x + LADO_CELULA + (LADO_CELULA * i )&&
    			 y > jogo->auxiliares[h].y + (LADO_CELULA * j) &&
    			 y < jogo->auxiliares[h].y + LADO_CELULA+(LADO_CELULA * j) ){
    			   	 
                     jogo->auxiliares[h].acoes[4 * j + i] = jogo->dragTemp;
                     position_mouse(mouse_x + LADO_CELULA, mouse_y + LADO_CELULA);
    	             show_mouse(jogo->bmpbuffer);
                     draw_sprite(jogo->auxiliares[h].imagem, jogo->painel.acoes[indiceImagem].imagem, (LADO_CELULA* i)+1, (LADO_CELULA*j)+1);
    			   	 draw_sprite(jogo->bmpbuffer, jogo->auxiliares[h].imagem, jogo->auxiliares[h].x, jogo->auxiliares[h].y);
    			   	 draw_sprite(screen, jogo->bmpbuffer, 0, 0);
    			   	 position_mouse(mouse_x - LADO_CELULA, mouse_y - LADO_CELULA);
    				 return ;
                 }
                 
             }
         }
     }
}

void stop(JOGO_T *jogo, int *startStop){
     position_mouse(mouse_x + TAMANHO_X_BOTAO, mouse_y + TAMANHO_X_BOTAO);
     printaBotao(jogo, &jogo->botoes[1], 0 );
     position_mouse(mouse_x - TAMANHO_X_BOTAO, mouse_y - TAMANHO_X_BOTAO);
     *startStop = 0;
     pintaCelulaTabuleiro(jogo, jogo->robo.x, jogo->robo.y);
     initRobo(jogo);
     desenhaRobo(jogo);
     printaRobo(jogo);
}

void reset(JOGO_T *jogo){
     initJogo(jogo);
     desenhaJogo(jogo);
     printaJogo(jogo);
}

void start(JOGO_T *jogo, int *startStop){
     position_mouse(mouse_x + TAMANHO_X_BOTAO, mouse_y + TAMANHO_X_BOTAO);
     printaBotao(jogo, &jogo->botoes[1], 1);
     position_mouse(mouse_x - TAMANHO_X_BOTAO, mouse_y - TAMANHO_X_BOTAO);
     *startStop = 1;
     executaFuncao(jogo, &jogo->main, N_ACOES_MAIN, startStop);
}

int mouseClickBotao(JOGO_T *jogo){
     static int mx = 0, my = 0, startStop = 0; //Atual 0 = start ; Atual 1 = stop
     int x = mouse_x, y = mouse_y;
     
     if(mx != x && my != y){
        mx = mouse_x;
        my = mouse_y;

        //Botao Reset
        if((x >= jogo->botoes[0].x && x <= jogo->botoes[0].x + TAMANHO_X_BOTAO) &&
           (y >= jogo->botoes[0].y && y <= jogo->botoes[0].y + TAMANHO_Y_BOTAO)){
               reset(jogo);
        }
        
        //Botao Start/Stop
        else if((x >= jogo->botoes[1].x && x <= jogo->botoes[1].x + TAMANHO_X_BOTAO) &&
                (y >= jogo->botoes[1].y && y <= jogo->botoes[1].y + TAMANHO_Y_BOTAO)){
               if(!startStop){
                  start(jogo, &startStop);
               }
               else{
                  stop(jogo, &startStop);
                  return 1;
               }
        }
     }
     return 0;
}

void mouseClickEsquerdo(JOGO_T *jogo, int *grab, int *draggedImage){
     if(!(*grab)){
        int x = mouse_x,
            y = mouse_y;
        
        show_mouse(jogo->bmpbuffer);
        if(dragSobreArea(jogo, x, y, draggedImage)){
           select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);
           *grab = 1;
        }
        
        else mouseClickBotao(jogo);
     }
        
}

void mouseClickDireito(JOGO_T *jogo){
     int h, i, j;
     int x = mouse_x;
     int y = mouse_y;
     
     //allegro_message("Clicou com direito\nx = %d | y = %d", mouse_x, mouse_y);
     //Apagar ação na Main
     for (i = 0; i < 4; i++ ){
         for (j = 0; j < jogo->main.n_pos/4; j++){
             if(x > jogo->main.x + (LADO_CELULA * i) &&
			 x < jogo->main.x + LADO_CELULA + (LADO_CELULA * i )&&
			 y > jogo->main.y + (LADO_CELULA * j) &&
			 y < jogo->main.y + LADO_CELULA+(LADO_CELULA * j) ){
                 
                 jogo->main.acoes[4 * j + i] = NULL;
                 position_mouse(mouse_x + LADO_CELULA, mouse_y + LADO_CELULA);
                 rectfill( jogo->main.imagem, (LADO_CELULA * i) + 1, (LADO_CELULA * j) + 1,
                           LADO_CELULA + (LADO_CELULA * i ) - 1,
                           LADO_CELULA + (LADO_CELULA * j ) - 1, makecol(255, 255, 255));
			   	 draw_sprite(jogo->bmpbuffer, jogo->main.imagem, jogo->main.x, jogo->main.y);
			   	 draw_sprite(screen, jogo->bmpbuffer, 0, 0);
                 position_mouse(mouse_x - LADO_CELULA, mouse_y - LADO_CELULA);
				 return ;
             }
             
         }
     }
     
     //Apagar ação nas funções auxiliares
     for(h = 0; h < N_FUNCOES_AUXILIARES; h++){
         for (i = 0; i < 4; i++ ){
             for (j = 0; j < jogo->auxiliares[h].n_pos/4; j++){
                 if(x > jogo->auxiliares[h].x + (LADO_CELULA * i) &&
    			 x < jogo->auxiliares[h].x + LADO_CELULA + (LADO_CELULA * i )&&
    			 y > jogo->auxiliares[h].y + (LADO_CELULA * j) &&
    			 y < jogo->auxiliares[h].y + LADO_CELULA+(LADO_CELULA * j) ){
    			   	 
                     jogo->auxiliares[h].acoes[4 * j + i] = NULL;
                     position_mouse(mouse_x + LADO_CELULA, mouse_y + LADO_CELULA);
                     rectfill( jogo->auxiliares[h].imagem, (LADO_CELULA * i) + 1, (LADO_CELULA * j) + 1,
                           LADO_CELULA + (LADO_CELULA * i ) - 1,
                           LADO_CELULA + (LADO_CELULA * j ) - 1, makecol(255, 255, 255));
                     draw_sprite(jogo->bmpbuffer, jogo->auxiliares[h].imagem, jogo->auxiliares[h].x, jogo->auxiliares[h].y);
			   	     draw_sprite(screen, jogo->bmpbuffer, 0, 0);
                     position_mouse(mouse_x - LADO_CELULA, mouse_y - LADO_CELULA);
				     return ;
                 }
                 
             }
         }
     }
}
