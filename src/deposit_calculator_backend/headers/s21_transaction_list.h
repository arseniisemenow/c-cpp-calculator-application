#ifndef S21_TRANSACTION_LIST_H_
#define S21_TRANSACTION_LIST_H_

#include "s21_deposit_api.h"
#include "s21_deposit_structs.h"

#define S21_INIT_LIST_COUNT 10
#define S21_APPEND_LIST_COUNT 10

typedef struct {
  TransactionDateType *transactionArray;
  int realCount;
  int allocatedCount;
} TransactionList;

int initTransactionList(TransactionList *transactionList);

void destroyTransactionList(TransactionList *transactionList);

int reallocTransactionList(TransactionList *transactionList);

int pushTransactionList(TransactionList *transactionList,
                        TransactionDateType transaction,
                        TransactionType transactionType);

#endif // S21_TRANSACTION_LIST_H_