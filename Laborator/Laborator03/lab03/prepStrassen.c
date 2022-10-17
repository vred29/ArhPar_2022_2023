#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int A11, A12, A21, A22, B11, B12, B21, B22;
int M1, M2, M3, M4, M5, M6, M7;
int C11, C12, C21, C22;
pthread_barrier_t barrier;

void* threadFunction1(void *var)
{
	M1 = (A11 + A22) * (B11 + B22);
	pthread_barrier_wait(&barrier);
}

void* threadFunction2(void *var)
{
	M2 = (A21 + A22) * B11;
	pthread_barrier_wait(&barrier);
}


void* threadFunction3(void *var)
{
	M3 = A11 * (B12 - B22);
	pthread_barrier_wait(&barrier);
}


void* threadFunction4(void *var)
{
	M4 = A22 * (B21 - B11);
	pthread_barrier_wait(&barrier);
}


void* threadFunction5(void *var)
{
	M5 = (A11 + A12) * B22;
	pthread_barrier_wait(&barrier);
}

void* threadFunction6(void *var)
{
	M6 = (A21 - A11) * (B11 + B12);
	pthread_barrier_wait(&barrier);
}
void* threadFunction7(void *var)
{
	M7 = (A12 - A22) * (B21 + B22);
	pthread_barrier_wait(&barrier);
}

void* threadFunctionC(void *var)
{
	pthread_barrier_wait(&barrier);
	C11 = M1 + M4 - M5 + M7;
	C12 = M3 + M5;
	C21 = M2 + M4;
	C22 = M1 - M2 + M3 + M6;
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
	A11 = 3213215;
	A12 = 5454;
	A21 = 5456;
	A22 = 9898;
	B11 = 54544;
	B12 = 90821;
	B21 = 9807879;
	B22 = 329132;
}

void printPartial()
{
	printf("%i %i %i %i \n", C11, C12, C21, C22);
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
	P = 8;
	pthread_t tid[P];
	int thread_id[P];

	long long i;
	pthread_barrier_init(&barrier, NULL, 8);

	pthread_create(&(tid[0]), NULL, threadFunction1, &(thread_id[0]));
	pthread_create(&(tid[1]), NULL, threadFunction2, &(thread_id[1]));
	pthread_create(&(tid[2]), NULL, threadFunction3, &(thread_id[2]));
	pthread_create(&(tid[3]), NULL, threadFunction4, &(thread_id[3]));
	pthread_create(&(tid[4]), NULL, threadFunction5, &(thread_id[4]));
	pthread_create(&(tid[5]), NULL, threadFunction6, &(thread_id[5]));
	pthread_create(&(tid[6]), NULL, threadFunction7, &(thread_id[6]));
	pthread_create(&(tid[7]), NULL, threadFunctionC, &(thread_id[7]));

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	print();
	pthread_barrier_destroy(&barrier);

	return 0;
}
