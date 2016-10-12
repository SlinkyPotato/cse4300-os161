#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Defined Functions
void * printThread(void *);

// Global Variables
#define NUM_THREADS 5
int last_threadID = 1;
pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex;

struct threadArgs {
  int threadId;
  int numOfCalls;
};

struct threadArgs threadArgsArray[NUM_THREADS];

int main(int argc, char const *argv[]) {
  int taskIds[NUM_THREADS];
  // struct threadArgs *threadData;
  void *status;
  pthread_attr_t attr;

  pthread_mutex_init(&mutex, NULL);

  // Create theads to perform calculation
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (int i = 0; i < NUM_THREADS; i++) {
    taskIds[i] = i + 1;
    threadArgsArray[i].threadId = taskIds[i];
    int rc = pthread_create(&threads[i], NULL, printThread, &threadArgsArray[i]);
    if (rc) {
      printf("An error has occured while trying to create a pthread.");
      exit(-1);
    }
  }
  pthread_attr_destroy(&attr);

  for(int i=0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], &status);
  }
  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);
}

void * printThread(void *pThreadArgs) {
  struct threadArgs *pthreadArgs = (struct threadArgs *) pThreadArgs;
  int threadId = pthreadArgs->threadId;
  int numOfCalls = threadArgsArray[threadId].numOfCalls;
  // printf("Outside numOfCalls: %d\n", threadId);
  // while (numOfCalls < 10) {
    pthread_mutex_lock(&mutex);
    int differenceThread = threadId - last_threadID;
    if (differenceThread == 0) {
      printf("My Turn: %d\n", threadId);
      threadArgsArray[threadId].numOfCalls = numOfCalls + 1;
    } else {
      printf("Not My Turn: %d\n", threadId);
    }
    last_threadID = (threadId == 5) ? 1 : threadId + 1;
    pthread_mutex_unlock (&mutex);
    pthread_exit((void*) 0);
  // }
}