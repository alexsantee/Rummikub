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
MAO *encadeia(MAO *mao);//uso interno para o inicia mao
CARTA *remove_carta(int posicao,MAO *mao);//começa no pisição 0 e verificar antes se a posição é valida

#endif // MAO_H_INCLUDED
