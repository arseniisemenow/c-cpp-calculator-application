#include "../headers/s21_quick_sort.h"

void swapTransactions(TransactionDateType *a, TransactionDateType *b) {
  TransactionDateType tempDate = *a;
  *a = *b;
  *b = tempDate;
}

int partitionDates(TransactionDateType *arr, int lowestIndex,
                   int highestIndex) {
  TransactionDateType pivot = arr[highestIndex];

  int i = (lowestIndex - 1);

  for (int j = lowestIndex; j <= highestIndex - 1; j++) {
    time_t timePivot = mktime(&pivot.date);
    time_t timeElement = mktime(&arr[j].date);

    if (timeElement < timePivot) {
      i++;
      swapTransactions(&arr[i], &arr[j]);
    }
  }

  swapTransactions(&arr[i + 1], &arr[highestIndex]);

  return (i + 1);
}

void quickSortDates(TransactionDateType *arr, int lowestIndex,
                    int highestIndex) {
  if (lowestIndex < highestIndex) {
    int pi = partitionDates(arr, lowestIndex, highestIndex);

    quickSortDates(arr, lowestIndex, pi - 1);
    quickSortDates(arr, pi + 1, highestIndex);
  }
}
