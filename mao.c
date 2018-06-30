#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "defines.h"
#include "baralho.h"

//passar parte do add_carta_mao para a interface

typedef struct mao MAO;

struct mao
{
    int num_jogador;
    CARTA *first;
    MAO *next;	//Lista encadeada cíclica
};

MAO *inicia_mao(int nj,CARTA *baralho)
{
    int i;
    MAO *mao_inicial;
    MAO *mao_atual;

    
    mao_inicial = calloc(1,sizeof(MAO)); //alocando memoria, zerando os valores da mao inicial(mao vazia)
    if(mao_inicial==NULL)
    {
        printf("[!]Falta memoria[!]\n");
        pause();
        exit(1);
    }
    mao_inicial->num_jogador=0;
    mao_atual = mao_inicial;

    for(i=1;i<nj;i++)	//identificando o numero do jogador
    {//add_carta_mao???
        mao_atual->next=calloc(1,sizeof(MAO)); //faz com que a mao do proximo jogador esteja alocada, porem zerada(mao vazia)
        if(mao_atual->next==NULL)
        {
            printf("[!]Falta memoria[!]\n");
            pause();
            exit(1);
        }
        mao_atual->next->num_jogador=i;
        mao_atual=mao_atual->next;
    }

    mao_atual->next=mao_inicial;	//Fecha o ciclo da lista encadeada
    mao_atual=mao_inicial;
//--------------------ESSE TRECHO NÃO FUNCIONA-----------------------
    for(i=0;i<(nj*N_MAO_INICIAL);i++)
    {
        mao_atual->first=sacar_carta(baralho);
        mao_atual->first=mao_atual->first->next;
        mao_atual=mao_atual->next;
    }
//-------------------------------------------------------------------
    return mao_atual;
}

void add_carta_mao(MAO *mao,CARTA *baralho)
{
    CARTA *c;
    c = mao->first;
    while(c->next!=NULL)
    {
        c=c->next;
    }
    c->next=sacar_carta(baralho);
	c = c->next;
    if(c->next==NULL)
    {
        printf("[!]Fim do baralho, sem cartas para comprar[!]\n");
        pause();
        clear();
    }else
        {
        printf("Voce comprou a carta ");
        imprime_carta(*c);
        putchar('\n');
        pause();
        clear();
        }
}

//void remove_carta()
