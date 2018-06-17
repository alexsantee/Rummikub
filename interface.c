#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//para colocar a escrita em portugues;

void clear();
void pause();
int menu_inicial();
int jogo(int j);

int main()
{
    //char resp;
    int j=0;
    int nj;
    int vitoria=0;

    setlocale(LC_CTYPE, "Portuguese");

    nj = menu_inicial();
    while(vitoria==0)
    {
        vitoria=jogo(j);
        clear();
        if(vitoria==0)
            {
                j++;
                j=j%nj;
                clear();
            }
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

int menu_inicial()
{
    char resp_inicial;//colocado em char para o programa não quebrar com resposta não numerica;
    int i;

    printf("Bem-vindo ao Rummikub.\n");
    do{
    printf("Quantos jogadores(1-5):\n");
    scanf(" %c",&resp_inicial);
    clear();
    }while(resp_inicial>'5'||resp_inicial<'1');
    if(resp_inicial=='1')i=1;
    if(resp_inicial=='2')i=2;
    if(resp_inicial=='3')i=3;
    if(resp_inicial=='4')i=4;
    if(resp_inicial=='5')i=5;

    return (i);
}

int jogo(int j)
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
