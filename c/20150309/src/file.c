#include "file.h"


BOOL WriteToFile_Loans(PLOAN_NODE node, FILE *fp){
	while (NULL != node){
		fwrite(node, sizeof(LOAN_INFO), 1, fp);
		node = node->next;
	}
	return TRUE;	
}

BOOL WriteToFile_Records(PRECORD_NODE node, FILE *fp){
	while (NULL != node){
		fwrite(node, sizeof(RECORD_INFO), 1, fp);
		node = node->next;
	}
	return TRUE;
}

BOOL WriteToFile_Transfers(PTRANSFER_NODE node, FILE *fp){
	while (NULL != node){
		fwrite(node, sizeof(TRANSFER_INFO), 1, fp);
		node = node->next;
	}
	return TRUE;
}

BOOL WriteToFile_Accounts(PACCOUNT_NODE node, FILE *fp_account, FILE *fp_loan, FILE *fp_record, FILE *fp_transfer){
	// if (NULL == node){
	// 	printf("In WriteToFile_Accounts node is NULL\n");
	// }
	while (NULL != node){
		// printf("Write account\n");
		fwrite(node, sizeof(ACCOUNT_INFO), 1, fp_account);
		WriteToFile_Loans(node->loans, fp_loan);
		WriteToFile_Records(node->records, fp_record);
		WriteToFile_Transfers(node->transfers, fp_transfer);
		node = node->next;
	}
	return TRUE;
}

BOOL WriteToFile(PCUSTOMER_HEAD head){
	if (NULL == head){
		printf("In \"WriteToFile\" head is NULL\n");
		return FALSE;
	}
	FILE *fp_customer = fopen(FILE_CUSTOMER, "wb");
	FILE *fp_account = fopen(FILE_ACCOUNT, "wb");
	FILE *fp_loan = fopen(FILE_LOAN, "wb");
	FILE *fp_record = fopen(FILE_RECORD, "wb");
	FILE *fp_transfer = fopen(FILE_TRANSFER, "wb");
	
	PCUSTOMER_NODE customer = head->customers;
	while (NULL != customer){
		// printf("Write customer\n");
		fwrite(customer, sizeof(CUSTOMER_INFO), 1, fp_customer);
		WriteToFile_Accounts(customer->accounts, fp_account, fp_loan, fp_record, fp_transfer);
		customer = customer->next;
	}

	fclose(fp_customer);
	fclose(fp_account);
	fclose(fp_loan);
	fclose(fp_record);
	fclose(fp_transfer);

	return TRUE;
}

BOOL ReadFromFile_Loans(PCUSTOMER_HEAD head, FILE *fp){
	PACCOUNT_NODE account = NULL;
	PLOAN_NODE node = NULL;
	while (!feof(fp)){
		node = (PLOAN_NODE) Create_List(LIST_LOAN);
		if (fread(node, sizeof(LOAN_INFO), 1, fp)){
			account = FindById_Account(head->customers, node->info.account_id);
			if (NULL != account){
				InsertFromHead_Loan(head, account, node);
			}else{
				printf("The data of loan is invalid!\n");
			}
		}else{
			free(node);
			break;
		}
	}
	return TRUE;
}

BOOL ReadFromFile_Records(PCUSTOMER_HEAD head, FILE *fp){
	PACCOUNT_NODE account = NULL;
	PRECORD_NODE node = NULL;
	while (!feof(fp)){
		node = (PRECORD_NODE) Create_List(LIST_RECORD);
		if (fread(node, sizeof(RECORD_INFO), 1, fp)){
			account = FindById_Account(head->customers, node->info.account_id);
			if (NULL != account){
				InsertFromHead_Record(account, node);
			}else{
				printf("The data of record is invalid!\n");
			}
		}else{
			free(node);
			break;
		}
	}
	return TRUE;	
}

BOOL ReadFromFile_Transfers(PCUSTOMER_HEAD head, FILE *fp){
	PACCOUNT_NODE account = NULL;
	PTRANSFER_NODE node = NULL;
	while (!feof(fp)){
		node = (PTRANSFER_NODE) Create_List(LIST_TRANSFER);
		if (fread(node, sizeof(TRANSFER_INFO), 1, fp)){
			account = FindById_Account(head->customers, node->info.from_account);
			if (NULL != account){
				InsertFromHead_Transfer(account, node);
			}else{
				printf("The data of transfer is invalid!\n");
			}
		}else{
			free(node);
			break;
		}
	}
	return TRUE;
}

BOOL ReadFromFile_Accounts(PCUSTOMER_HEAD head, FILE *fp){
	PCUSTOMER_NODE customer = NULL;
	PACCOUNT_NODE node = NULL;
	while (!feof(fp)){
		printf("read Accounts\n");
		node = (PACCOUNT_NODE) Create_List(LIST_ACCOUNT);
		if (fread(node, sizeof(ACCOUNT_INFO), 1, fp)){
			customer = FindById_Customer(head->customers, node->info.customer_id);
			if (NULL != customer){
				InsertFromHead_Account(head, customer, node);
				printf("Insert Account\n");
			}else{
				printf("The data of account is invalid!\n");
			}
		}else{
			free(node);
			break;
		}
	}
	return TRUE;
}

BOOL ReadFromFile_Customers(PCUSTOMER_HEAD head, FILE *fp){
	PCUSTOMER_NODE node = NULL;
	while (!feof(fp)){
		printf("read Customers\n");
		node = (PCUSTOMER_NODE) Create_List(LIST_CUSTOMER);
		if (fread(node, sizeof(CUSTOMER_INFO), 1, fp)){
			InsertFromHead_Customer(head, node);
			printf("Insert Customer\n");
		}else{
			free(node);
			break;
		}
	}
	return TRUE;
}

BOOL ReadFromFile(PCUSTOMER_HEAD head){
	if (NULL == head){
		printf("In \"ReadFromFile\" head is NULL\n");
		return FALSE;
	}
	FILE *fp_customer = fopen(FILE_CUSTOMER, "rb");
	FILE *fp_account = fopen(FILE_ACCOUNT, "rb");
	FILE *fp_loan = fopen(FILE_LOAN, "rb");
	FILE *fp_record = fopen(FILE_RECORD, "rb");
	FILE *fp_transfer = fopen(FILE_TRANSFER, "rb");
	if (NULL == fp_customer || NULL == fp_account || NULL == fp_loan \
		|| NULL == fp_record || NULL == fp_transfer){
		printf("Data file is missing!\n");
		return FALSE;
	}
	ReadFromFile_Customers(head, fp_customer);
	ReadFromFile_Accounts(head, fp_account);
	ReadFromFile_Loans(head, fp_loan);
	ReadFromFile_Records(head, fp_record);
	ReadFromFile_Transfers(head, fp_transfer);

	fclose(fp_customer);
	fclose(fp_account);
	fclose(fp_loan);
	fclose(fp_record);
	fclose(fp_transfer);

	return TRUE;	
}