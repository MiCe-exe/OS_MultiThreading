//	Michael Cervantes
//	3/11/2023
//	Lab 6 - Producer Consumer Problems 
//	Description - Signaling from one Task to Another
//	

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 26
#define NUM_THREAD 2

char currChar = 'A';
sem_t empty;
sem_t full;
sem_t mutex;
int buffer[MAX];
int fill = 0;
int use = 0;
//int *counter = 0;

void put(int c)
{
	buffer[fill] = c;
	fill = (fill + 1) % MAX;
}

int get()
{
	int tmp = buffer[use];
	use = (use + 1) % MAX;
	return tmp;
}

void *producer(void *arg)
{

	int j = arg;

	while(j <= 'Z')
	{	
		sem_wait(&empty);
		sem_wait(&mutex);
		put(j);
		sem_post(&mutex);
		sem_post(&full);
		//printf("Producer: %c\n", j);		//check J value
		j++;
	}
}

void *consumer(void *arg)
{
	int tmp = 0;	
	int k = 0;
	while(k < 26)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		tmp = get();
		sem_post(&mutex);
		sem_post(&empty);
		printf("%c\n", tmp);
		k++;
	} 

}

int main()
{
	pthread_t prod_tid;
	pthread_t con_tid;
	
	sem_init(&empty, 0, MAX);
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);


	pthread_create(&prod_tid, NULL, producer, (void *)(size_t)currChar);	
	pthread_create(&con_tid, NULL, consumer, (void *)buffer);
		
	
	pthread_join(prod_tid, NULL);
	pthread_join(con_tid, NULL);
	
	printf("\nMain end\n");
		
	sem_destroy(&empty);
	sem_destroy(&full);
	sem_destroy(&mutex);
	return 0;
}


