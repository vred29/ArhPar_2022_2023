#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int** a;
int** b;
int** c;

pthread_mutex_t mutex; 

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void* threadFunction(void *args)
{
	// TODO: Implement parallel multiply of matrices: C = A * B
	// using P threads by splitting the inner loop.

	int thread_id = *(int*)args;
	int i,j,k, aux;
	int start = thread_id * (int)ceil((double)N/(double)P);
	int end = min(N,(thread_id+1)*(int)ceil((double)N/(double)P));
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {

			aux = 0;
			for(k = start; k < end; k++) {
			 	aux += a[i][k] * b[j][k];
			}
			pthread_mutex_lock(&mutex);
			c[i][j] += aux;
			pthread_mutex_unlock(&mutex);
			
		}
	}
	

	return NULL;
}

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N printLevel P\n");
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
	if(a == NULL || b == NULL || c == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i, j;
	for(i = 0; i < N; i++) {
		a[i] = malloc(sizeof(int) * N);
		b[i] = malloc(sizeof(int) * N);
		c[i] = malloc(sizeof(int) * N);
		if(a[i] == NULL || b[i] == NULL || c[i] == NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			c[i][j] = 0;
			if(i <= j) {
				a[i][j] = 1;
				b[i][j] = 1;
			}
			else {
				a[i][j] = 0;
				b[i][j] = 0;
			}
		}
	}
}

void printAll()
{
	int i, j;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i\t",c[i][j]);
		}
		printf("\n");
	}
}

void printPartial()
{
	printAll();
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
	int i, j, k, aux;
	getArgs(argc, argv);
	init();
	pthread_mutex_init(&mutex, NULL);
	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	//optimizarea memoriei/accesului la memorie in cea de a doua matrice (B)
	for(i = 0; i < N; i++) {
		aux = 0;
		for(j = i; j < N; j++) {
			aux = b[i][j];
			b[i][j]=b[j][i];
			b[j][i] = aux;
		}
	}


	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();
	pthread_mutex_destroy(&mutex);
	return 0;
}
