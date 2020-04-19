#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define DEBUG 1


struct threadData {
	int myself;
	int otherPlayer;
	char symbol;
};
pthread_mutex_t mutex;
pthread_cond_t cond;

int turn =1;
int gameover = 0;

char buff[MAX]; //FORMAT : C123456789 
	//Client 1 - X
	//Client 2 - O
	//Display - D-----------------...
	//Init - I---------
	//WIN - WC
	//LOSE - LC
/*
void func(int sockfd)
{
	char buff[MAX];
	int n;

	for (;;) 
	{
		bzero(buff, MAX);
		read(sockfd, buff, sizeof(buff));
		printf("From Client : %s\t To Client : ", buff);
		bzero(buff, MAX);
		n=0;

		while((buff[n++] = getchar()) != '\n');
		
		write(sockfd, buff, sizeof(buff));

		if(strncmp("exit", buff, 4) ==0) 
		{
			printf("Server Exit .. \n");
			break;
		}
	}
} */


void initBoard() {
	buff[0] = 'I';
        for (int i=1;i<=9;i++)
                buff[i] = '-';
}

void displayBoard()
{
        printf("Client1 (X) and Client2 (O)\n");
	if(buff[0] == '1')
		printf("Client 1 turn over\n");
	else if(buff[0] == '2')
		printf("Client 2 turn over\n");
	else if(buff[0] == 'I')
		printf("Init Board\n");
        
	for (int i =1; i<=9;i++){
                if((i-1)%3 ==0) printf("\n");
                printf("\t %c", buff[i]);
        }
	printf("\n");
	
	if(buff[0] == '1')
		printf("Awaiting Client 2 \n");
	else if(buff[0] == '2')
		printf("Awaiting Client 1 \n");

}

void frameBuffer(char c, char *toclient)
{
	printf("In framebuffer .. \n");
	//toclient[0]=c;
	buff[0] = c;
	int i,j=0;
	for (i =1; i<=9;i++)
	{
		if(j%7 ==0) 
			toclient[j++] = '\n';
		toclient[j++] = buff[i];
		toclient[j++] = '\t';
	}
	toclient[j] = '\n';
}
	
// Integrate buffer, marks the input for the client. 

void integrateBuffer(char *pos, char sym)
{
	printf("In Integratebuffer.. \n");
	int i;
	sscanf(pos, "%d", &i);
	if(DEBUG) printf("postiiiion %c---> %d for %c \n", pos[0], i, sym);
	buff[i] = sym;
	displayBoard();

}

//validate if the input position is free or taken. 
//
int validateInputFromClient(char *pos)
{
	if (DEBUG) printf("in validateInputFromClient....buff = %s \n", buff);
	int i;
	if(strlen(pos) ==2)
	{
		sscanf(pos, "%d", &i);
		if(DEBUG) printf("postion %c---> %d -- buff[ : %c \n", pos[0], i, buff[i]);
		if (buff[i] == '-') return 1;
	}
	else if(strncmp("exit", pos, 4)==0)
		return 2;
	return 0;
}

// Winning strategy.. 
// return client number.. 
//  0 - no win or tie
//  1- Win
//  2- Tie
int winStrategy()
{

	char sym;
	if (DEBUG) printf("buffer .. %s", buff);
	switch (buff[0])
	{
		case '1':
			sym = 'X';
			break;
		case '2' :
			sym ='O';
			break;
	}
// check if all the elements are filled, then declare TIE.. if not game can continue
	for(int i =1;i<=9; i++)
		if (buff[i] == '-') 
			break;
		else if (i==9)
			return 2;	

	if(
		((buff[1]==buff[2]) && (buff[2]==buff[3]) && (buff[3]==sym)) ||
		((buff[4]==buff[5]) && (buff[5]==buff[6]) && (buff[6]==sym)) ||
		((buff[7]==buff[8]) && (buff[8]==buff[9]) && (buff[9]==sym)) ||
		((buff[1]==buff[5]) && (buff[5]==buff[9]) && (buff[9]==sym)) ||
		((buff[7]==buff[5]) && (buff[5]==buff[3]) && (buff[3]==sym)) ||
		((buff[1]==buff[4]) && (buff[4]==buff[7]) && (buff[7]==sym)) ||
		((buff[2]==buff[5]) && (buff[5]==buff[8]) && (buff[8]==sym)) ||
		((buff[3]==buff[6]) && (buff[6]==buff[9]) && (buff[9]==sym))
	  )
		return 1;
	return 0;
}


void *func(void *data)
{
	struct threadData *sockfd;
	sockfd = (struct threadData *) data;
	char cbuff[MAX];
	int valid;
	//char buff[MAX]; //FORMAT : C123456789 
	//int n;
	
	
	pthread_mutex_lock(&mutex);
//	if(DEBUG) printf("in func. active thread %d\n", sockfd->myself);
	for (;;) 
	{
//		pthread_mutex_lock(&mutex);
		while(turn != sockfd->myself)
		{
				if(DEBUG) printf("in CONDWAIT before. active thread %d\n", sockfd->myself);
			pthread_cond_wait(&cond, &mutex);
				if(DEBUG) printf("in CondWait after. active thread %d\n", sockfd->myself);
		}
		
		while(1)
		{
			if(gameover == 1 || gameover == 2)
			{
				if(gameover == 1) 
					strcpy(cbuff, "other player WON\n");
				else if (gameover == 2)
					strcpy(cbuff, "Tie Game\n");
				write(sockfd->myself, cbuff, sizeof(cbuff));
				//printf("Player %c won\n", sockfd->symbol);
				break;
			}
			else 
			{
				bzero(cbuff, MAX);
				frameBuffer(sockfd->symbol=='X'?'1':'2', cbuff);
				if(DEBUG) printf("String to Client : %s", cbuff);
				write(sockfd->myself, cbuff, sizeof(cbuff));
			}
		
			bzero(cbuff, MAX);
				if(DEBUG) printf("in before READ active thread %d\n", sockfd->myself);
			read(sockfd->myself, cbuff, sizeof(cbuff));
				if(DEBUG) printf("in after READ active thread %d\n", sockfd->myself);
			printf("From Client : %s\tlength is %d\n",  cbuff, strlen(cbuff));
			//bzero(buff, MAX);
			//n=0;
			//while((buff[n++] = getchar()) != '\n');

			valid = validateInputFromClient(cbuff);
			printf("validate = %d\n", valid);
			if(valid == 0)
				continue;
			else if(valid == 1)
				break;
			else if(valid == 2)
				printf("Server Exit .. \n");
				break;
		} // while end
		if(DEBUG) printf("after while 1 validate = %d\n", valid);

		if(valid == 1 && gameover ==0)
		{
			integrateBuffer(cbuff, sockfd->symbol);	
		}
		
		gameover = winStrategy();
		printf("GAMEOVER : %d\n", gameover);
		if(gameover == 1)
		{
			strcpy(cbuff,"You Won\n");
			printf("Player %c won\n", sockfd->symbol);
		}
		else if(gameover == 2)
		{
			strcpy(cbuff, "Tie Game\n");
			printf("Tie Game\n");
		}
		else	
		{
			strcpy(cbuff,"Awaiting other player ... \n");
		}
			
		write(sockfd->myself, cbuff, sizeof(cbuff));
		
		turn = sockfd->otherPlayer;
		pthread_cond_broadcast(&cond);
		if (valid == 2) 
		{
			printf("Exiting thread %d,,, sockfd : %d \n" , pthread_self(), sockfd->myself);
			pthread_cancel(pthread_self());
			break;
		}
//		pthread_mutex_unlock(&mutex);
	}
	if(valid ==2) pthread_cancel(pthread_self());
	pthread_mutex_unlock(&mutex);
}
			

int main()
{
	int sockfd, connfd[2], len;
	struct sockaddr_in servaddr, cli;
	int count =1;
	///
	struct threadData td[2];
	pthread_t threads[2];

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);
	int rt;
	void *ret;
	///
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd ==-1) {
		printf("socket creation failed... \n");
		exit(0);
	}
	else
		printf("Socket successfully created .. %d \n", sockfd);
	bzero(&servaddr, sizeof(servaddr));
	
		if(DEBUG) printf("bzero done.. %u \n", &servaddr);

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);


	if((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) !=0)
	{
		printf("socket bind failed .. \n");
		exit(0);
	}
	else 
		printf("Socket successfully binded .. \n");

	if((listen(sockfd, 5)) !=0) 
	{
		printf("listen failed .. \n");
		exit(0);
	}
	else
		printf ("Server listeningg.... \n");
	len = sizeof(cli);

	///// ACCEPT the data packet from Client
	while(count<=2) 
	{
		int i = count-1;

		connfd[i] = accept(sockfd, (SA*)&cli, &len);
		if(DEBUG) printf("connfd ID : %d\n", connfd[i]);

		if(connfd <0)
		{
			printf("server accept failed.. \n");
			exit(0);
		}
		else
			printf("server accept the client.. \n");
		
		count++;
		td[i].myself = connfd[i];
	}
	printf("Connections created.. Spawning threads \n");
	turn = td[0].myself;
	td[0].symbol = 'X';
	td[1].symbol = 'O';
	initBoard();

	for(int i =0;i <2;i++)
	{
		td[i].otherPlayer = td[(i+1)%2].myself;

		if(DEBUG) printf ("threaddata : %d-- %d\n", td[i].myself, td[i].otherPlayer);

		rt = pthread_create(&threads[i], NULL, func, (void *)&td[i]);
		if (rt) 
		{
			printf("Error :unable to create thread... \n");
			exit(0);
		}
	}
	//func(connfd[1]);
	for (int i =0;i<2; i++)
		pthread_join(threads[i], &ret);

	close(sockfd);
}

