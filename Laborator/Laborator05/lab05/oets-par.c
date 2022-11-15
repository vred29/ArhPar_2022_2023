#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int* v;
int *vQSort;
int *vNew;

pthread_barrier_t* barriers1, *barriers2;

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
	int i,j, aux;
	int start, end;
	for(i = 0; i < N; i++) {
		
		start = thread_id * (int)ceil(((double)(N/2)/(double)P));
		end = min(N/2,(thread_id+1)*(int)ceil((double)(N/2)/(double)P));
		
		for(j = start; j < end; j++) {
			if(v[2*j] > v[2*j + 1]) {
				aux = v[2*j];
				v[2*j] = v[2*j + 1];
				v[2*j + 1] = aux;
			}
		}
		pthread_barrier_wait(&barriers1[i]);
		start = thread_id * (int)ceil(((double)((N-1)/2)/(double)P));
		end = min((N-1)/2,(thread_id+1)*(int)ceil((double)((N-1)/2)/(double)P));
		// printf("Buna ziua! %d %d\n", start,end);
		for(j = start; j < end; j++) {
			if(v[2*j+1] > v[2*j + 2]) {
				aux = v[2*j+1];
				v[2*j+1] = v[2*j + 2];
				v[2*j + 2] = aux;
			}
		}
		pthread_barrier_wait(&barriers2[i]);
	}
}

void compareVectors(int * a, int * b) {
	// DO NOT MODIFY
	int i;
	for(i = 0; i < N; i++) {
		if(a[i]!=b[i]) {
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int * v) {
	// DO NOT MODIFY
	int i;
	int max = 1;
	for(i = 0; i < N; i++)
		if(max<log10(v[i]))
			max = log10(v[i]);
	int displayWidth = 2 + max;
	for(i = 0; i < N; i++) {
		printf("%*i", displayWidth, v[i]);
		if(!((i+1) % 20))
			printf("\n");
	}
	printf("\n");
}

int cmp(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
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
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);
	vNew = malloc(sizeof(int) * N);
	if(v == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	// generate the vector v with random values
	// DO NOT MODIFY
	srand(42);
	for(i = 0; i < N; i++)
		v[i] = rand()%N;
}

void printPartial()
{
	int i;
	compareVectors(v, vQSort);
}

void printAll()
{
	displayVector(v);
	displayVector(vQSort);
	compareVectors(v, vQSort);
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
	int i, j, aux;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
	for(i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);

	//paralelise
	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	barriers1 = malloc(sizeof(pthread_barrier_t) * N );
	if(barriers1 == NULL)
		return -1;

	barriers2 = malloc(sizeof(pthread_barrier_t) * N );
	if(barriers2 == NULL)
		return -1;


	for(int i=0;i<N;i++) {
		pthread_barrier_init(&barriers1[i], NULL, P);
		pthread_barrier_init(&barriers2[i], NULL, P);
	}
		
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}


	print();
	for(int i=0;i<N;i++) {
		pthread_barrier_destroy(&barriers1[i]);
		pthread_barrier_destroy(&barriers2[i]);
	}
	return 0;
}
