#include <stdio.h>
#include <stdlib.h>

 typedef struct carta CARTA;
  struct carta
    {
	char naipe;
	char n;
	CARTA *next;
    };
int checagrupo(CARTA* a){
    int c//contador
    if(a->n==a->next->n){
    while(a->next,c++){
    if(a->n==a->next->n&&c<5){
        a=a->next;
    }
    else{
        return 0;
    }
    }

    }
    else{
        while(a->next){
        if((a->naipe==a->next->naipe)&&(a->n+1==a->next->n)){//mesmo naipe em ambos e valor do primeiro ser um antes do segundo(1  2,2 3)
                a=a->n;
        }
        else {
            return 0;
        }
        }
    }

return 1;

}

