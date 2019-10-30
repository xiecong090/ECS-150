#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>

#include "context.h"
#include "preempt.h"
#include "queue.h"
#include "uthread.h"
#define USHRT_MAX 65535

/* TODO Phase 2 */

static uthread_t NextTID = 0;
static queue_t readyQueue;
static struct TCB* runningThread;
static struct TCB* threadArray[USHRT_MAX];

enum state {ready, running, exited};

struct	TCB
{
	uthread_t tid;
	enum state status;
	ucontext_t* context;
	void* stack;
	int returnValue;
	bool joined;
	int blocked;
};

struct TCB* NewTCB(void)
{
	struct TCB *newTCB = (struct TCB*)malloc(sizeof(struct TCB));
	newTCB->tid = NextTID;
	newTCB->status = ready;
	newTCB->context = malloc(sizeof(ucontext_t));
	newTCB->stack = uthread_ctx_alloc_stack();
	newTCB->joined = false;
	return newTCB;
}

void initialization(void)
{
	queue_t q = queue_create();

	readyQueue = q;

	struct TCB* newThread = NewTCB();
	newThread->status = running;
	
	getcontext(newThread->context);
	
	threadArray[NextTID] = newThread;
	runningThread = threadArray[NextTID];
	
	preempt_start();
	
	
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
	struct TCB* newThread;
	struct TCB* currentThread = runningThread;
	if(queue_dequeue(readyQueue,(void*)&newThread) != -1)
	{
		newThread->status = running;
		runningThread = newThread;
		if(currentThread->status == ready || runningThread->status == running)
		{
			if(currentThread->tid != 0)
			{
				currentThread->status = ready;

				queue_enqueue(readyQueue,(void*)currentThread);
			}
			
		}
		
		preempt_disable();
		uthread_ctx_switch(currentThread->context, runningThread->context);	
		preempt_enable();
	}
	
}

uthread_t uthread_self(void)
{
	/* TODO Phase 2 */
	return runningThread->tid;
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */

	if(NextTID == 0)
	{
		initialization();
		
	}


	preempt_disable();
	NextTID++;
	struct TCB* newThread = NewTCB();
	newThread->tid = NextTID;
	
	if(newThread == NULL)
	{
		return -1;
	}
	
	if(newThread->tid > USHRT_MAX)
	{
		return -1;
	}
		
	 
	if(uthread_ctx_init(newThread->context, newThread->stack, func,arg) != 0)
	{
		return -1;
	}
	
	threadArray[NextTID] = newThread;
	
	queue_enqueue(readyQueue,newThread);


	preempt_enable();
	
	
	return	newThread->tid;
}

void uthread_exit(int retval)
{
	/* TODO Phase 2 */

	preempt_disable();

	runningThread->status = exited;
	runningThread->returnValue = retval;
	
	if(runningThread->joined != false)
	{
		queue_enqueue(readyQueue,threadArray[runningThread->blocked]);
	}
	
	preempt_enable();
	uthread_yield();
}

int uthread_join(uthread_t tid, int *retval)
{
	/* TODO Phase 2 */
	/* TODO Phase 3 */

	if(tid == 0 || tid == runningThread->tid || tid > NextTID || threadArray[tid]->status == exited || threadArray[tid]->joined == true)
	{
		return -1;
	}

	threadArray[tid]->blocked = runningThread->tid;
	runningThread->joined = true;
	
	uthread_yield();

	uthread_ctx_destroy_stack(threadArray[tid]->stack);

	
	if(retval != NULL)
	{
		*retval = threadArray[tid]->returnValue;
	}

	return 0;
}

