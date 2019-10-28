#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "queue.h"

//linked list node to store entry data
struct Qnode {
	int item;
	struct Qnode* next;
};

//the queue includes size, front node, and rear node
struct queue {
	int size;
	struct Qnode* front;
	struct Qnode* rear;
};

//create a new linked list node
struct Qnode* newNode(void* data)
{
	struct Qnode* tempNewNode = (struct Qnode*)malloc(sizeof(struct Qnode));
	tempNewNode->item = *(int*)data;
	tempNewNode->next = NULL;
	return tempNewNode;
};

//create a new empty queue
queue_t queue_create(void)
{
	struct queue *newQueue = (struct queue*)malloc(sizeof(struct queue));
	newQueue->size = 0;
	newQueue->front = newQueue->rear = NULL;
	return newQueue;
}

//destroy the queue
int queue_destroy(queue_t queue)
{
	if(queue == NULL || queue->size != 0){ 
		return -1;					//if the queue is NULL, or its
	} else {						//size is not 0, return -1
		queue->front = queue->rear = NULL;
		free(queue);
	}
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
	if(queue == NULL || data == NULL || queue->size == 0){
		return -1;
	}
	struct Qnode* temp = queue->front;
	
	int* value = (int*)malloc(sizeof(int));
	*value = temp->item;
	free(temp);
	*data = value;
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
	if(queue->front->item != *(int*)data){
		return -1;
	}
	
	struct Qnode* temp = queue->front;
	free(temp);
 	 	
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
	if(queue == NULL || func == NULL){
		return -1;
	}

	struct Qnode* current = queue->front;
	void* nodeItem = &(current->item);
	while(current != NULL)
	{
		if(func(nodeItem,arg) == 1){
			*data = nodeItem;
			return 0;
		}
		current = current->next;
		nodeItem = &(current->item);
	}
	return 0;
	
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
