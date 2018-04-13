/*------------------------------------------
  Real time chat using sockets and threads |
  ------------------------------------------*/
/* Server  side */
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
#include<pthread.h>

/*declaration of posix thread holders*/
pthread_t s,r;
/* Thread function declarations*/
void *sendthread();
void *recvthread();
int server_socket = 0, client_socket = 0,clen,serlen;
struct sockaddr_in serv_addr,client; 

char sendBuff[1024],recvBuff[1024],chat[1024]={0};

int main(int argc, char *argv[])
{

        /* socket creation in connected mode*/
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

        /*listening to the created socket*/
	listen(server_socket, 10); 
	clen = sizeof(client);
           /*Accepting the request from the clients*/
	if ((client_socket = accept(server_socket, (struct sockaddr *)&serv_addr, (socklen_t*)&clen))<0)
	{
		printf("Accept failed\n");
		close(server_socket);
		return 0;
	}
	/* Invoking "sendthread" function as a thread whose handle is "s" */
	pthread_create(&s,NULL,sendthread,NULL);

	/* Invoking "receivethread" function as a thread whose handle is "r" */
	pthread_create(&r,NULL,recvthread,NULL);
	pthread_join(s,NULL);
	pthread_join(r,NULL);
	while(1);
}
/*..................................CHAT STARTS HERE..............................*/
void *sendthread()
{
	while(1)
	{
		printf("Enter text to be sent to the client\n");
		gets(chat);
		write(client_socket ,chat, strlen(chat)+1 );
		memset(chat, '0', sizeof(chat)); 

	}
}
void *recvthread()
{
	while(1)
	{    read(client_socket ,recvBuff, 1000);
		printf("%70s%s\n","client:",recvBuff);


	}
}





