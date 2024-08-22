#include "thread.h"
#include <semaphore.h>

int n, count = 0;

pthread_mutex_t lk = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cv = PTHREAD_COND_INITIALIZER;


void Tproduce(){
	while(1){
		pthread_mutex_lock(&lk);
		while(count == n){
			pthread_cond_wait(&cv,&lk);
		}
		assert(count != n);
		printf("(");
		count++;
		//printf("%d\t", count);
		pthread_cond_signal(&cv);
		pthread_mutex_unlock(&lk);
	}
}


void Tconsume(){
	while(1){
		pthread_mutex_lock(&lk);
		while(count == 0){
			pthread_cond_wait(&cv,&lk);
		}
		assert(count != 0);
		printf(")");
		count--;
		//printf("%d\t",count);
		pthread_cond_signal(&cv);
		pthread_mutex_unlock(&lk);
	}
}



int main(int argc, char* argv[]){
	assert(argc==2);
	n=atoi(argv[1]);
	setbuf(stdout,NULL);
	for(int i = 0; i < 8; i++){
		create(Tproduce);
		create(Tconsume);
	}
}


