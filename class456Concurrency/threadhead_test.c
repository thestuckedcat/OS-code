#include "thread.h"


void get_thread_id(int i){
	printf("%d\n",i);
}



int main(){
	for(int i = 0; i < 10;i++){
		create(get_thread_id);
	}
}
