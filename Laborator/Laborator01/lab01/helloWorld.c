#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/sysinfo.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;
	printf("CONTOR %i\n", thread_id);
	int x = 1, y = 2;
	while(x!=y)
	{
		y++;
		x = y-x;
	}

	// for(int i=0;i<100;i++)
	// {
	// 	printf("Hello world from thread %i, iteration %i\n", thread_id, i);
	// }

}

int main(int argc, char **argv)
{
	
	int P = 4;     
	int i;

	//ex 3
	// P = 2;

	//ex 4
	P = 100;

	//ex 5
	// P = get_nprocs();  /* processors available can be less than proc conf by the os */
	
	
	//ex 6
	// P = 2;
	//ex 8
	P = 98156;

	pthread_t* tid = malloc(sizeof(pthread_t) * P);
	int* thread_id  = malloc(sizeof(int) * P);

	for(i = 0;i < P; i++)
		thread_id[i] = i;

	// printf("This system has %d processors configured and %d processors available.\n", get_nprocs_conf(), get_nprocs());
	int contor = 0;

	for(i = 0; i < P; i++) {
		if(pthread_create(&(tid[i]), NULL, threadFunction, &(contor)) == 0)
			contor++;
	}
	printf("%d\n", contor);
	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
	printf("%d\n", contor);

	return 0;
}
