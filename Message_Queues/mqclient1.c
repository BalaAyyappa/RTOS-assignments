/* C program for the design of the client1 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
 
/* structure for message queue*/
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
 
int main()
{
    key_t key;
    int msgid,mlen;
 
   /* ftok to generate unique key*/
    key = ftok("client-server", 65);
     
   /* msgget creates a message queue and returns identifier*/
    msgid = msgget(key, 0666 | IPC_CREAT);
   /* this message type is used get message intended by the client*/
    message.mesg_type = 1;
 
    printf("Write the expression to be calculated(eg:2+3) : ");
    gets(message.mesg_text);
    /* mlen specifies the valid length of the data in mesg_text*/
    mlen = strlen(message.mesg_text) + 1;
    /* msgsnd to send message*/
    if (msgsnd(msgid, &message, mlen, 0) == -1)
         printf("\nmsgsnd"); 
     /* display the message  */
    printf("Data send is : %s \n", message.mesg_text);
 
    /* msgrcv to receive the  message */
    msgrcv(msgid, &message, sizeof(message), 0, 0);
    printf("\nResult calculated by the  server is %s",message.mesg_text); 

    return 0;
}
