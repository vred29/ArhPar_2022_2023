#include <pthread.h>
#define QUEUE_SIZE 1000000
extern int P;
 
extern int gotTasks;
extern int putTasks;

typedef struct Task {
	pthread_mutex_t waitUntilFinished;
	void (*runTask)(void*);
	void* data;
}Task;

typedef struct myDataColor {
	int* colors;
	int step;
}myDataColor;

typedef struct myData {
	int* partialPath;
	int step;
	int dest;
}myData;

void forceShutDownWorkers();
void putTask(Task task);
void startWorkers();
void joinWorkerThreads();