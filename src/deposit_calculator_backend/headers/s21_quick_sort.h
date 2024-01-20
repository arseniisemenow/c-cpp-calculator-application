#ifndef S21_QUICK_SORT_H_
#define S21_QUICK_SORT_H_

#include "s21_deposit_structs.h"

void swapTransactions(TransactionDateType *a, TransactionDateType *b);

int partitionDates(TransactionDateType *arr, int lowestIndex, int highestIndex);

void quickSortDates(TransactionDateType *arr, int lowestIndex,
                    int highestIndex);

#endif // S21_QUICK_SORT_H_