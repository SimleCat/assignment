#include "view.h"

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

PACCOUNT_NODE view_getAccountByID(PCUSTOMER_HEAD head){
	u64 id;
	PACCOUNT_NODE account = NULL;
	while (1){
		printf(">> ");
		scanf("%lld", &id);
		fflush(stdin);
		if (id == 0){
			return NULL;
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
	return account;
}

PCUSTOMER_NODE view_getCustomerByID(PCUSTOMER_HEAD head){
	u64 id = 0;
	PCUSTOMER_NODE customer = NULL;
	while (1){
		printf(">> ");
		scanf("%lld", &id);
		fflush(stdin);
		if (id == 0){
			return NULL;
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
	return customer;
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
	printf("\n\tModify customer\n");
	printf("Please enter the customer id(Exit:equal zero).\n");
	customer = view_getCustomerByID(head);
	if (NULL == customer){
		return;
	}
	printf("1 Add a new account\n");
	printf("2 Modify account\n");
	printf("3 Delete account\n");
	printf("0 Back\n");
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
	PACCOUNT_NODE account = view_getAccountByID(head);
	if (NULL == account){
		return;
	}
	if (STATE_BLOCKED == account->info.state){
		printf("The account is blocked.\n");
		return;
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
			PRECORD_NODE record = (PRECORD_NODE)Create_List(LIST_RECORD);
			record->info.account_id = account->info.id;
			record->info.date = time(0);
			record->info.sum = amount;
			record->info.type = TYPE_DEPOSIT;
			record->info.type_access = TYPE_CASH;
			InsertFromHead_Record(account, record);
			printf("Deposit sucess.\n");
			break;
		}
	}
	// printf("Deposit sucess.\n");
}

void view_withdrawals(PCUSTOMER_HEAD head){
	printf("\n\tWithdrawals\n");
	printf("Please enter the account id(Exit:equal zero).\n");
	PACCOUNT_NODE account = view_getAccountByID(head);
	if (NULL == account){
		return;
	}
	if (STATE_BLOCKED == account->info.state){
		printf("The account is blocked.\n");
		return;
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
			PRECORD_NODE record = (PRECORD_NODE)Create_List(LIST_RECORD);
			record->info.account_id = account->info.id;
			record->info.date = time(0);
			record->info.sum = amount;
			record->info.type = TYPE_WITHDRAWAL;
			record->info.type_access = TYPE_CASH;
			InsertFromHead_Record(account, record);
			printf("Withdrawal sucess.\n");
			break;
		}
	}
}

void view_loan(PCUSTOMER_HEAD head){
	printf("\n\tLoan\n");
	printf("Please enter the account id(Exit:equal zero).\n");
	PACCOUNT_NODE account = view_getAccountByID(head);
	if (NULL == account){
		return;
	}
	if (STATE_ACTIVE != account->info.state){
		printf("The account is not active.\n");
		return;
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
			printf("The loan amount is not greater than %lld\n", MAX_AMOUNT_OF_LOAN);
		}
		else{
			loan->info.amounts = amount;
			break;
		}
	}
	u32 len_day = 0;
	printf("Please enter the loan time(days).\n");
	while (1){
		printf(">> ");
		scanf("%u", &len_day);
		fflush(stdin);
		if (len_day > MAX_LOAN_TIME){
			printf("Loan time length should not exceed %d days.\n", len_day);
		}
		else{
			loan->info.len_day = len_day;
			break;
		}
	}
	float interests = 0;
	printf("Please enter the interests.\n");
	while (1){
		printf(">> ");
		scanf("%f", &interests);
		fflush(stdin);
		if (interests <= 0){
			printf("The interest cannot be less than zero.\n");
		}
		else if (interests > MAX_INTERESTS){
			printf("The interest is not greater than %.4f\n", MAX_INTERESTS);
		}
		else{
			loan->info.interests = interests;
			break;
		}
	}
	loan->info.start_date = time(0);
	loan->info.end_date = loan->info.start_date + len_day * 24 * 60 * 60;
	InsertFromHead_Loan(head, account, loan);
	printf("Loan sucess.\n");
	print_loan(loan, TRUE);
}
//typedef struct{
//	u64 from_account;
//	u64 to_account;
//	u16 set_date;
//	time_t start_date;
//	time_t end_date;
//}TRANSFER_INFO;
void view_transfer(PCUSTOMER_HEAD head){
	printf("\n\tTransfer\n");
	PACCOUNT_NODE from_account = NULL;
	PACCOUNT_NODE to_account = NULL;
	double amount = 0;
	u16 set_date = 0;

	printf("Please enter the from_account id(Exit:equal zero).\n");
	from_account = view_getAccountByID(head);
	if (NULL == from_account){
		return;
	}
	if (STATE_BLOCKED == from_account->info.state){
		printf("The account is blocked.\n");
		return;
	}
	printf("Please enter the to_account id(Exit:equal zero).\n");
	to_account = view_getAccountByID(head);
	if (NULL == to_account){
		return;
	}
	if (STATE_BLOCKED == to_account->info.state){
		printf("The account is blocked.\n");
		return;
	}
	if (from_account->info.id == to_account->info.id){
		printf("Account cannot be the same.\n");
		return;
	}
	printf("Please enter the amount of transfer.\n");
	while (1){
		printf(">> ");
		scanf("%lf", &amount);
		fflush(stdin);
		if (amount < 0){
			printf("Amount not less than zero.\n");
		}
		else if (amount > MAX_AMOUNT_OF_TRANSFER){
			printf("The loan amount is not greater than %lld", MAX_AMOUNT_OF_TRANSFER);
		}
		else{
			break;
		}
	}
	printf("Please enter the setting date(1-30).\n");
	set_date = select_num(1, 30);
	time_t cur_date;
	time(&cur_date);
	struct tm *pCurTm = gmtime(&cur_date);
	struct tm tm_start;
	memset(&tm_start, 0, sizeof(tm_start));
	struct tm tm_end;
	memset(&tm_end, 0, sizeof(tm_end));
	time_t start_date = 0;
	time_t end_date = 0;

	printf("Please enter the starting date(year, month, day).\n");
	while (1){
		printf(">> ");
		int ret = scanf("%u, %u, %u", &(tm_start.tm_year), &(tm_start.tm_mon), &(tm_start.tm_mday));
		fflush(stdin);
		if (ret != 3){
			printf("Input is error.\n");
			continue;
		}
		if (tm_start.tm_year < pCurTm->tm_year + 1900){
			printf("Year can not less than %u\n", pCurTm->tm_year + 1900);
		}
		else if (tm_start.tm_mon < 1 || tm_start.tm_mon > 12){
			printf("Month must between 1 to 12\n");
		}
		else if (tm_start.tm_mday < 1 || tm_start.tm_mday > 30){
			printf("Day must between 1 to 30\n");
		}
		else{
			tm_start.tm_year -= 1900;
			tm_start.tm_mon -= 1;
			tm_start.tm_mday += 1;
			start_date = mktime(&tm_start);
			if (start_date < cur_date){
				printf("Start date cannot be less than the current date.\n");
			}
			else{
				break;
			}
		}
	}

	printf("Please enter the ending date(year, month, day).\n");
	while (1){
		printf(">> ");
		int ret = scanf("%u, %u, %u", &(tm_end.tm_year), &(tm_end.tm_mon), &(tm_end.tm_mday));
		fflush(stdin);
		if (ret != 3){
			printf("Input is error.\n");
			continue;
		}
		if (tm_end.tm_year < tm_start.tm_year + 1900){
			printf("Year can not less than starting date(%u)\n", tm_start.tm_year + 1900);
		}
		else if (tm_end.tm_mon < 1 || tm_end.tm_mon > 12){
			printf("Month must between 1 to 12\n");
		}
		else if (tm_end.tm_mday < 1 || tm_end.tm_mday > 30){
			printf("Day must between 1 to 30\n");
		}
		else{
			tm_end.tm_year -= 1900;
			tm_end.tm_mon -= 1;
			tm_end.tm_mday += 1;
			end_date = mktime(&tm_end);
			if (end_date < start_date){
				printf("End date cannot be less than the start date.\n");
			}
			else{
				break;
			}
		}
	}
	PTRANSFER_NODE transfer = (PTRANSFER_NODE)Create_List(LIST_TRANSFER);
	transfer->info.from_account = from_account->info.id;
	transfer->info.to_account = to_account->info.id;
	transfer->info.amount = amount;
	transfer->info.set_date = set_date;
	transfer->info.start_date = start_date;
	transfer->info.end_date = end_date;
	InsertFromHead_Transfer(from_account, transfer);
	printf("Transfer setting sucess.\n");
}

void view_manageInfo_findCustomer(PCUSTOMER_HEAD head){
	printf("\n\tFind customer\n");
	printf("Please enter the customer id(Exit:equal zero).\n");
	PCUSTOMER_NODE customer = view_getCustomerByID(head);
	if (NULL == customer){
		return;
	}
	print_customer(customer);
}

void view_manageInfo_findAccount(PCUSTOMER_HEAD head){
	printf("\n\tFind account\n");
	printf("Please enter the account id(Exit:equal zero).\n");
	PACCOUNT_NODE account = view_getAccountByID(head);
	if (NULL == account){
		return;
	}
	print_account(account);
}

void view_manageInfo_all(PCUSTOMER_HEAD head){
	print_customers(head->customers);
}

void view_manageInfo_statistis(PCUSTOMER_HEAD head){
	printf("\n\tTo view statistics\n");
	printf("Number of customers: %u\n", head->customers_num);
	printf("Number of accounts: %u\n", head->accounts_num);
	printf("Number of loans: %u\n", head->loans_num);
	printf("Account balances all: %.2lf, average: %.2lf\n", head->balance, head->balance / head->accounts_num);
	printf("Loan amounts all: %.2lf, average: %.2lf\n", head->loan_amounts, head->loan_amounts / head->loans_num);
}

void view_manageInfo(PCUSTOMER_HEAD head){
	while (1){
		printf("\n\tManage customer information\n");
		printf("1 Find customer\n");
		printf("2 Find account\n");
		printf("3 Check all the information\n");
		printf("4 To view statistics\n");
		printf("0 Back\n");
		int select = select_num(0, 4);
		switch (select){
		case 0:
			return;
		case 1:
			view_manageInfo_findCustomer(head);
			break;
		case 2:
			view_manageInfo_findAccount(head);
			break;
		case 3:
			view_manageInfo_all(head);
			break;
		case 4:
			view_manageInfo_statistis(head);
			break;
		default:
			break;
		}
	}


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
		case 5:
			view_loan(head);
			break;
		case 6:
			view_transfer(head);
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



