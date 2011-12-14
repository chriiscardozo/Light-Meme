# Makefile for MD project

CC=gcc
CCflags=-lalleg
LINK=#not used for not conflicting with windows
OBJECTS=#not used for not conflicting with windows


all:
	$(CC) $(CCflags) $(LINK) -o LightMeme acao.c celula.c funcao.c game.c painel.c robo.c tabuleiro.c util.c main.c


clear:
	rm -f main init pos.mol vel.mol thm.mol *~

exec:

	./init
	time ./main
	
# -lz PATH/objects (include objects)     
# mcmodel = large | small | kernel (large stands best exec time)
# mfpmath = sse | sse+387 | see,387 | 387 (instruction set)
# m64 | m32
# mpc32,64,80 : number of bits in floating precision
# march = amdfam10 (local) | native | athlonxp ... (sets all instructions sets)
# fopenmp: multiple processors - check it later
