#include "../headers/s21_transaction_list.h"

int initTransactionList(TransactionList *transactionList) {
  int errorCode = DepositErrorCode_none;

  transactionList->transactionArray =
      calloc(S21_INIT_LIST_COUNT, sizeof(TransactionDateType));
  transactionList->realCount = 0;
  transactionList->allocatedCount = 0;
  if (transactionList->transactionArray) {
    transactionList->allocatedCount = S21_INIT_LIST_COUNT;
  } else {
    errorCode = DepositErrorCode_memoryAllocationError;
  }

  return errorCode;
}

void destroyTransactionList(TransactionList *transactionList) {
  free(transactionList->transactionArray);
}

void initArray(TransactionList *transactionList,
               TransactionDateType *reservePatternArray) {
  for (int i = 0; i < S21_APPEND_LIST_COUNT; ++i) {
    int index = i + transactionList->allocatedCount;
    reservePatternArray[index].value = 0;
    initDate(&reservePatternArray[index].date);
  }
}

TransactionDateType *
reallocMemoryForTransactions(TransactionList *transactionList) {
  return realloc(transactionList->transactionArray,
                 (transactionList->allocatedCount + S21_APPEND_LIST_COUNT) *
                     sizeof(TransactionDateType));
}

int reallocTransactionList(TransactionList *transactionList) {
  int errorCode = DepositErrorCode_none;

  TransactionDateType *reservePatternArray = NULL;
  reservePatternArray = reallocMemoryForTransactions(transactionList);

  if (reservePatternArray) {
    initArray(transactionList, reservePatternArray);
    transactionList->transactionArray = reservePatternArray;
    transactionList->allocatedCount =
        transactionList->allocatedCount + S21_APPEND_LIST_COUNT;
  } else {
    errorCode = DepositErrorCode_memoryAllocationError;
  }

  return errorCode;
}

int pushTransactionList(TransactionList *transactionList,
                        TransactionDateType transaction,
                        TransactionType transactionType) {
  int errorCode = DepositErrorCode_none;

  if (transactionList->realCount >= transactionList->allocatedCount) {
    errorCode = reallocTransactionList(transactionList);
  }

  if (!errorCode) {
    transaction.transactionType = transactionType;
    transactionList->transactionArray[transactionList->realCount] = transaction;
    transactionList->realCount++;
  }

  return errorCode;
}
