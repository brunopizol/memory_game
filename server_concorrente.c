#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int countUsuarios;
char playerVez[7];
//int totalcards[18];
char *totalcards;
char *cartasAcertadas;
int statusPlayer1;
int statusPlayer2;
char *tempCartas;
int numbercards;
char *tempJogada;
char *msgToSend;
int cardsA[100];
void doprocessing (int sock);
void verificaMsg(char *msg);
void converteArray();
void buscaJogadas();
void registerPlayer();

int main( int argc, char *argv[] )
{
    FILE* temp1;
    /*FILE* temp2;
    FILE* temp3;
    FILE* temp4;
    FILE* temp5;
    FILE* temp6;*/

    int sockfd, newsockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n, pid;

    numbercards=0;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    temp1 = fopen("cartasAcertadas.txt","wt");
    /*temp2 = fopen("player2.txt","wt");
    temp3 = fopen("jogada.txt","wt");
    temp4 = fopen("cartasAcertadas.txt","wt");
    temp5 = fopen("cartasErradas.txt","wt");
    temp6 = fopen("conexao.txt","wt");*/

    /*fclose(temp1);
    fclose(temp2);
    fclose(temp3);
    fclose(temp4);
    fclose(temp5);
    fclose(temp6);*/
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 54666;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here
       * process will go in sleep mode and will wait
       * for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

        if (newsockfd < 0)
        {
            perror("ERROR on accept");
            exit(1);
        }
        registerPlayer();
        buscaJogadas();

        /* Create child process */
        pid = fork();

        if (pid < 0)
        {
            perror("ERROR on fork");
            exit(1);
        }

        if (pid == 0)
        {
            /* This is the client process */
            close(sockfd);
            doprocessing(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }

    } /* end of while */
}


void doprocessing (int sock)
{
    int n;
    int result;
    int length;
    char SendMsg[1024];
    char buffer[1024];
    char *bufferS;
    bzero(buffer,1024);
    //bzero(bufferS, 2048);
    n = read(sock,buffer,1024);
    //buscaJogadas();


    verificaMsg(buffer);
    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(1);
    }
    //sendCards();
    //converteArray();
    buscaJogadas();
    length = sizeof(totalcards)+10;
    printf("\nHere is the message: %s\n",buffer);
    printf("\nvalor do buffer de teste: %s",totalcards);
    //printf("\ncartas acertadas: %s", cartasAcertadas);
    //strcpy(bufferS, cartasAcertadas);
    //printf("\ncartas acertadas: %s", bufferS);
    n = write(sock, totalcards,length);
    //n = write(sock, buffer, 1024);

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(1);
    }
    buscaJogadas();

}


void verificaMsg(char *msg)
{

    const char tok1[2] = "#";
    const char tok2[2] = "@";
    const char tok3[2] = "%";
    const char tok4[2] = "!";

    FILE *arq;
    FILE *arq2;
    FILE *arq3;

    arq2 = fopen("jogada.txt","a");
    arq3 = fopen("cartasAcertadas.txt","a");


    char *play;
    char *card1;
    char *card2;
    char *player;
    char *playertemp;
    char *tempMsg;
    char *msgTemp1;
    char *msgTemp2;
    int resultado;
    int tempt;
    int count=0;
    int autoriza=0;

    char tempP1[7] = "player1";
    char tempP2[7] = "player2";


    char *line = NULL;
    char acertou[7] = "acertou";
    char errou[5] = "errou";
    size_t len = 0;
    ssize_t read;





    //strcpy(msgTemp1, msg);
    //strcpy(msgTemp2, msg);



/// ------------------------- verifica qual player ------------------------------------------
    player = strtok(msg, tok4);
    //player = strtok(msgTemp1, tok4);
    //printf("\nValor de msg: %s", msg);
    //tempMsg = strtok(msgTemp2, tok1);
    //strcpy(playertemp, player);

    if(strcmp(player, tempP1)==0)
    {
        printf("\nentrou no return 1");
        printf("\nplayer verificado com sucesso: %s", player);
        resultado=1;
        statusPlayer1=1;
        statusPlayer2=0;
    }

    else if(strcmp(player, tempP2)==0)
    {
        printf("\nentrou no return 2");
        printf("\nplayer verificado com sucesso: %s", player);
        resultado= 0;
        statusPlayer2=1;
        statusPlayer1=0;
    }


    if(resultado==1)
    {
        arq = fopen("player1.txt","a");
        if(arq == NULL)
            arq = fopen("player1.txt","wt");

    }

    if(resultado==0)
    {
        arq = fopen("player2.txt","a");
        if(arq == NULL)
            arq = fopen("player2.txt","wt");

    }

    /// --------------------- começa a verificacao da msg ----------------------------------------

    while(player != NULL)
    {
        count++;
        printf("\n%s ",player);
        fprintf(arq," %s ", player);
        //fprintf(arq2,"\n%s\r\n", playertemp);
        player = strtok(NULL, tok4);

          if(count>=2 && count<4){
              if(numbercards==0){
              //cardsA[numbercards]= atoi(player);
              numbercards++;
              fprintf(arq3,"%s, ",player);
              //sprintf(msgToSend,"%s",player);
              //strcpy(msgToSend,player);
              }else{
              //strcat(totalcards,player);
              fprintf(arq3,"%s, ",player);
              //sprintf(msgToSend,"%s %s",msgToSend,player);
              //strcat(msgToSend,player);
              //cardsA[numbercards]= atoi(player);
              numbercards++;
              }
          }
        ///====================

        /*if(count==4){
           if(numbercards==0){
           numbercards++;
           fprintf(arq3,"\n%s\r\n",player);
           //strcpy(totalcards,player);
           }else{
           //strcat(totalcards,player);
           fprintf(arq3,"\n%s\r\n",player);
           }
                }*/
        //sprintf(tempJogada,"%s %s",tempJogada,player);
        //strcpy(playertemp, player);


    }
    fprintf(arq2,"@ ");
    fprintf(arq,"@ ");

    //converteArray();

//printf("\nValor de tempJogada: %s", tempJogada);
//puts(tempJogada);
//fclose(arq3);

}

void converteArray()
{
    int i=0;

    for(i=0; i<numbercards; i++)
    {

        msgToSend[i]=cardsA[i];

    }


}

void buscaJogadas()
{
    //totalcards = 0;
    long length;
    FILE * f = fopen ("cartasAcertadas.txt", "rt");

   /* if(statusPlayer1==1)
    {

        f = fopen ("player1.txt", "rt");
    }
    else if(statusPlayer2==1)
    {

        f = fopen ("player2.txt", "rt");
    }*/

    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        totalcards = malloc (length);
        if (totalcards)
        {
            fread (totalcards, 1, length, f);
        }
        //fclose (f);
    }



}


void registerPlayer()
{
    FILE *arq1;

    arq1 = fopen("usuarios.txt", "wt");
    if(countUsuarios == 0)
    {
        fprintf(arq1,"\nplayer1");
        countUsuarios++;

    }
    else if(countUsuarios == 1)
    {

        fprintf(arq1,"\nplayer2");
        countUsuarios++;

    }
    else
    {


    }
    fclose(arq1);

}

