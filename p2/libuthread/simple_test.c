#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void step1(void)
{
	printf("this is step 1\n");
}

void test_create(void)
{
    queue_t q;
    q = queue_create();
    assert(q != NULL);
	printf("create test successed!\n");
}

void test_destroy(void)
{
	queue_t q,q1;
    	q = queue_create();
	int i = queue_destroy(q);
	q1 = queue_create();
	int data = 3;
	queue_enqueue(q1,&data);
	int k = queue_length(q1);
	int j = queue_destroy(q1);
}

void test_queue_simple(void)
{
	printf("I am 1!\n");
    queue_t q;
	printf("I am 1.5!\n");
    int data = 3, *ptr;
	printf("I am 2!\n");
    q = queue_create();
	printf("I am 5!\n");
	printf("before enqueue, the ptr is %d\n",6);
    queue_enqueue(q, &data);
	printf("after enqueue, the ptr is %d\n",7);
    queue_dequeue(q, (void**)&ptr);
	printf("after dequeue, the ptr is %d\n",*ptr);
}

static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;
if (*a == match)
        return 1;

    return 0;
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);
    /* Add value '1' to every item of the queue */
    queue_iterate(q, inc_item, (void*)1, NULL);

    assert(data[0] == 2);

    /* Find and get the item which is equal to value '5' */
    ptr = NULL;
    queue_iterate(q, find_item, (void*)5, (void**)&ptr);
    assert(ptr != NULL);
    assert(*ptr == 5);	
    assert(ptr == &data[3]);
}

int main()
{
	step1();
	test_create();
	printf("hello!\n");
	test_queue_simple();
	printf("hello!\n");
	test_iterator();
	printf("everything is good!\n");
	test_destroy();
	printf("everything is great!\n");
	return 0;
}
