#ifndef BARALHO_H
#define BARALHO_H

typedef struct carta CARTA;

CARTA *cria_baralho();	//Cria lista com as cartas e retorna ponteiro para ela
void embaralha(CARTA *baralho);	//Embaralha as cartas
void swap(CARTA *a, CARTA *b);	//Troca duas cartas de posição

struct carta
{
	char naipe;
	char n;
	CARTA *next;	//Para encadeamentos na mão e na mesa
};

#endif
