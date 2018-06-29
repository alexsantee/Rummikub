/*
------------------------------------------------------------------------------
    A função não verifica os coringas!!!
------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct conjunto CONJ;
typedef struct carta CARTA;

struct conjunto
{
	CARTA *first;
	CONJ *next;
};

struct carta
{
char naipe;
char n;
CARTA *next;
};

int checagrupo(CONJ* conj){
    //recebe um ponteiro para o grupo ORDENADO e
    //retorna 0 (grupo invalido) ou 1(grupo valido)

    int i=0;//contador
	CARTA* c;
	c=conj->first;

    if(c->n==c->next->n)    //Caso números iguais de naipes diferentes
    {
        while(c->next!=NULL)
        {
            if(c->n==c->next->n)
            {
                c=c->next;
                i++;
            }
            else
            {
               return 0;
            }
        }

        if(i<2)    //Número insuficiente de cartas
        {
            return 0;
        }
    }

    else    //Caso sequência numérica
    {
        while(c->next!=NULL)
        {
            if( (c->naipe==c->next->naipe) && ( (c->n)+1==c->next->n ) )
            {//mesmo naipe em ambos e valor do primeiro ser um antes do segundo(1  2,2 3)
                    c=c->next;
            }
            else
            {
                return 0;
            }
        }

        if(i<2)    //Número insuficiente de cartas
        {
            return 0;
        }
    }

	return 1;

}
