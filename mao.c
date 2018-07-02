#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "defines.h"
#include "baralho.h"

//passar parte do add_carta_mao para a interface

typedef struct mao MAO;

struct mao//é uma lista encadeada ciclica
{
    int num_jogador;//identificar o numero do jogador
    CARTA *first;
    MAO *next;
};

MAO *inicia_mao(int nj,CARTA *baralho)
{
    int i;
    MAO *mao;
    MAO *inicio;

    mao=calloc(1,sizeof(MAO));
    if(mao_atual==NULL)
    {
        printf("Falta memoria!.");
        exit(1);
    }
    inicio=mao;
    for(i=0;i++;i<nj-1)//loop para iniciar o encadeamento
    {
        mao=encadeia(mao);
    }
    mao->next=inicio;
    mao=incio;
    for(i=0;i++;i<nj)//loop marcando os jogadores
    {
        mao->num_jogadores=i;
        mao->carta=NULL;
        mao=mao->next;
    }
    for(i=0;i++;i<N_MAO_INICIAL-*nj)//distribuindo as cartas na mão
    {
        add_carta_mao(mao,baralho);
        mao=mao->next;
    }
    return (mao);
}

MAO *encadeia(MAO *mao)
{
    MAO *nova_mao;
    nova_mao=calloc(1,sizeof(MAO));
    if(nova_mao==NULL)
    {
        printf("Falha na encadeação!");
        exit(0);
    }else{
        mao->next=nova_mao;
        nova_mao->next=NULL;
    }
    return (nova_mao);
}


void add_carta_mao(MAO *mao,CARTA *baralho)
{
    CARTA carta;
    carta=mao->first;
    while(carta!=NULL)
    {
        carta=carta->next;
    }
    carta=sacar_carta(baralho);
    if(carta==NULL)
    {
        printf("Não tem mais carta no baralho.");
    }else{
        carta->next=NULL;
        printf("A carta comprada foi: ");
		imprime_carta(*carta);
		printf("\n");
    }
    pause();
    clear();
}


void remove_carta(int posicao,MAO *mao)//começa no posição 0 e verificar antes se a posição é valida
{
    CARTA *copia;

    if(posica==0)
    {
        copia=mao->first;
        mao->first=copia->next;
    }else{
        for(i=1;i++;i<posicao)
        {
            mao=mao->next;
        }
        copia=mao->next;
        mao->next=copia->next;
    }
    copia->next=NULL;
    free(copia);
}
