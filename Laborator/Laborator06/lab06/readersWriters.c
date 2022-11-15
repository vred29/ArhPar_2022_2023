#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
int printLevel;

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

int resource = 0;
int countReaders = 0;
int read_write_check = 0;
int write_write_check = 0;
int read_read_check = 0;
pthread_mutex_t Wmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t Rmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t RWmutex = PTHREAD_MUTEX_INITIALIZER;


int get() {
	read_read_check += 2;
	pthread_mutex_lock(&RWmutex);
	read_write_check += 2;
	pthread_mutex_unlock(&RWmutex);
	return resource;
}

void put(int value) {
	write_write_check += 2;
	read_write_check += 2;
	resource = value;
}


//HERE IS WHERE YOU NEED TO IMPLEMENT YOUR SOLUTION
int get_safe() {
	int aux;

	pthread_mutex_lock(&Rmutex);
	countReaders++;
	if(countReaders == 1)
		pthread_mutex_lock(&Wmutex);
	pthread_mutex_unlock(&Rmutex);

	aux = get();
	return aux;
}

void put_safe(int value) {
	pthread_mutex_lock(&Wmutex);
	put(value);
	pthread_mutex_unlock(&Wmutex);
}
//END HERE IS WHERE YOU NEED TO IMPLEMENT YOUR SOLUTION


int value;
void* readerThread(void *var)
{
	int i;

	for (i = 0; i < N; i++) {
		value = get_safe();
		pthread_mutex_lock(&Rmutex);
		countReaders--;
		if(countReaders == 0)
			pthread_mutex_unlock(&Wmutex);
		pthread_mutex_unlock(&Rmutex);
	}

	return NULL;
}

void* writerThread(void *var)
{
	int i;

	for (i = 0; i < N; i++) {
		put_safe(i);
	}

	return NULL;
}

int main(int argc, char **argv)
{
	getArgs(argc, argv);

	int i;
	int NREAD=P;
	int NWRITE=P;
	pthread_t tid[NREAD+NWRITE];

	for(i = 0; i < NREAD; i++) {
		pthread_create(&(tid[i]), NULL, readerThread, NULL);
	}

	for(; i < NREAD+NWRITE; i++) {
		pthread_create(&(tid[i]), NULL, writerThread, NULL);
	}

	for(i = 0; i < NREAD+NWRITE; i++) {
		pthread_join(tid[i], NULL);
	}

	if(N * 2 * P == read_read_check && P > 1) { //n ar trb sa fie diferit de N*2*P? -- implementarea nu e eficienta, accesul este 
	// oferit read-read, dar este modificata o variabila globala - "read_read_check" - la iteratii putine nici nu apare conditia de racing
	// la rulari de mana (nu cu scriptul); pe de alta parte citirea poate fi efectuata simultan prin "return resource"
		printf("Failed two simultaneous readers %d\n", read_read_check);
		return 1;
	}
	if(N * 2 * P * 2 != read_write_check) {
		printf("Failed read when write %i %i \n", N * 2 * P * 2, read_write_check);
		return 1;
	}
	if(N * 2 * P != write_write_check) {
		printf("Failed write when write\n");
		return 1;
	}
	printf("Passed all\n");

	return 0;
}
