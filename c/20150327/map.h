#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include <memory.h>
#include <malloc.h>

#define KEY_SIZE				10
#define VALUE_SIZE				10

typedef struct map{
	char key[KEY_SIZE];
	char value[VALUE_SIZE];
	struct map *next;
}MAP, *PMAP;

int map_insert(PMAP *phead, const char *key, const char *value);
PMAP map_find(PMAP head, const char *key);
void map_free(PMAP head);
void map_print(PMAP head);
PMAP get_map(PMAP *phead, const char *filename);


#endif