#include <stdlib.h>	//Faz callocs e define NULL
#include <stdio.h>	//Imprime erros

#include "defines.h"
#include "baralho.h"

//passar parte do add_carta_mao para a interface

typedef struct mao MAO;

MAO *inicia_mao(int nj,CARTA *baralho);
MAO *encadeia(MAO *mao);
void add_carta_mao(MAO *mao,CARTA *baralho);
void remove_carta(int posicao,MAO *mao);

struct mao//Ã© uma lista encadeada ciclica
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
        mao->first=NULL;
        mao=mao->next;
    }
    for(i=0;i<N_MAO_INICIAL*nj;i++)//distribuindo as cartas na mÃo
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
        printf("Falha na encadeaÃ§Ã£o!");
        exit(0);
    }else{
        mao->next=nova_mao;
        nova_mao->next=NULL;
    }
    return (nova_mao);
}


void add_carta_mao(MAO *mao,CARTA *baralho)
{
    CARTA *carta;
    carta=mao->first;
    while(carta!=NULL)
    {
        carta=carta->next;
    }
    carta=sacar_carta(baralho);
    if(carta==NULL)
    {
        printf("NÃ£o tem mais carta no baralho.");
    }else{
        carta->next=NULL;
        printf("A carta comprada foi: ");
		imprime_carta(*carta);
		printf("\n");
    }
}


void remove_carta(int posicao,MAO *mao)//começa na posição 0 e verificar antes se a posição é válida
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
        for(i=1;i<posicao;i++)
        {
            atual=atual->next;
        }
        copia=atual->next;
        atual->next=copia->next;
    }
    free(copia);
}
