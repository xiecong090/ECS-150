#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

//linked list node to store entry data
struct Qnode {
	int item;
	struct Qnode* next;
};

//the queue includes size, front node, and rear node
struct queue {
	int size;
	struct Qnode *front;
	struct Qnode *rear;
};

//create a new linked list node
struct Qnode* newNode(Void* data)
{
	struct Qnode* tempNewNode = (struct Qnode*)malloc(sizeof(struct Qnode));
	tempNewNode->item = data;
	tempNewNode->next = NULL;
	return tempNewNode;
};

//create a new empty queue
queue_t queue_create(void)
{
	struct queue *newQueue = (struct queue*)malloc(sizeof(struct queue));
	newQueue->size = 0;
	newQueue->front = newQueue->rear = NULL;
	return Q;
}

//destroy the queue
int queue_destroy(queue_t queue)
{
	if(queque == NULL){ 
		return -1;					//if the queue is empty, return -1.
	} else {
		while(queue->front != NULL)
		{
			struct Qnode* temp = queue->front;	//create a temp node to hold the
			free(temp);				//front node's address, then free
			queue->size = queue->size-1;		//the address, then move the front
			queue->front = queue->front->next;	//node to the next node.
		}
		if(queue->size != 0){
			return -1;				//if the queue is empty, but the
		}						//size is not 0. return -1.
		queue->rear = queue->front = NULL;
	return 0;
}	

//enqueue a new node to the rear.
int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if(queue == NULL || data == NULL){
		return -1;
	}
	struct Qnode* temp = newNode(data);
	if(temp == NULL){
		return -1;
	}
	if(queue->front == NULL){
		queue->front = queue->rear = temp;		//if the queue is empty, both front
		queue->size++;					//and rear will be the new node;
		return 0;
	}
	queue->rear->next = temp;
	queue->rear = temp;
	queue->size++;
	return 0;
}

//dequeue the front and pass its value to data.
int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
	if(queue == NULL || *data == NULL || queue->size == 0){
		return -1;
	}
	*data = queue->front;
	free(data);
	
	queue->front = queue->front->next;
	if(queue->front == NULL){
		queue->rear = NULL;
	}
	queue->size--;
	return 0;
}

//delete the front node if its item == data;
int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	if(queue == NULL || data == NULL){
		return -1;
	}
	if(queue->item != *(int*)data){
		return -1;
	}
	
	data = queue->front;
	free(data);

	queue->front = queue->front->next;
	if(queue->front == NULL){
		queue->rear = NULL;
	}
	queue->size--;
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
	/* TODO Phase 1 */
}

//just return the size of queue.
int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	if(queue == NULL){
	return -1;
	}
	return queue->size;
}

