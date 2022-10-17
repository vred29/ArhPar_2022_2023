#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

int printLevel;
int N;
int P;
sem_t semaphore1, semaphore2, semaphore3;
int semaphore_value= 1;

void* threadFunction(void *var)
{
	//TODO preserve the correct order by using semaphores you will need to add a library and the correct flag when compiling
	int thread_id = *(int*)var;
	if(thread_id==0)
	{
		sem_wait(&semaphore3);
		printf("I should be displayed last\n");
	}
	else if(thread_id==1)
	{
		sem_wait(&semaphore1);
		printf("I should be displayed first or in the middle\n");
		sem_post(&semaphore2);
	}
	else if(thread_id==2)
	{
		sem_wait(&semaphore2);
		printf("I should be displayed first or in the middle\n");
		sem_post(&semaphore3);
	}
}

void getArgs(int argc, char **argv)
{

}

void init() 
{
}	

void printAll()
{
}

void printPartial()
{
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

int main(int argc, char *argv[])
{
	getArgs(argc, argv);
	init();

	P = 3; // ATTENTION, WE OVERWRITE THE NUMBER OF THREADS. WE ONLY NEED 3
	int i;

	pthread_t tid[P];
	int thread_id[P];

	sem_init(&semaphore1, 0, 1);
	sem_init(&semaphore2, 0, 0);
	sem_init(&semaphore3, 0, 0);
	
	for(i = 0;i < P; i++)
		thread_id[i] = i;
	//DO NOT EDIT
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	//DO NOT EDIT
	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	//DO NOT EDIT
	print();
	sem_destroy(&semaphore1);
	sem_destroy(&semaphore2);
	sem_destroy(&semaphore3);

	return 0;
}
