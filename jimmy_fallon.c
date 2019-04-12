#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Prototypes
void* phonecall(void* vargp);
int next_id = 0;

int main() {
  int NUM_CALLERS = 10;
  sem_t operators;
  sem_init(&operators, 0, 3);

  sem_init(&lock, 0, 1);
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, phonecall, NULL);
  pthread_create(&tid2, NULL, phonecall, NULL);

  while (NUM_CALLERS > 0) {
    printf("here\n");
    pthread_t tid;
    pthread_create(&tid, NULL, phonecall, NULL);
    sleep(2);
    NUM_CALLERS--;
  }

  return 0;
}


void* phonecall(void* vargp) {
  static int NUM_OPERATORS = 3;
  static int NUM_LINES = 5;
  static int connected = 0;    // Callers that are connected
  static sem_t connected_lock;
  static sem_t operators;
  int id = next_id;

  if (connected == NUM_OPERATORS) {
    sem_wait(&operators);
  }
  connected++;
  next_id++;
  // Ticket ordering
  printf("Person: %i bought a ticket \n", id);
  //sleep(3);

  sem_post(&operators);
  connected--;
}
