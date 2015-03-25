#ifndef __COMMON_H__
#define __COMMON_H__

#define QUEUE_SIZE		10

typedef long s32;
typedef unsigned long u32;

typedef enum{
	TRUE=1,
	FALSE=0
}_BOOL;

typedef struct {
	int source_thread;
	double time_stamp_in_ms;
}candy_t;


#endif