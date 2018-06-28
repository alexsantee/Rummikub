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
int checagrupo(CONJ* d){//recebe um pontero para o grupo ORDENADO e retorna 0 (grupo invalido) ou 1(grupo valido)
    int c=0;//contador
	CARTA* a;
	a=d->first;
    if(a->n==a->next->n)
        {

        while(a->next!=NULL)
        {

            if(a->n==a->next->n&&c<4)
            {
                a=a->next;
                c++;
            }
            else
            {
            return 0;
            }
        }
    if(0!=c&&c!=2){
        return 0;
    }


    }
    else{//checa sequencias
        while(a->next!=NULL)
            {
        if((a->naipe==a->next->naipe)&&((a->n)+1==a->next->n))
        {//mesmo naipe em ambos e valor do primeiro ser um antes do segundo(1  2,2 3)
                a=a->next;
        }
        else
        {
            return 0;
        }
        }
    }

return 1;

}
