#ifndef MESA_H
#define MESA_H

typedef struct conjunto CONJ;
typedef struct mesa MESA;

MESA *cria_mesa();	//Inicializa a mesa e retorna ponteiro para ela
void insere_na_mesa(CONJ *conj, int pos, MESA *mesa);	//Coloca conj na mesa
void apaga_mesa(MESA *mesa);	//Limpa memória usada pela mesa
CONJ *cria_conjunto();	//Inicializa um conjunto e retorna ponteiro para ele
void insere_no_conjunto(CARTA *c, int pos, CONJ *conj);	//Coloca carta em conj
void apaga_conjunto(int pos, MESA *mesa);	//limpa conj na posição pos da mesa

struct conjunto
{
	CARTA *first;
	CONJ *next;
};

struct mesa
{
	CONJ *first;
};

#endif
