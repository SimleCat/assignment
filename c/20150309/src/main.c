// #define GLOBAL_VARIABLES_HERE
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "list.h"
#include "file.h"
#include "view.h"

int main(){
	printf("u64 size: %d\n", sizeof(u64));
	printf("u32 size: %d\n", sizeof(u32));
	printf("u16 size: %d\n", sizeof(u16));

	PCUSTOMER_HEAD head = (PCUSTOMER_HEAD) Create_List(LIST_CUSTOMER_HEAD);
	PCUSTOMER_NODE customer = (PCUSTOMER_NODE) Create_List(LIST_CUSTOMER);

	PLOAN_NODE loan = (PLOAN_NODE) Create_List(LIST_LOAN);
	PLOAN_NODE loan2 = (PLOAN_NODE) Create_List(LIST_LOAN);
	loan->info.account_id = 12345678901;
	loan->info.len_day = 10;
	loan->info.amounts = 300.5;
	loan->info.interests = 0.01;
	loan->info.start_date = 1426066389;
	loan->info.end_date = 1426066389;
	// loan->next = loan2;
	loan2->info.account_id = 12345678901;
	loan2->info.len_day = 100;
	loan2->info.amounts = 450.8;
	loan2->info.interests = 0.02;
	loan2->info.start_date = 1426166389;
	loan2->info.end_date = 1426266389;
	// print_loans(loan);

	PRECORD_NODE record = (PRECORD_NODE) Create_List(LIST_RECORD);
	PRECORD_NODE record2 = (PRECORD_NODE) Create_List(LIST_RECORD);
	record->info.account_id = 12345678901;
	record->info.type = TYPE_DEPOSIT;
	record->info.date = 1426366389;
	record->info.sum = 200.0;
	record->info.type_access = TYPE_CASH;
	// record->next = record2;
	record2->info.account_id = 12345678901;
	record2->info.type = TYPE_WITHDRAWAL;
	record2->info.date = 1426366389;
	record2->info.sum = 100.0;
	record2->info.type_access = TYPE_TRANSFER;
	// print_records(record);


	PTRANSFER_NODE transfer= (PTRANSFER_NODE) Create_List(LIST_TRANSFER);
	transfer->info.from_account = 12345678901;
	transfer->info.to_account = 12345678002;
	transfer->info.set_date = 15;
	transfer->info.start_date = 1426666389;
	transfer->info.end_date = 1429666389;


	PACCOUNT_NODE account = (PACCOUNT_NODE) Create_List(LIST_ACCOUNT);
	account->info.customer_id = 12345678900;
	account->info.id = 12345678901;
	account->info.state = STATE_ACTIVE;
	account->info.balance = 10000;
	account->info.loans_num = 2;
	InsertFromHead_Record(account, record);
	InsertFromHead_Record(account, record2);
	InsertFromHead_Loan(head, account, loan);
	InsertFromHead_Loan(head, account, loan2);
	InsertFromHead_Transfer(account, transfer);
	//account->info.loans = loan;
	//account->info.records = record;
	// print_account(account);

	customer->info.id = 12345678900;
	customer->info.type = TYPE_PASSPOR;
	strcpy(customer->info.name, "FengLong");
	strcpy(customer->info.address, "shanghai");
	strcpy(customer->info.phone, "123456789022");
	customer->info.state = STATE_WORKING;
	InsertFromHead_Account(head, customer, account);
	InsertFromHead_Customer(head, customer);
	print_customers(head->customers);

	printf("\n--- find account ---\n");
	account = FindById_Account(head->customers, 12345678901);
	print_account(account);

	// printf("\n--- del account ---\n");
	// DelById_Account(head->customers, 12345678901);
	// print_customers(head->customers);
	WriteToFile(head);
	free_all(head);

	printf("\n-------------------------------------------\n");
	head = (PCUSTOMER_HEAD) Create_List(LIST_CUSTOMER_HEAD);
	ReadFromFile(head);
	print_customers(head->customers);
	

	view_main(head);

	free_all(head);

	return 0;
}