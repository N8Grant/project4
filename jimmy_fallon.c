#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// Prototypes
void* phonecall(void* vargp);
void* queue(void* vargp);
int next_id = 0;
int NUM_CALLERS = 10;


int main(int argc, char **argv) {
  if (argc == 2) {
    NUM_CALLERS = atoi(argv[1]);
  }

  pthread_t tid;
  pthread_create(&tid, NULL, queue, NULL);

  return 0;
}

void* queue(void* vargp) {
  pthread_t calls[NUM_CALLERS];

  for (int i=0; i < NUM_CALLERS; i++) {
    pthread_create(&calls[i], NULL, phonecall, NULL);
  }
  for (int i = 0; i < NUM_CALLERS; i++) {
    pthread_join(calls[i], NULL);
  }

}


void* phonecall(void* vargp) {
  static int NUM_OPERATORS = 3;
  static int NUM_LINES = 5;
  static int connected = 0;    // Callers that are connected
  static sem_t connected_lock;
  static sem_t operators;
  int id = next_id;

  printf("Attempt to connect has been made\n");
  if (connected==NUM_LINES) {

  }
  else {
    if (sem_getvalue()) {

    }
    else {
      connected++;
      //exit critical section
    }
  }
  sem_wait(&operators);
  printf("Order is being taken by an operator\n");
  sleep(2);
  printf("Order is complete!!\n");
  connected--;
  print("Call has ended...\n");
  next_id++;
  // Ticket ordering
  printf("Person: %i bought a ticket \n", id);
  sleep(3);
  sem_post(&operators);
  connected--;
}
