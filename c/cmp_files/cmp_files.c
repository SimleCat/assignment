#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <fcntl.h>

// ��ŵ���λ����Ϣ
struct location{
    int row; // ��
    int column; //��
    struct location *next;
};

// ��ŵ�����Ϣ(���ʲ��ظ�)
typedef struct eachword{
    char *content; // ��������
    int num; // �õ��ʳ��ֶ��ٴ�
    struct location *loc; // ���ʶ����������
    struct eachword *next;
}EACHWORD, *PEACHWORD;

// ��ŵ�����Ϣ(��λ��˳���ţ����ظ�)
typedef struct myword{
    char *content; // ��������
    int row; //��
    int column; //��
    struct myword *next;
}MYWORD, *PMYWORD;

// ��������ظ�����
typedef struct repeatword{
    PMYWORD node_start; // �����ظ����ʵĵ�һ������
    int repeat_num; // �������ʵĸ���
    struct repeatword *next;
}REPEATWORD, *PREPEATWORD;

// �ļ��ĵ��ʵ���Ϣ
struct files_info{
    char *file_name[2]; // �����ļ���
    PMYWORD head_myword[2]; // ������Ϣ(���ظ�)
    PEACHWORD head_eachword[2]; // ������Ϣ(���ظ�)
    PEACHWORD head_repeat[2]; // �ظ��ĵ���
    PREPEATWORD node_repeat[2]; // �����ظ�5�����ϵĵ���
    int word_num[2]; // �ļ��еĵ�����
    int repeat_num[2]; // �ظ�������
    int repeat5_num; // �����ظ�5�����ϵĵ��ʵĵ�����

};


PMYWORD create_myword_list(); // ����'myword'����
PMYWORD insert_myword(PMYWORD head, const char *content, int row, int column); // 'myword'�������
PMYWORD find_myword(PMYWORD head, const char *content); // ��'myword'�����и��ݵ�������(content)����
void free_myword_list(PMYWORD head); // �ͷ�'myword'����

PEACHWORD create_eachword_list(); // ����'eachword'����
PEACHWORD insert_eachword(PEACHWORD head, const char *content, int row, int column); // 'eachword'�������
PEACHWORD find_eachword(PEACHWORD head, const char *content); // ��'eachword'�����и��ݵ�������(content)����
void free_eachword_list(PEACHWORD head); // �ͷ�'eachword'����

PREPEATWORD create_repeatword_list(); // ����'repeatword'����
PREPEATWORD insert_repeatword(PREPEATWORD head, PMYWORD node_start, int repeat_num);// 'repeatword'�������
PMYWORD find_repeatword(PREPEATWORD head, PMYWORD node); // ��'repeatword'������ݵ��ʵ�ַ(node)����
void free_repeatword(PREPEATWORD head); // �ͷ�'repeatword'����

void free_info(struct files_info *info); // �ͷ����е�����Ϣ����

void print_myword(PMYWORD head); // ��ӡ'myword'����
void print_eachword(PEACHWORD head); // ��ӡ'eachwword'����

void study_files(FILE *fp[], struct files_info *info); // �����ļ�
void cmp_singleword(struct files_info *info); // �Ƚ������ļ��е�ÿ������
void cmp_fiveword(struct files_info *info); // �Ƚ������ļ��У���������������ϵ��ظ�

int main(int argc, char *argv[]){
	FILE *fp[2] = {NULL, NULL};
	struct files_info info;
	char file[2][50] = {'\0'};
    int i = 0;

	// ��ȡ�����ļ�·��
    printf("Please input two paths about two files, them need cmpare.\n");
    printf("There are two test files maybe you need:\"file\\file1.txt\", \"file\\file2.txt\"\n");
    printf("File1>> ");
    scanf("%s", file[0]);
    printf("File2>> ");
    scanf("%s", file[1]);

    info.file_name[0] = file[0];
    info.file_name[1] = file[1];

	// �������ļ�
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

	// �����ļ��õ�������Ϣ
    study_files(fp, &info);

    // ��ӡ�ļ�1�ĵ�����Ϣ
    printf("�ļ�1: \'%s\' ��%d������: \n", info.file_name[0], info.word_num[0]);
    // print_myword(info.head_myword[0]);
    // printf("----------------------------\n");
    print_eachword(info.head_eachword[0]);
    printf("\n");
    // ��ӡ�ļ�2�ĵ�����Ϣ
    printf("�ļ�2: \'%s\' ��%d������: \n", info.file_name[1], info.word_num[1]);
    //print_myword(info.head_myword[1]);
    //printf("----------------------------\n");
    print_eachword(info.head_eachword[1]);
    printf("\n");

	// �Ƚ������ļ����õ��ظ�����
	printf("ÿ�������������ļ��г��ֵĴ�����λ��\n");
    cmp_singleword(&info);
    printf("�ļ�1: %d������,%d�������ظ�,�ظ���: %.2f%%\n", \
        info.word_num[0], info.repeat_num[0], (float)info.repeat_num[0]/info.word_num[0]*100);
    printf("�ļ�2: %d������,%d�������ظ�,�ظ���: %.2f%%\n", \
        info.word_num[1], info.repeat_num[1], (float)info.repeat_num[1]/info.word_num[1]*100);
	printf("\n");

	// �Ƚ������ļ����õ�����5�����ʼ������ظ�
	printf("����5�����ʼ������ظ�\n");
    cmp_fiveword(&info);
    printf("�ļ�1: %d������,�����ظ�������:%d, �ظ���: %.2f%%\n", \
        info.word_num[0], info.repeat5_num, (float)info.repeat5_num/info.word_num[0]*100);
    printf("�ļ�2: %d������,�����ظ�������:%d, �ظ���: %.2f%%\n", \
        info.word_num[1], info.repeat5_num, (float)info.repeat5_num/info.word_num[1]*100);    

	// �ͷ���Դ
    fclose(fp[0]);
    fclose(fp[1]);
    free_info(&info);

    return 0;

}

// �Ƚ������ļ��е�ÿ������
void cmp_singleword(struct files_info *info){
    PEACHWORD head[2] = {NULL, NULL};
    PEACHWORD node = NULL;
	struct location *node_loc;
    assert(NULL != info);

    head[0] = info->head_eachword[0];
    head[1] = info->head_eachword[1];
    info->repeat_num[0] = 0;
    info->repeat_num[1] = 0;

	printf("[����] [F�ļ����:���ִ���]:(��,��)...; [�ļ����:���ִ���]:(��,��)...\n");
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

// �Ƚ������ļ��У���������������ϵ��ظ�
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

	printf("[�ַ���] (���ļ�1�е���ʼλ��) (���ļ�2�е���ʼλ��)\n");
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

// �����ļ�
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

// ����'myword'����
PMYWORD create_myword_list(){
    PMYWORD head = (PMYWORD) malloc(sizeof(MYWORD));
    if (NULL == head){
        printf("out of memory\n");
        return NULL;
    }
    memset(head, 0, sizeof(MYWORD));
    return head;
}

// β�巨����'myword'����
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

// ��'myword'�����и��ݵ�������(content)����
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

// �ͷ�'myword'����
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

// ����'eachword'����
PEACHWORD create_eachword_list(){    
    PEACHWORD head = (PEACHWORD) malloc(sizeof(EACHWORD));
    if (NULL == head){
        printf("out of memory.\n");
        return NULL;
    }
    memset(head, 0, sizeof(EACHWORD));

    return head;
}

// β�巨����'eachword'����
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

// ��'eachword'�����и��ݵ�������(content)����
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

// �ͷ�'eachword'����
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

// ����'repeatword'����
PREPEATWORD create_repeatword_list(){
    PREPEATWORD head = (PREPEATWORD) malloc(sizeof(REPEATWORD));
    if (NULL == head){
        printf("out of memory.\n");
        return NULL;
    }
    memset(head, 0, sizeof(REPEATWORD));

    return head;
}

// ͷ�巨����'repeatword'����
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

// ��'repeatword'������ݵ��ʵ�ַ(node)����
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

// �ͷ�'repeatword'����
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

// �ͷ����е�����Ϣ����
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

// ��ӡ'myword'����
void print_myword(PMYWORD head){
    assert(NULL != head);
    while(NULL != head->next){
        head = head->next;
        printf("[%s] (%d, %d)\n", head->content, head->row, head->column);
    }
   
}

// ��ӡ'eachwword'����
void print_eachword(PEACHWORD head){
	struct location *loc;
    assert(NULL != head);
    printf("[����] (��,��),(��,��) ... \n");
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
