#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
long long* v;
long long sum;

typedef struct thrContent{
	int thread_id;
	long long sum; 
} thrContent;


int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void* threadFunction(void *var)
{
	int thread_id = ((thrContent*)var)->thread_id;
	int i;

	int start = thread_id * (int)ceil((double)N/(double)P);
	int end = min(N,(thread_id+1)*(int)ceil((double)N/(double)P));
	//TODO MAKE OPERATIONS ON a SAFE
	for(i = start; i < end; i++)
	{
		((thrContent*)var)->sum += v[i];
	}	
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
	int i;

	pthread_t tid[P];
	thrContent vThr[P]; 

	for(i = 0;i < P; i++)
	{
		vThr[i].thread_id = i;
		vThr[i].sum = 0;
	}
		

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(vThr[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	for(i = 0; i < P; i++)
		sum += vThr[i].sum;

	print();
	
	return 0;
}
