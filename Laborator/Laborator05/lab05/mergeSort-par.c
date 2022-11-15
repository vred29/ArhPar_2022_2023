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

pthread_barrier_t* barriers, *barriers2;

void merge(int source[], int start, int mid, int end, int destination[]) {
	// DO NOT MODIFY
	int iA = start;
	int iB = mid;
	int i;

	for (i = start; i < end; i++)
	{
		if (end == iB || (iA < mid && source[iA] <= source[iB])) {
			destination[i] = source[iA];
			iA++;
		} else {
			destination[i] = source[iB];
			iB++;
		}
	}
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

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

void* threadFunction(void *args)
{
	// sort the vector v
	// PARALLELIZE ME
	int thread_id = *(int*)args;
	int i, width, *aux, start, end, itBar = 0;

	for (width = 1; width < N; width = 2 * width, itBar++) {
		//formulele de start/end
		start = thread_id * (int)ceil((double)N/(double)P);
		end = min(N,(thread_id+1)*(int)ceil((double)N/(double)P));

		//rotunjim la 2*w
		start = (2*width)* floor((double)start/ (double)(2*width)) ;
		end = (2*width)* floor((double)end/ (double)(2*width)) ;
		for (i = start; i < end; i = i + 2 * width) {
			merge(v, i, i + width, i + 2 * width, vNew);
		}
		//bariera 1 ca sa termine toate thr munca, apoi 1 singur thr va face update la v
		pthread_barrier_wait(&barriers[itBar]);
		if(thread_id == 0)
		{
			aux = v;
			v = vNew;
			vNew = aux;
		}
		//bariera ca sa nu se duca threadurile inainte de a face thr 0 update la v cu vNew
		pthread_barrier_wait(&barriers2[itBar]); 
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
	if(log2(N)!=(int)log2(N)) {
		printf("N needs to be a power of 2\n");
		exit(1);
	}
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
	int i, j, nrBar =0;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
	for(i = 0; i < N; i++)
		vQSort[i] = v[i];
	qsort(vQSort, N, sizeof(int), cmp);
	
	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	for (i = 1; i < N; i = 2 * i, nrBar++) {;}


	barriers = malloc(sizeof(pthread_barrier_t) * nrBar );
	if(barriers == NULL)
		return -1;
	barriers2 = malloc(sizeof(pthread_barrier_t) * nrBar );
	if(barriers2 == NULL)
		return -1;

	for(int i=0;i<nrBar;i++) {
		pthread_barrier_init(&barriers[i], NULL, P);
		pthread_barrier_init(&barriers2[i], NULL, P);
	}
	
	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}
	// displayVector(v);
	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	
	print();
	for(int i=0;i<nrBar;i++) {
		pthread_barrier_destroy(&barriers[i]);
		pthread_barrier_destroy(&barriers2[i]);
	}

	return 0;
}
