#include <stdlib.h>	//Define ponteiro para NULL e funções aleatórias
#include <time.h>	//Fornece seed para funções aleatórias

#define N_BARALHOS 2	//Numero de baralhos usados
#define N_CORINGAS (2*N_BARALHOS)	//Número de coringas
#define V_CORINGA '*'	//Valor numérico que representa os coringas
#define N_NUM_CARTAS 13	//Números de valores numéricos diferentes
#define N_NAIPES 4	//Quantos naipes existem na próxima lista
#define NAIPES {'!', '@', '#', '$'}	//Naipes utilizados
#define N_CARTAS (N_BARALHOS*N_NUM_CARTAS*N_NAIPES + N_CORINGAS)	//Número total de cartas
#define N_EMB 1000	//Número de trocas durante o embaralhamento

typedef struct carta CARTA;

CARTA *cria_baralho();	//Cria lista com as cartas e retorna ponteiro para ela
void embaralha(CARTA *baralho);	//Embaralha as cartas
void swap(CARTA *a, CARTA *b);	//Troca duas cartas de posição
//CARTA sacar_carta(*baralho);	//Retira carta do topo do baralho

struct carta
{
	char naipe;
	char n;
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

void swap(CARTA *a, CARTA *b)
	//Essa função troca duas cartas de posição
{
	CARTA tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
