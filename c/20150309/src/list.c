#define GLOBAL_VARIABLES_HERE
#include "list.h"

void *Create_List(LIST_TYPE type){
	int size = 0;
	switch (type){
		case LIST_LOAN			: size = sizeof(LOAN_NODE); break;
		case LIST_RECORD 		: size = sizeof(RECORD_NODE); break;
		case LIST_TRANSFER		: size = sizeof(TRANSFER_NODE); break;
		case LIST_ACCOUNT 		: size = sizeof(ACCOUNT_NODE); break;
		case LIST_CUSTOMER 		: size = sizeof(CUSTOMER_NODE); break;
		case LIST_CUSTOMER_HEAD	: size = sizeof(CUSTOMER_HEAD); break;
		default					: return NULL;
	}
	void *node = malloc(size);
	if (NULL == node){
		printf("Create list fail!\n");
		return NULL;
	}
	memset(node, 0, size);

	return node;
}

BOOL InsertFromHead_Customer(PCUSTOMER_HEAD head, PCUSTOMER_NODE node){
	if (NULL == head || NULL == node){
		printf("In \"InsertFromHead_Customer\" head or node is NULL!\n");
		return FALSE;
	}
	node->next = head->customers;
	head->customers = node;
	head->customers_num += 1;

	return TRUE;
}

BOOL InsertFromHead_Account(PCUSTOMER_HEAD head, PCUSTOMER_NODE customer, PACCOUNT_NODE node){
	if (NULL == head || NULL == customer || NULL == node){
		printf("In \"InsertFromHead_Account\" head or customer or node is NULL!\n");
		return FALSE;
	}
	node->next = customer->accounts;
	customer->accounts = node;
	customer->info.accounts_num += 1;
	head->balance += node->info.balance;
	head->accounts_num += 1;

	return TRUE;
}

BOOL InsertFromHead_Loan(PCUSTOMER_HEAD head, PACCOUNT_NODE account, PLOAN_NODE node){
	if (NULL == head || NULL == account || NULL == node){
		printf("In \"InsertFromHead_Loan\" head or account or node is NULL!\n");
		return FALSE;
	}
	node->next = account->loans;
	account->loans = node;
	account->info.loans_num += 1;
	head->loans_num += 1;
	head->loan_amounts += node->info.amounts;

	return TRUE;
}

BOOL InsertFromHead_Record(PACCOUNT_NODE account, PRECORD_NODE node){
	if (NULL == account || NULL == node){
		printf("In \"InsertFromHead_Record\" account or node is NULL!\n");
		return FALSE;
	}
	node->next = account->records;
	account->records = node;

	return TRUE;
}

BOOL InsertFromHead_Transfer(PACCOUNT_NODE account, PTRANSFER_NODE node){
	if (NULL == account || NULL == node){
		printf("In \"InsertFromHead_Transfer\" account or node is NULL!\n");
		return FALSE;
	}
	node->next = account->transfers;
	account->transfers = node;

	return TRUE;
}

void print_loan(PLOAN_NODE node){
	struct tm *p;
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("%ld, ", node->info.len_day);
	printf("%.2f, ", node->info.amounts);
	printf("%.3f, ", node->info.interests);
	p = gmtime(&(node->info.start_date));
	printf("%d/%d/%d, ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
	p = gmtime(&(node->info.end_date));
	printf("%d/%d/%d\n", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
}
void print_loans(PLOAN_NODE node){
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("length(day), amounts, interests, start_date, end_date\n");
	while (NULL != node){
		print_loan(node);
		node = node->next;
	}
}


void print_record(PRECORD_NODE node){
	struct tm *p;	
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("%s, ", record_type[node->info.type]);
	p = gmtime(&(node->info.date));
	printf("%d/%d/%d, ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
	printf("%.2f, ", node->info.sum);
	printf("%s\n", access_type[node->info.type_access]);	
}
void print_records(PRECORD_NODE node){
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("Type, Date, Sum, Type of access\n");
	while (NULL != node){
		print_record(node);
		node = node->next;
	}
}

void print_transfer(PTRANSFER_NODE node){
	struct tm *p;	
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("%ld, ", node->info.from_account);
	printf("%ld, ", node->info.to_account);
	printf("%d, ", node->info.set_date);
	p = gmtime(&(node->info.start_date));
	printf("%d/%d/%d, ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
	p = gmtime(&(node->info.end_date));
	printf("%d/%d/%d\n", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);

}
void print_transfers(PTRANSFER_NODE node){
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("from_account, to_account, setting_date, starting_date, ending_date\n");
	while (NULL != node){
		print_transfer(node);
		node = node->next;
	}
}

void print_account(PACCOUNT_NODE node){
	if (NULL == node){
		printf("NULL\n");
		return;
	}	
	printf("id, state, balance, loans_num\n");
	printf("%ld, ", node->info.id);
	printf("%s, ", account_state[node->info.state]);
	printf("%.2f, ", node->info.balance);
	printf("%d\n", node->info.loans_num);
	printf("* loans info *\n");
	print_loans(node->loans);
	printf("* records info *\n");
	print_records(node->records);
	printf("* transfer info *\n");
	print_transfers(node->transfers);
}

void print_accounts(PACCOUNT_NODE node){
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	while (NULL != node){
		print_account(node);
		node = node->next;
	}
}

void print_customer(PCUSTOMER_NODE node){
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("%ld, ", node->info.id);
	printf("%s, ", customer_type[node->info.type]);
	printf("%s, ", node->info.name);
	printf("%s, ", node->info.address);
	printf("%s, ", node->info.phone);
	printf("%s ", customer_state[node->info.state]);
	printf("%d\n", node->info.accounts_num);
	printf("** accounts info **\n");
	print_accounts(node->accounts);
}

void print_customers(PCUSTOMER_NODE node){
	if (NULL == node){
		printf("NULL\n");
		return;
	}
	printf("id, type, name, address, phone_number, state, accounts_num\n");
	while (NULL != node){
		print_customer(node);
		node = node->next;
	}
}

PCUSTOMER_NODE FindById_Customer(PCUSTOMER_NODE node, u64 id){
	while (NULL != node){
		if (node->info.id == id){
			return node;
		}
		node = node->next;
	}
	return NULL;
}

PACCOUNT_NODE FindById_Account(PCUSTOMER_NODE node, u64 id){
	PCUSTOMER_NODE customer = FindById_Customer(node, id/MAX_ACCOUNT_NUM*MAX_ACCOUNT_NUM);
	if (NULL == customer){
		return NULL;
	}
	PACCOUNT_NODE accounts = customer->accounts;
	while (NULL != accounts){
		if (accounts->info.id == id){
			return accounts;
		}
		accounts = accounts->next;
	}
	return NULL;
}

void free_account(PACCOUNT_NODE node){
	PLOAN_NODE loans = NULL;
	PRECORD_NODE records = NULL;
	while (NULL != node->loans){
		loans = node->loans;
		node->loans = loans->next;
		free(loans);
	}
	while (NULL != node->records){
		records = node->records;
		node->records = records->next;
		free(records);
	}
	free(node);
}

void free_customer(PCUSTOMER_NODE node){
	PACCOUNT_NODE accounts = NULL;
	while (NULL != node->accounts){
		accounts = node->accounts;
		node->accounts = accounts->next;
		free(accounts);
	}
	free(node);
}

void free_all(PCUSTOMER_HEAD head){
	PCUSTOMER_NODE customers = NULL;
	while (NULL != head->customers){
		customers = head->customers;
		head->customers = customers->next;
		free_customer(customers);
	}
	free(head);
}

BOOL DelById_Account(PCUSTOMER_NODE node, u64 id){
	PCUSTOMER_NODE customer = FindById_Customer(node, id/MAX_ACCOUNT_NUM*MAX_ACCOUNT_NUM);
	if (NULL == customer){
		return FALSE;
	}
	PACCOUNT_NODE accounts = customer->accounts;
	if (accounts->info.id == id){
		customer->accounts = accounts->next;
		free_account(accounts);
		return TRUE; 
	}
	PACCOUNT_NODE accounts_pre = accounts;
	accounts = accounts->next;
	while (NULL != accounts){
		if (accounts->info.id == id){
			accounts_pre->next = accounts->next;
			free_account(accounts);
			return TRUE;
		}
		accounts_pre = accounts;
		accounts = accounts->next;
	}
	return FALSE;
}

