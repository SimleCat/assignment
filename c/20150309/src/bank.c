#include "bank.h"

// typedef struct{
// 	u64 customer_id;	
// 	u64 id;
// 	u16 state;
// 	double balance;
// 	u32 loans_num;
// 	PLOAN_NODE loans;
// 	PRECORD_NODE records;
// }ACCOUNT_INFO;

u64 create_customerID(PCUSTOMER_NODE customers){
	u64 id = 0;
	srand((unsigned int)time(0));
	while (1){
		id = rand() * rand();
		// printf("%d\n", id);
		// getchar();
		if (id > 100000000 && id < 999999999){
			id = id * 100;
			if (FindById_Customer(customers, id) == NULL){
				break;
			}
		}
	}
	return id;
}

u64 create_accountID(PCUSTOMER_NODE customer, u64 customer_id){
	u64 id = customer_id;
	while (1){
		++id;
		if (id % 100 >= MAX_ACCOUNT_NUM){
			printf("Account number has reached the upper limit.\n");
			return -1;
		}
		if (FindById_Account(customer, id) == NULL){
			break;
		}
	}
	return id;
}

BOOL deposit(PACCOUNT_NODE node, double money, u16 type){
	


	return TRUE;
}