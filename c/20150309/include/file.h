#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <memory.h>
#include <memory.h>
#include "common.h"
#include "list.h"

#define FILE_CUSTOMER			"./data/customer.dat"
#define FILE_ACCOUNT			"./data/account.dat"
#define FILE_RECORD				"./data/record.dat"
#define FILE_LOAN				"./data/loan.dat"
#define FILE_TRANSFER			"./data/tarnsfer.dat"


BOOL WriteToFile(PCUSTOMER_HEAD head);
BOOL ReadFromFile(PCUSTOMER_HEAD head);


#endif