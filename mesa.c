#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "baralho.h"	//Definição de carta
#include "defines.h"

typedef struct conjunto CONJ;
typedef struct mesa MESA;

MESA *cria_mesa();	//Inicializa a mesa e retorna ponteiro para ela
void insere_na_mesa(CONJ *conj, int pos, MESA *mesa);	//Coloca conj na mesa
void apaga_mesa(MESA *mesa);	//Limpa memória usada pela mesa
CONJ *cria_conjunto();	//Inicializa um conjunto e retorna ponteiro para ele
CONJ *localiza_conjunto(int pos, MESA *mesa);//Recebe posição e retorna o conjunto
void insere_no_conjunto(CARTA *c, int pos, CONJ *conj);	//Coloca carta em conj
CARTA *retira_do_conjunto(int pos, CONJ *conj); //Retira carta do conjunto e retorna-a
void apaga_conjunto(int pos, MESA *mesa);	//limpa conj na posição pos da mesa
int checa_conjunto(CONJ* conj);	//Recebe conjunto e retorna a pontuação dele

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

CONJ *localiza_conjunto(int pos, MESA *mesa)
{   //ESSA FUNÇÃO ESTÁ SUJEITA A SEGFAULT
    CONJ *conj;
    conj = mesa->first;
    int i;
    for(i=0;i<pos;i++)
    {
        conj=conj->next;
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

CARTA *retira_do_conjunto(int pos, CONJ *conj)
{
    //ESSA FUNÇÃO ESTÁ SUJEITA A SEGFAULT-----------------------------------
    CARTA *c;
    c = conj->first;
    if(pos==0)
    {
        conj->first = NULL;
        return c;
    }
    int i;
    for(i=1;i<pos;i++)  //Para na anterior
    {
        c=c->next;
    }
    CARTA *tmp;
    tmp = c->next;
    c->next=tmp->next;
    tmp->next = NULL;
    return tmp;
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

int checa_conjunto(CONJ* conj){
    //recebe um ponteiro para o grupo ORDENADO e
    //retorna a pontuação do conjunto ou 0 caso inválido

	//Flags para o caso sequência de mesmo naipe
    int mesmo_naipe = 1;
    int seq_numerica = 1;

	//Flags para o caso mesmo número com naipes diferentes
	int mesmo_num = 1;
	int naipe_repete = 0;

    char naipe_da_seq = '\0';
    char num_esp_seq = 0;	//Número esperado supondo sequência numérica
	char num_esp_nai = 0;	//Número esperado supondo mesmo naipe
	char naipes_usados[MAX_CONJ];
	int i;
	for(i=0;i<MAX_CONJ;i++){naipes_usados[i]=0;}
    int tam_conj = 0;
	int pontos = 0;
    CARTA *c;
    c = conj->first;

    while(c != NULL)
    {
        //Inicia a sequência mesmo que o conjunto comece por coringas
        if (num_esp_seq == 0 && c->n != V_CORINGA)
        {
            num_esp_seq = c->n;
			num_esp_nai = c->n;
        }

        if (naipe_da_seq == '\0' && c->naipe != V_CORINGA)
        {
            naipe_da_seq = c->naipe;
        }

        if(num_esp_seq != c->n && c->n != V_CORINGA)
        {seq_numerica = 0;}
		if(num_esp_nai != c->n && c->n != V_CORINGA)
        {mesmo_num = 0;}
        if(naipe_da_seq != c->naipe && c->naipe != V_CORINGA)
        {mesmo_naipe = 0;}
		for(i=0;i<MAX_CONJ&&naipes_usados[i]!=0;i++)
		{
			if(c->naipe==naipes_usados[i]){naipe_repete = 1;}
		}

		//Soma carta na pontuação
		if(c->n != V_CORINGA){pontos+=c->n;}	//Caso não coringa
		else if(num_esp_seq != 0){pontos+=num_esp_seq;}	//Coringa no meio
		else	//Coringas no início	//Aproveitar para esp_seq_num----------
		{
			CARTA *tmp;
			tmp = c;
			for(i=1; tmp->n!=V_CORINGA;i++)
			{
				tmp = tmp->next;
			}
			pontos += (tmp->n - i);
		}

		if(num_esp_seq != 0) {num_esp_seq++;}
		naipes_usados[tam_conj] = c->naipe;
        tam_conj++;
        c = c->next;
    }

    if(tam_conj < MIN_CONJ || tam_conj > MAX_CONJ) {return 0;}
    if ( (mesmo_naipe && seq_numerica) || (mesmo_num && !naipe_repete))
		{
			return pontos;
		}
	return 0;
}
