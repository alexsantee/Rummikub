#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "defines.h"
#include "baralho.h"

typedef struct mao MAO;

struct mao
{
    int num_jogador;
    CARTA *first;
    MAO *next;
};

MAO inicia_mao(MAO *mao,int nj,CARTA *baralho)
{
    int i;
    for(i=0;i<nj;i++)//identificando o numero do jogador
    {
        mao=calloc(1,sizeof(MAO));
        if(mao=NULL)
        {
            printf("Falta memoria!.");
            pause();
            exit(1);
        }
        mao->num_jogador=i;
        mao=mao.next;
    }
    for(i=0;i<nj*N_MAO_INICIAL;i++)
    {
        mao.first=sacar_carta(baralho);
        mao.first=mao.CARTA.next;
        mao=mao.next;
    }
    return
}
