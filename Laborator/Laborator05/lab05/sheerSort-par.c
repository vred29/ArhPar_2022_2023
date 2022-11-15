#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int P;
int doneVar;
int** mat;

pthread_barrier_t* barriers, *barriers2, *barriers3;

int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}


int cmp1(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return A-B;
}

int cmp2(const void *a, const void *b) {
	// DO NOT MODIFY
	int A = *(int*)a;
	int B = *(int*)b;
	return B-A;
}

int notDone()
{
    //compararea celui mai mare element de pe linia i cu cel mai mic de pe linia i+1
    for(int i=0;i<N-1;i++)
    {
        if(i%2 ==0) {
            //linia este para => ascendent(mic la mare)
            if(mat[i][N-1] > mat[i+1][N-1])
            {
                return 1;
            }
                
        }
        else {
            //linia este impara => desscendent(mare la mic)
            if(mat[i][0] > mat[i+1][0])
            {
                return 1;
            }
        }
    }
    return 0;
}

void* threadFunction(void *args)
{
	// PARALLELIZE ME
    int thread_id = *(int*)args;
    int i, start, end, itBar = 0, sorted, aux;
    start = thread_id * (int)ceil((double)N/(double)P);
	end = min(N,(thread_id+1)*(int)ceil((double)N/(double)P));
    // printf("Th %d, %d -> %d\n", thread_id, start, end);
	while(1)
    {
        for(i=start;i<end;i++)
        {
            if(i%2==0)
            {
                qsort(mat[i], N, sizeof(int), cmp1);
            }
            else
            {
                qsort(mat[i], N, sizeof(int), cmp2);
            } 
        }
        
        //aici bariera
        pthread_barrier_wait(&barriers[itBar]);
        if(thread_id == 0)
        {
            doneVar = notDone();
            // printf("done: %d\n", doneVar);
        }
        pthread_barrier_wait(&barriers2[itBar]);
        if(doneVar)
        {
            sorted=0;
            aux=0;
            //sortam crescator pe coloana
            while(!sorted) {
                sorted = 1;
                for(int j=start;j<end;j++)
                {
                    for(int i=0;i<N-1;i++)
                    {
                        if(mat[i][j] > mat[i+1][j]) {
                            aux =mat[i][j];
                            mat[i][j] = mat[i+1][j];
                            mat[i+1][j] = aux;
                            sorted = 0;
                        }
                    }
                }
            }
        }
        else
        {
            break;
        }
        //aici bariera
        pthread_barrier_wait(&barriers3[itBar]);
        itBar++;
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

void init()
{
	mat = malloc(sizeof(int *) * N);

	if(mat == NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i, j;
	for(i = 0; i < N; i++) {
		mat[i] = malloc(sizeof(int) * N);
		if(mat[i] == NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}
    srand(42);
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			mat[i][j] = rand()%(N*N);
		}
	}
}

void printAll()
{
	int i, j;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i\t",mat[i][j]);
		}
		printf("\n");
	}
}

void printVector()
{
	int i, j;
	for(i = 0; i < N; i++) {
        if(i%2 == 0)
        {
            for(j = 0; j < N; j++) {
			    printf("%i ",mat[i][j]);
		    }
        }
        else
        {
            for(j = N-1; j > -1; j--) {
			    printf("%i ",mat[i][j]);
		    }
        }
	}
    printf("\n");
}

void printPartial()
{
	printVector();
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
	int i, j, nrBar = 0;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
    pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

    nrBar = ceil(2.0 * (double)N * log2(N) * log2(sqrt((double)N))) + 1;
    // printf("%d\n", nrBar);
    barriers = malloc(sizeof(pthread_barrier_t) * nrBar );
	if(barriers == NULL)
		return -1;
	barriers2 = malloc(sizeof(pthread_barrier_t) * nrBar );
	if(barriers2 == NULL)
		return -1;
    barriers3 = malloc(sizeof(pthread_barrier_t) * nrBar );
	if(barriers3 == NULL)
		return -1;


    for(int i=0;i<nrBar;i++) {
		pthread_barrier_init(&barriers[i], NULL, P);
		pthread_barrier_init(&barriers2[i], NULL, P);
		pthread_barrier_init(&barriers3[i], NULL, P);
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
		pthread_barrier_destroy(&barriers3[i]);
	}

	return 0;
}
