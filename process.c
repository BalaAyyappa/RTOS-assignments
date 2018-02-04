/*Creating three processes and killing them using bash script*/
/*printing the addresses of the local variables of the three processes and to observe them*/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int g_1,g_2,g_3,x;
pid_t pid1, pid2,pid3;
void printvariable();
void main()
{
 int l_1,l_2,l_3;

printf("g_1=%x\ng_2=%x\ng_3=%x\n",&g_1,&g_2,&g_3);
printf("l_1=%x\nl_2=%x\nl_3=%x\n",&l_1,&l_2,&l_3);
printf("\n");
pid1=fork();
printf("pid1=%d\n",pid1);
FILE *fp;

if(pid1>=0)
 {
    if(0 == pid1)
     {
      printf("chiild process 1 global and local variables\n");
     printvariable();
     while(1);
     }
    else
     {
      fp=fopen("balu.sh","w");
      fprintf(fp,"%s ","kill");
     fprintf(fp,"%d\n",pid1);
      fclose(fp);
     pid2=fork();
    
     printf("pid2=%d\n",pid2);
     if(pid2>=0)
      {
      if(0 == pid2)
       {
        printf("chiild process 2 global and local variables\n");
       printvariable();
       while(1);
       }
      else
       {
      fp=fopen("balu.sh","a");
       fprintf(fp,"%s ","kill");
       fprintf(fp,"%d\n",pid2);
       fclose(fp);  
       pid3=fork();
        
      
       printf("pid3=%d\n",pid3);
       if(pid3>=0)
        {
        if(0 == pid3)
         {
         printf("chiild process 3 global and local variables\n");
         printvariable();
         while(1);
         }
        else
         {
       fp=fopen("balu.sh","a");
        fprintf(fp,"%s ","kill");
        fprintf(fp,"%d\n",pid3);
        x=getpid();
         fprintf(fp,"%s ","kill");
        fprintf(fp,"%d\n",x);
         fclose(fp);
        printf("parent pid=%d\n",x);
         while(1);
        }
         
        }
      }   
     }
  }
 }
}

void printvariable()
{
     int i,j,k;
    
     printf("g_1=%x\ng_2=%x\ng_3=%x\n",&g_1,&g_2,&g_3);
     printf("local1_1=%x\nlocal1_2=%x\nlocal1_3=%x\n",&i,&j,&k);
     printf("\n");
 }
/*observations*/

 /* 1.all the three child processes local variables have the same logical address.
    2.To get the physical address we need to add the offset to the logical address .
    3.So all the three child process have different offsets for their local variable addresses.
    4.So they will have different physical addresses but the same logical addresses.
  */
