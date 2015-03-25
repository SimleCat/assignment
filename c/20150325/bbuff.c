#include "bbuff.h"

sem_t sem_mutex;
sem_t sem_space;
sem_t sem_data;
queue_t *queue;

void bbuff_init(void){
	queue = (queue_t *)malloc(sizeof(queue_t));
	if (NULL == queue){
		perror("Error: Malloc failed in bbuff_init\n");
		return;
	}
	memset(queue, 0, sizeof(queue_t));
	sem_init(&sem_mutex, 0, 1);
	sem_init(&sem_space, 0, QUEUE_SIZE);
	sem_init(&sem_data, 0, 0);
}

void bbuff_blocking_insert(void *item){
	sem_wait(&sem_space);
	sem_wait(&sem_mutex);
	queue->buff[queue->rear] = item;
	if (queue->rear >= QUEUE_SIZE-1){
		queue->rear = 0;
	} else {
		queue->rear++;
	}
	sem_post(&sem_mutex);
	sem_post(&sem_data);
}

void *bbuff_blocking_extract(void){
	void * item = NULL;
	sem_wait(&sem_data);
	sem_wait(&sem_mutex);
	item = queue->buff[queue->front];
	if (queue->front >= QUEUE_SIZE-1){
		queue->front = 0;
	}else{
		queue->front++;
	}
	sem_post(&sem_mutex);
	sem_post(&sem_space);
	return item;
}

_BOOL bbuff_is_data_available(void){
	if (queue->front == queue->rear){
		return FALSE;
	}
	return TRUE;
}

void bbuff_destroy(void){
	sem_destroy(&sem_mutex);
	sem_destroy(&sem_space);
	sem_destroy(&sem_data);
	free(queue);
}