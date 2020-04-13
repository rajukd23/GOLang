
// Server side implementation of UDP client-server model 
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
 
char array[9];
char* validateInput(char *hello, size_t inputLen)
{
        while(1){
                printf("HEY :Enter a number -- ");
                getline(&hello, &inputLen, stdin);
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
    //char hello[MAXLINE];// = "Hello from server"; 
    char *hello = NULL;
    struct sockaddr_in servaddr, cliaddr; 
      
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    }
   printf("Server started \n" );

    printf("Intializing the board\n");
    initArray();
    displayBoard();
 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int n; 
    socklen_t len;
    size_t inputLen=0;
    len = sizeof(cliaddr);  //len is value/resuslt 

    while(sizeof(buffer) !=1 && buffer[0]!=0)
    {
  
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
                MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Client : %s\n", buffer);
    manipulateBoard(buffer,'X'); 
//    printf("HEY : print next string - ");
    //scanf ("%s", hello);
 //   getline(&hello, &inputLen, stdin);
    hello = validateInput(hello, inputLen);
    sendto(sockfd, (const char *)hello, strlen(hello),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len);
    manipulateBoard(hello, 'O'); 
    printf("message sent.\n");  
    } // end while
      
    return 0; 
} 

