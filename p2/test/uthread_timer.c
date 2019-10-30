/*
	Tests timer interrupt by switching using timer between 3 threads 10 times


*/


#include <stdio.h>
#include <stdlib.h>

#include <uthread.h>


uthread_t current;
int count;

int thread3(){
	while(1){

		if(count > 10){
			break;
		}
		if(uthread_self() != current){
			count++;
			current = uthread_self();
			printf("Am in thread: %d\n", uthread_self());

		}

	}
	return 0;
}
int thread2(){

	while(1){
		if(count > 10){
			break;
		}

		if(uthread_self() != current){
			count++;
			current = uthread_self();
			printf("Am in thread: %d\n", uthread_self());
		}

	}
	return 0;
}

int thread1(){
	uthread_create(thread2, NULL);
	uthread_create(thread3, NULL);

	while(1){
		if(count > 10){
			break;
		}

		if(uthread_self() != current){
			count++;
			current = uthread_self();
			printf("Am in thread: %d\n", uthread_self());
		}

	}
	return 0;
}


int main(){
	current = 0;
	uthread_join(uthread_create(thread1, NULL), NULL);

	return 0;
}
