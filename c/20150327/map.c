#include "map.h"

int map_insert(PMAP *phead, const char *key, const char *value){
	PMAP node = (PMAP) malloc(sizeof(MAP));
	if (NULL == node){
		perror("Error: malloc failed!\n");
		return 0;
	}
	memset(node, 0, sizeof(MAP));
	strcpy(node->key, key);
	strcpy(node->value, value);
	if (NULL == (*phead)){
		(*phead) = node;
	}else{
		node->next = (*phead)->next;
		(*phead)->next = node;		
	}
	return 1;
}

PMAP map_find(PMAP head, const char *key){
	while (NULL != head){
		if (strcmp(head->key, key) == 0){
			return head;
		}
		head = head->next;
	}
	return NULL;
}

void map_free(PMAP head){
	if (NULL == head){
		return;
	}
	PMAP node = head->next;
	while (node != NULL){
		head->next = node->next;
		free(node);
		node = head->next;
	}
	free(head);
}

void map_print(PMAP head){
	while (NULL != head){
		printf("<< %s %s\n", head->key, head->value);
		head = head->next;
	}
}

PMAP get_map(PMAP *phead, const char *filename){
	FILE *fp = fopen(filename, "r");
	if (NULL == fp){
		perror("Error: open file failed!\n");
		return NULL;
	}
	char buf[64] = {'\0'};
	while ( !feof(fp) ){
		fgets(buf, sizeof(buf), fp);
		buf[strlen(buf)-1] = '\0';
		// printf(">> [%s]\n", buf);
		char *key;
		char *value;
		key = strtok(buf, " ");
		value = strtok(NULL, " ");
		if (NULL != key && NULL != value){
			map_insert(phead, key, value);
		}
		memset(buf, 0, sizeof(buf));
	}
	return *phead;
}