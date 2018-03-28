/* C Program for the design of the server which uses message Queues for simple mathematics */
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

 
/* structure for message queue*/
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;
 
int main()
{
    key_t key;		
    int msgid,len,a=0,i=0,x,y;
	char input[3];
	char operator;
	float output;
 
    /* ftok to generate unique key*/
    key = ftok("client-server", 65);
    /* msgget creates a message queue and returns identifier*/
    msgid = msgget(key, 0666 | IPC_CREAT);
 
    while(1)
	{
    /* msgrcv to receive message requests fro the clients,the first 0 argment represents it will serve the 1st message in the message queue*/
    	msgrcv(msgid, &message, sizeof(message), 0, 0);
    	    /* display the received message*/
    	printf("Data Received is : %s \n", message.mesg_text);
         /* decoding the message and calculating the result*/    
        for(i=0;i<3;i++)
		{
        	input[i]=message.mesg_text[i];
       		}
		operator=input[1];
                x=atoi(input);
                y=atoi(input+2);
		switch(operator)
		{
			case '+':
				output=x+y;
				break;
			case '-':
				output=x-y;
				break;

			case '*':
				output=x*y;
				break;
		    case '/':
                output=x/y;
				break;			
			default:
				printf("the operator is not valid\n");
                break; 
         }
			
       
      printf("output sent is %f\n",output);
        /* converting float to the string */
      gcvt(output, 5, message.mesg_text);
      /*specifies the lenth of the message sent*/
      len = strlen(message.mesg_text)+1;  
   
        
        if(msgsnd(msgid, &message,len , 0) == -1) 
            printf("\nmsgsnd");  
	   } 	
	 
    /* to destroy the message queue after the usage*/
    msgctl(msgid, IPC_RMID, NULL);
 
    return 0;
}
