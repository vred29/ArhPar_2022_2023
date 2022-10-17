#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	printf("Hello world from thread %i\n", thread_id);
	pthread_exit(NULL);
}

void* threadFunction2()
{
	printf("Salutare Planeta!\n");
	pthread_exit(NULL);
}


int main(int argc, char **argv)
{
	int P = 2;
	int i;
	void *status = NULL;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	pthread_create(&(tid[0]), NULL, threadFunction, &(thread_id[0]));
	pthread_create(&(tid[1]), NULL, threadFunction2, NULL);
	

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], &status);
		printf("%p\n",status); 
	}

	return 0;
}
