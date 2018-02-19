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
    int listenfd = 0, connfd = 0,clen,serlen;
    struct sockaddr_in serv_addr,client; 

    char sendBuff[1024];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port =0; 
    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 
     serlen = sizeof(serv_addr);
   if (getsockname(listenfd, (struct sockaddr *) &serv_addr, &serlen) < 0)
   {
      
       exit(3);
   }

   printf("Port assigned is %d\n", ntohs(serv_addr.sin_port));


    listen(listenfd, 10); 
     clen = sizeof(client);

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)&client,&clen); 
       printf("Received message   from domain %s port %d internet\
 address %s\n",
       
       (client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
       ntohs(client.sin_port),

       inet_ntoa(client.sin_addr));
     printf("connection established\n");

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%s\r\n", ctime(&ticks));
        printf("%s\n",sendBuff);
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
}
