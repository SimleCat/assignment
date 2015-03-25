#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "common.h"
#include "bbuff.h"
#include "stats.h"


_BOOL stop_thread = FALSE;
pthread_t *pthFac_id = NULL;
pthread_t *pthKid_id = NULL;

_BOOL check_argv(int argc, char **argv, int *pFac, int *pKid, int *pSec);
double current_time_in_ms(void);
void *thread_factory(void *arg);
void *thread_kid(void *arg);
void clean(void);


int main(int argc, char **argv){
	// 1.Extract Arguments
	int num_fac = 0;
	int num_kid = 0;
	int num_sec = 0;
	if (! check_argv(argc, argv, &num_fac, &num_kid, &num_sec)){
		perror("Error: All arguments must be positive.\n");
		return 1;
	}
	// printf("num_fac = %d, num_kid = %d, num_sec = %d\n", num_fac, num_kid, num_sec);

	// 2.Initialize Modules
	bbuff_init();
	stats_init(num_fac);
	pthFac_id = (pthread_t *)malloc(sizeof(pthread_t) * num_fac);
	pthKid_id = (pthread_t *)malloc(sizeof(pthread_t) * num_kid);
	if (NULL == pthFac_id || NULL == pthKid_id){
		perror("Error: Malloc failed\n");
		return 1;
	}
	
	// 3.Launch factory threads
	for (u32 i=0; i<num_fac; i++){
		int ret = pthread_create(&(pthFac_id[i]), NULL, thread_factory, (void *)i);
		if (ret != 0){
			perror("Error: Create pthread failed.\n");
			return 1;
		}
	}

	// 4.Launch kid threads
	for (u32 i=0; i<num_kid; i++){
		int ret = pthread_create(&(pthKid_id[i]), NULL, thread_kid, (void *)i);
		if (ret != 0){
			perror("Error: Create pthread failed.\n");
			return 1;
		}
	}

	// 5.Wait for requested time
	for (u32 i=0; i<num_sec; i++){
		sleep(1);
		printf("Time\t%lus:\n", i);
	}

	// 6.Wait for requested time
	stop_thread = TRUE;
	for (int i=0; i<num_fac; i++){
		pthread_join(pthFac_id[i], NULL);
	}

	// 7.Wait until no more candy
	while(bbuff_is_data_available()){
		printf("Waiting for all candy to be consumed.\n");
		sleep(1);
	}

	// 8.Stop kid threads
	printf("Stopping kids.\n");
	for (int i=0; i<num_kid; i++){
		pthread_cancel(pthKid_id[i]);
		pthread_join(pthKid_id[i], NULL);
	}

	// 9.Print statistics
	stats_display();

	// 10.Cleanup any allocated memory
	clean();
	return 0;
}

_BOOL check_argv(int argc, char **argv, int *pFac, int *pKid, int *pSec){
	if (argc != 4){
		return FALSE;
	}
	*pFac = atoi(argv[1]);
	*pKid = atoi(argv[2]);
	*pSec = atoi(argv[3]);
	if (*pFac <= 0 || *pKid <= 0 || *pSec <= 0){
		return FALSE;
	}
	return TRUE;
}

void *thread_factory(void *arg){
	u32 fac_no = (u32)arg;
	while(!stop_thread){
		int wait_time = rand()%4;
		printf("\tFactory %lu ship candy & wait %ds\n", fac_no, wait_time);
		candy_t *candy = (candy_t *)malloc(sizeof(candy_t));
		if (NULL == candy){
			perror("Error: Malloc failed in thread_factory\n");
			return NULL;
		}
		candy->source_thread = fac_no;
		candy->time_stamp_in_ms = current_time_in_ms();
		bbuff_blocking_insert(candy);
		stats_record_produced(fac_no);
		sleep(wait_time);
	}
	printf("Candy-factory %lu done\n", fac_no);
	return NULL;
}

void *thread_kid(void *arg){
	// u32 kid_no = (u32)arg;
	while(1){
		int wait_time = rand()%2;
		candy_t *candy = (candy_t *)bbuff_blocking_extract();
		double delay_in_ms = current_time_in_ms() - candy->time_stamp_in_ms;
		stats_record_consumed(candy->source_thread, delay_in_ms);
		free(candy);
		// printf("\tKid %lu eat a candy & wait %ds\n", kid_no, wait_time);
		sleep(wait_time);
	}
	return NULL;
}


double current_time_in_ms(void){
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}

void clean(void){
	free(pthFac_id);
	free(pthKid_id);
	bbuff_destroy();
	stats_cleanup();
}