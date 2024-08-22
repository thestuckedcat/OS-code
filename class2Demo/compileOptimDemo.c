
extern int g;

void foo(int x){
	g++;
	__sync_synchronize();
	g++;
}



