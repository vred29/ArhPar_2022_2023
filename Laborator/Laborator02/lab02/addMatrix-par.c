#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int P;
int** a;
int** b;
int** c;

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void* threadFunction(void *var)
{
	int i, j, k;
	int thread_id = *(int*)var;

	// printf("Hello world from thread %d\n", thread_id);
	
	int start = thread_id * (int)ceil((double)N/(double)P);
	int end = min(N,(thread_id+1)*(int)ceil((double)N/(double)P));
	for( k = 0; k < NReps; k++)
	{
		for(i = start; i < end; i++)
		{
			for(j = 0; j< N ; j++)
			{
				c[i][j] = a[i][j] + b[i][j];
			}
		}	
	}
	pthread_exit(0);
}

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\nprintLevel: 0=no, 1=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
	P = atoi(argv[3]);
}

void init()
{
	a = malloc(sizeof(int *) * N);
	b = malloc(sizeof(int *) * N);
	c = malloc(sizeof(int *) * N);

	if (a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i, j;
	for (i = 0; i < N; i++) {
		a[i] = malloc(sizeof(int) * N);
		b[i] = malloc(sizeof(int) * N);
		c[i] = malloc(sizeof(int) * N);
		if (a[i] == NULL || b[i] == NULL || c[i] == NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			c[i][j] = 0;
			a[i][j] = i%500 + j%500;
			b[i][j] = i%500 + j%500;
		}
	}
}

void printAll()
{
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%d ", c[i][j]);
		}
		printf("\n");
	}
}

void print()
{
	if(printLevel == 0)
		return;
	else
		printAll();
}

int main(int argc, char *argv[])
{
	int i, j;
	NReps = 1;
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
