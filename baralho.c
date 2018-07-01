#include <stdlib.h>	//Define ponteiro para NULL e funções aleatórias
#include <stdio.h>	//Para comandos de arquivo e saída de erros
#include <time.h>	//Fornece seed para funções aleatórias

#include "defines.h"

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
	int da_mesa;	//Flag para que o jogador não pegue carta da mesa para si
	CARTA *next;	//Para encadeamentos na mão e na mesa
};

CARTA *cria_baralho()
	//Essa função coloca as cartas na lista baralho
{
	CARTA *baralho;
	baralho = calloc(N_CARTAS, sizeof(CARTA));
	
	char naipes[N_NAIPES] = NAIPES;	//lista com os naipes
	int i;
	int j;
	int k;
	int i_carta;	//Índice da carta na lista

	for(i=0;i<N_BARALHOS;i++)	//Para cada baralho
	{
		for(j=0;j<N_NAIPES;j++)	//Para cada naipe
		{
			for(k = 0; k < N_NUM_CARTAS; k++)	//Para cada número
				{
					i_carta =
					N_NAIPES*N_NUM_CARTAS*i+
					N_NUM_CARTAS*j+
					k;

					//Escreve número na carta
					if (k<9){baralho[i_carta].n = '1'+k;}
					else {baralho[i_carta].n = 'A'+(k-9);}

					//Adiciona naipe
					baralho[i_carta].naipe = naipes[j];

					//Inicializa next
					baralho[i_carta].next = NULL;
				}
		}
	}
	for(i=1; i<= N_CORINGAS; i++)
	{
		baralho[i_carta+i].n = V_CORINGA;
		baralho[i_carta+i].next = NULL;
		baralho[i_carta+i].naipe = V_CORINGA;
	}
	return baralho;
}

void embaralha(CARTA *baralho)
	//Essa função embaralha as cartas
{
	srand(time(NULL));
	int i;
	int a,b;
	for (i=0; i < N_EMB ; i++)
	{
		a = rand()%N_CARTAS;
		b = rand()%N_CARTAS;
		swap(&(baralho[a]), &(baralho[b]));
	}
}

CARTA *cria_baralho_arq(const char *nome_arquivo)
{
	//Essa função lê um baralho de um arquivo e retorna como lista.
	//Retorna NULL caso exista problema.

	FILE *fp;
	fp = fopen(nome_arquivo, "rt");
	if(fp==NULL)
	{
		fprintf(stderr, "Falha ao abrir arquivo!\n");
		return NULL;
	}

	//Conta número de cartas que o arquivo define
	int n_cartas = 0;
	int c;
	while(!feof(fp))
	{
		if ( (c=getc(fp)) == '\n'){n_cartas++;}
	}
	if(n_cartas!=N_CARTAS)
	{
		fprintf(stderr, "Número inválido de cartas!\n");
		return NULL;
	}
	fseek(fp, 0, SEEK_SET);

	//Lê as cartas
	CARTA *baralho;
	baralho = calloc(n_cartas, sizeof(CARTA));
	if (baralho==NULL)
	{
		fprintf(stderr, "Memória cheia!\n");
		return NULL;
	}
	
	int i;
	for (i=0; i<n_cartas && !feof(fp); i++)
	{
		c = getc(fp);
		baralho[i].naipe = c;
		c = getc(fp);
		baralho[i].n = c;
		c = getc(fp);
		if(c!='\n')
		{
			fprintf(stderr, "Arquivo fora do formato!\n");
			free(baralho);
			return NULL;
		}
	}
	if(feof(fp))
	{
		fprintf(stderr, "Arquivo fora do formato!\n");
		free(baralho);
		return NULL;
	}
	fclose(fp);
	return baralho;
}

CARTA *sacar_carta(CARTA *baralho)
{
	//Essa função recebe um baralho e retorna ponteiro para a última carta
	//não usada.
	//Retorna NULL caso o baralho tenha acabado.
	
	static int last = 0;
	if(last<N_CARTAS)
	{
		return &(baralho[last++]);
	}
	else{return NULL;}
	
}

void swap(CARTA *a, CARTA *b)
	//Essa função troca duas cartas de posição
{
	CARTA tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void imprime_carta(CARTA c)
{
	printf("%c%c", c.naipe, c.n);
}
