#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr


//Entered data should be a number.. or exit.
void takeValidInput(char *hello)//, size_t inputLen)
{
        while(1){
                // Get Input
                printf("HEY :Enter a number -- or \'exit\' ");
		int n=0;
		while((hello[n++] = getchar()) != '\n');
                //getline(&hello, &inputLen, stdin);
//              printf("strelen %u\n", strlen(hello));
                //printf("hello[0] %c\n", hello[0]);

                // check if the number is from 1 to 9
                if((strlen(hello)==2 && hello[0]>=49 && hello[0]<=57) || strncmp("exit", hello, 4) == 0)
			break;
                // check if the position is already used. 
                        //if (array[hello[0] == '-')
                            //    return hello;
        }

}

void func(int sockfd)
{
	char buff[MAX];
	int n;
	
	for (;;)
	{
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);
		
		if(strncmp(buff, "You Won", 7) ==0)
			break;
		else if(strncmp(buff, "other player WON", 16) ==0)
			break;
		else if(strncmp(buff, "Tie Game", 8) ==0)
			break;
		else if (strncmp(buff, "Awaiting other player ...", 25) ==0)
			continue;
	

		if((strncmp(buff, "exit", 4)) == 0) 
		{
			printf("Client Exit.. \n");
			exit(0);
		}
		bzero(buff, sizeof(buff));
		//n=0;
		//while((buff[n++] = getchar()) != '\n');
		takeValidInput(buff);
		write(sockfd, buff, sizeof(buff));
		if(strncmp(buff, "exit", 4) == 0) return;
		bzero(buff, sizeof(buff));
		//read(sockfd, buff, sizeof(buff));
		//printf("From Server : %s", buff);
		//if(strncmp(buff, "You Won", 7) ==0)
		//	break;
		//else if(strncmp(buff, "other player WON", 16) ==0)
		//	break;
		//else 
		//	continue;

	}
}


int main() 
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd ==-1)
	{
		printf("socket creation failed.. \n");
		exit(0);
	}
	else
		printf("Socket successfully created.. \n");
	
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// CONNECT the client to server
	if(connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) !=0) 
	{
		printf("connection with server failed.. \n");
		exit(0);
	}
	else
		printf("connected to the server... \n");
	
	func(sockfd);

	close(sockfd);
}

