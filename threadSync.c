//	Michael Cervantes
//	3/11/2023
//	Lab 6 - Producer Consumer Problems 
//	Description - Signaling from one Task to Another
//	

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 10
pthread_t threads[NTHREADS];
sem_t mutex;

void *go(void *arg)
{
   sem_wait(&mutex);
   printf("Thread %lu Entered Critical Section..\n", (size_t)arg);
   sleep(1);
   sem_post(&mutex);
   return (NULL);
}

int main()
{
   sem_init(&mutex, 0, 1);
   static int i;

   for (i = 0; i < NTHREADS; i++)
      pthread_create(&threads[i], NULL, go, (void *)(size_t)i);

   for (i = 0; i < NTHREADS; i++)
   {
      pthread_join(threads[i], NULL);
      printf("Thread %d returned \n", i);
   }

   printf("Main thread done.\n");
   sem_destroy(&mutex);

   return 0;
}
