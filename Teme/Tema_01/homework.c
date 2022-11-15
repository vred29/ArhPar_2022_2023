#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef enum {
    nonfluid,
    fluid
}myCellType;

typedef struct MyCell
{
    myCellType type;
    double tmpr;
    char typeLiteral;
}MyCell;

int X,Y,Z;
int matType;
int N;
int P;
int doneVar;
MyCell** mat2, **mat2_tmp;
MyCell*** mat3 , ***mat3_tmp;
char* inFile, *outFile;

pthread_barrier_t* barriers1, *barriers2;



int min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}


double calc_tmpr(int row,int col)
{
    // avand in vedere ca am verificat inainte daca elem curent e fluid si ca si el e luat in calcul la medie,  daca e inconjurat de vecini nf, se final se imparte la 1 => ramane la fel
    double sum = 0;
    double nrOfFluidNeigh = 0;
    
    for(int i = max(0,row-1);i<= min(row+1,X-1);i++){
        for(int j = max(0, col-1); j <= min(col+1, Y-1);j++){
            if(mat2[i][j].type == fluid){
                sum+=mat2[i][j].tmpr;
                nrOfFluidNeigh++;
            }
        }
    }
    sum = sum / nrOfFluidNeigh;
    return sum;
}

double calc_tmpr_3d(int row,int col, int depth){
    // avand in vedere ca am verificat inainte daca elem curent e fluid si ca si el e luat in calcul la medie,  daca e inconjurat de vecini nf, se final se imparte la 1 => ramane la fel
    double sum = 0;
    double nrOfFluidNeigh = 0;
    
    for(int i = max(0,row-1);i<= min(row+1,X-1);i++){
        for(int j = max(0, col-1); j <= min(col+1, Y-1);j++){
            for(int k = max(0,depth-1); k<= min(depth+1, Z-1); k++){
                if(mat3[i][j][k].type == fluid){
                    sum+=mat3[i][j][k].tmpr;
                    nrOfFluidNeigh++;
                }    
            }
            
        }
    }
    sum = sum / nrOfFluidNeigh;
    return sum;
}

void* threadFunction(void *args)
{
	// PARALLELIZE ME
    int thread_id = *(int*)args;
    int start, end, itBar = 0;
    void* aux = NULL;

    start = thread_id * (int)ceil((double)X/(double)P);
	end = min(X,(thread_id+1)*(int)ceil((double)X/(double)P));
    
    if(matType == 2){
        for(int pas=0;pas<N;pas++, itBar++){
            // TODO 1: pentru liniile de la start la end, verifica vecinii si scrie si calculeaza rezultatul in slot-ul coresp din mat2_tmp 
            for(int i=start;i<end;i++){
                // TODO 1.1: functie calculare temp in functie de vecini
                for(int j=0;j<Y;j++){
                    if(mat2[i][j].type == fluid){
                        mat2_tmp[i][j].tmpr = calc_tmpr(i,j);
                    }
                }
            }

            pthread_barrier_wait(&barriers1[itBar]);
            // TODO 2: swap de pointeri la final doar de catre th 1
            if(thread_id == 0){
                aux = (void*)mat2;
                mat2 = mat2_tmp;
                mat2_tmp = (MyCell**)aux;
            }
            pthread_barrier_wait(&barriers2[itBar]);
        }
    }else{
        for(int pas=0;pas<N;pas++, itBar++){
            // TODO 1: pentru liniile de la start la end, verifica vecinii si scrie si calculeaza rezultatul in slot-ul coresp din mat2_tmp 
            for(int i=start;i<end;i++){
                // TODO 1.1: functie calculare temp in functie de vecini
                for(int j=0;j<Y;j++){
                    for(int k=0;k<Z;k++){
                        if(mat3[i][j][k].type == fluid){
                            mat3_tmp[i][j][k].tmpr = calc_tmpr_3d(i,j,k);
                        }
                    }
                    
                }
            }
            pthread_barrier_wait(&barriers1[itBar]);
            // TODO 2: swap de pointeri la final doar de catre th 1
            if(thread_id == 0){
                aux = (void*)mat3;
                mat3 = mat3_tmp;
                mat3_tmp = (MyCell***)aux;
            }
            pthread_barrier_wait(&barriers2[itBar]);
        }
    }
    
}


void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters:  ./homework INPUT_FILE OUTPUT_FILE NUM_THREADS\n");
		exit(1);
	}
	inFile = argv[1];
	outFile = argv[2];
    P = atoi(argv[3]);
}

void init2d()
{

	mat2= (MyCell**)malloc(sizeof(MyCell*) * X);
	mat2_tmp= (MyCell**)malloc(sizeof(MyCell*) * X);
    
	if(mat2 == NULL || mat2_tmp==NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i, j;
	for(i = 0; i < X; i++) {
		mat2[i] = (MyCell*)malloc(sizeof(MyCell) * Y);
        mat2_tmp[i] = (MyCell*)malloc(sizeof(MyCell) * Y);
        
		if(mat2[i] == NULL || mat2_tmp[i]==NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}
    
}

void init3d()
{

	//TODO
    mat3= (MyCell***)malloc(sizeof(MyCell**) * X);
	mat3_tmp= (MyCell***)malloc(sizeof(MyCell**) * X);
    
	if(mat3 == NULL || mat3_tmp==NULL) {
		printf("malloc failed!");
		exit(1);
	}

	int i, j;
	for(i = 0; i < X; i++) {
		mat3[i] = (MyCell**)malloc(sizeof(MyCell*) * Y);
        mat3_tmp[i] = (MyCell**)malloc(sizeof(MyCell*) * Y);
        
		if(mat3[i] == NULL || mat3_tmp[i]==NULL) {
			printf("malloc failed!");
			exit(1);
		}
        for(int j=0;j<Y;j++){
            mat3[i][j] = (MyCell*)malloc(sizeof(MyCell)*Z);
            mat3_tmp[i][j] = (MyCell*)malloc(sizeof(MyCell)*Z);
            if(mat3[i][j] == NULL || mat3_tmp[i][j]==NULL) {
                printf("malloc failed!");
                exit(1);
            }
        }
	}
}

void readFromFile()
{
    FILE* f= NULL;
    f= fopen(inFile, "r");
    if(f==NULL){
        printf("file open failed!");
		exit(1);
    }

    fscanf(f,"%d",&matType);
    if(matType==2){
        fscanf(f, "%d %d\n", &X,&Y);
        init2d();
        
        for(int j=0;j<Y;j++){
            for(int i=0;i<X;i++){
                fscanf(f, "%c %lf\n", &mat2[i][j].typeLiteral, &mat2[i][j].tmpr);
                if(mat2[i][j].typeLiteral == 'f'){
                    mat2[i][j].type = fluid;
                    mat2_tmp[i][j].type = fluid;
                }else{
                    mat2[i][j].type = nonfluid;
                    mat2_tmp[i][j].type = nonfluid;     
                }
                mat2_tmp[i][j].typeLiteral = mat2[i][j].typeLiteral;
                mat2_tmp[i][j].tmpr = mat2[i][j].tmpr;
            }
        }
    }else if (matType==3){
        fscanf(f, "%d %d %d\n", &X,&Y, &Z);
        init3d();
        //TODO: make 3d mat
        for(int k =0; k<Z;k++){
            for(int j=0;j<Y;j++){
                for(int i=0;i<X;i++){
                    fscanf(f, "%c %lf\n", &mat3[i][j][k].typeLiteral, &mat3[i][j][k].tmpr);
                    if(mat3[i][j][k].typeLiteral == 'f'){
                        mat3[i][j][k].type = fluid;
                        mat3_tmp[i][j][k].type = fluid;
                    }else{
                        mat3[i][j][k].type = nonfluid;
                        mat3_tmp[i][j][k].type = nonfluid;     
                    }
                    mat3_tmp[i][j][k].typeLiteral = mat3[i][j][k].typeLiteral;
                    mat3_tmp[i][j][k].tmpr = mat3[i][j][k].tmpr;
                }
            }
        }
    }
    fscanf(f,"%d", &N);

    fclose(f);
}

void writeToFile()
{
    FILE* f = NULL;
    f= fopen(outFile, "w");
    if(f==NULL){
        printf("file open failed!");
		exit(1);
    }
    
    if(matType == 2){
        fprintf(f,"%d %d %d\n", matType, X,Y);
        for(int j=0;j<Y;j++){
            for(int i=0;i<X;i++){
                fprintf(f, "%c %lf\n", mat2[i][j].typeLiteral, mat2[i][j].tmpr);
            }
        }
        
    }else{
        fprintf(f, "%d %d %d %d\n", matType, X,Y,Z);
        for(int k =0; k<Z;k++){
            for(int j=0;j<Y;j++){
                for(int i=0;i<X;i++)
                {
                    fprintf(f, "%c %lf\n", mat3[i][j][k].typeLiteral, mat3[i][j][k].tmpr);
                }
            }
        }
        
    }
    fclose(f);
}

void printMat()
{
    if(matType==2){
        for(int j=0;j<Y;j++){
            for(int i=0;i<X;i++){
                printf("%lf\t", mat2[i][j].tmpr);
            }
        }    
    }else{
        for(int k =0; k<Z;k++){
            for(int j=0;j<Y;j++){
                for(int i=0;i<X;i++)
                {
                    printf("%c %lf\n", mat3[i][j][k].typeLiteral, mat3[i][j][k].tmpr);
                }
            }
        }
        
    }
}

int main(int argc, char *argv[])
{
	int i, j;
	getArgs(argc, argv);
    readFromFile();
    // printMat();

    // DO NOT MODIFY
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

    writeToFile();

    for(int i=0;i<N;i++) {
		pthread_barrier_destroy(&barriers1[i]);
		pthread_barrier_destroy(&barriers2[i]);
	}
    
	return 0;
}
