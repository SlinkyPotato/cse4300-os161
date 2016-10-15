#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5 // number of threads

int last_threadID = 1; // global thread tracker

pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex;

typedef struct threadArgs { // arguments of threads
  int threadId;
  int numOfCalls;
} ThreadArgs;

ThreadArgs threadArgsArray[NUM_THREADS]; // arguments stored in array

// Defined Functions
void * printThread(void *); 

int main(int argc, char const *argv[]) {
  pthread_attr_t attr;
  void *status;
  
  // Initialize thread variables
  pthread_mutex_init(&mutex, NULL); // initialize mutex
  pthread_attr_init(&attr); // create threads to perform calculation
  
  // Create joinable threads
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  for (int i = 0; i < NUM_THREADS; i++) {
    threadArgsArray[i].threadId = i + 1;
    int rc = pthread_create(&threads[i], &attr, printThread, &threadArgsArray[i]);
    if (rc) {
      printf("An error has occured while trying to create a pthread.");
      exit(-1);
    }
  }
  
  // Wait for threads to finish
  for (int i = 0; i < NUM_THREADS; i++) {
    int rc = pthread_join(threads[i], &status);
    if (rc) {
      printf("An error occured while trying to synchronize threads.");
      exit(-1);
    }
  }
  
  // Clean up
  pthread_attr_destroy(&attr);
  pthread_mutex_destroy(&mutex);
  printf("All threads finished their jobs\n");
  pthread_exit(NULL);
}

void * printThread(void *pThreadArgs) {
  ThreadArgs *threadArgs = (ThreadArgs *) pThreadArgs; // cast object to Thread Args
  int *threadId = &threadArgs->threadId; // assigne ID to object that is pointed
  int *numOfCalls = &threadArgs->numOfCalls; // assign number of calls to object that is pointed at
  while (*numOfCalls < 10) { // while number of calls is less than 10
    pthread_mutex_lock(&mutex); // lock thread access using mutex
    int differenceThread = *threadId - last_threadID;
    if (differenceThread == 0) {
      printf("My Turn: %d\n", *threadId);
      last_threadID = (*threadId == 5) ? 1 : *threadId + 1;
      *numOfCalls = *numOfCalls + 1;
    } else {
      printf("Not My Turn: %d\n", *threadId);
    }
    pthread_mutex_unlock (&mutex);
    sleep(1);
  }
  pthread_exit(NULL);
}