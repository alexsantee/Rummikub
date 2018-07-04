#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "defines.h"
#include "baralho.h"

//passar parte do add_carta_mao para a interface

typedef struct mao MAO;

MAO *inicia_mao(int nj,CARTA *baralho);
MAO *encadeia(MAO *mao);
void add_carta_mao(MAO *mao,CARTA *baralho);
CARTA *remove_carta(int posicao,MAO *mao);

struct mao//É uma lista encadeada ciclica
{
    int num_jogador;//identificar o numero do jogador
    CARTA *first;
    MAO *next;
};

MAO *inicia_mao(int nj,CARTA *baralho)
{
    int i;
    MAO *inicio;
    MAO *mao;

    mao=calloc(1,sizeof(MAO));
    if(mao==NULL)
    {
        printf("Falta memoria!.");
        exit(1);
    }
    inicio=mao;
    for(i=0;i<nj-1;i++)//loop para iniciar o encadeamento
    {
        mao=encadeia(mao);
    }
    mao->next=inicio;
    mao=inicio;
    for(i=0;i<nj;i++)//loop marcando os jogadores
    {
        mao->num_jogador=i;
        mao=mao->next;
    }
    for(i=0;i<N_MAO_INICIAL*nj;i++)//distribuindo as cartas na mão
    {
        add_carta_mao(mao,baralho);
        mao=mao->next;
    }
    return (inicio);
}

MAO *encadeia(MAO *mao)
{
    MAO *nova_mao;
    nova_mao=calloc(1,sizeof(MAO));
    if(nova_mao==NULL)
    {
        printf("Falha na encadeação!");
        exit(1);
    }else{
        mao->next=nova_mao;
    }
    return (nova_mao);
}


void add_carta_mao(MAO *mao,CARTA *baralho)
{
    CARTA *nova;
    nova = sacar_carta(baralho);
    if(nova==NULL)
    {
        printf("Não tem mais carta no baralho.");
        return;
    }

    if(mao->first==NULL)
    {
        mao->first=nova;
        return;
    }

    CARTA *carta;
    carta=mao->first;
    while(carta->next!=NULL)
    {
        carta=carta->next;
    }
    carta->next=nova;
    
    printf("A carta comprada foi: ");
	imprime_carta(*carta);
    printf("\n");
}


CARTA *remove_carta(int posicao,MAO *mao)//começa na posisão 0 e verificar antes se a posão é válida
{
    CARTA *copia;

    if(posicao==0)
    {
        copia=mao->first;
        mao->first=copia->next;
    }else{
		int i;
		CARTA *atual;
		atual = mao->first;
        for(i=1;i<posicao;i++)  //Para uma carta antes
        {
            atual=atual->next;
        }
        copia=atual->next;
        atual->next=copia->next;
    }
    copia->next = NULL;
    return copia;
}
