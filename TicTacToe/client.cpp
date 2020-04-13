
// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024


// structure for TICTACTOE
char array[9];


char* validateInput(char *hello, size_t inputLen)
{
	while(1){
		printf("HEY :Enter a number -- ");
		getline(&hello, &inputLen, stdin);
//		printf("strelen %u\n", strlen(hello));
		printf("hello[0] %c\n", hello[0]);

		if(strlen(hello)==2 && hello[0]>=49 && hello[0]<=57)
			return hello;
	}

}

void initArray() {
	for (int i=0;i< 9;i++)
		array[i] = '-';
}

void displayBoard()
{
	printf("Client (X) and Server (O)\n");
	for (int i =0; i<9;i++){
		if((i)%3 ==0) printf("\n");
		printf("\t %c", array[i]);
	}
	printf("\n");

}

// update Array with the provided numbers
void manipulateBoard(char *c, char source)
{
	int i;
	sscanf(c, "%d", &i); // Using sscanf
	array[i-1] = source;

	displayBoard();
}

// Driver code
int main() {
    int sockfd;
    char buffer[MAXLINE];
    //char *hello = "Hello from client";
    //char hello[MAXLINE];
    char *hello = NULL;
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("CLIENT : CONNECTION ESTABISHED\n" );

    printf("Intializing the board\n");
    initArray();
    displayBoard();

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n;
    socklen_t len;
    size_t inputLen =0;

   while (strlen(buffer)!=1 && buffer[0] !=0) {

    hello = validateInput(hello, inputLen);

    printf("Entered number %s\n", hello);
    sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,
            sizeof(servaddr));
    manipulateBoard(hello, 'X');

    printf("message sent.\n");

    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                MSG_WAITALL, (struct sockaddr *) &servaddr,
                &len);
    buffer[n] = '\0';
    printf("Server : %s\n", buffer);
    manipulateBoard(buffer, 'O');
   } // end while..

    close(sockfd);
    return 0;
}
