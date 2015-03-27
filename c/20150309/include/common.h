#ifndef __COMMON_H__
#define __COMMON_H__

#include <time.h>

/*
 * 常量
 */
#define NAME_SIZE				50			// 名字存储所占字节数
#define ADDRESS_SIZE			100			// 地址存储所占字节数
#define PHONR_SIZE				20			// 电话存储所占字节数
#define MAX_ACCOUNT_NUM			99			// 一个客户最大账户数量
#define MAX_AMOUNT_OF_DEPOSIT	99999999	// 一次存款最大金额
#define MAX_AMOUNT_OF_LOAN		999999		// 一次贷款最大金额
#define MAX_LOAN_TIME			1095		// 贷款最大时长
#define MAX_INTERESTS			0.8			// 贷款最大利率
#define MAX_AMOUNT_OF_TRANSFER	99999999	// 一次转账最大金额

/*
 * 通用变量定义
 */
typedef unsigned long long	u64;
typedef long long			s64;
typedef unsigned long	 	u32;
typedef long				s32;
typedef unsigned short		u16;
typedef short				s16;

/*
 * 状态和类型的下标定义
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
 * 全局变量
 */
#ifdef GLOBAL_VARIABLES_HERE	// 在GLOBAL_VARIABLES_HERE define处定义变量，其他地方只声明。
const char *customer_state[] = {"blocked", "working"};					// 客户状态
const char *customer_type[] = {"passport", "ID", "Driving license"};	// 客户登记证件类型
const char *account_state[] = {"blocked", "inactive", "active"};		// 账户状态
const char *access_type[] = {"cash", "cheque", "transfer"};				// 交易类型
const char *record_type[] = {"deposit", "withdrawal"};					// 记录类型（存款、取款）
#else
extern char *customer_state[];
extern char *customer_type[];
extern char *account_state[];
extern char *access_type[];
extern char *record_type[];
#endif

/*
 * 自定义布尔变量
 */
typedef enum{
	TRUE=1,
	FALSE=0
}BOOL;

/*
 * 链表类型（创建链表时使用）
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
 * 转账信息结构体
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
 * 转账结构体
 */
typedef struct transfer_node{
	TRANSFER_INFO info;
	struct transfer_node *next;
}TRANSFER_NODE, *PTRANSFER_NODE;

/*
 * 贷款信息结构体
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
 * 贷款结构体
 */
typedef struct loan_node{
	LOAN_INFO info;
	struct loan_node *next;
}LOAN_NODE, *PLOAN_NODE;

/*
 * 记录信息结构体
 */
typedef struct{
	u64 account_id;
	u16 type;
	time_t date;
	double sum;
	u16 type_access;
}RECORD_INFO;

/*
 * 记录结构体
 */
typedef struct record_node{
	RECORD_INFO info;
	struct record_node *next;
}RECORD_NODE, *PRECORD_NODE;

/*
 * 账户信息结构体
 */
typedef struct{
	u64 customer_id;	
	u64 id;
	u16 state;
	double balance;
	u32 loans_num;
}ACCOUNT_INFO;

/*
 * 账户结构体
 */
typedef struct account_node{
	ACCOUNT_INFO info;
	PLOAN_NODE loans;
	PRECORD_NODE records;
	PTRANSFER_NODE transfers;
	struct account_node *next;	
}ACCOUNT_NODE, *PACCOUNT_NODE;

/*
 * 客户信息结构体
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
 * 客户结构体
 */
typedef struct customer_node{
	CUSTOMER_INFO info;
	PACCOUNT_NODE accounts;
	struct customer_node *next;
}CUSTOMER_NODE, *PCUSTOMER_NODE;

/*
 * 客户头结点结构体（记录一些统计信息）
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

