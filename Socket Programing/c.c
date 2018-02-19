#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main(int argc, char *argv[])
{
    int csockfd = 0,PORT;
    char recvBuff[1024],message[1024];
    struct sockaddr_in serv_addr; 
     char hostname[1024];
     hostname[1023] = '\0';
     gethostname(hostname, 1023);
     printf("Hostname: %s\n", hostname);
    
    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server>  <server port number>\n ",argv[0]);
        return 1;
    } 
     PORT=atoi(argv[2]);

    memset(recvBuff, '0',sizeof(recvBuff));
    if((csockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(csockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 
   
   /*..........................................CHAT STARTS HERE..........................*/   
    while(!(strcmp(recvBuff,"END")==0))
    {
         printf("Enter the data to be send to server\n");
         gets(message);
         write(csockfd, message, strlen(message)+1 );
         memset(message, '0', sizeof(message)); 
         read(csockfd, recvBuff, 1024);
         printf("Server: %s\n",recvBuff);         
    }
    /* Send END to client to indicate end of session */
    char dummy[] = "END\0";
    strcpy(message, dummy);
    write(csockfd ,message, strlen(message)+1);
 printf("Session ended with server\n");
    /* Close the socket */
    close(csockfd);
}

