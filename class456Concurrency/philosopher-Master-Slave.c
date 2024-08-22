#include "thread.h"
#include<semaphore.h>
#include<stdio.h>
#include<string.h>

#define N 5

enum STATE{
	REQUEST,
	RETURN,
	IDLE
};


enum STATE states[N+1];

int allowed[N+1];

pthread_mutex_t lk_state = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lk_allowed = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;
int forkState[N];
void Twaiter(){
	memset(forkState,1,sizeof(forkState));

	while(1){
		for(int i = 1; i <= N; i++){
			pthread_mutex_lock(&lk_state);
			//printf("%d Philosopher hold the state lock\n", i);
			if(states[i] == REQUEST){
				//printf("%d Philosopher is requesting forks\n", i);
				if(forkState[i-1] && forkState[i%N]){
					//printf("%d Philosopher get the forks\n", i);
					pthread_mutex_lock(&lk_allowed);
					forkState[i-1] = 0;
					forkState[i%N] = 0;
					allowed[i] = 1;
					states[i] = IDLE;					
					pthread_cond_broadcast(&cv);
					pthread_mutex_unlock(&lk_allowed);
				}
			}
			else if(states[i] == RETURN){
				//printf("%d Philosopher is returning forks\n",i);
				forkState[i-1] = 1;
				forkState[i%N] = 1;
				//allowed[i] = 0;
				states[i] = IDLE;
			}

			pthread_mutex_unlock(&lk_state);
		}
	}
}




void Tphilosopher(int id){
	while(1){
		// Modify state for requesti
		pthread_mutex_lock(&lk_state);

		states[id] = REQUEST;

		pthread_mutex_unlock(&lk_state);
		

		// sleep until license permited
		pthread_mutex_lock(&lk_allowed);
		while(!allowed[id]){
			pthread_cond_wait(&cv, &lk_allowed);
		}

		allowed[id] = 0;
		pthread_mutex_unlock(&lk_allowed);
		



		// hold forks, do something
		printf("%d Philosopher hold fork %d and %d\n", id, id-1, id%N);



		//sleep(1000);

		// Modify state for return
		pthread_mutex_lock(&lk_state);

		states[id] = RETURN;

		pthread_mutex_unlock(&lk_state);

		//sleep(1000);

	}
}




int main(){
	for(int i = 0; i <= N; i++){
		states[i] = IDLE;
		allowed[i] = 0;
	}

	for(int i = 0; i < N; i++){

		create(Tphilosopher);
	}

	create(Twaiter);


}
