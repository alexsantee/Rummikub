#ifndef MAO_H_INCLUDED
#define MAO_H_INCLUDED

typedef struct mao MAO;

struct mao//é uma listab encateada ciclica
{
    int num_jogador;
    CARTA *first;
    MAO *next;
};

MAO *inicia_mao(int nj,CARTA *baralho);//cria a mão incial
void add_carda_mao(MAO *mao,CARTA *baralho);//coloca uma carta na mão

#endif // MAO_H_INCLUDED
