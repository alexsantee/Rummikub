#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "defines.h"
#include "baralho.h"

//passar parte do add_carda_mao para a interface

typedef struct mao MAO;

struct mao//é uma listab encateada ciclica
{
    int num_jogador;
    CARTA *first;
    MAO *next;
};

MAO *inicia_mao(int nj,CARTA *baralho)
{
    int i;
    MAO *mao_incial;
    MAO *mao_atual;


    mao_atual=calloc(1,sizeof(MAO));
    if(mao_atual=NULL)
    {
        printf("Falta memoria!.");
        exit(1);
    }
    mao_atual.num_jogador=0;

    mao_inicial=calloc(1,sizeof(MAO));
    if(mao_inicial=NULL)
        {
            printf("Falta memoria!.");
            exit(1);
        }
    mao_incial=mao_atual;

    for(i=1;i<nj;i++)//identificando o numero do jogador
    {add_carda_mao
        mao_atual.next=calloc(1,sizeof(MAO));
        if(mao_atual.next=NULL)
        {
            printf("Falta memoria!.");
            exit(1);
        }
        *mao_atual.next.num_jogador=i;
        mao_atual=mao_atual.next;
    }

    mao_atual.next=mao_inicial;
    mao_atual=mao_incial;

    for(i=0;i<nj*N_MAO_INICIAL;i++)
    {
        mao_atual.first=sacar_carta(baralho);
        mao_atual.first=mao_atual.first.next;
        mao_atual=mao_atual.next;
    }
    return mao_atual;
}

void add_carda_mao(MAO *mao,CARTA *baralho)
{
    CARTA carta;
    c = mao->first;
    while(carta.next!=NULL)
    {
        carta=carta.next;
    }
    carta.next=sacar_carta(baralho);
    if(carta.next==NULL)
    {
        printf("Sem carta para comprar.\n");
        pause();
        clear();
    }else
        {
        printf("Você comprou a carta ");
        imprime_carta(CARTA carta);
        putchar('\n');
        pause();
        clear();
        }
}

//void remove_carta()
