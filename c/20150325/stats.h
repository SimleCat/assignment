#ifndef __STARTS_H__
#define __STARTS_H__

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <malloc.h>
#include <memory.h>
#include "common.h"

typedef struct{
	int num_made;
	int num_eaten;
	double min_delay;
	double max_delay;
	double total_delay;
}stats_t;

void stats_init(int num_fac);
void stats_cleanup(void);
void stats_record_produced(u32 fac_no);
void stats_record_consumed(u32 fac_no, double delay_in_ms);
void stats_display(void);

#endif