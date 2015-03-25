#ifndef __BBUFF_H__
#define __BBUFF_H__

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <malloc.h>
#include <memory.h>
#include "common.h"

typedef struct{
	void *buff[QUEUE_SIZE];
	int front;
	int rear;
}queue_t;

void bbuff_init(void);
void bbuff_blocking_insert(void *item);
void *bbuff_blocking_extract(void);
_BOOL bbuff_is_data_available(void);
void bbuff_destroy(void);

#endif