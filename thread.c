/*....Creating threads.......
and usage of semaphores in the synchronization of threads...*/


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
sem_t len;
int a,b,c;
void * Thread1proc()
{
sem_wait(&len);
int i=1,j=2,k=3;
a=i;b=j;c=k;
printf("the address of the variables in thread1 i=%x j=%x k=%x\n",&i,&j,&k);
printf("the values of global variables in Thread1 are a=%d b=%d c=%d\n",a,b,c);
sem_post(&len);
while(1);
}
void * Thread2proc()
{

int i=-1,j=-2,k=-3;
a=i;b=j;c=k;
printf("the address of the variables in thread2 i=%x j=%x k=%x\n",&i,&j,&k);
printf("the values of global variables in Thread2 are a=%d b=%d c=%d\n",a,b,c);
sem_post(&len);
while(1);
}
void * Thread3proc()
{ 
sem_wait(&len);
int i=-2,j=-3,k=-4;
a=i;b=j;c=k;
printf("the address of the variables in thread3 i=%x j=%x k=%x\n",&i,&j,&k);
printf("the values of global variables in Thread3 are a=%d b=%d c=%d\n",a,b,c);
sem_post(&len);
while(1);
}
int main()
{
int status;
pthread_t t1, t2,t3;
char *ptr ;
const int x = 100;
ptr = (char*) malloc(100);
printf("Address of pointer variable is %x\n ", &ptr);
printf("Address on heap is %x \n", ptr);
printf("Address on const is %x \n", &x);
printf("Address on global is %x \n", &len);
pthread_create(&t1,NULL,Thread1proc,NULL);
pthread_create(&t2,NULL,Thread2proc,NULL);
pthread_create(&t3,NULL,Thread3proc,NULL);
printf("Pthread1 value = %d\n", t1);
printf("Pthread2 value = %d\n", t2);
printf("Pthread3 value = %d\n", t3);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
pthread_join(t3,NULL);
}
/*observations*/

/*
  1.Only one thread can access the shared common data(like global variables),then one thread is using shared data,other threads remain 
    in wait(Locked) state with the use of sem_wait().
  2.if we put sem_wait() in the starting of the three processors then they will go to dead lock state.
  3.so one of the state should be free of sem_wait().
  4.so by using semaphores we can control the execution flow between the threads.
  5.global variables are shared by all threads and global variables addresses remain same in all threads.
  6.local variables are private to each thread, local variables of one thread can't be accessed by other threads.So addresses
   are different for different local variables of threads.
*/  
