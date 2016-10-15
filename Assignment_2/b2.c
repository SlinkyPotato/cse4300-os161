#include <stdlib.h> // import standard library
#include <pthread.h> // import pthread library
#include <stdio.h> // import standard I/O library

#define NUM_PRODUCERS 2 // number of producers 
#define NUM_CONSUMERS 1 // number of consumers
#define NUM_ITEMS_PROCESSED 1000 // number of items to be processed by conumers and producers
#define QUEUE_SIZE 15

pthread_t producerThreads[NUM_PRODUCERS]; // arguments of producer thread
pthread_t consumerThreads[NUM_CONSUMERS]; // arguments of consumer thread
pthread_mutex_t mutex; // mutex variable used for sync

typedef struct threadArgs { // thread arguments
	int threadId;
} ThreadArgs;

ThreadArgs producerArgs[NUM_PRODUCERS]; // initialize producer arguments
ThreadArgs consumerArgs[NUM_CONSUMERS]; // initialize consumer arguments

void * produceItem(void *); // producer thread function
void * consumeItem(void *); // consumer thread function

int main(int argc, char const *argv[]) { // main thread
	pthread_attr_t attr; // attributes of the thread
	void *status; // status used with attribute

	// Initialize thread variables
	pthread_mutex_init(&mutex, NULL);
	pthread_attr_init(&attr);

	// Create producer threads
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (int i = 0; i < NUM_PRODUCERS; i++) {
		producerArgs[i].threadId = i + 1;
		int rc = pthread_create(&threads[i], &attr, produceItem, &producerArgs[i]);
		if (rc) {
			printf("An error has occured while trying to create a producer pthread.");
			exit(-1);
		}
	}
	
	// Create consumer threads
	for (int i = 0; i < NUM_CONSUMERS; i++) {
		consumerArgs[i].threadIs = i + 1;
		int rc = pthread_create(&threads[i], &attr, consumeItem, &consumerArgs[i]);
		if (rc) {
			printf("An error occured whiletrying to create a consumer thread.");
			exit(-1);
		}
	}

	// Wait for producer thread to finish
	for (int i = 0; i < NUM_PRODUCERS; i++) {
		int rc = pthread_join(threads[i], &status);
		if (rc) {
			printf("An error occured while trying to synchronize producers.");
			exit(-1);
		}
	}

	// Wait for consumer threads to finish
	for (int i = 0; i < NUM_CONSUMERS; i++) {
		int rc = pthread_join(threads[i], &status);
		if (rc) {
			printf("An error occured while trying to synchronize consumers.");
			exit(-1);
		}
	}

	// Clean up
	pthread_attr_destroy(&attr);
	pthread_mutex_destory(&mutex);
	printf("All threads finished their jobs");
	pthread_exit(NULL);
}

void * produceItem(void * threadArgs) {
	ThreadArgs *thread
}