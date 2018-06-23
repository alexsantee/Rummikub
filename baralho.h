#ifndef BARALHO_H
#define BARALHO_H

typedef struct carta CARTA;

CARTA *cria_baralho();	//Cria lista com as cartas e retorna ponteiro para ela
void embaralha(CARTA *baralho);	//Embaralha as cartas
CARTA *cria_baralho_arq(const char *nome_arquivo);	//Lê baralho de arquivo
CARTA *sacar_carta(CARTA *baralho);	//Retira carta do topo do baralho
void swap(CARTA *a, CARTA *b);	//Troca duas cartas de posição
void imprime_carta(CARTA c);

struct carta
{
	char naipe;
	char n;
	CARTA *next;	//Para encadeamentos na mão e na mesa
};

#endif
