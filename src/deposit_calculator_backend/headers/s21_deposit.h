#ifndef S21_DEPOSIT_H_
#define S21_DEPOSIT_H_

#include "../../common/headers/s21_aux_funcs.h"
#include "s21_deposit_api.h"
#include "s21_taxes.h"
#include "s21_transaction_list.h"
#include "s21_transactions.h"

int handlePaymentMatch(DepositConfig *config,
                       PaymentDateArrayType datesPayments, DateType currentDay,
                       int *pPaymentIndex, int dayIndex);

int handleAllTransactions(DepositConfig *depositConfig);

double getPayment(DateType lastDay, int dayIndex, DepositParameters *params);

#endif // S21_DEPOSIT_H_