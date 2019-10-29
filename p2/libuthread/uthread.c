#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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

enum state {ready, running, blocked, zombie};

struct	TCB
{
	uthread_t tid;
	enum state status;
	ucontext_t* context;
	void* stack;
	int returnValue;
	int joinThread;
};

struct TCB* NewTCB(void)
{
	struct TCB *newTCB = (struct TCB*)malloc(sizeof(struct TCB));
	newTCB->tid = NextTID;
	newTCB->status = ready;
	newTCB->context = malloc(sizeof(ucontext_t));
	newTCB->stack = uthread_ctx_alloc_stack();
	newTCB->joinThread = -1;
	return newTCB;
}

int initialization(void)
{
	queue_t q = queue_create();

	if(q == NULL)
	{
		return -1;
	}

	readyQueue = q;

	struct TCB* newThread = NewTCB();
	newThread->status = running;
	
	getcontext(newThread->context);
	
	threadArray[NextTID] = newThread;
	
	runningThread = newThread;
	
	NextTID++;
	return 0;
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
	struct TCB* newThread;
	
	if(queue_dequeue(readyQueue,(void*)&newThread) != -1)
	{
		if(runningThread->status != blocked && runningThread->status != zombie)
		{
			runningThread->status = ready;
			queue_enqueue(readyQueue,(void*)runningThread);
		}
		
		newThread->status = running;
		
		uthread_ctx_switch(runningThread->context, newThread->context);		//switch from current thread
		runningThread = newThread;						//to next ready thread
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
		return initialization();
		
	}
	
	struct TCB* newThread = NewTCB();
	
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
	
	queue_enqueue(readyQueue,newThread);

	threadArray[NextTID] = newThread;
	
	NextTID++;
	return	newThread->tid;
}

void uthread_exit(int retval)
{
	/* TODO Phase 2 */
	runningThread->status = zombie;
	runningThread->returnValue = retval;
	
	if(runningThread->joinThread != -1)
	{
		queue_enqueue(readyQueue,threadArray[runningThread->joinThread]);
	}
	
	uthread_yield();
}

int uthread_join(uthread_t tid, int *retval)
{
	/* TODO Phase 2 */
	/* TODO Phase 3 */
	if(tid == 0 || tid == runningThread->tid || tid > NextTID || threadArray[tid]->status == zombie || threadArray[tid]->status == blocked)
	{
		return -1;
	}

	threadArray[tid]->joinThread = runningThread->tid;
	runningThread->status = blocked;
	
	uthread_yield();
	
	if(retval != NULL)
	{
		*retval = threadArray[tid]->returnValue;
	}
	return 0;
}
