#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	//TODO Write code to make me run for at least a minute
	double x = __DBL_MAX__, y = 0;
	while(x!=y)
	{
		x = sqrt(x);
		
	}
}

int main(int argc, char **argv)
{
	int P = 4;
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

	return 0;
}
