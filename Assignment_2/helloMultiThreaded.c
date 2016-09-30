#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *PrintHello(void *threadId) {
	long tId = (long) threadId;
	printf("Hello World! It's me, thread #%ld!\n", tId);
	pthread_exit(NULL);
}

int main(int argc, char*argv[]) {
	pthread_t threads[NUM_THREADS];
	long t;
	int rc;
	for (t = 0; t < NUM_THREADS; t++) {
		printf("In main: creating thread %ld\n", t);
		rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	pthread_exit(NULL); // last thing that main() should do to clean up
}