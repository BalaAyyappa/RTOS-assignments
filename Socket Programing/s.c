#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int server_socket = 0, client_socket = 0,clen,serlen;
    struct sockaddr_in serv_addr,client; 

    char sendBuff[1024],recvBuff[1024],chat[1024]={0},clock[128];
    time_t ticks; 

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port =0; 
    bind(server_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
     serlen = sizeof(serv_addr);
   if (getsockname(server_socket, (struct sockaddr *) &serv_addr, &serlen) < 0)
   {
      
       exit(3);
   }

   printf("Port assigned is %d\n", ntohs(serv_addr.sin_port));


    listen(server_socket, 10); 
     clen = sizeof(client);

     if ((client_socket = accept(server_socket, (struct sockaddr *)&serv_addr, (socklen_t*)&clen))<0)
    {
        printf("Accept failed\n");
        close(server_socket);
        return 0;
    }
   /*..................................CHAT STARTS HERE..............................*/
    read(client_socket ,recvBuff, 1000);
    printf("client: %s\n",recvBuff);

    /* Chat until receives a END from client */
    while(!(strcmp(recvBuff,"END")==0))
    { 
      
        printf("Enter text to be sent to the client\n");
        gets(chat);
        write(client_socket ,chat, strlen(chat)+1 );
        memset(chat, '0', sizeof(chat)); 
        read(client_socket ,recvBuff, 1000);
        printf("client:%s\n",recvBuff);
    }
    
    /* Send END to Server to indicate end of session */
    char dummy[] = "END\0";
    strcpy(chat, dummy);
    write(client_socket, chat, strlen(chat)+1);

    printf("Session ended with client\n");
   
    /* Close both the sockets */
    close(server_socket);
    close(client_socket);
    return 0;    

 }

