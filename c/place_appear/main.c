#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <fcntl.h>

typedef struct place{
    char name[9];
	struct place *next;
}PLACE, *PPLACE;

typedef struct place_list{
	int num;
	PPLACE next;
	PPLACE tail;
}PLACE_LIST, *PPLACE_LIST; 

struct place_codes{
	int num;
	int code[10];
};

int isExists(PPLACE_LIST head, char *name);
void add(int num, char *name, PPLACE_LIST tables);
void print(PPLACE_LIST head);
void free_tables(PPLACE_LIST tables);

int study_file(char *file_name, PPLACE_LIST tables);
int getCodeFromString(char *str, struct place_codes *codes);
void printByCodes(PPLACE_LIST tables, struct place_codes *codes);

int main(){
	char file_name[50] = {'\0'};
	PLACE_LIST tables[10];
	struct place_codes codes;
	char codes_str[50] = {'\0'};
	int ret = 0;

	memset(tables, 0, sizeof(PLACE_LIST)*10);
	// memset(&codes, 0, sizeof(struct place_codes));

	printf("Please input a file`s name.\n");
	printf("(Mybe you need the test file \"table.txt\")\n");
	printf(">> ");
	scanf("%s", file_name);
	fflush(stdin);
	study_file(file_name, tables);
	// print(tables);

	while (1){
		printf("Please input the codes of places.\n");
		printf(">> ");
		ret = scanf("%49[^\n]", codes_str);
		fflush(stdin);
		if (0 == ret){
			break;
		}
		ret = getCodeFromString(codes_str, &codes);
		if (ret != 0){
			printf("Input error.\n");
			continue;
		}
		for (ret=0; ret<codes.num; ret++){
			printf("%d\n", codes.code[ret]);
		}
		printByCodes(tables, &codes);
	}

    free_tables(tables);

	return 0;
}

int study_file(char *file_name, PPLACE_LIST tables){
	FILE *fp = NULL;
	char ch = '\0';
	int cnt = 0;
	int line_cnt = 1;
	int flag = 0;
	char place_name[9];
	char place_code[3];

    fp = fopen(file_name, "r");
    if (NULL == fp){
        printf("The file \'%s\' can not open.\n", file_name);
        return 1;
    }
	while(ch = fgetc(fp)){
		if (EOF == ch){
			break;
		}else if (' ' == ch){
			if (cnt != 8){
				printf("Invaild format about place`s code: line %d.\n", line_cnt);
				return 1;
			}
			place_name[8] = '\0';
			cnt = 0;
			flag = 1;
		}else if ('\n' == ch){
			place_code[cnt] = '\0';
			cnt = atoi(place_code);
			if(cnt<1 || cnt>10){
				printf("Invaild format about place`s code: line %d.\n", line_cnt);
				return 1;
			}
			add(cnt, place_name, tables);
			line_cnt ++;
			flag = 0;
			cnt = 0;
		}else{
			if (0 == flag){
				if (cnt > 7){
					printf("Invaild format about place`s name: line %d.\n", line_cnt);
					return 1;
				}else{
					place_name[cnt] = ch;
				}
			}else{
				if (cnt > 1){
					printf("Invaild format about place`s code: line %d.\n", line_cnt);
					return 1;					
				}else{
					place_code[cnt] = ch;
				}
			}
			cnt ++;
		}
	}

	return 0;
}

int getCodeFromString(char *str, struct place_codes *codes){
	char *ch = str;
	char cnt = 0;
	char code_str[3];
	
	codes->num = 0;
	while(1){
		if (' '==*ch || '\0'==*ch){
			if (cnt <= 0){
			}else if (cnt >2){
				return 1;
			}else{
				code_str[cnt] = '\0';
				cnt = atoi(code_str);
				if (1<=cnt && cnt<=10){
					if (codes->num>=10){
						return 2;
					}
					codes->code[codes->num++] = cnt;
				}else{
					return 1;
				}
			}
			if('\0' == *ch){
				break;
			}
			cnt = 0;
		}else{
			if (cnt > 1){
				return 1;
			}
			code_str[cnt++] = *ch;
		}
		ch ++;
	}

	return 0;
}


int isExists(PPLACE_LIST head, char *name){
	PPLACE node = NULL;

	assert(NULL != head);
	node = head->next;
	while(NULL != node){
		if (strcmp(name, node->name) == 0){
			return 1;
		}
		node = node->next;
	}
	return 0;
}

void add(int num, char *name, PPLACE_LIST tables){
	PPLACE node = NULL;
	PPLACE_LIST head = tables+num-1;

	if (isExists(head, name)){
		return;
	}else{
		node = (PPLACE) malloc(sizeof(PLACE));
		strcpy(node->name, name);
		node->next = NULL;
		if (NULL == head->tail){
			head->next = head->tail = node;
		}else{
			head->tail->next = node;
			head->tail = node;
		}
		head->num ++;
	}
}

void print(PPLACE_LIST head){
	PPLACE node = NULL;

	assert(NULL != head);
	node = head->next;
	while(NULL != node){
		printf("%s\n", node->name);
		node = node->next;
	}
}

void free_tables(PPLACE_LIST tables){
	int i = 0;
	PPLACE node = NULL;

	for(i=0; i<10; i++){
		node = tables[i].next;
		while(NULL != node){
			tables[i].next = node->next;
			free(node);
			node = tables[i].next;
		}	
	}
}

void printByCodes(PPLACE_LIST tables, struct place_codes *codes){
	int cnt = 0;
	PPLACE node = NULL;
	int i;

	if (0 == codes->num){
	}else if(1 == codes->num){
		cnt = tables[codes->code[0]-1].num;
		print(tables+codes->code[0]-1);
	}else{
		node = tables[codes->code[0]-1].next;
		while(NULL != node){
			for(i=1; i<codes->num; i++){
				if(!isExists(tables+codes->code[i]-1, node->name)){
					break;
				}
			}
			if (i == codes->num){
				cnt ++;
				printf("%s\n", node->name);
			}
			node = node->next;
		}
	}

	printf("(num: %d)\n", cnt);
}