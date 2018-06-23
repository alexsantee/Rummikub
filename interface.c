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
    nj = Menu_nj();
    for(int i = 0; i < nj ; i++)
    {
        mao_jogador[i] = cria_mao_jogador( baralho );
    }

    for(jogador=0;vitoria==0;jogador++,jogador=jogador%nj)
    {
        vitoria=turno(jogador,*mao_jogador[jogador],/* mesa */);
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

int Menu_nj()
{
    char resp_inicial;//colocado em char para o programa não quebrar com resposta não numerica;
    int nj;

    printf("Bem-vindo ao Rummikub.\n");
    do{
    printf("Quantos jogadores(1-5):\n");
    scanf(" %c",&resp_inicial);
    clear();
    }while(resp_inicial>'5'||resp_inicial<'1');
    nj=(resp_inicail - '0');

    return (nj);
}

int turno(int j,CARTA *mao_jogador[jogador],/*tipomesa mesa */)
{
    int vitoria;
    int fim=0;
    char resp_turno='1';

    printf("É a vez do jogador %d.\n",j+1);
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
            /*  printf(mesa)*/
            prinf("************************")
            printf("Vez do jogador %d",j+1);
            printf("Opções de ações:\");
            prinf("1.jogar cartas da mão.");
            printf("2.formar uma nova combinação.\n");
            if(fim==0){printf("3.Compra do Baralho e terminar o turno.\n>>")}
            if(fim!=0){printf("3.Terminar o turno\n>>");}
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
