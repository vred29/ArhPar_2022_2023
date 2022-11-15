#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int printLevel;
int N;
int** mat;


void getArgs(int argc, char **argv)
{
	if(argc < 3) {
		printf("Not enough paramters: ./program N printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	printLevel = atoi(argv[2]);
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
                return 1;
        }
        else {
            //linia este impara => desscendent(mare la mic)
            if(mat[i][0] > mat[i][0])
                return 1;
        }
    }
    return 0;
}

void sortColumn()
{
    int sorted=0, aux=0;
    //sortam crescator pe coloana
    while(!sorted) {
		sorted = 1;
        for(int j=0;j<N;j++)
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

int main(int argc, char *argv[])
{
	int i, j;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY
    while(1)
    {
        for(int i=0;i<N;i++)
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
        if(notDone())
        {
            sortColumn();
        }
        else
        {
            break;
        }
    }

	print();

	return 0;
}
