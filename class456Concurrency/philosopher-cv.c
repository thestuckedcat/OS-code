#include "thread.h"
#include <semaphore.h>
#include <stdio.h>
#include<string.h>
#define N 3

pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;

int available[N];

void Tphilosopher(int id) {
  int lhs = (id - 1) % N;
  int rhs = id % N;
  while (1) {
    pthread_mutex_lock(&lk);
    while(!(available[lhs] && available[rhs])){
	pthread_cond_wait(&cv, &lk);
    }
    available[rhs] = 0;
    available[lhs] = 0;

    pthread_mutex_unlock(&lk);
	

    printf("T%d Got %d\n", id, lhs + 1);
    printf("T%d Got %d\n", id, rhs + 1);


    pthread_mutex_lock(&lk);
    available[rhs] = 1;
    available[lhs] = 1;
    pthread_cond_broadcast(&cv);
    pthread_mutex_unlock(&lk);
  }
}

int main(int argc, char *argv[]) {

  memset(available, 1, sizeof(available));
  for (int i = 0; i < N; i++) {
    create(Tphilosopher);
  }
}
