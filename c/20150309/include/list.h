#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "common.h"

void *Create_List(LIST_TYPE type);	// 创建链表
BOOL InsertFromHead_Customer(PCUSTOMER_HEAD head, PCUSTOMER_NODE node); // 头插法 插入客户链表
BOOL InsertFromHead_Account(PCUSTOMER_HEAD head, PCUSTOMER_NODE customer, PACCOUNT_NODE node);	// 头插法 插入账户链表
BOOL InsertFromHead_Loan(PCUSTOMER_HEAD head, PACCOUNT_NODE account, PLOAN_NODE node);	// 头插法 插入贷款链表
BOOL InsertFromHead_Record(PACCOUNT_NODE account, PRECORD_NODE node);		// 头插法 插入记录链表
BOOL InsertFromHead_Transfer(PACCOUNT_NODE account, PTRANSFER_NODE node);	// 头插法 插入转账链表

void print_loan(PLOAN_NODE node, BOOL title);			// 打印一条贷款信息
void print_loans(PLOAN_NODE node);						// 打印多条贷款信息
void print_record(PRECORD_NODE node, BOOL title);		// 打印一条记录
void print_records(PRECORD_NODE node);					// 打印多条记录
void print_transfer(PTRANSFER_NODE node, BOOL title);	// 打印一条转账信息
void print_transfers(PTRANSFER_NODE node);				// 打印多条转账信息
void print_account(PACCOUNT_NODE node);					// 打印一条账户信息
void print_accounts(PACCOUNT_NODE node);				// 打印多条账户信息
void print_customer(PCUSTOMER_NODE node);				// 打印一条客户信息
void print_customers(PCUSTOMER_NODE node);				// 打印多条客户信息
PCUSTOMER_NODE FindById_Customer(PCUSTOMER_NODE node, u64 id);	// 通过ID查找客户
PACCOUNT_NODE FindById_Account(PCUSTOMER_NODE node, u64 id);	// 通过ID查找账户
BOOL DelById_Account(PCUSTOMER_NODE node, u64 id);				// 通过ID删除一个账户

void free_all(PCUSTOMER_HEAD head);	// 释放所有链表

#endif