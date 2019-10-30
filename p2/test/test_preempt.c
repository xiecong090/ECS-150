/*
	test the preempt. to see if we can swtich between threads. we used the count to % 4 +1,
	the result will be in (1, 2, 3, 4). so every time its equal to thread's TID, the count
	+1. if the we don't switch bewteen threads, the output would be alway :I am in thread 4.
*/


#include <stdio.h>
#include <stdlib.h>

#include <uthread.h>


int count = 1;

int thread4(){
	while(1)
	{
		if(count > 20)
		{
			break;
		}
		if(uthread_self() == count%4+1)
		{
		printf("i am in thread %d\n",uthread_self());
		count++;
		}
	}
	return 0;
}


int thread3(){
	while(1)
	{
		if(count >  20)
		{
			break;
		}
		if(uthread_self() == count%4+1)
		{
		printf("i am in thread %d\n",uthread_self());
		count++;
		}
	}
	return 0;
}
	
int thread2(){

	while(1)
	{
		if(count > 20)
		{
			break;
		}
		
		if(uthread_self() == count%4+1)
		{
		printf("i am in thread %d\n",uthread_self());
		count++;
		}
	}
	return 0;
}

int thread1(){
	uthread_create(thread2, NULL);
	uthread_create(thread3, NULL);
	uthread_create(thread4, NULL);
	while(1)
	{
		if(count > 20)
		{
			break;
		}
		
		if(uthread_self() == count%4+1)
		{
		printf("i am in thread %d\n",uthread_self());
		count++;
		}
	}
	return 0;

}


int main(){
	uthread_join(uthread_create(thread1, NULL), NULL);

	return 0;
}
