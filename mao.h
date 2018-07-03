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
MAO *encadeia(MAO *mao);//uso interno para o inicia mao
CARTA *remove_carta(int posicao,MAO *mao);//come�a no pisi��o 0 e verificar antes se a posi��o � valida

#endif // MAO_H_INCLUDED
