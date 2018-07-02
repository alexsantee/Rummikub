#ifndef DEFINES_H
#define DEFINES_H
//utilizado para poder utilizar os valores de defeines entre os varios arquivos

//defines do main

#define LEN_NOME_ARQ 60//tamanho da string do nome do arquivo
#define MAX_JOGADORES '5'//numero maximo de jogadores{1-9},COLOCAR EM CARCTER
#define NUM_CARTAS 14	//????????????????????????????????????????????????????
#define NUM_CARTAS_MESA 10	//????????????????????????????????????????????????

//defines do baralho

#define N_BARALHOS 2	//Numero de baralhos usados
#define N_CORINGAS (2*N_BARALHOS)	//Número de coringas
#define V_CORINGA '*'	//Valor numérico que representa os coringas
#define N_NUM_CARTAS 13	//Números de valores numéricos diferentes
#define N_NAIPES 4	//Quantos naipes existem na próxima lista
#define NAIPES {'!', '@', '#', '$'}	//Naipes utilizados
#define N_CARTAS (N_BARALHOS*N_NUM_CARTAS*N_NAIPES + N_CORINGAS)	//Número total de cartas
#define N_EMB 1000	//Número de trocas durante o embaralhamento

//defines da mesa
#define MAX_CONJ 13	//Número máximo de cartas em um conjunto
#define MIN_CONJ  3	//Número mínimo de cartas em um conjunto

//defines da mao
#define N_MAO_INICIAL 14	//numero de cartas na mão inicial

#endif
