#include <stdlib.h> // import standard library
#include <pthread.h> // import pthread library
#include <stdio.h> // import standard I/O library

#define NUM_PRODUCERS 2 // number of producers 
#define NUM_CONSUMERS 1 // number of consumers
#define NUM_ITEMS_PROCESSED 1000 // number of items to be processed by conumers and producers
#define QUEUE_LIMIT 15 // code includs offset
#define TRUE 1
#define FALSE 0

int buffer = 0; // buffer is initialize starting at 0
int itemsProduced = 0;
int itemsConsumed = 0;
int numProducerSleeps = 0;
int numConsumerSleeps = 0;

pthread_t producerThreads[NUM_PRODUCERS]; // arguments of producer thread
pthread_t consumerThreads[NUM_CONSUMERS]; // arguments of consumer thread
pthread_mutex_t mutex; // mutex variable used for sync
pthread_cond_t producerCond; // producer condition variable
pthread_cond_t consumerCond; // consumer condition variable

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
	pthread_cond_init(&producerCond, NULL);
	pthread_cond_init(&consumerCond, NULL);
	pthread_attr_init(&attr);

	// Create producer threads
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	for (int i = 0; i < NUM_PRODUCERS; i++) {
		producerArgs[i].threadId = i + 1;
		int rc = pthread_create(&producerThreads[i], &attr, produceItem, &producerArgs[i]);
		if (rc) {
			printf("An error has occured while trying to create a producer pthread.");
			exit(-1);
		}
	}
	
	// Create consumer threads
	for (int i = 0; i < NUM_CONSUMERS; i++) {
		int rc = pthread_create(&consumerThreads[i], &attr, consumeItem, &consumerArgs[i]);
		if (rc) {
			printf("An error occured while trying to create a consumer thread.");
			exit(-1);
		}
	}

	// Wait for producer threads to finish
	for (int i = 0; i < NUM_PRODUCERS; i++) {
		int rc = pthread_join(producerThreads[i], &status);
		if (rc) {
			printf("An error occured while trying to synchronize producers.");
			exit(-1);
		}
	}

	// Wait for consumer threads to finish
	for (int i = 0; i < NUM_CONSUMERS; i++) {
		int rc = pthread_join(consumerThreads[i], &status);
		if (rc) {
			printf("An error occured while trying to synchronize consumers.");
			exit(-1);
		}
	}

	// Clean up
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&producerCond);
	pthread_cond_destroy(&consumerCond);
	printf("Number of producers: %d\n Number of times producer went to sleep: %d", NUM_PRODUCERS, numProducerSleeps);
	printf("Number of consumers %d\n Number of times consumer went to sleep:  %d times.", NUM_CONSUMERS, numConsumerSleeps); 
	pthread_exit(NULL);
}

void * produceItem(void * pThreadArgs) {
	// ThreadArgs *threadArgs = (ThreadArgs *) pThreadArgs;
	int item;
	while (TRUE) {
		pthread_mutex_lock(&mutex); 
		if (buffer >= QUEUE_LIMIT) {
			numProducerSleeps += 1;
			pthread_cond_wait(&producerCond, &mutex); // put producer to sleep
		}
		item = 1; // generate item
		buffer += item;
		itemsProduced += 1;
		if (buffer == 1) pthread_cond_broadcast(&consumerCond); 
		pthread_mutex_unlock(&mutex);
		if (itemsProduced >= NUM_ITEMS_PROCESSED) pthread_exit(NULL); // exit when processed items is reached
	}
}

void * consumeItem(void * pThreadArgs) {
	int item;
	while (TRUE) {
		pthread_mutex_lock(&mutex);
		if (buffer <= 0) {
			numConsumerSleeps += 1;
			pthread_cond_wait(&consumerCond, &mutex);
		} 
		item = 1;
		buffer -= item;
		itemsConsumed += 1;
		if (buffer == QUEUE_LIMIT - 1) pthread_cond_broadcast(&producerCond);
		pthread_mutex_unlock(&mutex);
		if (itemsConsumed >= NUM_ITEMS_PROCESSED) pthread_exit(NULL); // exit when consumes items is reached
	}
}