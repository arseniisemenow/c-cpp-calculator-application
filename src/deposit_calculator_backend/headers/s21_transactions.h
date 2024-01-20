#ifndef S21_TRANSACTIONS_H_
#define S21_TRANSACTIONS_H_

#include "s21_deposit_structs.h"
#include "s21_quick_sort.h"
#include "s21_transaction_list.h"

#define S21_MIN_COEFFICIENT (0.0)
#define S21_MAX_COEFFICIENT (1.0)

#define S21_ONE_PAYMENT (1)

#define S21_INIT_VALUE_COEFFICIENT (1)

int makeAllTransactions(DepositParameters *params,
                        PaymentDateArrayType *datesPayments,
                        TransactionList *transactionList);

int makeArrayOfPayments(DepositParameters *params,
                        PaymentDateArrayType *dateArray);

int makeArrayOfTransactions(DepositParameters *params,
                            TransactionDateArray *dateArray,
                            TransactionData transactionData);

int summarizeTransactions(TransactionList *transactionList,
                          TransactionDateArray *dateArray,
                          TransactionType transactionType);

int getNumberOfRecordsInArrayOfPayments(DepositParameters *params);

int getNumberOfRecordsInTransactionsArray(DepositParameters *params,
                                          TransactionData transactionData);

int handleOnePaymentCase(DepositParameters *params,
                         PaymentDateArrayType *dateArray);

void handleCoefficientForLastPayment(DepositParameters *params,
                                     PaymentDateArrayType *dateArray);

#endif // S21_TRANSACTIONS_H_