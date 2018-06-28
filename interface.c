#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//para colocar a escrita em portugues;

#include "baralho.h"
#include "mesa.h"
#include "defines.h"

void clear();
void pause();
int pegaQuantidade_jogadores();
int jogo(int j);
int Menu_nj();
int turno(int j,CARTA *mao_jogador[int jogador],MESA *mesa);//--------mexer
CARTA *Inicia_Baralho(); // determina o tipo de baralho, ja criando ele
                      // ou pegando ele de algum arquivo que queiramos
CARTA *cria_mao_jogador( CARTA *baralho );

int main()
{
    int nj;//numero de jogadores
    CARTA *baralho;
	MAO *mao_jogador;

    enum estado_jogo(sem_carda=-1,em_andamento,vitoria=1)//variavel para determinar se alguem ganhou

    setlocale(LC_CTYPE, "Portuguese"); //adapta a linguagem para portugues(acentos)

    baralho= Inicia_Baralho(); //cria e torna o baralho
    nj = Menu_nj();
    
    mao_jogador = inicia_mao(nj,*baralho);

    while(estado_jogo==0);
    {
        estado_jogo=turno(*mao_jogador,*mesa);
        clear();
    }
	if(estado_jogo==1)
		{
    	printf("O jogador %d foi o vencedor.\n",(mao_jogador->num_jogador)+1);
		}else{
		//executa verificação de vencedor
		}
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

int Menu_nj()
{
    char resp_inicial;//colocado em char para o programa não quebrar com resposta não numerica;
    int nj;

    printf("Bem-vindo ao Rummikub.\n");
    do{
    printf("Quantos jogadores(1-5):\n");
    scanf(" %c",&resp_inicial);
    clear();
    }while(resp_inicial>MAX_JOGADORES||resp_inicial<'1');
    nj=(resp_inicial - '0');

    return (nj);
}

int turno(MAO *mao_jogador;MESA *mesa)
{
    int vitoria;
    int fim=0;//flag para permitir passar o turno
    char resp_turno;

    printf("É a vez do jogador %d.\n",(mao_jogador->num_jogador)+1);
    pause();
    clear();

    while(fim==0)
    {
        int movimentos;
    /*  if(cartas_na_mao ==0)
            {
            fim++;
            vitoria++;
            }
        else{*///tem que terminar o fechamente de chaves " } "
        do{
            printa_mesa;
            printf("************************");
            printf("Vez do jogador %d",j+1);
            printf("Opções de ações:\n");
            printf("1.jogar cartas da mão.");
            printf("2.formar uma nova combinação.\n");
            if(fim==0){printf("3.Compra do Baralho e terminar o turno.\n>>");}
            else{printf("3.Terminar o turno\n>>");}
            scanf("%c",&resp_turno);
            clear();
            }while(resp_turno>'3'||resp_turno<'1');
        switch(resp_turno) {
        case '1':
            {
            char n_cartas;
            do{
                clear();
                printf("Quantas cartas?\n>>");
                scanf("%c",&n_cartas);
                }while(n_cartas<'0'/*||n_cartas< "cartas na mão" , max 9*/);
            int aux;//usado para conversões momentaneas de char pra int;
            aux=n_cartas - '0';
            char posição[aux];
            aux=0;//limpando para se utilizado novamente
            for(char i='0';i<n_cartas;i++)
            {
                printf("posição da carta %c/%c",i+1,n_cartas);
                scanf("%c",&posição[aux]);
                aux++;
            }
            //função de verificação
            //resposta se foi execultado o movimento ou o movimento era invalido
            pause();
            clear();
            break;
            }
        case '2':
            {
                           char posição[3];
            for(int i=0;i<3;i++)
            {
                printf("posição da carta %c/%d",i+1,3);
                scanf("%c",&posição[i]);
            }
            //função de verificação
            //resposta se foi execultado o movimento ou o movimento era invalido
            pause();
            clear();
            break;
            }
        case '3':
            {
                if(movimentos==0)
                {
                    //função compra
                    //printar carta comprada
                    fim++;
                    pause();
                    clear();
                }else{
                    fim++;
                    clear();
                }
            }
        }
    }
    return (vitoria);
}
void printa_mesa(MESA *mesa)
{
    int i=0;//contador de conjunto
    MESA *print_mesa;//ponteiro usar ler os valores nos endereços sem reprisar, no final, volta o ponteiro para a possição inicial
    print_mesa = mesa;//copiando o endereço para não prescissar depois voltar para a posição inicial
    while(print_mesa.first != NULL)//loop para mostrar um conjunto
        {
        printf("Conjunto %d ->",i+1);
        while(print_mesa.first.carta != NULL)//loop pra mostrar as cartas do conjunto
            {
                printf("  %c%c",CARTA->naipe,CARTA->n);//tamanho de caracteres na tela:4
                print_mesa.first.carta = print_mesa.first.next;
            }
        print_mesa.first = print_mesa.next;//passar para outro conjunto
        putchar("\n").
        i++;
        }
}

CARTA *Inicia_Baralho()
{
    char resp_baralho;
    CARTA *baralho;
    do{
    printf("Você deseja usar um baralho aleatorio[1] ou importar um baralho[2]?\n>> ");
    resp_baralho=getc(stdin);
    clear();
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
