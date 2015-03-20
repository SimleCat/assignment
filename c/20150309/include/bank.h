#ifndef __BANK_H__
#define __BANK_H__

#include <stdlib.h>
#include <time.h>
#include "common.h"
#include "list.h"

u64 create_customerID(PCUSTOMER_NODE customers);
u64 create_accountID(PCUSTOMER_NODE customer, u64 customer_id);

#endif