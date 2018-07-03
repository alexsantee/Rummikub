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
int turno(MAO *mao_jogador,MESA *mesa, CARTA *baralho);//precissa ser melhorado
void printa_mesa(MESA *mesa);//função para printar a mesa atual
CARTA *Inicia_Baralho(); /* determina o tipo de baralho, ja criando ele
                            ou pegando ele de algum arquivo que queiramos */
void splash();

int main()
{
    //splash();
    int nj;//numero de jogadores
    CARTA *baralho;
	MAO *mao_jogador;
    MESA *mesa;

   int estado_jogo=0;

    setlocale(LC_CTYPE, "Portuguese");

    baralho = Inicia_Baralho();
    mesa=cria_mesa();

    nj = Menu_nj();

    mao_jogador = inicia_mao(nj,baralho);

    while(estado_jogo==0)
    {
        estado_jogo=turno(mao_jogador,mesa, baralho);
        mao_jogador = mao_jogador->next;
        //INICIALIZAR TODOS AS CARTAS DA MESA COMO DA_MESA---------------------
        clear();
    }
	if(estado_jogo==1){
    	printf("O jogador %d foi o vencedor.\n",(mao_jogador->num_jogador)+1);
	}
    else{
		//EXECUTA VERIFICAÇÃO DE VENCEDOR------------------------------------------
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
    nj=(resp_inicial - '0');

    return (nj);
}

int turno(MAO *mao_jogador,MESA *mesa, CARTA *baralho)
{
    int vitoria=0;
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
                printf("2.Tirar carta da mesa\n");
                if(fim==0){printf("3.Compra do Baralho e terminar o turno.\n>>");}//verificar se a regra do jogo nesta parte esta certa**************
                else{printf("3.Terminar o turno\n>>");}
                scanf(" %c",&resp_turno);
                clear();
                }while(resp_turno>'3'||resp_turno<'1');
                switch(resp_turno) {
                case '1':   //Jogar carta da mão
                {
                    int pos_carta_mao;
                    int n_conj;
                    int pos_conj;
                    printf("Carta de que posição? ");
                    scanf(" %d", &pos_carta_mao);
                    pos_carta_mao--;  //Índice 1->0
                    printf("Em que conjunto colocar? ");
                    scanf(" %d", &n_conj);
                    n_conj--;
                    printf("Qual a posição naquele conjunto? ");
                    scanf(" %d", &pos_conj);
                    pos_conj--;
                    CARTA *c;
                    CONJ *conj;
                    c = remove_carta(pos_carta_mao, mao_jogador);
                    conj = localiza_conjunto(n_conj, mesa);
                    insere_no_conjunto(c, pos_conj, conj);
                    
                    break;
                }
                case '2':   //Tirar carta da mesa
                {
                    int n_conj;
                    int n_carta;
                    printf("Retirar carta de que conjunto? ");
                    scanf(" %d", &n_conj);
                    n_conj--;
                    printf("Qual a posição da carta no conjunto? ");
                    scanf(" %d", &n_carta);
                    n_carta--;
                    CARTA *c;
                    CONJ *conj;
                    conj = localiza_conjunto(n_conj, mesa);
                    c = retira_do_conjunto(n_carta, conj);
                    c->next = mao_jogador->first;//DEVIAMOS COLOCAR NO FINAL
                    mao_jogador->first = c;
                    break;
                }
                case '3':   //finalizar turno comprando ou não carta
                {
                    if(movimentos==0)
                    {
                        add_carda_mao(mao_jogador, baralho);
                        fim++;
                        pausa();
                        clear();
                    }else{
                        fim++;
                        clear();
                    }
                    break;
                }
            }
        }
    }while(fim==0);
    return (vitoria);
}


void printa_mesa(MESA *mesa)
{
    int i=0;
    CONJ *conj_copia;
    conj_copia = mesa->first;
    CARTA *carta_copia;
    if(conj_copia!=NULL){carta_copia=conj_copia->first;}
    while(conj_copia != NULL)//loop para mostrar um conjunto
        {
        printf("Conjunto %d ->",i+1);
        while(carta_copia != NULL)//loop pra mostrar as cartas do conjunto
            {
                imprime_carta(*carta_copia);
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
    }while(resp_baralho<'1'||resp_baralho>'2');
    if(resp_baralho=='1')
        {
            baralho = cria_baralho();
            if(baralho == NULL){
                printf("[!]Nao foi possivel criar o baralho! Tente novamente.\n");
                pausa();
                exit(0);
            }
            else{
                printf("[!]Baralho aleatório criado.\n");
                pausa();
            }
            embaralha(baralho);
        }
    if(resp_baralho=='2')
        {
            char nome_arquivo[LEN_NOME_ARQ];
            printf("Qual o nome do arquivo:(inclua o .txt !)\n>> ");
            fgets(nome_arquivo,LEN_NOME_ARQ,stdin);
            baralho=cria_baralho_arq(nome_arquivo);
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
    return (baralho);
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
