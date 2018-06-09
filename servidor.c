# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <netdb.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>

#define MAXBUFF 1024
#define FIM     "fim da transmissao"

// autores: Bruno Pizol e Dennes Spinola

int termina;
int termina1;
int termina2;
int par1;
int par2;
int par3;
int par4;
int par5;
int par6;
int semaforo;
int matrizCartas[3][4]; //se der errado mudar para [3][4]
int server(int socketfd);
void mostraJogada(int card1, int card2);
void atualizaTela (int  *tmp);
void atualizaMatriz(int par);
void MostraCartaEscolhida (int carta1,int carta2);
pthread_t thread2;

  int r1=0;
    int r2=0;
int server(int);

//=============inicio do main ================



int main (argc, argv)
int    argc;
char   *argv[];

{
int carta1=0;
    int carta2=0;
    int cont1=0;
    int cont2=0;
    int resultado=0;
    int click=0;
    int aux=0;
    int i,j;


    termina=0;
par1=0;
par2=0;
par3=0;
par4=0;
par5=0;
par6=0;

matrizCartas[0][0]=1;
matrizCartas[0][1]=2;
matrizCartas[0][2]=2;
matrizCartas[0][3]=3;
matrizCartas[1][0]=4;
matrizCartas[1][1]=1;
matrizCartas[1][2]=5;
matrizCartas[1][3]=4;
matrizCartas[2][0]=3;
matrizCartas[2][1]=5;
matrizCartas[2][2]=6;
matrizCartas[2][3]=6;

long temp3;
//=================================================================================================
   int       socketfd, serv_len;
	int porta=56664,portatemp;
   struct sockaddr_in   serv_addr;

   //Cria o socket TCP
   if ( (socketfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0){
  printf("servidor: erro na criacao do socket");
  exit(0);
   }


   //Preenche a estrutura do servidor e faz o Bind Local
   bzero( (char*) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family        = AF_INET;
   serv_addr.sin_addr.s_addr  = htonl(INADDR_ANY);
   serv_addr.sin_port        = porta;



//================== faz a conexao e trata erro de porta ===================
   serv_len = sizeof(serv_addr);
   if (bind(socketfd, (struct sockaddr *) &serv_addr, serv_len)<0) {
  printf("servidor: erro no bind local");
	printf("\ndigite uma nova porta: ");
	scanf("%d", &portatemp);
	serv_addr.sin_port        = portatemp;
		if (bind(socketfd, (struct sockaddr *) &serv_addr, serv_len)<0) {
  			printf("\nporta invalida");
			printf("\ndigite uma nova porta: ");
			scanf("%d", &portatemp);
			serv_addr.sin_port        = portatemp;
		}



   }

   //Mostra a porta alocada dinamicamente
   if (getsockname(socketfd, (struct sockaddr *)&serv_addr, &serv_len) < 0) {
  printf("servidor: erro na chamada da funcao getsockname");
  close(socketfd);
  exit(0);
   }


   //Chama a funcao servidor para esperar uma requisicao de servico


	server(socketfd);

   //fecha o socket apos uso

   close (socketfd);
   exit(0);
}


//====================================================================================
int server(socketfd)
int socketfd;
{
  char              buff[MAXBUFF];
  int                    newsocketfd, n, fd, cli_len;
  char buff1[MAXBUFF],buff2[MAXBUFF];

	int carta1=0, carta2=0, resultado=0,i=0,j=0,cont1=0,cont2=0/*,termina2=0*/;
	int card1=0,card2=0,card3=0,card4=0,card5=0,card6=0,card7=0,
		card8=0,card9=0,card10=0,card11=0,card12=0;

  struct sockaddr_in   cli_addr;
  //Prepara para receber conexoes dos clientes
  listen(socketfd,5);

   cli_len=sizeof(cli_addr);

  //Aguarda a conexao de algum cliente
  if ((newsocketfd=accept(socketfd,(struct sockaddr *)&cli_addr,&cli_len))<0){
       printf("Funcao server: erro no accept"); //se ocorreu erro no accept
       close(socketfd);
       exit(0);
  }

while(1){
  //Le o nome do arquivo enviado pelo cliente atraves do socket
  if ((n = read(newsocketfd, buff1, MAXBUFF))<0) {
     printf("Funcao server:  erro no recebimento do nome do arquivo");
     close(socketfd);
     close(newsocketfd);
     exit(0);
  }

		printf(" \n jogador 2 <-[RECEBE] %s",buff1);
		printf("\n");
		pthread_create (&thread2, NULL, (void *) atualizaTela, (int  *) &r1);
		sleep(1);



	printf("\n");

	printf("\n");
	printf("\n");
		printf("\n jogador 2 [ENVIA]-> Escolha o numero da primeira carta desejada: ");
	    scanf("%d",&carta1);
	    printf("\n jogador 2 [ENVIA]-> Escolha o numero da segunda carta desejada: ");
	    scanf("%d",&carta2);





		switch(carta1)
	    {
		case 1:

		cont1= matrizCartas[0][0];
		break;

		case 2:

		cont1 = matrizCartas[0][1];
		break;
		case 3:

		cont1 = matrizCartas[0][2];
		break;

		case 4:

		cont1= matrizCartas[0][3];
		break;

		case 5:

		cont1= matrizCartas[1][0];
		break;

		case 6:

		cont1 =  matrizCartas[1][1];
		break;

		case 7:

		cont1 = matrizCartas[1][2];
		break;

		case 8:

		cont1 = matrizCartas[1][3];
		break;

		case 9:

		cont1 = matrizCartas[2][0];
		break;

		case 10:

		cont1= matrizCartas[2][1];

		break;

		case 11:

		cont1 = matrizCartas[2][2];

		break;

		case 12:

		cont1 = matrizCartas[2][3];
		break;

		default:
		break;
	    }


	    if(carta1!=carta2){
	    switch(carta2)
	    {
	       case 1:

		cont2= matrizCartas[0][0];
		break;

		case 2:

		cont2 = matrizCartas[0][1];
		break;
		case 3:

		cont2 = matrizCartas[0][2];
		break;

		case 4:

		cont2 = matrizCartas[0][3];
		break;

		case 5:

		cont2 = matrizCartas[1][0];
		break;

		case 6:

		cont2 =  matrizCartas[1][1];
		break;

		case 7:

		cont2 = matrizCartas[1][2];
		break;

		case 8:

		cont2 = matrizCartas[1][3];
		break;

		case 9:

		cont2 = matrizCartas[2][0];
		break;

		case 10:

		cont2 = matrizCartas[2][1];

		break;

		case 11:

		cont2 = matrizCartas[2][2];

		break;

		case 12:

		cont2 = matrizCartas[2][3];
		break;

		default:
		break;
	    	}
}
		else{
	    printf("\n Voce escolheu a mesma carta!! portanto perdeu a vez");
		snprintf(buff2, MAXBUFF, "\n O player 2 escolheu as mesmas cartas As cartas foram : %d e %d ||", carta1, carta2);


	    }
mostraJogada(carta1,carta2);

			MostraCartaEscolhida (carta1,carta2);
			if(cont1==0)
			{
			snprintf(buff2, MAXBUFF,"\n O player 2 escolheu uma carta ja escolha anteriormente ou por outro player!! portanto perdeu a vez As cartas foram : %d e %d ||", carta1, carta2);

			}



		 if(cont1 == cont2 && cont1!=0)		// FAZ A COMPARAÇÃO PRA VER SE A CARTA É IGUAL
		{


					switch(cont1)
			    {
				case 1:

				par1=1;
				atualizaMatriz(par1);
				break;

				case 2:

				par2=2;
				atualizaMatriz(par2);
				break;
				case 3:

				par3=3;
				atualizaMatriz(par3);
				break;

				case 4:

				par4=4;
				atualizaMatriz(par4);

				break;

				case 5:

				par5=5;
				atualizaMatriz(par5);

				break;

				case 6:

				par6=6;
				atualizaMatriz(par6);
				break;



				default:
				break;
			    }

			termina2++;
			semaforo=1;
			if(termina2<=3){
			snprintf(buff2, MAXBUFF, "\n O player 2 acertou  As cartas foram: %d e %d e sua pontuacao é: %d ||", carta1, carta2,termina2);

			printf("\n O player 2 acertou  As cartas foram: %d e %d e sua pontuacao é: %d ||", carta1, carta2,termina2);
}else if(termina2==4){

		snprintf(buff2, MAXBUFF, "\n O player 2   G A N H O U !!!  As cartas foram: %d e %d E A PONTUACAO FOI: %d ||", carta1, carta2,termina2);
}

		}
		else{
			snprintf(buff2, MAXBUFF, "\n O player 2 errou  As cartas foram: %d e %d ||", carta1, carta2);
				printf("\n O player 2 errou  As cartas foram: %d e %d ||", carta1, carta2);


		}




		if(termina2>=4)
	    {
		printf("\n ============================================================================ ");
		printf("\n ||        P A R A B E N S  PLAYER 2 !!!   V O C E    G A N H O U  !!!!!!  || ");
		printf("\n ============================================================================ ");

		getchar();
		exit(1);

	    }
    buff[n]='\0';

  //Abre o arquivo para leitura e envia seu conteudo pelo socket
 if ((fd = open(buff, 0)) < 0) {
     //se ocorreu erro, envia uma mensagem de erro ao cliente
    	  sprintf(buff, "Servidor nao consegue abrir arquivo solicitado\n");
      n = strlen(buff2);
     if (write(newsocketfd, buff2, n) != n) {
    printf("Funcao server: erro no envio da mensagem de erro");
        close(socketfd);
        close(newsocketfd);
        exit(0);
     }
   }
   else {    //Se o arquivo existe, Le seu conteudo e envia-o para o cliente
     while ((n = read(newsocketfd, buff2, MAXBUFF)) > 0)
       if (write(newsocketfd, buff2, n) != n) {
      printf("Funcao server: erro no envio dos dados do arq. pelo socket");
    close(socketfd);
    close(newsocketfd);
        exit(0);
       }

    if (n < 0) {
        printf("Funcao server:erro na leitura do arquivo");
    close(socketfd);
    close(newsocketfd);
        exit(0);
    }

   }//fim do else

   sleep(1); //Sincronismo

   //Envia aviso de fim de transmissao
   n = sizeof(FIM);
   if (write(newsocketfd, FIM, n) != n) {
       printf("Funcao server: erro no envio do fim de transmissao pelo socket");
       close(socketfd);
       close(newsocketfd);
       exit(0);
   }
}

} //Fim Funcao server


void atualizaMatriz(int par)
{


				switch(par)
			    {
				case 1:
				matrizCartas[0][0]=0;
				matrizCartas[1][1]=0;

				break;

				case 2:
				matrizCartas[0][1]=0;
				matrizCartas[0][2]=0;

				break;
				case 3:
				matrizCartas[0][3]=0;
				matrizCartas[2][0]=0;
				break;

				case 4:
				matrizCartas[1][0]=0;
				matrizCartas[1][3]=0;


				break;

				case 5:
				matrizCartas[1][2]=0;
				matrizCartas[2][1]=0;

				break;

				case 6:
				matrizCartas[2][2]=0;
				matrizCartas[2][3]=0;

				break;
				default:
				break;

		}





}










void atualizaTela(int *tmp)
{

	int card1=0,card2=0,card3=0,card4=0,card5=0,card6=0,card7=0,
		card8=0,card9=0,card10=0,card11=0,card12=0;

	int par1=1,par2=1,par3=1,par4=1,par5=1,par6=1;

	card1=matrizCartas[0][0];
	card2=matrizCartas[0][1];
	card3=matrizCartas[0][2];
	card4=matrizCartas[0][3];
	card5=matrizCartas[1][0];
	card6=matrizCartas[1][1];
	card7=matrizCartas[1][2];
	card8=matrizCartas[1][3];
	card9=matrizCartas[2][0];
	card10=matrizCartas[2][1];
	card11=matrizCartas[2][2];
	card12=matrizCartas[2][3];



	if(card1==card6 && card1==0)
{
	par1=0;
}else{
par1=1;
}
	if(card2==card3 && card2==0)
{
	par2=0;
}else{
par2=1;
}
	if(card4==card9 && card4==0)
{
	par3=0;
}else{
par3=1;
}
	if(card5==card8 && card5==0)
{
	par4=0;
}else{
par4=1;
}
	if(card7==card10 && card7==0)
{
	par5=0;
}else{
par5=1;
}
	if(card11==card12 && card11==0)
{
	par6=0;
}else{
par6=1;
}



	if(par1==1 && par2==1 && par3==1 && par4==1 && par5==1 && par6==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1  |-| CARTA2 |-| CARTA3 |-| CARTA4 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-| CARTA6 |-| CARTA7 |-| CARTA8 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9  |-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(par1==0 && par2==1 && par3==1 && par4==1 && par5==1 && par6==1)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-| CARTA4 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-|ESCOLHIDA|-| CARTA7 |-| CARTA8|           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9  |-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==0 && par3==1 && par4==1 && par5==1 && par6==1)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-| CARTA4 |             || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-|ESCOLHIDA|-| CARTA7 |-| CARTA8|           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9  |-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==0 && par3==0 && par4==1 && par5==1 && par6==1)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-|ESCOLHIDA|-| CARTA7 |-| CARTA8|           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}


else if(par1==0 && par2==0 && par3==0 && par4==0 && par5==1 && par6==1)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-| CARTA7 |-|ESCOLHIDA |            || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==0 && par3==0 && par4==0 && par5==0 && par6==1)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-|ESCOLHIDA|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==0 && par3==0 && par4==0 && par5==0 && par6==0)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==1 && par3==0 && par4==1 && par5==1 && par6==1)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-|ESCOLHIDA|         	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-|ESCOLHIDA|-| CARTA7 |-| CARTA8|           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==1 && par3==0 && par4==0 && par5==1 && par6==1)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-|ESCOLHIDA|         	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-| CARTA7 |-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==1 && par3==0 && par4==0 && par5==1 && par6==1)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-|ESCOLHIDA|         	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-| CARTA7 |-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==1 && par3==0 && par4==0 && par5==0 && par6==1)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-|ESCOLHIDA|         	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-|ESCOLHIDA|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==1 && par3==0 && par4==0 && par5==0 && par6==0)//010000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-|ESCOLHIDA|         	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}


else if(par1==0 && par2==1 && par3==1 && par4==0 && par5==1 && par6==1)//011011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-| CARTA4 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-| CARTA7 |-|ESCOLHIDA|         	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9  |-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}


else if(par1==0 && par2==1 && par3==1 && par4==0 && par5==0 && par6==1)//011001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-| CARTA4 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9  |-|ESCOLHIDA|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==1 && par3==1 && par4==0 && par5==0 && par6==0)//011000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-| CARTA3 |-| CARTA4 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9  |-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==0 && par2==1 && par3==0 && par4==0 && par5==0 && par6==0)//010000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA2 |-|ESCOLHIDA |-| CARTA4 |         	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}



else if(par1==1 && par2==0 && par3==1 && par4==1 && par5==1 && par6==1)//101111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1  |-|ESCOLHIDA|-|ESCOLHIDA|-|CARTA4|               || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-| CARTA6 |-| CARTA7 |-| CARTA8 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9  |-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==1 && par2==0 && par3==0 && par4==1 && par5==1 && par6==1)//100111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1  |-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-| CARTA6 |-| CARTA7 |-| CARTA8 |           	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}


else if(par1==1 && par2==0 && par3==0 && par4==0 && par5==1 && par6==1)//100011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1  |-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA6 |-| CARTA7 |-|ESCOLHIDA|              || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-| CARTA10|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(par1==1 && par2==0 && par3==0 && par4==0 && par5==0 && par6==1)//100001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1  |-|ESCOLHIDA|-|ESCOLHIDA|-|ESCOLHIDA|            || ");
	printf("\n ============================================================================ ");
	printf("\n ||		|ESCOLHIDA|-| CARTA6 |-|ESCOLHIDA|- |ESCOLHIDA|              || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-|ESCOLHIDA|-| CARTA11|-| CARTA12|        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}


else if(par1==1 && par2==1 && par3==0 && par4==1 && par5==1 && par6==1)//110111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1  |-| CARTA2 |-| CARTA4 |-|ESCOLHIDA|              || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5  |-| CARTA6 |-| CARTA7 |-| CARTA8 |               || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	|ESCOLHIDA|-|CARTA10 |-|CARTA11 |-|CARTA12 |        	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


//printf("\n  A    T  H R E A D      F  U N C I O N O U  !!!");
//getchar();




//sleep(1000);









}


void MostraCartaEscolhida (int carta1,int carta2)
{

if(carta1 == carta2)
{
printf("Tela nao atualizada! foram escolhidas as mesmas cartas");
}


//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA1 COMBINAÇÃO-------------------------------------------

	if(carta1==1 && carta2==2)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| NUMERO-2 |-| CARTA3 |-| CARTA4 |           || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7 |-| CARTA8 |  	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11|-| CARTA12|   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==1 && carta2==3)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2 |-| NUMERO-2  |-| CARTA4 |          || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-|CARTA6  |-| CARTA7    |-| CARTA8|      	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10|-| CARTA11   |-| CARTA12|  	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==1 && carta2==4)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2 |-| CARTA3 |-| NUMERO-3 |           || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6 |-| CARTA7 |-| CARTA8   |      	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10|-| CARTA11|-| CARTA12  |      	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==1 && carta2==5)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2 |-| CARTA3 |-| CARTA4 |           || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6 |-| CARTA7 |-| CARTA8 |      	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10|-| CARTA11|-| CARTA12|      	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==1 && carta2==6)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3  |-| CARTA4 |          || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7  |-| CARTA8 |      	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11 |-| CARTA12 |    	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==1 && carta2==7)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4 |          || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8 |    	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12 |    	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==1 && carta2==8)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==1 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

if(carta1==1 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

if(carta1==1 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

if(carta1==1 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11 |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA2 COMBINAÇÃO-------------------------------------------


	if(carta1==2 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| NUMERO-2 |-| CARTA3 |-| CARTA4 |           || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7 |-| CARTA8 |  	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11|-| CARTA12|   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==2 && carta2==3)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| NUMERO-2 |-| CARTA4 |         || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-|CARTA6    |-| CARTA7   |-| CARTA8|      	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12|  	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==2 && carta2==4)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3 |-| NUMERO-3 |         || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7 |-| CARTA8   |     	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11|-| CARTA12  |     	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==2 && carta2==5)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-|NUMERO-2|-| CARTA3 |-| CARTA4 |           || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6 |-| CARTA7 |-| CARTA8 |      	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10|-| CARTA11|-| CARTA12|      	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==2 && carta2==6)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3  |-| CARTA4 |          || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7  |-| CARTA8 |      	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11 |-| CARTA12 |    	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==2 && carta2==7)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4 |          || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8 |    	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12 |    	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==2 && carta2==8)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==2 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==2 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==2 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==2 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11 |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA3 COMBINAÇÃO-------------------------------------------


	else if(carta1==3 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==3 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==3 && carta2==4)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==3 && carta2==5)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==3 && carta2==6)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==3 && carta2==7)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==3 && carta2==8)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==3 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==3 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==3 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==3 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA4 COMBINAÇÃO-------------------------------------------


else if(carta1==4 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==4 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==4 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==4 && carta2==5)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==4 && carta2==6)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==4 && carta2==7)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==4 && carta2==8)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==4 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==4 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==4 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==4 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA5 COMBINAÇÃO-------------------------------------------


else if(carta1==5 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==5 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==5 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==5 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==5 && carta2==6)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==5 && carta2==7)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==5 && carta2==8)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==5 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==5 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==5 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==5 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA6 COMBINAÇÃO-------------------------------------------


	else if(carta1==6 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==6 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==6 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==6 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==6 && carta2==5)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==6 && carta2==7)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==6 && carta2==8)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==6 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==6 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==6 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==6 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA7 COMBINAÇÃO-------------------------------------------


	else if(carta1==7 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==7 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==7 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==7 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==7 && carta2==5)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==7 && carta2==6)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==7 && carta2==8)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==7 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==7 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==7 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==7 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA8 COMBINAÇÃO-------------------------------------------


	else if(carta1==8 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==8 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==8 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==8 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==8 && carta2==5)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==8 && carta2==6)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==8 && carta2==7)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==8 && carta2==9)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==8 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==8 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==8 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA9 COMBINAÇÃO-------------------------------------------


	else if(carta1==9 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==9 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==9 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==9 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==9 && carta2==5)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==9 && carta2==6)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==9 && carta2==7)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==9 && carta2==8)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==9 && carta2==10)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==9 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==9 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA10 COMBINAÇÃO-------------------------------------------


	else if(carta1==10 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==10 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==10 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==10 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==10 && carta2==5)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==10 && carta2==6)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==10 && carta2==7)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==10 && carta2==8)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==10 && carta2==9)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| NUMERO-5 |-| CARTA11  |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==10 && carta2==11)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==10 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA11 COMBINAÇÃO-------------------------------------------


	else if(carta1==11 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==11 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==11 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==11 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==11 && carta2==5)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==11 && carta2==6)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==11 && carta2==7)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==11 && carta2==8)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==11 && carta2==9)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==11 && carta2==10)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| NUMERO-6 |-| CARTA12  |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==11 && carta2==12)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}
//---------------------------------------------------------------------------------------------------
//--------------------------------------CARTA12 COMBINAÇÃO-------------------------------------------


	else if(carta1==12 && carta2==1)
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-1  |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");

}

else if(carta1==12 && carta2==2)//011111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| NUMERO-2 |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==12 && carta2==3)//001111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| NUMERO-2 |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==12 && carta2==4)//000111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| NUMERO-3 |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}


else if(carta1==12 && carta2==5)//000011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| NUMERO-4  |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");






}

else if(carta1==12 && carta2==6)//000001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| NUMERO-1 |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==12 && carta2==7)//000000
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| NUMERO-5 |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==12 && carta2==8)//010111
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| NUMERO-4 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}

else if(carta1==12 && carta2==9)//010011
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| NUMERO-3  |-| CARTA10  |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==12 && carta2==10)//0100
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| NUMERO-5 |-| CARTA11  |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");




}

else if(carta1==12 && carta2==11)//010001
{

	printf("\n");
	printf("\n");
	printf("\n ============================================================================ ");
	printf("\n ||        		ESCOLHA 	UMA 	CARTA:	            	   || ");
	printf("\n ============================================================================ ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA1    |-| CARTA2   |-| CARTA3   |-| CARTA4   |       || ");
	printf("\n ============================================================================ ");
	printf("\n ||		| CARTA5    |-| CARTA6   |-| CARTA7   |-| CARTA8   |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n ||	       	| CARTA9    |-| CARTA10  |-| NUMERO-6 |-| NUMERO-6 |   	   || ");
	printf("\n ============================================================================ ");
	printf("\n");
	printf("\n");





}











}








void mostraJogada(int card1, int card2){
printf("\n-----------------------------");

switch(card1){

case 1:
printf("\ncarta : alface");
break;

case 2:
printf("\ncarta : brocolis");

break;

case 3:
printf("\ncarta : brocolis");
break;

case 4:
printf("\ncarta : couve");
break;


case 5:
printf("\ncarta : chicoria");
break;


case 6:
printf("\ncarta : alface");
break;

case 7:
printf("\ncarta : mostarda");
break;

case 8:
printf("\ncarta : chicoria");
break;

case 9:
printf("\ncarta : couve");
break;

case 10:
printf("\ncarta : mostarda");
break;


case 11:
printf("\ncarta : rucula");
break;


case 12:
printf("\ncarta : rucula");
break;

default:
break;

}

switch(card2){

case 1:
printf("\ncarta : alface");
break;

case 2:
printf("\ncarta : brocolis");

break;

case 3:
printf("\ncarta : brocolis");
break;

case 4:
printf("\ncarta : couve");
break;


case 5:
printf("\ncarta : chicoria");
break;


case 6:
printf("\ncarta : alface");
break;

case 7:
printf("\ncarta : mostarda");
break;

case 8:
printf("\ncarta : chicoria");
break;

case 9:
printf("\ncarta : couve");
break;

case 10:
printf("\ncarta : mostarda");
break;


case 11:
printf("\ncarta : rucula");
break;


case 12:
printf("\ncarta : rucula");
break;

default:
break;

}

printf("\n-----------------------------------");
}
