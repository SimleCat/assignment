#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "common.h"

void *Create_List(LIST_TYPE type);
BOOL InsertFromHead_Customer(PCUSTOMER_HEAD head, PCUSTOMER_NODE node);
BOOL InsertFromHead_Account(PCUSTOMER_HEAD head, PCUSTOMER_NODE customer, PACCOUNT_NODE node);
BOOL InsertFromHead_Loan(PCUSTOMER_HEAD head, PACCOUNT_NODE account, PLOAN_NODE node);
BOOL InsertFromHead_Record(PACCOUNT_NODE account, PRECORD_NODE node);
BOOL InsertFromHead_Transfer(PACCOUNT_NODE account, PTRANSFER_NODE node);

void print_loan(PLOAN_NODE node);
void print_loans(PLOAN_NODE node);
void print_record(PRECORD_NODE node);
void print_records(PRECORD_NODE node);
void print_transfer(PTRANSFER_NODE node);
void print_transfers(PTRANSFER_NODE node);
void print_account(PACCOUNT_NODE node);
void print_accounts(PACCOUNT_NODE node);
void print_customer(PCUSTOMER_NODE node);
void print_customers(PCUSTOMER_NODE node);
PCUSTOMER_NODE FindById_Customer(PCUSTOMER_NODE node, u64 id);
PACCOUNT_NODE FindById_Account(PCUSTOMER_NODE node, u64 id);
BOOL DelById_Account(PCUSTOMER_NODE node, u64 id);

void free_all(PCUSTOMER_HEAD head);

#endif