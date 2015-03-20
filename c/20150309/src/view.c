#include <stdio.h>
#include "common.h"
#include "view.h"
#include "list.h"
#include "bank.h"

int select_num(int min, int max){
	int num = -1;
	while (1){
		printf("select: ");
		int ret = scanf("%d", &num);
		fflush(stdin);
		if (ret != 1 || num<min || num >max){
			printf("Pelase enter a number between %d and %d\n\n", min, max);
		}
		else{
			break;
		}
	}
	return num;
}

void view_createCustomer(PCUSTOMER_HEAD head){
	PCUSTOMER_NODE customer = (PCUSTOMER_NODE)Create_List(LIST_CUSTOMER);
	printf("\n\tCreate a new customer\n");
	printf("Type of identification:\n");
	for (int i = 0; i < 3; i++){
		printf("%d %s\n", i+1, customer_type[i]);
	}
	customer->info.type = select_num(1, 3)-1;
	printf("Name: ");
	scanf("%s", customer->info.name);
	printf("Address: ");
	scanf("%s", customer->info.address);
	printf("Phone number: ");
	scanf("%s", customer->info.phone);
	printf("State of the customer:\n");
	for (int i = 0; i < 2; i++){
		printf("%d %s\n", i + 1, customer_state[i]);
	}
	customer->info.state = select_num(1, 2)-1;
	customer->info.id = create_customerID(head->customers);
	InsertFromHead_Customer(head, customer);
	print_customer(customer);
}

void view_modifyCustomer_addAccount(PCUSTOMER_HEAD head, PCUSTOMER_NODE customer){
	printf("\n\tAdd a new account\n");
	PACCOUNT_NODE account = (PACCOUNT_NODE)Create_List(LIST_ACCOUNT);
	account->info.customer_id = customer->info.id;
	account->info.id = create_accountID(customer, customer->info.id);
	printf("State:\n");
	for (int i = 0; i < 3; i++){
		printf("%d %s\n", i + 1, account_state[i]);
	}
	account->info.state = select_num(1, 3)-1;
	InsertFromHead_Account(head, customer, account);
	print_account(account);
}

void view_modifyCustomer_modifyAccount(PCUSTOMER_HEAD head, PCUSTOMER_NODE customer){
	PACCOUNT_NODE account = NULL;
	printf("\n\tModify an account\n");
	printf("Please enter the account id after two(Exit:less than zero).\n");
	u64 account_id = 0;
	u32 tmp = 0;
	while (1){
		printf(">> ");
		scanf("%u", &tmp);
		fflush(stdin);
		if (tmp < 0){
			return;
		}
		if (tmp > 0 && tmp < 99){
			account_id = customer->info.id + tmp;
			account = FindById_Account(head->customers, account_id);
			if (account != NULL){
				break;
			}
			else{
				printf("Not Found!\n");
			}
		}
		else{
			printf("Please enter an integer with 2 digits.\n");
		}
	}
	printf("The current state of %s\n", account_state[account->info.state]);
	printf("Do you want to change:\n");
	for (int i = 0; i < 3; i++){
		printf("%d %s\n", i + 1, account_state[i]);
	}
	account->info.state = select_num(1, 3)-1;
}

void view_modifyCustomer_deleteAccount(PCUSTOMER_HEAD head, PCUSTOMER_NODE customer){
	PACCOUNT_NODE account = NULL;
	printf("\n\tDelete an account\n");
	printf("Please enter the account id after two(Exit:less than zero).\n");
	u64 account_id = 0;
	u32 tmp = 0;
	double balance;
	while (1){
		printf(">> ");
		scanf("%u", &tmp);
		fflush(stdin);
		if (tmp < 0){
			return;
		}
		if (tmp > 0 && tmp < 99){
			account_id = customer->info.id + tmp;
			account = FindById_Account(head->customers, account_id);
			if (account != NULL){
				balance = account->info.balance;
				if (DelById_Account(head->customers, account_id)){
					printf("Delete sucess.\n");
					break;
				}
				printf("Delete failure.\n");
			}
			else{
				printf("Not Found!\n");
			}
		}
		else{
			printf("Please enter an integer with 2 digits.\n");
		}
	}
	head->accounts_num -= 1;
	head->balance -= balance;
}

void view_modifyCustomer(PCUSTOMER_HEAD head){
	PCUSTOMER_NODE customer = NULL;
	u64 id = 0;
	printf("\n\tModify customer\n");
	printf("Please enter the customer id(Exit:equal zero).\n");
	while (1){
		printf(">> ");
		scanf("%lld", &id);
		fflush(stdin);
		if (id == 0){
			return;
		}
		if (id > 10000000000 && id < 99999999999){
			customer = FindById_Customer(head->customers, id);
			if (customer != NULL){
				break;
			}
			else{
				printf("Not Found!\n");
			}
		}
		else{
			printf("Please enter an integer with 11 digits.\n");
		}
	}
	printf("1 Add a new account\n");
	printf("2 Modify account\n");
	printf("3 Delete account\n");
	printf("0 Exit\n");
	int select = select_num(0, 3);
	switch (select){
	case 0:
		return;
	case 1:
		view_modifyCustomer_addAccount(head, customer);
		break;
	case 2:
		view_modifyCustomer_modifyAccount(head, customer);
		break;
	case 3:
		view_modifyCustomer_deleteAccount(head, customer);
		break;
	default:
		break;
	}
}

void view_deposit(PCUSTOMER_HEAD head){
	printf("\n\tDeposit\n");
	printf("Please enter the account id(Exit:equal zero).\n");
	u64 id;
	PACCOUNT_NODE account = NULL;
	while (1){
		printf(">> ");
		scanf("%lld", &id);
		fflush(stdin);
		if (id == 0){
			return;
		}
		if (id > 10000000000 && id < 99999999999){
			account = FindById_Account(head->customers, id);
			if (account != NULL){
				break;
			}
			else{
				printf("Not Found!\n");
			}
		}
		else{
			printf("Please enter an integer with 11 digits.\n");
		}
	}
	double amount = 0;
	printf("Please enter the amount of deposit.\n");
	while (1){
		printf(">> ");
		scanf("%lf", &amount);
		fflush(stdin);
		if (amount < 0){
			printf("Amount not less than zero.\n");
		}
		else if(amount > MAX_AMOUNT_OF_DEPOSIT){
			printf("The deposit amount is not greater than %lld", MAX_AMOUNT_OF_DEPOSIT);
		}
		else{
			account->info.balance += amount;
			head->balance += amount;
			printf("Deposit sucess.\n");
			break;
		}
	}
	// printf("Deposit sucess.\n");
}

void view_withdrawals(PCUSTOMER_HEAD head){
	printf("\n\tWithdrawals\n");
	printf("Please enter the account id(Exit:equal zero).\n");
	u64 id;
	PACCOUNT_NODE account = NULL;
	while (1){
		printf(">> ");
		scanf("%lld", &id);
		fflush(stdin);
		if (id == 0){
			return;
		}
		if (id > 10000000000 && id < 99999999999){
			account = FindById_Account(head->customers, id);
			if (account != NULL){
				break;
			}
			else{
				printf("Not Found!\n");
			}
		}
		else{
			printf("Please enter an integer with 11 digits.\n");
		}
	}
	if (account->info.balance <= 0){
		printf("Account balance is zero.\n");
		return;
	}
	double amount = 0;
	printf("Please enter the amount of withdrawals.\n");
	while (1){
		printf(">> ");
		scanf("%lf", &amount);
		fflush(stdin);
		if (amount < 0){
			printf("Amount not less than zero.\n");
		}
		else if (amount > MAX_AMOUNT_OF_DEPOSIT){
			printf("The withdrawal amount is not greater than %lld", MAX_AMOUNT_OF_DEPOSIT);
		}
		else{
			if (amount > account->info.balance){
				printf("Withdrawal amount is greater than the account balance.\n");
				printf("The account balance: %.2lf\n", account->info.balance);
				continue;
			}
			account->info.balance -= amount;
			head->balance -= amount;
			printf("Withdrawal sucess.\n");
			break;
		}
	}
}
typedef struct{
	u64 account_id;
	u32 len_day;
	double amounts;
	float interests;
	time_t start_date;
	time_t end_date;
}LOAN_INFO;
void view_loan(PCUSTOMER_HEAD head){
	printf("\n\Loan\n");
	printf("Please enter the account id(Exit:equal zero).\n");
	u64 id;
	PACCOUNT_NODE account = NULL;
	while (1){
		printf(">> ");
		scanf("%lld", &id);
		fflush(stdin);
		if (id == 0){
			return;
		}
		if (id > 10000000000 && id < 99999999999){
			account = FindById_Account(head->customers, id);
			if (account != NULL){
				break;
			}
			else{
				printf("Not Found!\n");
			}
		}
		else{
			printf("Please enter an integer with 11 digits.\n");
		}
	}
	double amount = 0;
	PLOAN_NODE loan = (PLOAN_NODE)Create_List(LIST_LOAN);
	printf("Please enter the amount of loan.\n");
	while (1){
		printf(">> ");
		scanf("%lf", &amount);
		fflush(stdin);
		if (amount < 0){
			printf("Amount not less than zero.\n");
		}
		else if (amount > MAX_AMOUNT_OF_LOAN){
			printf("The loan amount is not greater than %lld", MAX_AMOUNT_OF_LOAN);
		}
		else{
			loan->info.amounts = amount;
			printf("Loan sucess.\n");
			break;
		}
	}
	u32 len_day = 0;
	printf("Please enter the loan time.\n");
	while (1){
		printf(">> ");
		scanf("%u", &len_day);
		fflush(stdin);
		if (len_day > MAX_LOAN_TIME){
			printf("Loan time length should not exceed %d days.\n", len_day);
			continue;
		}
	}
}

void view_transfer(){
}

void view_manageInfo(PCUSTOMER_HEAD head){
	print_customers(head->customers);
}

void view_main(PCUSTOMER_HEAD head){
	while (1){
		printf("\n\tThe main menu\n");
		printf("1 Create a new customer\n");
		printf("2 Modify the customer\n");
		printf("3 Deposit\n");
		printf("4 Withdrawals\n");
		printf("5 Loan\n");
		printf("6 Transfer\n");
		printf("7 Manage customer information\n");
		printf("0 Exit\n");
		int select = select_num(0, 7);
		// printf("select: %d\n", select);
		switch (select){
		case 0: 
			return;
		case 1:
			view_createCustomer(head);
			break;
		case 2:
			view_modifyCustomer(head);
			break;
		case 3:
			view_deposit(head);
			break;
		case 4:
			view_withdrawals(head);
			break;
		case 7:
			view_manageInfo(head);
			break;
		default:
			break;
		}
		// printf("view_main \n");
	}

}



