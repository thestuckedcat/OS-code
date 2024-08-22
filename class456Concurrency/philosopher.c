#include "thread.h"
#include <semaphore.h>

#define N 3
sem_t locks[N];

void Tphilosopher(int id) {
  int lhs = (N + id - 1) % N;
  int rhs = id % N;
  while (1) {
    sem_wait(&locks[lhs]);
    printf("T%d Got %d\n", id, lhs + 1);
    sem_wait(&locks[rhs]);
    printf("T%d Got %d\n", id, rhs + 1);
    sem_post(&locks[lhs]);
    sem_post(&locks[rhs]);
  }
}

int main(int argc, char *argv[]) {
  for (int i = 0; i < N; i++) {
      sem_init(&locks[i],0, 1);
  }
  for (int i = 0; i < N; i++) {
    create(Tphilosopher);
  }
}
