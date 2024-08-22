# include<stdio.h>

int sum;

void func2(int N){
	sum+=N;
}


void func1(){
	for(int i = 0; i < 100; i++){
		sum++;
	}

	int a = 1+1;


	func2(100);
}

int main(){
		
	sum = 0;

	func1();


	sum += 1;
}




