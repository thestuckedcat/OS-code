#include "thread.h"
#include <semaphore.h>

sem_t fill, empty;

void producer() {
  while (1) {
    sem_wait(&empty);
    printf("(");
    sem_post(&fill);
  }
}

void consumer() {
  while (1) {
    sem_wait(&fill);
    printf(")");
    sem_post(&empty);
  }
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  sem_init(&fill, 0, 0);
  sem_init(&empty, 0, atoi(argv[1]));
  for (int i = 0; i < 8; i++) {
    create(producer);
    create(consumer);
  }
}
