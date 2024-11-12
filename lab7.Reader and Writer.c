#07]

#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

sem_t r,w;

int rcount=0;
void* reader(void* arg)
{
  sem_wait(&r);
  rcount++;
  if(rcount == 1){
    sem_wait(&w);
    
  }
  
 sem_post(&r);
 printf("\nReading Operation is performed");
 sem_wait(&r);
 rcount--;
 if(rcount == 0)
 {
   sem_post(&w);
   
  }
  
 sem_post(&r);
 return NULL;
 
}

void *writer (void* arg){
  sem_wait(&w);
  printf("\n Writing Operation is performed");
  sem_post(&w);
  return NULL;
  
}

 void main(){
  pthread_t Rtid[5];
  pthread_t Wtid[5];
  sem_init(&r,0,1);
  sem_init(&w,0,1);
  
for(int i=0;i<5;i++){
  pthread_create (&Wtid[i], NULL, writer , NULL);
   pthread_create (&Rtid[i], NULL, reader , NULL);
   
  }
  
 for(int i=0;i<5;i++){
   pthread_join(Rtid[i],NULL);
   pthread_join(Wtid[i],NULL);
   
 }
 
}     
      
//Output:- 	      
/*
student@student:~/Downloads$ gcc OS_Practical_07.c
student@student:~/Downloads$ ./a.out

 Writing Operation is performed
Reading Operation is performed
 Writing Operation is performed
Reading Operation is performed
Reading Operation is performed
Reading Operation is performed
 Writing Operation is performed
 Writing Operation is performed
Reading Operation is performed
 Writing Operation is performed

This code is a basic implementation of the Readers-Writers Problem using POSIX threads (pthreads) and semaphores in C. The goal is to handle concurrent access to a shared resource where multiple reader threads are allowed to read simultaneously, but only one writer thread is allowed to write at a time. This code is specifically an example of the first readers-writers problem, which gives priority to readers over writers.

Key Concepts in Readers-Writers Problem:
Readers: Threads that only read the shared resource. Multiple readers can read at the same time.
Writers: Threads that modify the shared resource. Only one writer can access the resource at a time, and no readers should access the resource while a writer is writing.
Semaphores: Used to manage concurrent access. Two semaphores are used in this code:
r semaphore: Controls access to the reader count (rcount).
w semaphore: Controls access to the shared resource for writing, allowing only one writer at a time.

 */