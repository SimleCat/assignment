array_stats_testapp:array_stats_test.c process_ancestors_testapp
	gcc -std=c99 -D _GNU_SOURCE -static array_stats_test.c -o array_stats_testapp

process_ancestors_testapp:process_ancestors_test.c
	gcc -std=c99 -D _GNU_SOURCE -static process_ancestors_test.c -o process_ancestors_testapp

.PHONY:clean
clean:
	rm -rf array_stats_testapp process_ancestors_testapp

.PHONY:transfer
transfer:
	scp -P 2222 array_stats_testapp root@localhost:~/
	scp -P 2222 process_ancestors_testapp root@localhost:~/	