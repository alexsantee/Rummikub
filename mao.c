#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "defines.h"
#include "baralho.h"

//passar parte do add_carda_mao para a interface

typedef struct mao MAO;

struct mao//� uma lista encateada ciclica
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
    for(i=0;i++;i<nj)//loop maracando os jogadores
    {
        mao->num_jogadores=i;
        mao->carta=NULL;
        mao=mao->next;
    }
    for(i=0;i++;i<N_MAO_INICIAL-*nj)//distribuindo as cartas na m�o
    {
        add_carda_mao(mao,baralho);
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
        printf("Falha na encadea��o!");
        exit(0);
    }else{
        mao->next=nova_mao;
        nova_mao->next=NULL;
    }
    return (nova_mao);
}


void add_carda_mao(MAO *mao,CARTA *baralho)
{
    CARTA carta;
    carta=mao->first;
    while(carta!=NULL)
    {
        carta=carta->next;
    }
    carda=sacar_carta(baralho);
    if(carda==NULL)
    {
        printf("N�o tem mais carta no baralho.");
    }else{
        carda->next=NULL;
        printf("A carda comprada foi: ");
		imprime_carta(*carta);
		printf("\n");
    }
    pause();
    clear();
}


void remove_carta(int posicao,MAO *mao)//come�a no pisi��o 0 e verificar antes se a posi��o � valida
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
