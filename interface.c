#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//para colocar a escrita em portugues;

#include "baralho.h"

#define LEN_NOME_ARQ 60//tamanho da string do nome do arquivo
#define MAX_JOGADORES 5
#define NUM_CARTAS 14
#define NUM_CARTAS_MESA 10

void clear();
void pause();
int pegaQuantidade_jogadores();
int jogo(int j);
CARTA tipo_baralho(); // determina o tipo de baralho, ja criando ele
                      // ou pegando ele de algum arquivo que queiramos
CARTA cria_mao_jogador( CARTA *baralho );

int main()
{
    int jogador;//atual jogador
    int nj;//numero de jogadores
    CARTA *baralho;
    CARTA *mao_jogador[MAX_JOGADORES];

    int vitoria=0;//variavel para determinar se alguem ganhou

    setlocale(LC_CTYPE, "Portuguese"); //adapta a linguagem para portugues(acentos)

    baralho= tipo_baralho(baralho); //cria e torna o baralho
    nj = pegaQuantidade_jogadores();
    for(int i = 0; i < nj ; i++)
    {
        mao_jogador[i] = cria_mao_jogador( baralho );
    }

    for(jogador=0;vitoria==0;jogador++,jogador=jogador%nj)
    {
        vitoria=turno(jogador);
        clear();
    }
    printf("O jogador %d foi o vencedor.\n",j+1);
    pause();
    return (0);
}

void clear()
{
	#ifdef WIN32
   		system("CLS");
	#else
        system("clear");
	#endif
}

void pause()
{
	getchar();	//Retira o \n
    char pausa;
    printf("Aperte ENTER para continuar...");
    while( (( pausa=getchar() ) != '\n') && (pausa != '\0'));   //Pula caracteres lixo
	clear();
}

int pegaQuantidade_jogadores()
{
    char resp_inicial;//colocado em char para o programa não quebrar com resposta não numerica;
    int nj;

    printf("Bem-vindo ao Rummikub.\n");
    do{
    printf("Quantos jogadores(1-5):\n");
    scanf(" %c",&resp_inicial);
    clear();
    }while(resp_inicial>'5'||resp_inicial<'1');
         if(resp_inicial=='1'){nj=1;}
    else if(resp_inicial=='2'){nj=2;}
    else if(resp_inicial=='3'){nj=3;}
    else if(resp_inicial=='4'){nj=4;}
    else if(resp_inicial=='5'){nj=5;}

    return (nj);
}

int turno(int j)
{
/*------------
setor do loop do jogo;
atualmente só funcionando para verificar a interface;
falta as funções e as interfaces especificas das funções;
--------------*/
    int v;

    printf("******>>Versão de Teste<<******\n");
    printf("Vitoria do jogador %d ?\n(Aperte 0 se não e qual outro valor se Sim\n",j+1);
    scanf(" %d",&v);

    return (v);
}

CARTA *tipo_baralho(CARTA *baralho)
{
    char resp_baralho;

    do{
    printf("Você deseja usar um baralho aleatorio[1] ou importar um baralho[2]?\n>> ");
    resp_baralho=getc(stdin);
    }while(resp_baralho<'1'||resp_baralho>'2');
    if(resp_baralho=='1')
        {
        baralho = cria_baralho();
        embaralha(baralho);
        printf("Baralho aleatorio criado.\n");
        }
    if(resp_baralho=='2')
        {
        char nome_arquivo[LEN_NOME_ARQ];
        do  {
            printf("Qual o nome do arquivo:(inclua o .txt !)\n>> ");
            fgets(nome_arquivo,LEN_NOME_ARQ,stdin);
            baralho=cria_baralho_arq(nome_arquivo);
            clear();
            }while(baralho!=NULL);
        printf("Baralho lido.\n");
        }
    pause();
    clear();

    return (baralho);
}

CARTA *cria_mao_jogador( CARTA *baralho )
//essa funcao cria a mao do jogador, retornando o ponteiro para ultima carta da mao (?)
//lembre-se: quanto a carta nao existir --> naipe vale 0 e valor vale 0
{      
    CARTA *mao;

    //lancando as cartas do baralho para a mao do usuario
    for(int i = 0; i < NUM_CARTAS; i++){
        //todo comeco de loop aloca memoria para a nova carta
        mao = (CARTA *)malloc(sizeof(CARTA));
        //transpondo os valores da ultima carta do baralho para a mao
        mao->naipe = baralho->naipe;
        mao->valor = baralho->valor;
        //inicializando a proxima carta da mao como sendo nula
        mao->next = NULL;
        //transpondo o proximo loop para a proxima carta da mao
        /*
            obs: quando estiver no ultimo loop, ele nao passa para a proxima
                 carta, pois se passasse, iria retornar a carta nula
        */
        if(i != NUM_CARTAS - 1){
            mao = mao->next;
            baralho = baralho->next;
        }
    }

    return mao;
}

CARTA *cria_mesa()
//essa funcao cria a mesa no comeco do jogo
{
    CARTA *mesa;

    //lancando as cartas do baralho para a mesa
    for(int i = 0; i < NUM_CARTAS_MESA; i++){
        //todo comeco de loop aloca memoria para a nova carta da mesa
        mesa = (CARTA *)malloc(sizeof(CARTA));
        //transpondo os valores da ultima carta do baralho para a mesa
        mesa->naipe = baralho->naipe;
        mesa->valor = baralho->valor;
        //inicializando a proxima carta da mesa como sendo nula
        mesa->next = NULL;
        //transpondo o proximo loop para a proxima carta da mesa...
        if(i != NUM_CARTAS_MESA - 1){
            mesa = mesa->next;
            baralho = baralho->next;
        }
    }

    return mesa;
}

void jogada(CARTA *mao, CARTA *mesa)
//essa funcao retira a carta da mao do usuario e a coloca na mesa
{


}











