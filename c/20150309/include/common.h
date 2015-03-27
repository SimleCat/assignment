#ifndef __COMMON_H__
#define __COMMON_H__

#include <time.h>

/*
 * ����
 */
#define NAME_SIZE				50			// ���ִ洢��ռ�ֽ���
#define ADDRESS_SIZE			100			// ��ַ�洢��ռ�ֽ���
#define PHONR_SIZE				20			// �绰�洢��ռ�ֽ���
#define MAX_ACCOUNT_NUM			99			// һ���ͻ�����˻�����
#define MAX_AMOUNT_OF_DEPOSIT	99999999	// һ�δ�������
#define MAX_AMOUNT_OF_LOAN		999999		// һ�δ��������
#define MAX_LOAN_TIME			1095		// �������ʱ��
#define MAX_INTERESTS			0.8			// �����������
#define MAX_AMOUNT_OF_TRANSFER	99999999	// һ��ת�������

/*
 * ͨ�ñ�������
 */
typedef unsigned long long	u64;
typedef long long			s64;
typedef unsigned long	 	u32;
typedef long				s32;
typedef unsigned short		u16;
typedef short				s16;

/*
 * ״̬�����͵��±궨��
 */
#define STATE_BLOCKED		0
#define STATE_WORKING		1
#define STATE_INACTIVE		1
#define STATE_ACTIVE		2
#define TYPE_CASH			0
#define TYPE_CHEQUE			1
#define TYPE_TRANSFER		2
#define TYPE_DEPOSIT		0
#define TYPE_WITHDRAWAL 	1
#define TYPE_PASSPOR		0
#define TYPE_ID 			1
#define TYPE_DRIVING		2

/*
 * ȫ�ֱ���
 */
#ifdef GLOBAL_VARIABLES_HERE	// ��GLOBAL_VARIABLES_HERE define����������������ط�ֻ������
const char *customer_state[] = {"blocked", "working"};					// �ͻ�״̬
const char *customer_type[] = {"passport", "ID", "Driving license"};	// �ͻ��Ǽ�֤������
const char *account_state[] = {"blocked", "inactive", "active"};		// �˻�״̬
const char *access_type[] = {"cash", "cheque", "transfer"};				// ��������
const char *record_type[] = {"deposit", "withdrawal"};					// ��¼���ͣ���ȡ�
#else
extern char *customer_state[];
extern char *customer_type[];
extern char *account_state[];
extern char *access_type[];
extern char *record_type[];
#endif

/*
 * �Զ��岼������
 */
typedef enum{
	TRUE=1,
	FALSE=0
}BOOL;

/*
 * �������ͣ���������ʱʹ�ã�
 */
typedef enum{
	LIST_LOAN,
	LIST_RECORD,
	LIST_TRANSFER,
	LIST_ACCOUNT,
	LIST_CUSTOMER,
	LIST_CUSTOMER_HEAD
}LIST_TYPE;

/*
 * ת����Ϣ�ṹ��
 */
typedef struct{
	u64 from_account;
	u64 to_account;
	double amount;
	u16 set_date;
	time_t start_date;
	time_t end_date;
}TRANSFER_INFO;

/*
 * ת�˽ṹ��
 */
typedef struct transfer_node{
	TRANSFER_INFO info;
	struct transfer_node *next;
}TRANSFER_NODE, *PTRANSFER_NODE;

/*
 * ������Ϣ�ṹ��
 */
typedef struct{
	u64 account_id;
	u32 len_day;
	double amounts;
	float interests;
	time_t start_date;
	time_t end_date;
}LOAN_INFO;

/*
 * ����ṹ��
 */
typedef struct loan_node{
	LOAN_INFO info;
	struct loan_node *next;
}LOAN_NODE, *PLOAN_NODE;

/*
 * ��¼��Ϣ�ṹ��
 */
typedef struct{
	u64 account_id;
	u16 type;
	time_t date;
	double sum;
	u16 type_access;
}RECORD_INFO;

/*
 * ��¼�ṹ��
 */
typedef struct record_node{
	RECORD_INFO info;
	struct record_node *next;
}RECORD_NODE, *PRECORD_NODE;

/*
 * �˻���Ϣ�ṹ��
 */
typedef struct{
	u64 customer_id;	
	u64 id;
	u16 state;
	double balance;
	u32 loans_num;
}ACCOUNT_INFO;

/*
 * �˻��ṹ��
 */
typedef struct account_node{
	ACCOUNT_INFO info;
	PLOAN_NODE loans;
	PRECORD_NODE records;
	PTRANSFER_NODE transfers;
	struct account_node *next;	
}ACCOUNT_NODE, *PACCOUNT_NODE;

/*
 * �ͻ���Ϣ�ṹ��
 */
typedef struct{
	u64 id;
	u16 state;
	u16 type;
	char name[NAME_SIZE];
	char address[ADDRESS_SIZE];
	char phone[PHONR_SIZE];
	u32 accounts_num;
}CUSTOMER_INFO;

/*
 * �ͻ��ṹ��
 */
typedef struct customer_node{
	CUSTOMER_INFO info;
	PACCOUNT_NODE accounts;
	struct customer_node *next;
}CUSTOMER_NODE, *PCUSTOMER_NODE;

/*
 * �ͻ�ͷ���ṹ�壨��¼һЩͳ����Ϣ��
 */
typedef struct customer_head{
	u32 customers_num;
	u32 accounts_num;
	double balance;
	double loan_amounts;
	u32 loans_num;
	PCUSTOMER_NODE customers;
}CUSTOMER_HEAD, *PCUSTOMER_HEAD;


#endif

