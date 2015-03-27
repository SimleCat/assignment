#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "common.h"

void *Create_List(LIST_TYPE type);	// ��������
BOOL InsertFromHead_Customer(PCUSTOMER_HEAD head, PCUSTOMER_NODE node); // ͷ�巨 ����ͻ�����
BOOL InsertFromHead_Account(PCUSTOMER_HEAD head, PCUSTOMER_NODE customer, PACCOUNT_NODE node);	// ͷ�巨 �����˻�����
BOOL InsertFromHead_Loan(PCUSTOMER_HEAD head, PACCOUNT_NODE account, PLOAN_NODE node);	// ͷ�巨 �����������
BOOL InsertFromHead_Record(PACCOUNT_NODE account, PRECORD_NODE node);		// ͷ�巨 �����¼����
BOOL InsertFromHead_Transfer(PACCOUNT_NODE account, PTRANSFER_NODE node);	// ͷ�巨 ����ת������

void print_loan(PLOAN_NODE node, BOOL title);			// ��ӡһ��������Ϣ
void print_loans(PLOAN_NODE node);						// ��ӡ����������Ϣ
void print_record(PRECORD_NODE node, BOOL title);		// ��ӡһ����¼
void print_records(PRECORD_NODE node);					// ��ӡ������¼
void print_transfer(PTRANSFER_NODE node, BOOL title);	// ��ӡһ��ת����Ϣ
void print_transfers(PTRANSFER_NODE node);				// ��ӡ����ת����Ϣ
void print_account(PACCOUNT_NODE node);					// ��ӡһ���˻���Ϣ
void print_accounts(PACCOUNT_NODE node);				// ��ӡ�����˻���Ϣ
void print_customer(PCUSTOMER_NODE node);				// ��ӡһ���ͻ���Ϣ
void print_customers(PCUSTOMER_NODE node);				// ��ӡ�����ͻ���Ϣ
PCUSTOMER_NODE FindById_Customer(PCUSTOMER_NODE node, u64 id);	// ͨ��ID���ҿͻ�
PACCOUNT_NODE FindById_Account(PCUSTOMER_NODE node, u64 id);	// ͨ��ID�����˻�
BOOL DelById_Account(PCUSTOMER_NODE node, u64 id);				// ͨ��IDɾ��һ���˻�

void free_all(PCUSTOMER_HEAD head);	// �ͷ���������

#endif