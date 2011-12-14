#include "game.h"

int main(){
    int grab = 0;
	int draggedImage = 0;
	
    JOGO_T *jogo = NULL;
    jogo = (JOGO_T*) malloc(sizeof(JOGO_T));
    if(!jogo) exit(1);
    
    init();
   	allegro_message("Aperte ESC para sair\nBom jogo!");
    
    novoJogo(jogo);
	while(!key[KEY_ESC]){
	    atualizaTela(jogo);
        
        if(mouse_b & 1){
           mouseClickEsquerdo(jogo, &grab, &draggedImage);
        }
        
        else if(mouse_b & 2){
           mouseClickDireito(jogo);
        }
        
        else if(grab){
           set_mouse_sprite(NULL);
           select_mouse_cursor(MOUSE_CURSOR_ARROW);
		   dropSobreArea(jogo, mouse_x, mouse_y, draggedImage);
           grab = 0;
           jogo->dragTemp = NULL;
        }
	}

	deinit();
	return 0;
}
END_OF_MAIN()

