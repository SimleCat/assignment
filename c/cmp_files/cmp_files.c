#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <fcntl.h>

// 存放单词位置信息
struct location{
    int row; // 行
    int column; //列
    struct location *next;
};

// 存放单词信息(单词不重复)
typedef struct eachword{
    char *content; // 单词内容
    int num; // 该单词出现多少次
    struct location *loc; // 单词都存放在哪里
    struct eachword *next;
}EACHWORD, *PEACHWORD;

// 存放单词信息(按位置顺序存放，可重复)
typedef struct myword{
    char *content; // 单词内容
    int row; //行
    int column; //列
    struct myword *next;
}MYWORD, *PMYWORD;

// 存放连续重复单词
typedef struct repeatword{
    PMYWORD node_start; // 连续重复单词的第一个单词
    int repeat_num; // 连续单词的个数
    struct repeatword *next;
}REPEATWORD, *PREPEATWORD;

// 文件的单词的信息
struct files_info{
    char *file_name[2]; // 两个文件名
    PMYWORD head_myword[2]; // 单词信息(可重复)
    PEACHWORD head_eachword[2]; // 单词信息(不重复)
    PEACHWORD head_repeat[2]; // 重复的单词
    PREPEATWORD node_repeat[2]; // 连续重复5次以上的单词
    int word_num[2]; // 文件中的单词数
    int repeat_num[2]; // 重复单词数
    int repeat5_num; // 连续重复5次以上的单词的单词数

};


PMYWORD create_myword_list(); // 创建'myword'链表
PMYWORD insert_myword(PMYWORD head, const char *content, int row, int column); // 'myword'链表插入
PMYWORD find_myword(PMYWORD head, const char *content); // 在'myword'链表中根据单词内容(content)查找
void free_myword_list(PMYWORD head); // 释放'myword'链表

PEACHWORD create_eachword_list(); // 创建'eachword'链表
PEACHWORD insert_eachword(PEACHWORD head, const char *content, int row, int column); // 'eachword'链表插入
PEACHWORD find_eachword(PEACHWORD head, const char *content); // 在'eachword'链表中根据单词内容(content)查找
void free_eachword_list(PEACHWORD head); // 释放'eachword'链表

PREPEATWORD create_repeatword_list(); // 创建'repeatword'链表
PREPEATWORD insert_repeatword(PREPEATWORD head, PMYWORD node_start, int repeat_num);// 'repeatword'链表插入
PMYWORD find_repeatword(PREPEATWORD head, PMYWORD node); // 在'repeatword'链表根据单词地址(node)查找
void free_repeatword(PREPEATWORD head); // 释放'repeatword'链表

void free_info(struct files_info *info); // 释放所有单词信息链表

void print_myword(PMYWORD head); // 打印'myword'链表
void print_eachword(PEACHWORD head); // 打印'eachwword'链表

void study_files(FILE *fp[], struct files_info *info); // 分析文件
void cmp_singleword(struct files_info *info); // 比较两个文件中的每个单词
void cmp_fiveword(struct files_info *info); // 比较两个文件中，连续五个单词以上的重复

int main(int argc, char *argv[]){
	FILE *fp[2] = {NULL, NULL};
	struct files_info info;
	char file[2][50] = {'\0'};
    int i = 0;

	// 获取两个文件路径
    printf("Please input two paths about two files, them need cmpare.\n");
    printf("There are two test files maybe you need:\"file\\file1.txt\", \"file\\file2.txt\"\n");
    printf("File1>> ");
    scanf("%s", file[0]);
    printf("File2>> ");
    scanf("%s", file[1]);

    info.file_name[0] = file[0];
    info.file_name[1] = file[1];

	// 打开两个文件
    fp[0] = fopen(info.file_name[0], "r");
    if (NULL == fp[0]){
        printf("The file \'%s\' can not open.\n", info.file_name[0]);
        return 1;
    }
    fp[1] = fopen(info.file_name[1], "r");
    if (NULL == fp[1]){
        printf("The file \'%s\' can not open.\n", info.file_name[1]);
        return 1;
    }

	// 分析文件得到单词信息
    study_files(fp, &info);

    // 打印文件1的单词信息
    printf("文件1: \'%s\' 有%d个单词: \n", info.file_name[0], info.word_num[0]);
    // print_myword(info.head_myword[0]);
    // printf("----------------------------\n");
    print_eachword(info.head_eachword[0]);
    printf("\n");
    // 打印文件2的单词信息
    printf("文件2: \'%s\' 有%d个单词: \n", info.file_name[1], info.word_num[1]);
    //print_myword(info.head_myword[1]);
    //printf("----------------------------\n");
    print_eachword(info.head_eachword[1]);
    printf("\n");

	// 比较两个文件，得到重复单词
	printf("每个单词在两个文件中出现的次数与位置\n");
    cmp_singleword(&info);
    printf("文件1: %d个单词,%d个单词重复,重复率: %.2f%%\n", \
        info.word_num[0], info.repeat_num[0], (float)info.repeat_num[0]/info.word_num[0]*100);
    printf("文件2: %d个单词,%d个单词重复,重复率: %.2f%%\n", \
        info.word_num[1], info.repeat_num[1], (float)info.repeat_num[1]/info.word_num[1]*100);
	printf("\n");

	// 比较两个文件，得到连续5个单词及以上重复
	printf("连续5个单词及以上重复\n");
    cmp_fiveword(&info);
    printf("文件1: %d个单词,连续重复单词数:%d, 重复率: %.2f%%\n", \
        info.word_num[0], info.repeat5_num, (float)info.repeat5_num/info.word_num[0]*100);
    printf("文件2: %d个单词,连续重复单词数:%d, 重复率: %.2f%%\n", \
        info.word_num[1], info.repeat5_num, (float)info.repeat5_num/info.word_num[1]*100);    

	// 释放资源
    fclose(fp[0]);
    fclose(fp[1]);
    free_info(&info);

    return 0;

}

// 比较两个文件中的每个单词
void cmp_singleword(struct files_info *info){
    PEACHWORD head[2] = {NULL, NULL};
    PEACHWORD node = NULL;
	struct location *node_loc;
    assert(NULL != info);

    head[0] = info->head_eachword[0];
    head[1] = info->head_eachword[1];
    info->repeat_num[0] = 0;
    info->repeat_num[1] = 0;

	printf("[单词] [F文件标号:出现次数]:(行,列)...; [文件标号:出现次数]:(行,列)...\n");
    while(head[0]->next != NULL){
        head[0] = head[0]->next;
        node = find_eachword(info->head_eachword[1], head[0]->content);
        printf("[%s] [F%d:%d]:(%d,%d)", \
            head[0]->content, 1, head[0]->num, head[0]->loc->row, head[0]->loc->column);
        node_loc = head[0]->loc;
        while(node_loc->next != NULL){
            node_loc = node_loc->next;
            printf(",(%d,%d)", node_loc->row, node_loc->column);
        }
        if (NULL == node){
            printf("\n");
            continue;
        } else {
            printf("; [F%d:%d]:(%d,%d)", \
                2, node->num, node->loc->row, node->loc->column);
            node_loc = node->loc;
            while(node_loc->next != NULL){
                node_loc = node_loc->next;
                printf(",(%d,%d)", node_loc->row, node_loc->column);
            }
            info->repeat_num[0] += head[0]->num;
        }
        printf("\n");
    }

    while(head[1]->next != NULL){
        head[1] = head[1]->next;
        node = find_eachword(info->head_eachword[0], head[1]->content);
        if (NULL == node){
            printf("[%s] [F%d:%d]:(%d,%d)", \
                head[1]->content, 2, head[1]->num, head[1]->loc->row, head[1]->loc->column);
                node_loc = head[1]->loc;
            while(node_loc->next != NULL){
                node_loc = node_loc->next;
                printf(",(%d,%d)", node_loc->row, node_loc->column);
            }
            printf("\n");      
        } else {
            info->repeat_num[1] += head[1]->num;
        }
    }

}

// 比较两个文件中，连续五个单词以上的重复
void cmp_fiveword(struct files_info *info){
    PMYWORD head[2] = {NULL, NULL};
    PMYWORD node = NULL;
    PMYWORD head_tmp = NULL;
    PMYWORD node_tmp = NULL;
    PMYWORD node_repstart = NULL;
    int rep_num = 0;
    int i = 0;
    assert(NULL != info);

    head[0] = info->head_myword[0];
    head[1] = info->head_myword[1];
    info->node_repeat[0] = create_repeatword_list();
    info->node_repeat[1] = create_repeatword_list();
	info->repeat5_num = 0;

	printf("[字符串] (在文件1中的起始位置) (在文件2中的起始位置)\n");
    while(NULL != head[0]->next){
        head[0] = head[0]->next;
        node = find_myword(head[1], head[0]->content);
        if (NULL == node){
            continue;
        } else {
            node_tmp = node;
            head_tmp = head[0];
            while(NULL != node){
                rep_num = 1;
                node_tmp = node;
                head_tmp = head[0];
                while(NULL!=head_tmp->next && NULL!=node_tmp->next){
                    head_tmp = head_tmp->next;
                    node_tmp = node_tmp->next;
                    if (strcmp(head_tmp->content, node_tmp->content) == 0){
                        if (NULL != find_repeatword(info->node_repeat[1], node_tmp)){
                            break;
                        }
                        rep_num ++;
                    } else {
                        break;
                    }
                }
                if (rep_num >= 5){
                    info->repeat5_num += rep_num;
                    node_repstart = head[0];
                    printf("[");
                    for (i=0; i<rep_num; i++){
                        printf("%s ", node_repstart->content);
                        node_repstart = node_repstart->next;
                    }
                    printf("\b] (%d,%d) (%d,%d)\n", \
						head[0]->row, head[0]->column, node->row, node->column);
                    insert_repeatword(info->node_repeat[0], head[0], rep_num);
                    insert_repeatword(info->node_repeat[1], node, rep_num);
                }
                node = find_myword(node, head[0]->content);
            }
        }
    }
}

// 分析文件
void study_files(FILE *fp[], struct files_info *info){
    char str[50] = {'\0'};
    int cnt_row= 0;
    int cnt_cloumn = 0;
    int cnt_word = 0;
    int i = 0;
    char ch = '\0';

    assert(NULL != fp);
    assert(NULL != info);

    for(i=0; i<2; i++){
        info->head_myword[i] = create_myword_list();
        info->head_eachword[i] = create_eachword_list();
        cnt_row = 0;
        cnt_cloumn = 0;
        cnt_word = 0;
        info->word_num[i] = 0;
        while(ch=fgetc(fp[i])){
            if (('a'<=ch&&ch<='z') ||
                ('A'<=ch&&ch<='Z') ||
                ('0'<=ch&&ch<='9') ||
                '_'==ch || '-'==ch){
                str[cnt_word] = ch;
                cnt_word ++;
            } else {
                if (cnt_word != 0){
                    str[cnt_word] = '\0';
                    insert_myword(info->head_myword[i], str, cnt_row+1, cnt_cloumn+1);
                    insert_eachword(info->head_eachword[i], str, cnt_row+1, cnt_cloumn+1);
                    info->word_num[i] ++;
                    cnt_word = 0;
                }
                if (EOF == ch){
                    break;
                } else if ('\n' == ch){
                    cnt_row ++;
                }
                cnt_word = 0;
                cnt_cloumn = 0;
            }
            cnt_cloumn ++;
        }
    }    
}

// 创建'myword'链表
PMYWORD create_myword_list(){
    PMYWORD head = (PMYWORD) malloc(sizeof(MYWORD));
    if (NULL == head){
        printf("out of memory\n");
        return NULL;
    }
    memset(head, 0, sizeof(MYWORD));
    return head;
}

// 尾插法插入'myword'链表
PMYWORD insert_myword(PMYWORD head, const char *content, int row, int column){
    PMYWORD node = NULL;
    assert(NULL != head);

    node = (PMYWORD) malloc(sizeof(MYWORD));
    if (NULL == node){
        printf("out of memory\n");
        return NULL;
    }
    node->content = (char *) malloc(strlen(content)*sizeof(char));
    if (NULL == node->content){
        printf("out of memory\n");
        return NULL;
    }
    strcpy(node->content, content);
    node->row = row;
    node->column = column;
	node->next = NULL;
    while(NULL != head->next){
        head = head->next;
    }
    head->next = node;

    return node;
}

// 在'myword'链表中根据单词内容(content)查找
PMYWORD find_myword(PMYWORD head, const char *content){
    assert(NULL != head);
    while(NULL != head->next){
        head = head->next;
        if (strcmp(head->content, content) == 0){
            return head;
        }
    }

    return NULL;
}

// 释放'myword'链表
void free_myword_list(PMYWORD head){
    PMYWORD node = NULL;
    if (NULL == head){
        return;
    }
    node = head->next;
    while(NULL != node){
        head->next = node->next;
        // free(node->content);
        free(node);
        node = head->next;
    }
    free(head);
}

// 创建'eachword'链表
PEACHWORD create_eachword_list(){    
    PEACHWORD head = (PEACHWORD) malloc(sizeof(EACHWORD));
    if (NULL == head){
        printf("out of memory.\n");
        return NULL;
    }
    memset(head, 0, sizeof(EACHWORD));

    return head;
}

// 尾插法插入'eachword'链表
PEACHWORD insert_eachword(PEACHWORD head, const char *content, int row, int column){
    PEACHWORD node = NULL;
	struct location *loc_node = NULL;
	struct location *loc = NULL;
    assert(NULL != head);
    node = find_eachword(head, content);
    if (NULL == node){
        node = (PEACHWORD) malloc(sizeof(EACHWORD));
        if (NULL == node){
            printf("out of memory.\n");
            return NULL;
        }

        node->content = (char *) malloc(strlen(content)*sizeof(char));
        if (NULL == node->content){
            printf("out of memory.\n");
            return NULL;
        }
        strcpy(node->content, content);
        node->loc = (struct location *) malloc(sizeof(struct location));
        if (NULL == node->loc){
            printf("out of memory.\n");
            return NULL;
        }
        node->loc->row = row;
        node->loc->column = column;
        node->loc->next = NULL;
        node->num = 1;
        node->next = NULL;

        while(NULL != head->next){
            head = head->next;
        }
        head->next = node;
    } else {
        node->num ++;
        loc_node = (struct location *) malloc(sizeof(struct location));
        loc_node->row = row;
        loc_node->column = column;
        loc_node->next = NULL;
        loc = node->loc;
        while(NULL != loc->next){
            loc = loc->next;
        }
        loc->next = loc_node;
    }
    
    return node;
}

// 在'eachword'链表中根据单词内容(content)查找
PEACHWORD find_eachword(PEACHWORD head, const char *content){
    assert(NULL != head);
    while(NULL != head->next){
        head = head->next;
        if (strcmp(head->content, content) == 0){
            return head;
        }
    }
 
    return NULL;
}

// 释放'eachword'链表
void free_eachword_list(PEACHWORD head){
    PEACHWORD node = NULL;
    struct location *loc = NULL;
    if (NULL == head){
        return;
    }
    node = head->next;
    while(NULL != node){
        head->next = node->next;
        // free(node->content);
        if (NULL != node->loc){
            loc = node->loc->next;
            while(NULL != loc){
                node->loc->next = loc->next;
                free(loc);
                loc = node->loc->next;
            }         
        }
        free(node);
        node = head->next;
    }
    free(head);
}

// 创建'repeatword'链表
PREPEATWORD create_repeatword_list(){
    PREPEATWORD head = (PREPEATWORD) malloc(sizeof(REPEATWORD));
    if (NULL == head){
        printf("out of memory.\n");
        return NULL;
    }
    memset(head, 0, sizeof(REPEATWORD));

    return head;
}

// 头插法插入'repeatword'链表
PREPEATWORD insert_repeatword(PREPEATWORD head, PMYWORD node_start, int repeat_num){
    PREPEATWORD node = NULL;
    assert(NULL != head);
    node = (PREPEATWORD) malloc(sizeof(REPEATWORD));
    if (NULL == node){
        printf("out of memory.\n");
        return NULL;
    }
    node->node_start = node_start;
    node->repeat_num = repeat_num;
    node->next = head->next;
    head->next = node;

	return node;
}

// 在'repeatword'链表根据单词地址(node)查找
PMYWORD find_repeatword(PREPEATWORD head, PMYWORD node){
    int i = 0;
    PMYWORD node_start = NULL;
    assert(NULL != head);
    while(NULL != head->next){
        head = head->next;
        node_start = head->node_start;
        for (i=0; i<head->repeat_num; i++){
            if (node_start == node){
                return node;
            }
            node_start = node_start->next;
        }
    }
    return NULL;
}

// 释放'repeatword'链表
void free_repeatword(PREPEATWORD head){
    PREPEATWORD node = NULL;
    if (NULL == head){
        return;
    }
    node = head->next;
    while(NULL != node){
        head->next = node->next;
        free(node);
        node = head->next;
    }
    free(head);
}

// 释放所有单词信息链表
void free_info(struct files_info *info){
    if (NULL == info){
        return;
    }
    free_myword_list(info->head_myword[0]);
    free_myword_list(info->head_myword[1]);
    free_eachword_list(info->head_eachword[0]);
    free_eachword_list(info->head_eachword[1]);
    free_repeatword(info->node_repeat[0]);
    free_repeatword(info->node_repeat[1]);
}

// 打印'myword'链表
void print_myword(PMYWORD head){
    assert(NULL != head);
    while(NULL != head->next){
        head = head->next;
        printf("[%s] (%d, %d)\n", head->content, head->row, head->column);
    }
   
}

// 打印'eachwword'链表
void print_eachword(PEACHWORD head){
	struct location *loc;
    assert(NULL != head);
    printf("[单词] (行,列),(行,列) ... \n");
    while(NULL != head->next){
        head = head->next;
        printf("[%s] (%d,%d)", head->content, head->loc->row, head->loc->column);
        loc = head->loc;
        while(NULL != loc->next){
            loc = loc->next;
            printf(",(%d,%d)", loc->row, loc->column);
        }
        printf("\n");
    }
}
