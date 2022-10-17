#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
long long* v;
long long sum;

pthread_mutex_t mutex; 


int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void* threadFunction(void *var)
{
	int thread_id = *(int *)var;
	int i;
	long long mySum = 0;

	int start = thread_id * (int)ceil((double)N/(double)P);
	int end = min(N,(thread_id+1)*(int)ceil((double)N/(double)P));
	//TODO MAKE OPERATIONS ON a SAFE
	for(i = start; i < end; i++)
	{
		mySum += v[i];
	}

	pthread_mutex_lock(&mutex);
	sum+=mySum;	
	pthread_mutex_unlock(&mutex);	
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

long long * allocVector(int N) {
	long long *v = malloc(sizeof(long long) * N);
	if(v == NULL) {
		printf("malloc failed!");
		exit(1);
	}
	return v;
}

void init()
{
	v = allocVector(N);

	int i;
	for(i = 0; i < N; i++) {
		v[i] = i+1;
	}
}

void printPartial()
{
	printf("Sum: %lli \n", sum);
}

void printAll()
{
	printPartial();
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
	pthread_mutex_init(&mutex, NULL);
	int i;

	pthread_t tid[P];
	int thread_id[P];

	for(i = 0;i < P; i++)
		thread_id[i] = i;

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
