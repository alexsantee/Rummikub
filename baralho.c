#include <stdlib.h>	//Define ponteiro para NULL e funções aleatórias
#include <stdio.h>	//Para comandos de arquivo e saída de erros
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
CARTA *cria_baralho_arq(const char *nome_arquivo);	//Lê baralho de arquivo
CARTA sacar_carta(CARTA *baralho);	//Retira carta do topo do baralho
void swap(CARTA *a, CARTA *b);	//Troca duas cartas de posição


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

CARTA sacar_carta(CARTA *baralho)
{
	//Essa função seleciona a carta no topo do baralho, substitui-a por
	//vazio e retorna seu valor.
	//Retorna CARTA vazio se não houver mais cartas.

	CARTA tmp;
	CARTA vazio;	//Para saber quando a carta foi usada
	vazio.naipe = 0;
	vazio.n = 0;
	int i;
	for (i=0;i<N_CARTAS;i++)
	{
		tmp = baralho[i];
		if(tmp.n!=vazio.n && tmp.naipe!=vazio.naipe)
		{
			baralho[i]=vazio;
			return tmp;
		}
	}
	return vazio;
}

void swap(CARTA *a, CARTA *b)
	//Essa função troca duas cartas de posição
{
	CARTA tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
