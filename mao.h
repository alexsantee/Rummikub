#ifndef MAO_H_INCLUDED
#define MAO_H_INCLUDED

typedef struct mao MAO;

struct mao//� uma listab encateada ciclica
{
    int num_jogador;
    CARTA *first;
    MAO *next;
};

MAO *inicia_mao(int nj,CARTA *baralho);//cria a m�o incial
void add_carda_mao(MAO *mao,CARTA *baralho);//coloca uma carta na m�o

#endif // MAO_H_INCLUDED
