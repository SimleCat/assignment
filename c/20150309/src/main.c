#include <stdio.h>
#include <string.h>
#include "common.h"
#include "list.h"
#include "file.h"
#include "view.h"

int main(){
	// 创建客户链表头结点
	PCUSTOMER_HEAD head = (PCUSTOMER_HEAD) Create_List(LIST_CUSTOMER_HEAD);
	printf("Read data from the file.\n");
	// 从文件中读取数据
	if (ReadFromFile(head) == TRUE){
		printf("Data read success.\n");
	}
	else{
		printf("Data does not exist or read failure.\n");
	}
	// print_customers(head->customers);
	// 显示主界面
	view_main(head);
	printf("\nSave the data to files.\n");
	// 保存数据到文件
	if (WriteToFile(head) == TRUE){
		printf("Save success.\n");
	}
	else{
		printf("Save failure.\n");
	}
	printf("\nRelease of lists\n");
	// 释放链表
	free_all(head);

	return 0;
}