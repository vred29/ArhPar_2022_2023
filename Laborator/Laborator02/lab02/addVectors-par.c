#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int P;
int* a;
int* b;
int* c;

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	// printf("Hello world from thread %d\n", thread_id);
	
	int start = thread_id * (int)ceil((double)N/(double)P);
	int end = min(N,(thread_id+1)*(int)ceil((double)N/(double)P));
	for(int j = 0; j < NReps; j++)
	{
		for(int i = start; i < end; i++)
		{
			c[i] = a[i] + b[i];
		}	
	}
	pthread_exit(0);
}

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

void init()
{
	a = malloc(sizeof(int) * N);
	b = malloc(sizeof(int) * N);
	c = malloc(sizeof(int) * N);
	if(a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i;
	for(i = 0; i < N; i++) {
		a[i] = i%500;
		b[i] = i%500;
	}
}

void printPartial()
{
	int i;
	for(i = 0; i < 10; i++)
		printf("%i ", c[i]);
	printf("\n");
	for(i = 20; i < N; i+=N/10)
		printf("%i ", c[i]);
	printf("\n");
	for(i = N - 10; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
}

void printAll()
{
	int i;
	for(i = 0; i < N; i++)
		printf("%i ", c[i]);
	printf("\n");
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
	int i, j;
	NReps = 100000;
	getArgs(argc, argv);
	init();

	pthread_t tid[P];
	int thread_id[P];

	
	for(i = 0;i < P; i++)
	{
		thread_id[i] = i;
	}

	//TODO paralelize me
	// for(j = 0; j < NReps; j++)
	// 	for(i = 0; i < N; i++)
	// 		c[i] = a[i] + b[i];

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &thread_id[i]);
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();

	return 0;
}
