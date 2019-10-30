#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#include "preempt.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

struct sigaction act;
struct itimerval timer;

void yield_handler(int signum)
{
	uthread_yield();
}


void preempt_disable(void)
{
	/* TODO Phase 4 */
	sigset_t signal;
	sigemptyset(&signal);
	sigaddset(&signal,SIGVTALRM);
	sigprocmask(SIG_BLOCK, &signal, NULL);
}

void preempt_enable(void)
{
	/* TODO Phase 4 */
	sigset_t signal;
	sigemptyset(&signal);
	sigaddset(&signal,SIGVTALRM);
	sigprocmask(SIG_UNBLOCK, &signal, NULL);
}

void preempt_start(void)
{
	/* TODO Phase 4 */
	memset(&act, 0, sizeof(act));
	act.sa_handler = &yield_handler;

	sigaction(SIGVTALRM, &act, NULL);
	
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 100*HZ;

	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 100*HZ;

	setitimer(ITIMER_VIRTUAL, &timer, NULL);

}

