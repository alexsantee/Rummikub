#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "baralho.h"	//Definição de carta

typedef struct conjunto CONJ;
typedef struct mesa MESA;

MESA *cria_mesa();	//Inicializa a mesa e retorna ponteiro para ela
void insere_na_mesa(CONJ *conj, int pos, MESA *mesa);	//Coloca conj na mesa
void apaga_mesa(MESA *mesa);	//Limpa memória usada pela mesa
CONJ *cria_conjunto();	//Inicializa um conjunto e retorna ponteiro para ele
void insere_no_conjunto(CARTA *c, int pos, CONJ *conj);	//Coloca carta em conj
void apaga_conjunto(int pos, MESA *mesa);	//limpa conj na posição pos da mesa

struct conjunto
{
	CARTA *first;
	CONJ *next;
};

struct mesa
{
	CONJ *first;
};

MESA *cria_mesa()
{
	//Cria uma mesa e retorna ponteiro para ela
	MESA *mesa;
	mesa = calloc(1,sizeof(MESA));
	if(mesa==NULL)
	{
		fprintf(stderr, "Falha ao reservar memória!\n");
		return NULL;
	}
	return mesa;
}

void insere_na_mesa(CONJ *conj, int pos, MESA *mesa)
{
	//Adiciona a carta c na posição pos do conjunto conj

	/*
	 	Pos é numerado conforme o modelo:
		{ [...] [...] [...] [...] [...] }
		 0     1     2     3     4     5
	*/

	if(pos==0)	//início do conjunto
	{
		conj->next = mesa->first;
		mesa->first = conj;
		return;
	}

	CONJ *tmp;
	tmp = mesa->first;
	int i;
	for(i=0;i<pos;i++)	//Para na carta anterior ao espaço
	{
		if(tmp->next==NULL)
		{
			fprintf(stderr, "Posição não existe na mesa!\n");
			return;
		}
		tmp = tmp->next;
	}
	conj->next = tmp->next;
	tmp->next = conj;
}

void apaga_mesa(MESA *mesa)
{
	//Para uso no final do jogo, limpa o lixo
	CONJ *conj;
	CONJ *tmp;
	conj = mesa->first;
	tmp = conj;
	while(conj!=NULL)
	{
		conj = conj->next;
		free(tmp);
		tmp=conj;
	}
	free(mesa);
}

CONJ *cria_conjunto()
{
	//Inicializa uma estrutura de conjunto e retorna ponteiro para ela
	CONJ *conj;
	conj = calloc(1,sizeof(CONJ));
	if(conj==NULL)
	{
		fprintf(stderr, "Falha ao reservar memória!\n");
		return NULL;
	}
	return conj;
}

void insere_no_conjunto(CARTA *c, int pos, CONJ *conj)
{
	//Adiciona a carta c na posição pos do conjunto conj

	/*
	 	A numeração de pos é como na figura:
		[ xx xx xx xx xx ]
		 0  1  2  3  4  5
	*/

	if(pos==0)	//início do conjunto
	{
		c->next = conj->first;
		conj->first = c;
		return;
	}

	CARTA *tmp;
	tmp = conj->first;
	int i;
	for(i=0;i<pos;i++)	//Para na carta anterior ao espaço
	{
		if(tmp->next==NULL)
		{
			fprintf(stderr, "Posição não existe no conjunto!\n");
			return;
		}
		tmp = tmp->next;
	}
	c->next = tmp->next;
	tmp->next = c;
}

void apaga_conjunto(int pos, MESA *mesa)
{
	CONJ *tmp;	//Guarda endereço para ser apagado
	if(pos==0)
	{
		tmp=mesa->first;
		mesa->first=tmp->next;
		free(tmp);
		return;
	}
	CONJ *conj;
	conj = mesa->first;
	int i;
	for(i=0;i<(pos-1);i++)	//Para no conjunto anterior ao apagado
	{
		if(conj->next==NULL)
		{
			fprintf(stderr, "Não existe o conjunto!\n");
		}
		conj=conj->next;
	}
	tmp = conj->next;
	conj->next = conj->next->next;
	free(tmp);
}
