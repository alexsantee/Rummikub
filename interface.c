#include <stdio.h>
#include <stdlib.h>
#include <locale.h>//para colocar a escrita em portugues;
#include <unistd.h>//Funções de pausa para splash screen

#include "baralho.h"
#include "mesa.h"
#include "defines.h"
#include "mao.h"

void clear(); //declarada a funcao que realiza a limpeza do terminal
void pausa(); //requer que o usuario pressione ENTER para continuar o programa
int Menu_nj();//menu para perguntar o numero de jogadores
int turno(MAO *mao_jogador,MESA *mesa);//precissa ser melhorado
void printa_mesa(MESA *mesa);//função para printar a mesa atual
CARTA *Inicia_Baralho(); /* determina o tipo de baralho, ja criando ele
                            ou pegando ele de algum arquivo que queiramos */
void splash();

int main()
{
    //splash();
    int nj;//numero de jogadores
    CARTA *baralho; //struct dos elementos que vao compor o baralho
	MAO *mao_jogador; //struct de elementos que compoe a mao do jogador
    MESA *mesa;

   int estado_jogo=0;//flag para monitorar

    setlocale(LC_CTYPE, "Portuguese"); //adapta a linguagem para portugues(acentos)

    baralho= Inicia_Baralho(); //cria e torna o baralho
    mesa=cria_mesa();

    nj = Menu_nj(); //obtem a quantidade de jogadores

    mao_jogador = inicia_mao(nj,baralho); //distribui cartas para a mao do jogador

    while(estado_jogo==0)
    {
        estado_jogo=turno(mao_jogador,mesa);
        //pula para a funcao que é o jogo em si, para o jogador de numero 1 inicialmente
        clear();
        /*
          esse bloco permanece rodando ate que se altere a variavel 'estado_jogo'
          assim sabemos que quando alterada o jogo acabou. O unico valor disponi-
          vel para alteracao é o 1. Verificando assim qual venceu
        */
    }
	if(estado_jogo==1){
    	printf("O jogador %d foi o vencedor.\n",(mao_jogador->num_jogador)+1);
	}
    else{
		//executa verificação de vencedor
	}
    pausa();
    return (0);
}

void clear()
{
	#ifdef WIN32 //para Windows
   		system("CLS");
	#else //para outro, seja MacOS ou Linux
        system("clear");
	#endif
}

void pausa()
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
    int nj; //transforma o dado obtido em inteiro para obtermos a quantidade de jogadores

    printf("[!][!]Bem-vindo ao Rummikub[!][!]\n");
    do{
    printf("Quantos jogadores[1-5]: ");
    scanf(" %c",&resp_inicial);
    clear();
    }while(resp_inicial>MAX_JOGADORES||resp_inicial<'1');
    //do while para forcar que o usuario escreva dentro de um intervalo válido
    nj=(resp_inicial - '0');

    return (nj); //retorna quantidade de jogadores
}

int turno(MAO *mao_jogador,MESA *mesa)
{
    int vitoria=0;//flag para a resposta se houve ou não vitoira
    int fim=0;//flag para permitir passar o turno
    char resp_turno;
    int movimentos=0;//flag para verificar se pode passar o turno

    printf("É a vez do jogador %d.\n",(mao_jogador->num_jogador)+1);
    pausa();
    clear();

    do{
        if(mao_jogador->first==NULL)//victoria se não tiver mais carta
        {
            fim++;
            vitoria++;
        }else{
            do{
                printa_mesa(mesa);
                printf("************************");
                printf("Opções de ações:\n");
                printf("1.Jogar cartas da mão\n");
                printf("2.Formar uma nova combinação\n");
                if(fim==0){printf("3.Compra do Baralho e terminar o turno.\n>>");}//verificar se a regra do jogo nesta parte esta certa**************
                else{printf("3.Terminar o turno\n>>");}
                scanf(" %c",&resp_turno);
                clear();
                }while(resp_turno>'3'||resp_turno<'1');
                switch(resp_turno) {
                case '1':
                {
                    char n_cartas;
                    do{
                        clear();
                        printf("Quantas cartas?\n>> ");
                        scanf(" %c",&n_cartas);
                    }while(n_cartas<'0'/*||n_cartas< "cartas na mão" , max 9*/);
                    int aux;//usado para conversões momentaneas de char pra int;
                    aux=n_cartas - '0';
                    char posicao[aux];
                    aux=0;//limpando para ser utilizado novamente
                    for(char i='0';i<n_cartas;i++)
                    {
                        printf("posição da carta %c/%c",i+1,n_cartas);
                        scanf("%c",&posicao[aux]);
                        aux++;
                    }
                    //função de verificação
                    //resposta se foi executado o movimento ou o movimento era invalido
                    pausa();
                    clear();
                    break;
                }
                case '2':
                {
                    char posicao[3];
                    for(int i=0;i<3;i++)
                    {
                        printf("posição da carta %c/%d",i+1,3);
                        scanf("%c",&posicao[i]);
                    }
                    //função de verificação
                    //resposta se foi executado o movimento ou o movimento era invalido
                    pausa();
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
                        pausa();
                        clear();
                    }else{
                        fim++;
                        clear();
                    }
                }
            }
        }
    }while(fim==0);//loop principal do turno
    if(vitoria==0)//passar para o proximo jogador
    {
        mao_jogador=mao_jogador->next;
    }
    return (vitoria);
}


void printa_mesa(MESA *mesa)
{
    int i=0;//contador de conjunto
    CONJ *conj_copia;//ponteiro usar ler os valores nos endereços sem reprisar, no final, volta o ponteiro para a posição inicial
    conj_copia = mesa->first;//copiando o endereço para não precisar depois voltar para a posição inicial
    CARTA *carta_copia;
    if(conj_copia!=NULL){carta_copia=conj_copia->first;}
    while(conj_copia != NULL)//loop para mostrar um conjunto
        {
        printf("Conjunto %d ->",i+1);
        while(carta_copia != NULL)//loop pra mostrar as cartas do conjunto
            {
                printf("  %c%c",carta_copia->naipe,carta_copia->n);//tamanho de caracteres na tela:4
                carta_copia=carta_copia->next;
            }
        conj_copia= conj_copia->next;//passar para outro conjunto
        printf("\n");
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
    }while(resp_baralho<'1'||resp_baralho>'2'); //o loop impossibilita respostas invalidas
    if(resp_baralho=='1')
        {
            baralho = cria_baralho(); //utiliza o ponteiro pra struct de cartas e cria o baralho
            if(baralho == NULL){
                printf("[!]Nao foi possivel criar o baralho! Tente novamente.\n");
                pausa();
                exit(0);
            }
            else{
                printf("[!]Baralho aleatório criado.\n");
                pausa();
            }
            embaralha(baralho); //utiliza o ponteiro com endereco do baralho e o embaralha
            /*
            obs: embaralho é realizado depois da verificacao do baralho NULL para evitar processamento
                 caso nao foi possivel criar o baralho
            */
        }
    if(resp_baralho=='2')
        {
            char nome_arquivo[LEN_NOME_ARQ];
            printf("Qual o nome do arquivo:(inclua o .txt !)\n>> ");
            fgets(nome_arquivo,LEN_NOME_ARQ,stdin);
            baralho=cria_baralho_arq(nome_arquivo);
            /*
              utiliza o ponteiro para structs e cria o baralho a partir da funcao
              especial criada pensando na string recolhida do usuario
            */
            clear();
            if(baralho == NULL){
                printf("[!]Baralho nao lido. Verifique se o nome esta correto e tente novamente.\n");
                pausa();
                exit(0);
            }
            else{
                printf("Baralho lido.\n");
            }
        }
    pausa();
    clear();
    return (baralho); //retorna o ponteiro para o baralho, caso ele consiga ser criado
}

void splash()
{
    const char *frame0 = "\n===============================================================================\n\n===============================================================================\n\n===============================================================================\n\n    _______                                      _       \n   (  ____ )                                    | \\    /\\\n   | (    )|                                    |  \\  / /\n   | (____)|                                    |  (_/ / \n   |     __)                                    |   _ (  \n   | (\\ (                                       |  ( \\ \\ \n   | ) \\ \\__                                    |  /  \\ \\\n   |/   \\__/                                    |_/    \\/\n                                                         \n\n===============================================================================\n\n===============================================================================\n\n===============================================================================\n\n";
    const char *frame1 = "===============================================================================\n\n===============================================================================\n\n===============================================================================\n\n\n    _______                                      _       \n   (  ____ )                                    | \\    /\\\n   | (    )|                                    |  \\  / /\n   | (____)|                                    |  (_/ / \n   |     __)                                    |   _ (  \n   | (\\ (                                       |  ( \\ \\ \n   | ) \\ \\__                                    |  /  \\ \\\n   |/   \\__/                                    |_/    \\/\n                                                         \n\n\n===============================================================================\n\n===============================================================================\n\n===============================================================================\n";
    const char *frame2 = "###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################\n###############################################################################";
    const char *frame3 = "X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n\n    _______           _______  _______ _________ _                 ______  \n   (  ____ )|\\     /|(       )(       )\\__   __/| \\    /\\|\\     /|(  ___ \\ \n   | (    )|| )   ( || () () || () () |   ) (   |  \\  / /| )   ( || (   ) )\n   | (____)|| |   | || || || || || || |   | |   |  (_/ / | |   | || (__/ / \n   |     __)| |   | || |(_)| || |(_)| |   | |   |   _ (  | |   | ||  __ (  \n   | (\\ (   | |   | || |   | || |   | |   | |   |  ( \\ \\ | |   | || (  \\ \\ \n   | ) \\ \\__| (___) || )   ( || )   ( |___) (___|  /  \\ \\| (___) || )___) )\n   |/   \\__/(_______)|/     \\||/     \\|\\_______/|_/    \\/(_______)|/ \\___/ \n                                                                           \n\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\n + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +\nX + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X +";
    const char *frame4 = "+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n\n    _______           _______  _______ _________ _                 ______  \n   (  ____ )|\\     /|(       )(       )\\__   __/| \\    /\\|\\     /|(  ___ \\ \n   | (    )|| )   ( || () () || () () |   ) (   |  \\  / /| )   ( || (   ) )\n   | (____)|| |   | || || || || || || |   | |   |  (_/ / | |   | || (__/ / \n   |     __)| |   | || |(_)| || |(_)| |   | |   |   _ (  | |   | ||  __ (  \n   | (\\ (   | |   | || |   | || |   | |   | |   |  ( \\ \\ | |   | || (  \\ \\ \n   | ) \\ \\__| (___) || )   ( || )   ( |___) (___|  /  \\ \\| (___) || )___) )\n   |/   \\__/(_______)|/     \\||/     \\|\\_______/|_/    \\/(_______)|/ \\___/ \n                                                                           \n\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X\n+ X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X + X";

    const char *frames[5];
    frames[0] = frame0;
    frames[1] = frame1;
    frames[2] = frame2;
    frames[3] = frame3;
    frames[4] = frame4;

    int i;
    for(i=0; i<30; i++)
    {
        putchar('\n');
        clear();
        printf("%s", frames[(i%2)]);
        usleep(100000);
    }
    
        putchar('\n');
        clear();
        printf("%s", frames[2]);
        usleep(400000);
        
        for(i=0; i<30; i++)
    {
        putchar('\n');
        clear();
        printf("%s", frames[(i%2)+3]);
        usleep(200000);
    }    

    putchar('\n');
    clear();
}
