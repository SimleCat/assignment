#include <stdio.h>
#include <string.h>
#include "common.h"
#include "list.h"
#include "file.h"
#include "view.h"

int main(){
	// �����ͻ�����ͷ���
	PCUSTOMER_HEAD head = (PCUSTOMER_HEAD) Create_List(LIST_CUSTOMER_HEAD);
	printf("Read data from the file.\n");
	// ���ļ��ж�ȡ����
	if (ReadFromFile(head) == TRUE){
		printf("Data read success.\n");
	}
	else{
		printf("Data does not exist or read failure.\n");
	}
	// print_customers(head->customers);
	// ��ʾ������
	view_main(head);
	printf("\nSave the data to files.\n");
	// �������ݵ��ļ�
	if (WriteToFile(head) == TRUE){
		printf("Save success.\n");
	}
	else{
		printf("Save failure.\n");
	}
	printf("\nRelease of lists\n");
	// �ͷ�����
	free_all(head);

	return 0;
}