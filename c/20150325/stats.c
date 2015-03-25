#include "stats.h"

stats_t *stats = NULL;
int num_factory = 0;

void stats_init(int num_fac){
	num_factory = num_fac;
	stats = (stats_t *)malloc(sizeof(stats_t) * num_fac);
	if (NULL == stats){
		perror("Error: Malloc failed in stats_init\n");
		return;
	}
	memset(stats, 0, sizeof(stats_t) * num_fac);
}

void stats_record_produced(u32 fac_no){
	stats[fac_no].num_made++;
}

void stats_record_consumed(u32 fac_no, double delay_in_ms){
	stats[fac_no].num_eaten++;
	if (stats[fac_no].min_delay == 0.0 || stats[fac_no].min_delay > delay_in_ms){
		stats[fac_no].min_delay = delay_in_ms;
	}
	if (stats[fac_no].max_delay < delay_in_ms){
		stats[fac_no].max_delay = delay_in_ms;
	}
	stats[fac_no].total_delay += delay_in_ms;
}

void stats_display(void){
	printf("Statistics:\n");
	printf("%10s  %6s  %6s  %13s  %13s  %13s\n", "Factory#", "#Made", \
		"#Eaten", "Min Delay[ms]", "Avg Delay[ms]", "Max Delay[ms]");
	for (int i=0; i<num_factory; i++){
		printf("%10d  %6d  %6d  %13.5f  %13.5f  %13.5f\n", i, stats[i].num_made, stats[i].num_eaten, \
			stats[i].min_delay, stats[i].total_delay/stats[i].num_eaten, stats[i].max_delay);
	}
}

void stats_cleanup(void){
	free(stats);
}