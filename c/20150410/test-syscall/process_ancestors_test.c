#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "process_ancestors.h"

#define _PROCESS_ANCESTORS_		332


void print_process_info(struct process_info *info, long size){
	int i;
	for (i=0; i<size; i++){

		printf("pid=%ld, name=%s, state=%ld, uid=%ld, nvcsw=%ld, nivcsw=%ld, childrens=%ld, sibling=%ld\n", \
		(info+i)->pid, (info+i)->name, (info+i)->state, (info+i)->uid, (info+i)->nvcsw, (info+i)->nivcsw, (info+i)->num_children, \
		(info+i)->num_siblings);
	}
}

long test_syscall(long size, long *num_filled){
	struct process_info *info_array = NULL;

	if (size > 0){
		info_array = malloc(sizeof(struct process_info)*size);
	}
	long ret = syscall(_PROCESS_ANCESTORS_, info_array, size, num_filled);
	printf("size=%ld, num_filled=%ld, ret=%ld\n", size, *num_filled, ret);
	if (info_array != NULL){
		print_process_info(info_array, *num_filled);
		free(info_array);
	}
	printf("\n");

	return ret;
}

void test_create_process(long num_fork, long size){
	long num_filled;
	int state;
	pid_t pid;
	long i, ret;
	assert(num_fork >= 0);

	if (num_fork == 0){
		ret = test_syscall(size, &num_filled);
		return;
	}

	// Create Process
	pid = fork();
	if (pid != 0){

		waitpid(pid, &state, 0);
		return;
	}
	for (i=1; i<num_fork; i++){
		pid = fork();
		if (pid != 0){
			waitpid(pid, &state, 0);
			exit(0);
		}
	}
	if (pid == 0){
		ret = test_syscall(size, &num_filled);
		exit(0);
	}
}

int main(int argc, char *argv[]){
	printf("***************************\n");
	printf("* Do not create process   *\n");
	printf("***************************\n");
	test_create_process(0, 0);
	test_create_process(0, 1);
	test_create_process(0, 5);

	printf("***************************\n");
	printf("* Create 1 process        *\n");
	printf("***************************\n");
	test_create_process(1, 0);
	test_create_process(1, 3);
	test_create_process(1, 6);

	printf("***************************\n");
	printf("* Create 3 process        *\n");
	printf("***************************\n");
	test_create_process(3, 5);
	test_create_process(3, 10);

	printf("***************************\n");
	printf("* Create 5 process        *\n");
	printf("***************************\n");
	test_create_process(3, 6);
	test_create_process(3, 12);

	return 0;
} 