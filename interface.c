#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//para colocar a escrita em portugues;

#include "baralho.h"

#define LEN_NOME_ARQ 60//tamanho da string do nome do arquivo

void clear();
void pause();
int menu_inicial();
int jogo(int j);
CARTA tipo_baralho();

int main()
{
    int jogador;//atual jogador
    int nj;//numero de jogadores
    CARTA *baralho;

    int vitoria=0;//variavel para determinar se alguem ganhou

    setlocale(LC_CTYPE, "Portuguese");

    barralho= tipo_baralho(baralho);
    nj = menu_inicial();
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
    printf("Aperte enter para continuar...");
    while( (( pausa=getchar() ) != '\n') && (pausa != '\0'));   //Pula caracteres lixo
	clear();
}

char menu_inicial()
{
    char resp_inicial;//colocado em char para o programa não quebrar com resposta não numerica;
    char nj;

    printf("Bem-vindo ao Rummikub.\n");
    do{
    printf("Quantos jogadores(1-5):\n");
    scanf(" %c",&resp_inicial);
    clear();
    }while(resp_inicial>'5'||resp_inicial<'1');
    if(resp_inicial=='1'){nj=1;}
    if(resp_inicial=='2'){nj=2;}
    if(resp_inicial=='3'){nj=3;}
    if(resp_inicial=='4'){nj=4;}
    if(resp_inicial=='5'){nj=5;}

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
    printf("Você deseja usar um baralho aleatoria(1) ou importar um baralho(2).\n");
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
            printf("Qual o nome do arquivo:(inclua o .txt !\n)");
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
